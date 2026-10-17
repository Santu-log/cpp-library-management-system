#include "Library.h"
#include <algorithm>
#include <cctype>
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <iomanip>
#include <limits>
#include <cstdio>

// Required by older GCC/MinGW versions when this constexpr member is odr-used.
constexpr int Library::LOAN_DAYS;

namespace {
std::string lower(std::string value) {
    std::transform(value.begin(), value.end(), value.begin(),
        [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
    return value;
}

using Clock = std::chrono::system_clock;
long long toEpochSeconds(Clock::time_point value) {
    return static_cast<long long>(std::chrono::duration_cast<std::chrono::seconds>(
        value.time_since_epoch()).count());
}
Clock::time_point fromEpochSeconds(long long value) {
    return Clock::time_point(std::chrono::seconds(value));
}
}

Library::Library(const std::string& filePrefix) : filePrefix_(filePrefix) {
    loadData();
}

void Library::loadData() {
    {
        std::ifstream in(filePrefix_ + "books.txt");
        if (in) {
            int id = 0, total = 0, available = 0;
            std::string title, author, isbn;
            while (in >> id >> std::quoted(title) >> std::quoted(author) >>
                   std::quoted(isbn) >> total >> available) {
                Book book(id, title, author, isbn, total, available);
                if (!books_.emplace(id, book).second) {
                    throw std::runtime_error("Duplicate book ID in books.txt.");
                }
            }
            if (!in.eof()) throw std::runtime_error("Invalid record in books.txt.");
        }
    }
    {
        std::ifstream in(filePrefix_ + "members.txt");
        if (in) {
            int id = 0, active = 1;
            std::string name, email;
            while (in >> id >> std::quoted(name) >> std::quoted(email) >> active) {
                if (active != 0 && active != 1) {
                    throw std::runtime_error("Invalid member status in members.txt.");
                }
                auto member = std::make_unique<Member>(id, name, email);
                member->setActive(active == 1);
                if (!members_.emplace(id, std::move(member)).second) {
                    throw std::runtime_error("Duplicate member ID in members.txt.");
                }
            }
            if (!in.eof()) throw std::runtime_error("Invalid record in members.txt.");
        }
    }
    {
        std::ifstream in(filePrefix_ + "loans.txt");
        if (in) {
            int id = 0, bookId = 0, memberId = 0, returned = 0;
            long long issue = 0, due = 0, returnedAt = 0;
            while (in >> id >> bookId >> memberId >> issue >> due >> returned >> returnedAt) {
                if (returned != 0 && returned != 1) {
                    throw std::runtime_error("Invalid return status in loans.txt.");
                }
                if (books_.find(bookId) == books_.end() || members_.find(memberId) == members_.end()) {
                    throw std::runtime_error("Loan references a missing book or member in loans.txt.");
                }
                Loan loan(id, bookId, memberId, fromEpochSeconds(issue),
                          fromEpochSeconds(due), returned == 1,
                          fromEpochSeconds(returnedAt));
                if (!loans_.emplace(id, loan).second) {
                    throw std::runtime_error("Duplicate loan ID in loans.txt.");
                }
                if (id >= nextLoanId_) nextLoanId_ = id + 1;
            }
            if (!in.eof()) throw std::runtime_error("Invalid record in loans.txt.");
        }
    }
}

void Library::saveData() const {
    {
        std::ofstream out(filePrefix_ + "books.txt", std::ios::trunc);
        if (!out) throw std::runtime_error("Cannot write books.txt.");
        for (const auto& entry : books_) {
            const Book& book = entry.second;
            out << book.getId() << ' ' << std::quoted(book.getTitle()) << ' '
                << std::quoted(book.getAuthor()) << ' ' << std::quoted(book.getIsbn()) << ' '
                << book.getTotalCopies() << ' ' << book.getAvailableCopies() << '\n';
        }
        if (!out) throw std::runtime_error("Failed while saving books.txt.");
    }
    {
        std::ofstream out(filePrefix_ + "members.txt", std::ios::trunc);
        if (!out) throw std::runtime_error("Cannot write members.txt.");
        for (const auto& entry : members_) {
            const Member& member = *entry.second;
            out << member.getId() << ' ' << std::quoted(member.getName()) << ' '
                << std::quoted(member.getEmail()) << ' ' << (member.isActive() ? 1 : 0) << '\n';
        }
        if (!out) throw std::runtime_error("Failed while saving members.txt.");
    }
    {
        std::ofstream out(filePrefix_ + "loans.txt", std::ios::trunc);
        if (!out) throw std::runtime_error("Cannot write loans.txt.");
        for (const auto& entry : loans_) {
            const Loan& loan = entry.second;
            out << loan.getId() << ' ' << loan.getBookId() << ' ' << loan.getMemberId() << ' '
                << toEpochSeconds(loan.getIssueDate()) << ' '
                << toEpochSeconds(loan.getDueDate()) << ' '
                << (loan.isReturned() ? 1 : 0) << ' '
                << toEpochSeconds(loan.getReturnDate()) << '\n';
        }
        if (!out) throw std::runtime_error("Failed while saving loans.txt.");
    }
}
void Library::addBook(const Book& book) {
    if (books_.count(book.getId())) throw std::invalid_argument("A book with that ID already exists.");
    for (const auto& entry : books_) if (entry.second.getIsbn() == book.getIsbn()) throw std::invalid_argument("That ISBN is already registered.");
    books_.emplace(book.getId(), book);
    saveData();
}
bool Library::updateBook(int id, const std::string& title, const std::string& author, const std::string& isbn, int copies) {
    auto it = books_.find(id); if (it == books_.end()) return false;
    for (const auto& entry : books_) if (entry.first != id && entry.second.getIsbn() == isbn) throw std::invalid_argument("That ISBN is already registered.");
    it->second.updateDetails(title, author, isbn, copies); saveData(); return true;
}
bool Library::deleteBook(int id) {
    auto it = books_.find(id); if (it == books_.end()) return false;
    for (const auto& pair : loans_) if (pair.second.getBookId() == id && !pair.second.isReturned()) throw std::runtime_error("Cannot delete a book with an active loan.");
    books_.erase(it); saveData(); return true;
}
Book* Library::findBook(int id) { auto it=books_.find(id); return it==books_.end()?nullptr:&it->second; }
const Book* Library::findBook(int id) const { auto it=books_.find(id); return it==books_.end()?nullptr:&it->second; }
std::vector<const Book*> Library::searchBooks(const std::string& query) const {
    std::vector<const Book*> result; auto q=lower(query);
    for (const auto& pair:books_) if (lower(pair.second.getTitle()).find(q)!=std::string::npos || lower(pair.second.getAuthor()).find(q)!=std::string::npos || lower(pair.second.getIsbn()).find(q)!=std::string::npos) result.push_back(&pair.second);
    return result;
}
void Library::displayBooks() const { if(books_.empty()) { std::cout<<"No books registered.\n"; return; } for(const auto& p:books_) p.second.display(); }
void Library::registerMember(int id,const std::string& name,const std::string& email) { if(members_.count(id)) throw std::invalid_argument("Member ID already exists."); members_.emplace(id,std::make_unique<Member>(id,name,email)); saveData(); }
bool Library::removeMember(int id) { auto it=members_.find(id); if(it==members_.end()) return false; for(const auto& p:loans_) if(p.second.getMemberId()==id&&!p.second.isReturned()) throw std::runtime_error("Cannot remove a member with active loans."); members_.erase(it); saveData(); return true; }
Member* Library::findMember(int id) { auto it=members_.find(id); return it==members_.end()?nullptr:it->second.get(); }
const Member* Library::findMember(int id) const { auto it=members_.find(id); return it==members_.end()?nullptr:it->second.get(); }
void Library::displayMembers() const { if(members_.empty()){std::cout<<"No members registered.\n";return;} for(const auto&p:members_)p.second->display(); }
int Library::issueBook(int bookId,int memberId) {
    auto book=findBook(bookId); auto member=findMember(memberId);
    if (!book) throw std::invalid_argument("Book not found.");
    if (!member) throw std::invalid_argument("Member not found.");
    if (!member->isActive()) throw std::runtime_error("Member account is inactive.");
    book->issueCopy(); try { int id=nextLoanId_++; loans_.emplace(std::piecewise_construct,std::forward_as_tuple(id),std::forward_as_tuple(id,bookId,memberId,LOAN_DAYS)); saveData(); return id; }
    catch(...) { book->returnCopy(); throw; }
}
double Library::returnBook(int loanId) { auto it=loans_.find(loanId); if(it==loans_.end()) throw std::invalid_argument("Loan not found."); if(it->second.isReturned()) throw std::runtime_error("Loan already returned."); auto book=findBook(it->second.getBookId()); if(!book) throw std::runtime_error("Associated book record is missing."); double fine=it->second.calculateFine(FINE_PER_DAY); it->second.markReturned(); book->returnCopy(); saveData(); return fine; }
void Library::displayLoans(bool activeOnly) const { bool found=false; for(const auto&p:loans_) if(!activeOnly||!p.second.isReturned()){p.second.display();found=true;} if(!found)std::cout<<(activeOnly?"No active loans.\n":"No loans recorded.\n"); }
void Library::displayStatistics() const { std::size_t copies=0,available=0,active=0,overdue=0; for(const auto&p:books_){copies+=p.second.getTotalCopies();available+=p.second.getAvailableCopies();} for(const auto&p:loans_)if(!p.second.isReturned()){++active;if(p.second.isOverdue())++overdue;} std::cout<<"\n--- Library Statistics ---\nTitles: "<<books_.size()<<"\nTotal copies: "<<copies<<"\nAvailable copies: "<<available<<"\nRegistered members: "<<members_.size()<<"\nActive loans: "<<active<<"\nOverdue loans: "<<overdue<<"\n"; }
std::size_t Library::bookCount() const noexcept{return books_.size();}
std::size_t Library::memberCount() const noexcept{return members_.size();}
std::size_t Library::activeLoanCount() const noexcept {return static_cast<std::size_t>(std::count_if(loans_.begin(),loans_.end(),[](const auto&p){return !p.second.isReturned();}));}
