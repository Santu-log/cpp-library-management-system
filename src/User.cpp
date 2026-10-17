#include "User.h"
#include <iostream>
#include <stdexcept>
#include <utility>
User::User(int id, std::string name, std::string email) : id_(id), name_(std::move(name)), email_(std::move(email)) {
    if (id <= 0 || name_.empty() || email_.empty()) throw std::invalid_argument("User ID, name, and email must be valid.");
}
User::~User() = default;
int User::getId() const noexcept { return id_; }
const std::string& User::getName() const noexcept { return name_; }
const std::string& User::getEmail() const noexcept { return email_; }
void User::updateContact(std::string name, std::string email) {
    if (name.empty() || email.empty()) throw std::invalid_argument("Name and email cannot be empty.");
    name_ = std::move(name); email_ = std::move(email);
}
void User::display() const { std::cout << "ID: " << id_ << " | " << name_ << " | " << email_ << " | Role: " << getRole() << '\n'; }
