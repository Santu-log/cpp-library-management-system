#include "Member.h"
#include <iostream>
Member::Member(int id, std::string name, std::string email) : User(id, std::move(name), std::move(email)), active_(true) {}
std::string Member::getRole() const { return "Member"; }
bool Member::isActive() const noexcept { return active_; }
void Member::setActive(bool active) noexcept { active_ = active; }
void Member::display() const { User::display(); std::cout << "   Status: " << (active_ ? "Active" : "Inactive") << '\n'; }
