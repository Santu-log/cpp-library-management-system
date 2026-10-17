# OOP Concepts in This Project

| Concept | Where it is demonstrated |
|---|---|
| Encapsulation | Private data members in `Book`, `User`, `Member`, `Loan`, and `Library`; public methods enforce invariants. |
| Abstraction | `User` is abstract because `getRole()` is pure virtual; `Library` exposes domain operations without exposing its containers. |
| Inheritance | `Admin` and `Member` derive from `User`. |
| Polymorphism | `User::getRole()` and `User::display()` are virtual and overridden by `Admin`/`Member`. |
| Constructors | All domain classes construct valid objects, e.g. `Book::Book`, `Loan::Loan`, `Member::Member`. |
| Destructors | `User::~User()` is virtual; derived destructors override it. `Library`'s `unique_ptr` members clean up automatically. |
| Constructor initializer lists | Used in `Book`, `User`, `Member`, and `Loan` constructors. `Admin` inherits the base constructors via `using User::User`. |
| Function overloading | `Library::findBook(int)` has mutable and const overloads; `findMember(int)` is also overloaded for const access. |
| Function overriding | `Admin::getRole/display` and `Member::getRole/display` override `User` virtual methods. |
| Virtual functions | `User::getRole()` and `User::display()`; destructor is virtual. |
| Abstract class | `User`, due to pure virtual `getRole()`. |
| Static members | `Loan::formatDate` is a static utility method. `Book` and `User` do not need shared mutable static state. |
| Const member functions | Read-only accessors such as `Book::getTitle() const`, `Loan::isReturned() const`, `Library::displayStatistics() const`. |
| Composition | `LibraryManagementSystem` owns a `Library`; `Library` owns its book, member, and loan collections. |
| Exception handling | Domain validation throws standard exceptions; UI `run()` catches exceptions and continues safely. |
| STL containers | `std::map`, `std::vector`, and `std::string` are used for in-memory collections and text. |
| References | Methods accept `const std::string&` to avoid unnecessary copies; map entries are iterated by reference. |
| Pointers | `findBook` / `findMember` return non-owning pointers, with `nullptr` for missing records. |
| Smart pointers | `std::unique_ptr<Member>` provides exclusive ownership and automatic cleanup. |
| RAII | Containers and smart pointers manage resource lifetimes automatically; no manual `new`/`delete`. |
| Input validation | `LibraryManagementSystem::readInt`, constructors, and domain methods reject invalid data. |

## Notes
- `Admin` is included to demonstrate the requested inheritance hierarchy; a role-authentication layer is not part of the current console feature set.
- This project deliberately does not use persistence or third-party libraries.

## File persistence

`Library::loadData()` loads saved book, member, and loan records from `books.txt`, `members.txt`, and `loans.txt` when a `Library` is constructed. `Library::saveData()` writes current records after successful mutations. Text fields use `std::quoted`; loan timestamps are stored as epoch seconds so issue, due, and return dates survive restarts.
