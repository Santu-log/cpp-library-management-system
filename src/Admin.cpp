#include "Admin.h"
#include <iostream>
std::string Admin::getRole() const { return "Admin"; }
void Admin::display() const { User::display(); }
