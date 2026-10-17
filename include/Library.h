#pragma once
#include "Book.h"
#include "Member.h"
#include "Loan.h"
#include <map>
#include <memory>
#include <string>
#include <string>
#include <vector>

class Library {
private:
    std::map<int, Book> books_;
    std::map<int, std::unique_ptr<Member>> members_;
    std::map<int, Loan> loans_;
    int nextLoanId_ = 1;
    std::string filePrefix_;
    void loadData();
    void saveData() const;
    static constexpr int LOAN_DAYS = 14;
    static constexpr double FINE_PER_DAY = 5.0;
public:
    explicit Library(const std::string& filePrefix = "");
    Library(const Library&) = delete;
    Library& operator=(const Library&) = delete;
    void addBook(const Book& book);
    bool updateBook(int id, const std::string& title, const std::string& author, const std::string& isbn, int copies);
    bool deleteBook(int id);
    Book* findBook(int id);
    const Book* findBook(int id) const;
    std::vector<const Book*> searchBooks(const std::string& query) const;
    void displayBooks() const;
    void registerMember(int id, const std::string& name, const std::string& email);
    bool removeMember(int id);
    Member* findMember(int id);
    const Member* findMember(int id) const;
    void displayMembers() const;
    int issueBook(int bookId, int memberId);
    double returnBook(int loanId);
    void displayLoans(bool activeOnly = false) const;
    void displayStatistics() const;
    std::size_t bookCount() const noexcept;
    std::size_t memberCount() const noexcept;
    std::size_t activeLoanCount() const noexcept;
};
