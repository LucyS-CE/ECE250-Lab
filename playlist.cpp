#include "playlist.h"
#include <iostream>
#include <string>
using namespace std;

const string EMPTY_VALUE = "empty";  // Choose a value to represent an empty entry

// implement classes' member functions here...

bool playlist :: check_song(string array[], int index, string name)
{
    if (check_ban(banned_list, ban_list_size_R, song_singer))
    {
        return false;           //return false if it is a banned song
    }

    for(int i = 0; i < index; i++)
    {
        if(name == list[i])
        {
            return false;           //return false if it is already in the list
        } 
    }
    return true;
}

bool playlist :: check_empty(string array[], int index, string empty_value)
{
    return array[index] != empty_value;         //return false if entry is empty
}

bool playlist :: check_ban(string array[], int index, string name)
{
    for(int i = 0; i < index; i++)
    {
        if(name == array[i])
        {
            return true;                       //return true if the song is banned in the list
        }
    }
    return false;
}

void playlist :: b()
{
    if(banned_list == nullptr)
    {
        cout << "Enter how many songs you want to banned for the playlist: ";
        cin >> ban_list_size_R;        //request to create an array for the playlist
        banned_list = new string[ban_list_size_R];         //create the dynamic array by # of entries: N
        for(int i = 0; i < ban_list_size_R; i++)
        {
            cout << "Enter the songs you want to banned: ";
            cin >> ban_song_singer;
            banned_list[i] = ban_song_singer;
            // cout << banned_list[i];
        }
        cout << endl;
        cout << "Successfully create a banned playlist." << endl;
        cout << endl;
    }
    else
    {
        cout << endl;
        cout << "Sorry the banned playlist has already been created." << endl;
    }
}

void playlist :: sb()
{
    if(command_b == "b")
    {
        cout << endl;
        cout << "~~~~~~~~~~BANNED PLAYLIST~~~~~~~~~~" << endl;
        for(int i = 0; i < ban_list_size_R; i++)
        {
            cout << "Playlist " << i << ": " << banned_list[i] << endl;
        }
        cout << "~~~~~~~~END BANNED PLAYLIST~~~~~~~~" << endl;
    }
    else
    {
        cout << endl;
        cout << "Please create a banned playlist first." << endl;
    }
}

void playlist :: c()
{
    if(list == nullptr)
    {
        cout << "Enter how many slot you want for the playlist: ";
        cin >> list_size_N;        //request to create an array for the playlist
        list = new string[list_size_N];         //create the dynamic array by # of entries: N
        for(int i = 0; i < list_size_N; i++)
        {
            list[i] = EMPTY_VALUE;          //initialize very entry to a defined empty value
        }
        cout << endl;
        cout << "Successfully create a playlist with " << list_size_N << " slot." << endl;
    }
    else
    {
        cout << endl;
        cout << "Already created a playlist, you need to end the program before creating a new one." << endl;
    }
}

void playlist :: i()
{
    if(command_c == "c")
    {
        cout << "Enter the song you like to add into the playlist: ";
        getline(cin >> ws, song_singer);      //getline(cin>>ws, xxx); ws to skip leading space
        if((count < list_size_N) && check_song(list, list_size_N, song_singer))
        {
            list[count] = song_singer;
            cout << endl;
            cout << "Successfully add " << song_singer << " to slot " << count << endl;
            count ++;
        }
        else
        {
        cout << endl;
        cout << "Sorry, can not insert " << song_singer << " to the list." << endl;
        }
    }
    else
    {
        cout << endl;
        cout << "Please create a playlist first." << endl;
    }
    
}

void playlist :: p()
{
    if(command_c == "c")
    {
        cout << "Enter the song position you want to play: ";
        cin >> song_position;
        if(song_position < list_size_N && check_empty(list, song_position, EMPTY_VALUE))
        {
            cout << endl;
            cout << "Playing song " << song_position << " " << list[song_position] << ", enjoy!"<< endl;
        }
        else
        {
            cout << endl;
            cout << "Sorry, can not play song " << song_position << endl;
        }
    }
    else
    {
        cout << endl;
        cout << "Please create a playlist first." << endl;
    }
    
}

void playlist :: e()
{
    if(command_c == "c")
    {
        cout << "Enter the song position you want to erase: ";
        cin >> song_position;
        if(song_position < list_size_N && check_empty(list, song_position, EMPTY_VALUE))       //check if the entry n(song_position) is empty
        {
            string erased_song = list[song_position];
            for(int i = song_position; i < count; i++)
            {
                list[i] = list[i+1];
            }                                                   //remove the song at postion n and move the rest songs up by 1
            list[count] = EMPTY_VALUE;                          //fill the position of the original last song by EMPTY_VALUE
            count--;
            cout << endl;
            cout << "Successfully erased " << song_position << " " << erased_song << endl;
        }
        else
        {
            cout << endl;
            cout << "Sorry, can not erase " << song_position << endl;
        }
    }
    else
    {
        cout << endl;
        cout << "Please create a playlist first." << endl;
    }
}

void playlist :: done()
{
    delete[] list;              //release memory by delete[]
    delete[] banned_list;
    list = nullptr;             //set to nullptr after deleting
    banned_list = nullptr;
    count = 0;                  //reset valid entry index to 0
    command_c = EMPTY_VALUE;    //initialize command_m to empty value
    command_b = EMPTY_VALUE;
    cout << endl;
    cout << "PLAYLIST cleared, program ends." << endl;
    cout << endl;
}
