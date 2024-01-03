#include "DataBase.h"



void Data_base::init_command_map()
{
    Command_map temp;

    // NO_ACC
    temp[pair<int, int>(POST, SIGNUP)] = &Data_base::signup;
    temp[pair<int, int>(POST, LOGIN)] = &Data_base::login;

    this->command_maps.push_back(temp);
    temp.clear();


    // COMMON
    temp[pair<int, int>(GET, MUSICS)] = &Data_base::get_musics;
    temp[pair<int, int>(GET, USERS)] = &Data_base::get_users;

    this->command_maps.push_back(temp);
    temp.clear();

    // USER
    temp[pair<int, int>(POST, PLAYLIST)] = &Data_base::   ;
    temp[pair<int, int>(PUT, ADD_PLAYLIST)] = &Data_base::    ;
    temp[pair<int, int>(GET, PLAYLIST)] = &Data_base::    ;
    temp[pair<int, int>(GET, SEARCH_MUSICS)] = &Data_base::    ;

    this->command_maps.push_back(temp);
    temp.clear();

    // ARTIST
    temp[pair<int, int>(POST, MUSICS)] = &Data_base::    ;
    temp[pair<int, int>(DELETE, MUSICS)] = &Data_base::    ;
    temp[pair<int, int>(GET, REGISTERED_MUSICS)] = &Data_base::    ;

    this->command_maps.push_back(temp);
    temp.clear();

    // IN_ACC
    temp[pair<int, int>(POST, LOGOUT)] = &Data_base::logout;

    this->command_maps.push_back(temp);
    temp.clear();

}



Data_base::Data_base()
{
    init_command_map();

}


pair<int, int> Data_base::make_command_code(pair<string, string>& command)
{
    pair<int, int> command_code = { -1, -1 };

    // first command
    if (command.first == "POST")
        command_code.first = POST;
    else if (command.first == "GET")
        command_code.first = GET;
    else if (command.first == "PUT")
        command_code.first = PUT;
    else if (command.first == "DELETE")
        command_code.first = DELETE;
    else
        throw runtime_error("Bad Request");

    //second command
    //COMMON COMMANDS
    if (command.second == "signup")
        command_code.second = SIGNUP;
    else if (command.second == "login")
		command_code.second = LOGIN;
    else if (command.second == "musics")
        command_code.second = MUSICS;
    else if (command.second == "users")
        command_code.second = USERS;
    else if (command.second == "logout")
        command_code.second = LOGOUT;

    //user
    if (command.second == "playlist")
        command_code.second = PLAYLIST;
    if (command.second == "add_playlist")
        command_code.second = ADD_PLAYLIST;

    //artist
    if (command.second == "search_music")
        command_code.second = SEARCH_MUSICS;



    if (command_code.second == -1)
        throw runtime_error("Not Found");

    return command_code;
}

bool Data_base::call_command_func(pair<int, int>& key, Command_map& command_map, vector<string>& arg)
{
    auto it = command_map.find(key);
    if (it == command_map.end())
        return false;
    (*this.*command_map[key])(arg);
    return true;
}


void Data_base::manage_command(pair<string, string>& command, vector<string>& arg)
{
    pair<int, int> command_code = make_command_code(command);

    if (call_command_func(command_code, this->command_maps[NO_ACC], arg))
        return;
    if (this->current.acc != nullptr)
    {
        if (call_command_func(command_code, this->command_maps[COMMON], arg))
            return;
        switch (this->current.prem_state)
        {
        case ARTIST:
            if (!call_command_func(command_code, this->command_maps[ARTIST], arg))
                throw runtime_error(ERR_BAD_REQ);
            break;
        case USER:
            if (!call_command_func(command_code, this->command_maps[USER], arg))
                throw runtime_error(ERR_BAD_REQ);
            break;
        }
    }
    else
    {
        if (!call_command_func(command_code, this->command_maps[NO_ACC], arg))
            throw runtime_error(ERR_BAD_REQ);
    }
}


