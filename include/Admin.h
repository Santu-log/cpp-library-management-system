#pragma once
#include "User.h"

class Admin final : public User {
public:
    using User::User;
    ~Admin() override = default;
    std::string getRole() const override;
    void display() const override;
};
