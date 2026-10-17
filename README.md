# Library Management System (C++17)

A modular, menu-driven console application using **only C++17 and the C++ Standard Library**. Records are persisted locally in plain-text files using only the C++ Standard Library. No SQL, database, API, or third-party library is used.

## Features
- Add, list, search (title/author/ISBN), update, and delete books
- Register, list, and remove members
- Issue and return books, with per-copy availability tracking
- Track active, returned, and overdue loans
- Calculate overdue fines at **Rs 5 per day** after a **14-day loan period**
- Library statistics and input/error validation
- Automatic file persistence in `books.txt`, `members.txt`, and `loans.txt`
- Prevent deleting books or members that have active loans; prevent duplicate IDs/ISBNs

## Requirements
- CMake 3.16 or newer
- A C++17 compiler (GCC, Clang, or MSVC / Visual Studio Build Tools)
- VS Code is optional; install a C++ extension and CMake Tools extension for a convenient workflow.

## Build and run (Windows PowerShell)
Open PowerShell in this project directory. Ensure CMake and a compiler are on PATH. For MSVC, launch a Developer PowerShell or configure Visual Studio Build Tools first.

```powershell
cmake -S . -B build
cmake --build build --config Release
ctest --test-dir build -C Release --output-on-failure
.\build\Release\library_management.exe
```

If using MinGW GCC, the executable is commonly at `build\library_management.exe` instead:

```powershell
cmake -S . -B build -G "MinGW Makefiles"
cmake --build build
ctest --test-dir build --output-on-failure
.\build\library_management.exe
```

## Build and run (Linux/macOS)
```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
ctest --test-dir build --output-on-failure
./build/library_management
```

## Quick usage
Choose a menu number, enter the requested values, and use the generated Loan ID when returning a book. Book IDs and member IDs are supplied by the operator and must be unique within their type. Search is case-insensitive. Dates use the system clock. The app has no login/authentication. Data files are read and written relative to the working directory used to launch the executable.

## Project layout
```text
include/       Public class declarations
src/           Implementations and application entry point
tests/         Automated core-feature tests
CMakeLists.txt Build configuration
OOP_CONCEPTS.md OOP feature-to-code mapping
```

## Notes / limitations
- Persistent records are stored in plain-text files in the current working directory. Keep the three files together and do not edit them while the application is running.
- The Admin class demonstrates inheritance/polymorphism, while this console version does not include a login or role-based authorization workflow.
- Fines use calendar-independent 24-hour periods and are rounded up to whole overdue days.
