#ifndef LOGIN_H
#define LOGIN_H

#include <string>

class Login
{
private:
    std::string username;
    int password;

public:
    Login();
    std::string getUsername() const;
    void signup();
    bool login();
};

#endif