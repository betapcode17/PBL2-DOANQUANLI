#pragma once
#include <iostream>
using namespace std;
class Users
{
private:
    int role;

public:
    wstring getName();
    wstring getPassword(int x, int y);
    int getRole() const
    {
        return role;
    }
    void setRole(int);
    void forgot_password();
    void register_account();
    bool login();
};