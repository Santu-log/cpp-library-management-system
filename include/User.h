#pragma once
#include <string>

class User {
private:
    int id_;
    std::string name_;
    std::string email_;
public:
    User(int id, std::string name, std::string email);
    virtual ~User();
    int getId() const noexcept;
    const std::string& getName() const noexcept;
    const std::string& getEmail() const noexcept;
    void updateContact(std::string name, std::string email);
    virtual std::string getRole() const = 0;
    virtual void display() const;
};
