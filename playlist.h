#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <iostream>
#include <string>
using namespace std;

class playlist{
    public:
        int list_size_N;                //playlist size
        string* list;                   //playlist
        string command_c;
        string command_b;

        void b();               //set restrict playlist
        void sb();              //show restrict playlist

        void c();               //set playlist size
        void i();               //add song t by a at teh end of the list
        void p();               //play song at n position
        void e();               //erase song at n postion, move any songs after up by 1
        void done();            // end the program

    private:    
        string song_singer;             //song & singer name
        int song_position;              //song position
        int count;                      //valid array size count
        string parameters;              //parameters after command

        string* banned_list;            //playlist to store banned songs
        int ban_list_size_R;            //banned playlist size
        string ban_song_singer;                //banned song & singer name

        bool check_song(string array[], int index,string name);      //check if there is duplicated  or restricted song
        bool check_empty(string array[], int index, string empty_value);        //check if the entry we want is empty
        bool check_ban(string array[], int index, string name);
};

#endif