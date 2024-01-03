#pragma once
#include "User.h"
#include "Artist.h"
#include "Song.h"
#include "Functions.h"
#include <map>
#include <algorithm>

class Data_base;


typedef void (Data_base::* Command_func_ptr)(vector<string>&);

typedef map<pair<int, int>, Command_func_ptr> Command_map;


enum
{
	POST,
	GET,
	PUT,
	DELETE
};




typedef struct CURRENT
{
	int prem_state = 0;
	shared_ptr<Account> acc = nullptr;
} Current;


typedef struct ARG
{
	string pin;
	string f_name;
	vector<string> arguments;
};

enum
{
	// COMMON
	USERS,
	MUSICS,
	// NO ACC
	SIGNUP,
	LOGIN,
	// USER
	PLAYLIST,
	ADD_PLAYLIST,
	SEARCH_MUSICS,
	// ARTIST
	REGISTERED_MUSICS,
	// IN ACC
	LOGOUT
};

enum
{
	NO_ACC,
	COMMON,
	USER,
	ARTIST,
	IN_ACC,
};

enum
{
	ARG_T_NAME_REGISTER = 1,
	ARG_T_NAME_IN_REGISTER,
	ARG_PASS_REGISTER,
	ARG_PASS_IN_REGISTER,
	ARG_REGISTER_NUM = 5,
};








class Data_base
{
public:
	Data_base();

	void manage_command(pair<string, string>& command, vector<string>& arg);

private:

	vector <shared_ptr<User>> users;
	vector <shared_ptr<Artist>> artists;
	vector <shared_ptr<Song>> songs;
	vector<Command_map> command_maps;


	void init_command_map();
	bool call_command_func(pair<int, int>& key, Command_map& command_map, vector<string>& arg);

	Current current;

	pair<int, int> make_command_code(pair<string, string>& command);

	void signup(vector<string>& arg);
	void check_signup_arg(vector<string>& arg) const;

	void login(vector<string>& arg);
	void check_login_arg(vector<string>& arg) const;

	void get_musics(vector<string>& arg);
	void get_users(vector<string>& arg);
	void make_playlist(vector<string>& arg);
	void add_playlist(vector<string>& arg);
	void get_playlist(vector<string>& arg);
	void search_music(vector<string>& arg);
	void make_music(vector<string>& arg);
	void delete_music(vector<string>& arg);
	void get_regestered_music(vector<string>& arg);








	/*
	void register_admin(vector<string>& arg);
	void check_register_admin_arg(vector<string>& arg);
	*/

	void logout(vector<string>& arg);
	void check_logout_arg(vector<string>& arg);





	int id = 0;
};






