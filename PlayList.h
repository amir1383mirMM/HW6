#pragma once
#include "Song.h"
#include "User.h"

class PlayList
{
public:
	PlayList(string name);

private:
	vector<shared_ptr<Song>> songs;
	string name;
};