void Data_base::signup(vector<string>& arg)
{
    check_signup_arg(arg);

    if (arg[7] == "artist")
    {
        this->artists.push_back(make_shared<Artist>(this->id++, arg[2], arg[4]));
        this->current.acc = artists.back();
        this->current.prem_state = ARTIST;
    }
    if (arg[7] == "user")
    {
        this->users.push_back(make_shared<User>(this->id++, arg[2], arg[4]));
        this->current.acc = users.back();
        this->current.prem_state = USER;
	}
    cout << "OK" << endl;
}

void Data_base::check_signup_arg(vector<string>& arg) const
{
    if (this->current.acc != nullptr)
        throw runtime_error(ERR_PERM);

    if (arg[6] != "artist" && arg[6] != "user")
        throw runtime_error(ERR_BAD_REQ);

    if (find_by_name<User>(this->users, arg[ARG_T_NAME_IN_REGISTER]) != nullptr)
        throw runtime_error(ERR_BAD_REQ);
}

void Data_base::login(vector<string>& arg)
{
    check_login_arg(arg);
    //user login or artist login?
    //this->current.prem_state = USER;
    this->current.acc = find_by_name<User>(this->users, arg[ARG_T_NAME_IN_REGISTER]); // has to change
    cout << "OK" << endl;
}

void Data_base::check_login_arg(vector<string>& arg) const
{
    if (this->current.acc != nullptr)
        throw runtime_error(ERR_PERM);

    shared_ptr<User> user_ = find_by_name<User>(this->users, arg[ARG_T_NAME_IN_REGISTER]);
    if (user_ != nullptr && !user_->check_pass(arg[ARG_PASS_IN_REGISTER]))
        throw runtime_error(ERR_PERM);
    
    shared_ptr<Artist> artist_ = find_by_name<Artist>(this->artists, arg[ARG_T_NAME_IN_REGISTER]);
    if(artist_ != nullptr && artist_->check_pass(arg[ARG_PASS_IN_REGISTER]))
        throw runtime_error(ERR_PERM);

    if (user_ == nullptr && artist_ == nullptr)
        throw runtime_error(ERR_NOT_FOUND);
}


// how write it?
void Data_base::get_musics(vector<string>& arg)
{
    if (arg.size() == 0)
    {
		cout << "ID" << ',' << " Name" << ',' << " Artist";
        for (auto song : this->songs)
        {
            song->introduce_briefly();
        }
        return;
    }
	shared_ptr<Song> song_ = find_by_id<Song>(this->songs, arg[1]);
    if (song_ == nullptr)
        throw runtime_error(ERR_NOT_FOUND);

    cout << "ID" << ',' << " Name" << ',' << " Artist" << ',' << "Year" << ',' << "Album" << ',' << "Tags" << ',' << "Duration";
    song_->introduce_completely();
    
}

void Data_base::get_users(vector<string>& arg)
{
    if (arg.size() == 0)
    {
        cout << "ID" << ',' << "Mode" << ',' << "Username" << ',' << "Playlists_number / Songs_number";
        for (auto user : this->users)
        {
            user->introduce_briefly();
        }
        return;
    }
    shared_ptr<User> user_ = find_by_id<User>(this->users, arg[1]);
    if (user_ == nullptr)
        throw runtime_error(ERR_NOT_FOUND);

    user_->introduce_completely();



}

void Data_base::make_playlist(vector<string>& arg)
{
    //find user 
    //uesr check repeated playlist?
    //make play list
   

}
void Data_base::add_playlist(vector<string>& arg)
{
    //find play list 
    //find music by id
    //add this music to vector <song> in playlist

}

void Data_base::get_playlist(vector<string>& arg)
{

}

void Data_base::search_music(vector<string>& arg)
{

}

void Data_base::make_music(vector<string>& arg)
{

}
void Data_base::delete_music(vector<string>& arg)
{

}

void Data_base::get_regestered_music(vector<string>& arg)
{

}


















void Data_base::logout(vector<string>& arg)
{
    check_logout_arg(arg);

    this->current.acc = nullptr;
    this->current.prem_state = NO_ACC;
    cout << "OK" << endl;
}

void Data_base::check_logout_arg(vector<string>& arg)
{
    if (current.acc == nullptr)
        throw runtime_error(ERR_BAD_REQ);
}











