#include "os.hpp"
#include <iostream>

FileStream::InputFileStream::InputFileStream(){
    file_handle = INVALID_HANDLE_VALUE;
    offset = 0;
    // Creating the buffer
    buffer_array = current_cursor = end = static_cast<unsigned char*>(::operator new(BUFFER_PAGE));
}

FileStream::InputFileStream::InputFileStream(const wchar_t* file){
    file_handle = CreateFileW(
                    file,
                    GENERIC_READ,
                    FILE_SHARE_READ,
                    NULL,
                    OPEN_EXISTING,
                    FILE_ATTRIBUTE_NORMAL | FILE_ATTRIBUTE_READONLY,
                    NULL);
    if(file_handle == INVALID_HANDLE_VALUE) return;
    buffer_array = current_cursor = end = static_cast<unsigned char*>(::operator new(BUFFER_PAGE));
    offset = 0;
}

FileStream::InputFileStream::~InputFileStream() noexcept{
    ::operator delete(buffer_array);
    if(file_handle != INVALID_HANDLE_VALUE) CloseHandle(file_handle);
}

// private
bool FileStream::InputFileStream::refil(){
    offset += static_cast<std::size_t>(end-buffer_array);
    DWORD bytes_read = 0;
    BOOL state = ReadFile(
                file_handle,
                buffer_array,
                static_cast<DWORD>(BUFFER_PAGE),
                &bytes_read,
                NULL
    );
    current_cursor = buffer_array;
    end = current_cursor + (state ? bytes_read : 0);
    return state && bytes_read>0;
}

// Essential Functons
void FileStream::InputFileStream::open(const wchar_t* file){
    if(file_handle != INVALID_HANDLE_VALUE) throw Exceptions::FileStream{};
    file_handle = CreateFileW(
                    file,
                    GENERIC_READ,
                    FILE_SHARE_READ,
                    NULL,
                    OPEN_EXISTING,
                    FILE_ATTRIBUTE_NORMAL | FILE_ATTRIBUTE_READONLY,
                    NULL);
    if(file_handle == INVALID_HANDLE_VALUE)throw Exceptions::FileStream{"File either does not exist or higher level of permission required"};
    offset = 0;
    current_cursor = end = buffer_array;
}

bool FileStream::InputFileStream::is_open() noexcept{
    return file_handle != INVALID_HANDLE_VALUE;
}

void FileStream::InputFileStream::close() noexcept{
    if(file_handle!=INVALID_HANDLE_VALUE) CloseHandle(file_handle);
}

// Reading Functions
ReadingState FileStream::InputFileStream::read(unsigned char* container, std::size_t bytes) noexcept{
    std::size_t copied{};
    for(; copied < bytes; ++copied){
        if(current_cursor == end) if(!refil()) break;
        container[copied] = *(current_cursor+copied); 
    }
    return ( copied == bytes ? ReadingState::FullRead : (!done && copied < bytes ? ReadingState::PartialRead : ReadingState::Fatal));
}

Cursor FileStream::InputFileStream::tellp() noexcept{
    if(!is_open()) return Cursor::eof;
    return static_cast<Cursor>(offset+(current_cursor-buffer_array));
}

bool FileStream::InputFileStream::seekp(Cursor idx) noexcept{
    if (idx >= static_cast<Cursor>(offset) && idx <= static_cast<Cursor>(offset+(current_cursor-buffer_array))){
        current_cursor = buffer_array + (static_cast<std::size_t>(idx)-offset);
        return true;
    }return false;
}

using namespace std;
int main(){
    cout << "Testing it" << endl;
    FileStream::InputFileStream file(L"Baka.bin");
    cout << file.is_open() << endl;
    int a;
    file.read(reinterpret_cast<unsigned char*>(&a), sizeof(a));
    cout << a;

    return 0;
}
