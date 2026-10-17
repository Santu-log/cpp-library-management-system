# 📚 Library Management System

A menu-driven **Library Management System built with C++17** that demonstrates object-oriented programming, file handling, STL containers, exception handling, and modular software design.

Manage books, members, and borrowing records through a simple console interface, with file-based persistence to retain data across application restarts.

## ✨ Features

- **Book Management:** Add, search, display, update, and delete books.
- **Member Management:** Register and manage library members.
- **Loan Management:** Issue and return books while tracking active loans.
- **Availability Tracking:** Maintain total and available book copies.
- **Overdue Fines:** Calculate fines for overdue books.
- **Persistent Storage:** Store books, members, and loans in text files.
- **Input Validation:** Handle invalid input and exceptional conditions.
- **Library Statistics:** View book inventory, members, and loan information.

## 🛠️ Tech Stack

- **Language:** C++17
- **Core Concepts:** OOP, STL, file handling, exception handling
- **Build System:** CMake
- **Testing:** CTest and C++ test executable
- **Storage:** Local text files; no external database or third-party libraries

## 🏗️ Object-Oriented Design

The project uses the following classes:

| Class | Responsibility |
|---|---|
| `Book` | Stores book information and copy counts |
| `User` | Abstract base class for library users |
| `Admin` | Represents administrative operations |
| `Member` | Represents registered library members |
| `Loan` | Tracks borrowing, due dates, returns, and fines |
| `Library` | Manages books, members, and loans |
| `LibraryManagementSystem` | Coordinates the application interface |

The implementation demonstrates encapsulation, abstraction, inheritance, polymorphism, constructors, virtual functions, composition, and smart pointers.

## 💾 Data Persistence

The application stores records in three local text files:

- `books.txt` — book details and copy counts
- `members.txt` — registered member details
- `loans.txt` — loan records, dates, and return status

Records are loaded when the application starts and saved as the application updates its data. Keep these files together in the application's working directory.

## 🚀 Getting Started

### Prerequisites

- A C++17-compatible compiler
- CMake
- MinGW Make or another supported build tool

### Build on Windows using PowerShell

Clone the repository:

```powershell
git clone https://github.com/YOUR-USERNAME/cpp-library-management-system.git
cd cpp-library-management-system
```

Configure the project:

```powershell
cmake -S . -B build -G "MinGW Makefiles"
```

Build the application:

```powershell
cmake --build build
```

Run the automated tests:

```powershell
ctest --test-dir build --output-on-failure
```

Launch the application:

```powershell
.\build\library_management.exe
```

Replace `YOUR-USERNAME` with your GitHub username. These commands assume MinGW and CMake are installed and available in PATH.

## 📂 Project Structure

```text
library-management-system/
├── include/       # Header files
├── src/           # Class implementations and main.cpp
├── tests/         # Automated tests
├── CMakeLists.txt
├── README.md
├── OOP_CONCEPTS.md
└── .gitignore
```

## 🧪 Testing

The project includes a C++ test executable that can be run through CTest. Tests cover core library operations and validation. Run the test command above to verify the current build.

## 🎯 Learning Objectives

This project demonstrates practical C++ skills relevant to software development interviews:

- Designing classes and managing object relationships
- Applying OOP principles to a real-world problem
- Using STL containers for in-memory management
- Implementing file-based persistence
- Handling invalid operations and exceptions
- Organizing and building a modular C++ application

## 🔮 Future Improvements

- Search and filtering enhancements
- Stronger automated test coverage
- File-format validation and recovery
- Role-based authorization
- A graphical user interface

## 📄 License

Add a license if you intend to publish the project for reuse. Until then, no license is specified.

---

**Built with C++17 and the Standard Library.**
