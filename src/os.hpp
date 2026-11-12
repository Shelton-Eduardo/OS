#ifndef OS_HPP_INCLUDED
#define OS_HPP_INCLUDED

#include <type_traits>
#include <windows.h>
#include <exception>
#include <cstdint>
#include <cstring>
#include <istream>
#include <ostream>
#include <new>

enum class Cursor : std::size_t{eof = static_cast<std::size_t>(-1)};
enum class ReadingState : std::uint8_t{FullRead = 1<<0,
                                    PartialRead = 1<<2,
                                          Fatal = 1<<3};

namespace Exceptions{
    class FileStream : public std::exception{
        private:
            const char* msg;
        public:
            FileStream(const char* m = "EXCEPTION IN FILE STREAM OCCOURED") : msg(m){}
            const char* what() const noexcept{
                return msg;
            }
    };

    class StreamBusy : public FileStream{
        public:
            StreamBusy(const char* m = "STREAM IS BUSY") : FileStream(m){}
    };
}

namespace FileStream{
    class InputFileStream{
        protected:
            static constexpr std::size_t BUFFER_PAGE{8192}; // 8KB buffer stream
        private:
            HANDLE file_handle;
            unsigned char* buffer_array;
            unsigned char* current_cursor;
            unsigned char* end;
            std::size_t offset;
            bool done = false;

            [[nodiscard]] bool refil();
        
        public:
        InputFileStream();
        explicit InputFileStream(const wchar_t* file);
        ~InputFileStream() noexcept;

        InputFileStream(const InputFileStream&)                = delete;
        InputFileStream(InputFileStream&&) noexcept            = delete;
        InputFileStream& operator=(const InputFileStream&)     = delete;
        InputFileStream& operator=(InputFileStream&&) noexcept = delete;

        // Essential Functions
        void open(const wchar_t* file);
        bool is_open() noexcept;
        void close() noexcept;

        // reading functions
        ReadingState read(unsigned char* container, std::size_t bytes) noexcept;

        // Cursor Functions
        Cursor tellp() noexcept;
        bool seekp(Cursor idx) noexcept;
    };

} // FileStream namespcae

namespace PathSystem{

}// PathSystem namespace



#endif
