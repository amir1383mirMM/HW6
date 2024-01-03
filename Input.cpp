#include "Input.h"


bool Input::set()
{
    string line;
    getline(cin, line);
    if (line == "")
    {
        this->is_running = false;
        return false;
    }

    vector<string> temp = seperate_words(line, " ");

    command.first = temp[0];
    command.second = temp[1];

    for (vector<string>::size_type i = 2; i < temp.size(); i++)
        value.push_back(temp[i]);
    return true;
}

void Input::clear()
{
    command.first.clear();
    command.second.clear();
    value.clear();
}