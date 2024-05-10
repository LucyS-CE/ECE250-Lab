// include libraries here (STL not allowed)
#include <iostream>
#include <string>
#include "game.cpp"
#include "game.h"
using namespace std;

string command;                         // string to store the splitted command
const int num_of_para = 2;              // max num of parameter

List list;

// asked chatgpt for the operations within string headers to realize the function of finding a specific character (space here)
// reference to cplusplus.com for operations of string header, 'string :: find', 'string :: npos', 'string :: substr'
void split_command_parameter(const string & line)       // we can use 'const string &' here is to avoid make changes to the line we processed, referred from cplusplus.com forum
{
    size_t position = 0;            // record the position of space
    int para_count = 0;             // record the number of parameters we get from line

    position = line.find(" ");      // 'string :: find' to find the position of the first space, by default start at position 0
    // "if no matches were found, the function returns 'string :: npos'" referenced from cplusplus.com
    
    if(position != string :: npos)                  // 'string :: npos' is like 'len' to check the max length of the string, it is a static member constant value with the greatest possible value for an element of type 'size_t'
    {
        command = line.substr(0, position);         // 'string :: substr(a, b)' is to create a new string(substring) by copying the original string from position a to b, not include b

        size_t start = position + 1;                // use a start variable to create a start position right after the first space
        position = line.find(" ", start);           // use to find the next space start at the variable we set above (after the first space), if there are not next space it will assign the 'string :: npos' to the 'size_t'.
        
        while(position != string :: npos && para_count < num_of_para)         // space position is not reach the end of string and parameters count(start at 0) are less than 2
        {
            list.parameters[para_count] = stod(line.substr(start, position - start));    // 'stod()' to convert string to double, 'substr(start, position - start)' create the 
            start = position + 1;                   // same reason as above
            position = line.find(" ", start);       // same reason as above
            para_count++;                           // add parameters' count by 1 for every loop
        }

        if (position == string::npos && para_count < num_of_para)     // for the last parameter
        {
            list.parameters[para_count] = stod(line.substr(start));      // set substring(from start to the end) to double 
            para_count++;       // add parameters' count
        }
    }
    else
    {
        command = line;         // there is no space, so only contain command in the line we got
        para_count = 0;         // no parameters
    }
}

void check_command()
{
    if(command == "SPAWN")
    {
        list.spawn_player(list.parameters[0], list.parameters[1]);
    }
    if(command == "TIME")
    {
        list.update_position(list.parameters[0]);
    }
    if(command == "LUNCH")
    {
        list.delete_player();
    }
    if(command == "NUM")
    {
        list.count_player();
    }
    if(command == "PRT")
    {
        list.print_player(list.parameters[0]);
    }
    if(command == "OVER")
    {
        list.game_over();
        exit(0);                // used to exit the program entirely
    }
    
}

int main()
{
    // your code goes here...
    string line; 
    while (getline(cin, line))
    {
        split_command_parameter(line);
        // cout << command << endl;
        // cout << list.parameters[0] << " " << list.parameters[1] << endl;
        check_command();
    }
}
