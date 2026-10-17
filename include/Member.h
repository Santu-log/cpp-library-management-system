#pragma once
#include "User.h"

class Member final : public User {
private:
    bool active_;
public:
    Member(int id, std::string name, std::string email);
    ~Member() override = default;
    std::string getRole() const override;
    bool isActive() const noexcept;
    void setActive(bool active) noexcept;
    void display() const override;
};
