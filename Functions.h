#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <memory>


using namespace std;

const string ARG_CHAR = "?";
const string ERR_PERM = "Permission Denied";
const string ERR_BAD_REQ = "Bad Request";
const string ERR_NOT_FOUND = "Not Found";

vector<string> seperate_words(const string line, string separate_char);

template <typename T>
shared_ptr<T> find_by_name(vector<shared_ptr<T>> ts, string name)
{
    auto it = find_if(ts.begin(), ts.end(), [&](shared_ptr<T> t)
        { return name == t->get_name(); });

    if (it != ts.end())
        return *it;
    return nullptr;
}

template <typename T>
shared_ptr<T> find_by_id(vector<shared_ptr<T>> ts, string id)
{
    auto it = find_if(ts.begin(), ts.end(), [&](shared_ptr<T> t)
        { return id == t->get_id(); });

    if (it != ts.end())
        return *it;
    return nullptr;
}
