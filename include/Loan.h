#pragma once
#include <chrono>
#include <string>

class Loan {
private:
    int id_;
    int bookId_;
    int memberId_;
    std::chrono::system_clock::time_point issueDate_;
    std::chrono::system_clock::time_point dueDate_;
    bool returned_;
    std::chrono::system_clock::time_point returnDate_;
public:
    Loan(int id, int bookId, int memberId, int loanDays = 14);
    Loan(int id, int bookId, int memberId,
         std::chrono::system_clock::time_point issueDate,
         std::chrono::system_clock::time_point dueDate, bool returned,
         std::chrono::system_clock::time_point returnDate);
    int getId() const noexcept;
    int getBookId() const noexcept;
    int getMemberId() const noexcept;
    bool isReturned() const noexcept;
    std::chrono::system_clock::time_point getIssueDate() const noexcept;
    std::chrono::system_clock::time_point getDueDate() const noexcept;
    std::chrono::system_clock::time_point getReturnDate() const noexcept;
    bool isOverdue() const;
    double calculateFine(double finePerDay = 5.0) const;
    void markReturned();
    void display() const;
    static std::string formatDate(std::chrono::system_clock::time_point date);
};
