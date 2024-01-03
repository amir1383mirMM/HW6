#pragma once
#include <iostream>
using namespace std;


class Account
{

public:
    Account(string& _id, string& _username, string& pass);

    string get_id() { return id; }
    string get_name() { return username; }
    bool check_pass(string pass) const { return password == pass; }


protected:
    string id;
    string username;
    string password;
};
