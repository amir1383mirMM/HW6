#pragma once
#include "Account.h"
#include "Playlist.h"

class User : public Account
{
public:
	User(string id, string name, string password);
	void introduce_completely();
	void introduce_briefly();

private:
	vector <PlayList >playlists;
};



