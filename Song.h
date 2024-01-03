#pragma once
#include <iostream>
#include "Artist.h"

#include <map>
#include <algorithm>



class Song
{
public:
	Song(string _id, string _name, Artist* _artist, string _year, string _album, string _tags, string _duration);
	string get_id() { return id; }
	string get_name() { return name; }
	string get_year() { return year; }
	string get_album() { return album; }
	Artist* get_artist() { return artist; }
	void introduce_completely();
	void introduce_briefly();



private:
	string id, name, year, album, tags, duration;
	Artist* artist;

};

