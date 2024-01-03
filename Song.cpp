#include "Song.h"

Song::Song(string _id, string _name, Artist* _artist, string _year, string _album, string _tags, string _duration)
	:id(_id), name(_name), artist(_artist), year(_year), album(_album), tags(_tags), duration(_duration)
{
}


void Song::introduce_completely()
{

}
void Song::introduce_briefly()
{
	cout << this->id << ',' << this->name << ',' << this->artist->get_name();
	cout << endl;
}


