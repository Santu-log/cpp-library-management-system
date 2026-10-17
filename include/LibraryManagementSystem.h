#pragma once
#include "Library.h"

class LibraryManagementSystem {
private:
    Library library_;
    bool running_ = true;
    void showMenu() const;
    void handleChoice(int choice);
    void addBook();
    void updateBook();
    void deleteBook();
    void searchBooks() const;
    void registerMember();
    void removeMember();
    void issueBook();
    void returnBook();
    static int readInt(const std::string& prompt);
    static std::string readLine(const std::string& prompt);
public:
    LibraryManagementSystem() = default;
    void run();
};
