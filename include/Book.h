#pragma once
#include <string>

class Book {
private:
    int id_;
    std::string title_;
    std::string author_;
    std::string isbn_;
    int totalCopies_;
    int availableCopies_;
public:
    Book(int id, std::string title, std::string author, std::string isbn, int copies);
    Book(int id, std::string title, std::string author, std::string isbn, int totalCopies, int availableCopies);
    int getId() const noexcept;
    const std::string& getTitle() const noexcept;
    const std::string& getAuthor() const noexcept;
    const std::string& getIsbn() const noexcept;
    int getTotalCopies() const noexcept;
    int getAvailableCopies() const noexcept;
    void updateDetails(const std::string& title, const std::string& author, const std::string& isbn, int totalCopies);
    void issueCopy();
    void returnCopy();
    void display() const;
};
