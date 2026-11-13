# SuDOs
**System-level utilities for Directories & Operating storage**

**SuDOs** is a lightweight, low-level C++ library built from scratch for direct file I/O and filesystem navigation. It gives developers fine-grained control over how data is read from and written to disk, alongside essential cross-platform directory traversal and file management utilities.

## Supported Platforms & Testing Grounds

SuDOs is actively developed and tested on both **Windows** and **Linux**:

| Platform | Underlying API / Mechanism | Direct Disk I/O Support | Status |
| :--- | :--- | :--- | :--- |
| **Linux** | POSIX (`open`, `read`, `write`, `dirent.h`) | `O_DIRECT` | Tested |
| **Windows** | Win32 API (`CreateFile`, `ReadFile`, `WriteFile`) | `FILE_FLAG_NO_BUFFERING` | Tested |

## Key Features

### Low-Level File I/O
* **Kernel-Buffered I/O:** Standard OS-cached file reading and writing for optimized general throughput.
* **Direct Disk I/O:** Bypass the OS page/kernel cache for unbuffered, direct-to-disk read and write operations.

### File Manipulation
* **Copy & Move:** Efficient file duplication and relocation across directories.
* **Rename:** Fast, atomic file and directory renaming.

### Directory Navigation
* **List & Walk:** Enumerate directory contents (`listdir`) and recursively traverse directory trees (`walk`).
* **Working Directory Control:** Query and update the current working directory (`getcwd`, `chdir`).

## Getting Started

### Prerequisites
* A C++ compiler supporting C++17 or later (`g++`, `clang++`, or `MSVC`)
* Windows SDK (for Windows builds) or standard POSIX/glibc headers (for Linux builds)

### Compilation & Usage
1. Clone the repository:
   ```bash
   git clone https://github.com
   cd SuDOs
   ```

2. Compile on **Linux**:
   ```bash
   g++ -std=c++17 main.cpp -o sudos_app
   ```

3. Compile on **Windows** (MinGW / MSVC):
   ```bash
   g++ -std=c++17 main.cpp -o sudos_app.exe
   ```

## Author
* **Shelton Eduardo**

## License
This project is open-source and available under the [MIT License](LICENSE).
