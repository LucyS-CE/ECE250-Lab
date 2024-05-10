#include <iostream>
#include <string>
#include "playlist.h"
#include "playlist.cpp"
using namespace std;

playlist PlayList;
string input_letter;
int input_number;
string preferred_input;

void choose_command()
{
    cout << "Do you prefer to input LETTER COMMAND or NUMBER COMMAND?" << endl;
    while(preferred_input != "l" && preferred_input != "n")
    {
        cout << "Type 'l' for letter command system and 'n' for number command: ";
        cin >> preferred_input;
        if(preferred_input == "l")
        {
            cout << "We will use the letter command system." << endl; 
            cout << endl;
                  
        }
        else if(preferred_input == "n")
        {
            cout << "We will use the number command system." << endl;
            cout << endl;
           
        }
        else
        {
            cout << "Wrong command." << endl;
        }
    }
}

void l_command_list()
{
    cout << "==------------Command list-------------==" << endl;
    cout << " c -- creating the playlist " << endl;
    cout << " i -- adding songs to the list " << endl;
    cout << " p -- playing song from the list " << endl;
    cout << " e -- erasing songs from the list " << endl;
    cout << " b -- creating the banned playlist " << endl;
    cout << " sb -- showing the banned playlist " << endl;
    cout << " l -- printing letter command list " << endl;
    cout << " done -- end the program & clear the list " << endl;
    cout << "==--------------------------------------==" << endl;  
}

void commands_l()
{
    cout << "Please enter command (l to recall command list): ";
    cin >> input_letter;

    if(input_letter == "c")
    {
        PlayList.command_c = input_letter;
        PlayList.c();                       //create the array
    }
    else if(input_letter == "i")
    {
        PlayList.i();
    }
    else if(input_letter == "p")
    {
        PlayList.p();
    }
    else if(input_letter == "e")
    {
        PlayList.e();
    }
    else if(input_letter == "b")
    {
        PlayList.command_b = "b";
        PlayList.b();
    }
    else if(input_letter == "sb")
    {
        PlayList.sb();
    }
    else if(input_letter == "l")
    {
        l_command_list();
    }
    else if(input_letter == "done")
    {
        PlayList.done();
    }
    else
    {
        cout << endl;
        cout << "You entered invalid command." << endl;
    }
}

void n_command_list()
{
    cout << "==-------------Command list-------------==" << endl;
    cout << " 1 -- creating the playlist " << endl;
    cout << " 2 -- adding songs to the list " << endl;
    cout << " 3 -- playing song from the list " << endl;
    cout << " 4 -- erasing songs from the list " << endl;
    cout << " 5 -- creating the banned playlist " << endl;
    cout << " 6 -- showing the banned playlist " << endl;
    cout << " 7 -- end the program & clear the list " << endl;
    cout << "==---------------------------------------==" << endl;
}

void commands_n()
{
    n_command_list();
    cout << "Please enter command: ";
    cin >> input_number;

    switch (input_number)
    {
    case 1:
        PlayList.command_c = "c";       // might need to change
        PlayList.c();  
        break;
    case 2:
        PlayList.i();
        break;
    case 3:
        PlayList.p();
        break;
    case 4:
        PlayList.e();
        break;
    case 5:
        PlayList.command_b = "b";
        PlayList.b();
        break;
    case 6:
        PlayList.sb();
        break;
    case 7:
        PlayList.done();
        break;    
    default:
        cout << endl;
        cout << "You entered invalid command." << endl;
        break;
    }
    
}

void playlist_run()
{
    while(input_letter != "done" || input_number != 7)
    {
        cout << input_letter << input_number << endl;
        if(preferred_input == "l")
        {
            commands_l();
        }
        else
        {
            commands_n();
        }
        // if(PlayList.command_c != "c" || input_letter == "sb" || input_letter == "done" || input_number == 8 || input_number == 6)
        // {
        //    cout << endl;
        // }
        // else
        // {   
        //     if(input_letter == "done" || input_number == 7)
        //     {
        //         break;
        //     }
        //     else
        //     {
        //         cout << endl;
        //         cout << "===========PLAYLIST===========" << endl;
        //         for(int i = 0; i < PlayList.list_size_N; i++)
        //         { 
        //             cout << "Playlist " << i << ": " << PlayList.list[i] << endl;
        //         }
        //         cout << "=========END PLAYLIST=========" << endl;
        //         cout << endl;
        //     }
        // } remake a function for this part as print_list();
    }
}

int main(int argc, char *argv[])
{
    choose_command();
    if(preferred_input == "l")
    {
        l_command_list();
        playlist_run();
    }
    else if(preferred_input == "n")
    {
        playlist_run();
    }
    return 0; 
}

//TODO: add function allow user to remake the ban list