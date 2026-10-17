#include "Book.h"
#include <iostream>
#include <stdexcept>
#include <utility>

Book::Book(int id, std::string title, std::string author, std::string isbn, int copies)
    : id_(id), title_(std::move(title)), author_(std::move(author)), isbn_(std::move(isbn)), totalCopies_(copies), availableCopies_(copies) {
    if (id <= 0 || title_.empty() || author_.empty() || isbn_.empty() || copies < 1)
        throw std::invalid_argument("Book needs a positive ID/copy count and non-empty title, author, and ISBN.");
}
Book::Book(int id, std::string title, std::string author, std::string isbn,
           int totalCopies, int availableCopies)
    : id_(id), title_(std::move(title)), author_(std::move(author)),
      isbn_(std::move(isbn)), totalCopies_(totalCopies),
      availableCopies_(availableCopies) {
    if (id <= 0 || title_.empty() || author_.empty() || isbn_.empty() ||
        totalCopies < 1 || availableCopies < 0 || availableCopies > totalCopies) {
        throw std::invalid_argument("Invalid book details or copy counts.");
    }
}
int Book::getId() const noexcept { return id_; }
const std::string& Book::getTitle() const noexcept { return title_; }
const std::string& Book::getAuthor() const noexcept { return author_; }
const std::string& Book::getIsbn() const noexcept { return isbn_; }
int Book::getTotalCopies() const noexcept { return totalCopies_; }
int Book::getAvailableCopies() const noexcept { return availableCopies_; }
void Book::updateDetails(const std::string& title, const std::string& author, const std::string& isbn, int totalCopies) {
    if (title.empty() || author.empty() || isbn.empty() || totalCopies < 1 || totalCopies < totalCopies_ - availableCopies_)
        throw std::invalid_argument("Invalid book details or total copies below the number currently on loan.");
    title_ = title; author_ = author; isbn_ = isbn;
    availableCopies_ = totalCopies - (totalCopies_ - availableCopies_); totalCopies_ = totalCopies;
}
void Book::issueCopy() { if (availableCopies_ <= 0) throw std::runtime_error("No copies are currently available."); --availableCopies_; }
void Book::returnCopy() { if (availableCopies_ >= totalCopies_) throw std::runtime_error("All copies are already in the library."); ++availableCopies_; }
void Book::display() const {
    std::cout << "ID: " << id_ << " | " << title_ << " | Author: " << author_ << " | ISBN: " << isbn_
              << " | Available: " << availableCopies_ << '/' << totalCopies_ << '\n';
}
