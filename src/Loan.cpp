#include "Loan.h"
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <sstream>
Loan::Loan(int id, int bookId, int memberId, int loanDays)
    : id_(id), bookId_(bookId), memberId_(memberId), issueDate_(std::chrono::system_clock::now()),
      dueDate_(issueDate_ + std::chrono::hours(24 * loanDays)), returned_(false), returnDate_{} {
    if (id <= 0 || bookId <= 0 || memberId <= 0 || loanDays < 1) throw std::invalid_argument("Invalid loan details.");
}
Loan::Loan(int id, int bookId, int memberId,
           std::chrono::system_clock::time_point issueDate,
           std::chrono::system_clock::time_point dueDate, bool returned,
           std::chrono::system_clock::time_point returnDate)
    : id_(id), bookId_(bookId), memberId_(memberId), issueDate_(issueDate),
      dueDate_(dueDate), returned_(returned), returnDate_(returnDate) {
    if (id <= 0 || bookId <= 0 || memberId <= 0 || dueDate < issueDate ||
        (returned && returnDate < issueDate)) {
        throw std::invalid_argument("Invalid saved loan details.");
    }
}

int Loan::getId() const noexcept { return id_; }
int Loan::getBookId() const noexcept { return bookId_; }
int Loan::getMemberId() const noexcept { return memberId_; }
bool Loan::isReturned() const noexcept { return returned_; }
std::chrono::system_clock::time_point Loan::getIssueDate() const noexcept { return issueDate_; }
std::chrono::system_clock::time_point Loan::getDueDate() const noexcept { return dueDate_; }
std::chrono::system_clock::time_point Loan::getReturnDate() const noexcept { return returnDate_; }
bool Loan::isOverdue() const { return !returned_ && std::chrono::system_clock::now() > dueDate_; }
double Loan::calculateFine(double finePerDay) const {
    if (finePerDay < 0) throw std::invalid_argument("Fine rate cannot be negative.");
    auto end = returned_ ? returnDate_ : std::chrono::system_clock::now();
    if (end <= dueDate_) return 0.0;
    auto hours = std::chrono::duration_cast<std::chrono::hours>(end - dueDate_).count();
    auto days = (hours + 23) / 24;
    return static_cast<double>(days) * finePerDay;
}
void Loan::markReturned() { if (returned_) throw std::runtime_error("This loan has already been returned."); returned_ = true; returnDate_ = std::chrono::system_clock::now(); }
std::string Loan::formatDate(std::chrono::system_clock::time_point date) {
    const std::time_t time = std::chrono::system_clock::to_time_t(date);
    std::tm tm{};
    const std::tm* localTime = std::localtime(&time);
    if (localTime == nullptr) {
        throw std::runtime_error("Failed to convert loan date.");
    }
    tm = *localTime;
    std::ostringstream out;
    out << std::put_time(&tm, "%Y-%m-%d");
    return out.str();
}
void Loan::display() const {
    std::cout << "Loan #" << id_ << " | Book #" << bookId_ << " | Member #" << memberId_
              << " | Issued: " << formatDate(issueDate_) << " | Due: " << formatDate(dueDate_)
              << " | " << (returned_ ? "Returned" : (isOverdue() ? "OVERDUE" : "Active"))
              << " | Fine: Rs " << std::fixed << std::setprecision(2) << calculateFine() << '\n';
}
