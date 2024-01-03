#pragma once
#include "Account.h"
#include "Song.h"
#include <vector>

class Artist :public Account
{
public:
	Artist(string _id, string _name, string _password);

private:
	vector<shared_ptr<Song>> songs;
};

