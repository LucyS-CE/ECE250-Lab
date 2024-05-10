// include libraries here (STL not allowed)
#include <iostream>
#include <string>
#include <fstream>
#include "trie.h"
using namespace std;

string command;                         // string to store the splitted command
string parameter;

Trie trie;

// asked chatgpt for the operations within string headers to realize the function of finding a specific character (space here)
// reference to cplusplus.com for operations of string header, 'string :: find', 'string :: npos', 'string :: substr'
void split_command_parameter(const string & line)       // we can use 'const string &' here is to avoid make changes to the line we processed, referred from cplusplus.com forum
{
    size_t position = 0;            // record the position of space
    // int para_count = 0;             // record the number of parameters we get from line

    position = line.find(" ");      // 'string :: find' to find the position of the first space, by default start at position 0
    // "if no matches were found, the function returns 'string :: npos'" referenced from cplusplus.com
    
    if(position != string :: npos)                  // 'string :: npos' is like 'len' to check the max length of the string, it is a static member constant value with the greatest possible value for an element of type 'size_t'
    {
        command = line.substr(0, position);         // 'string :: substr(a, b)' is to create a new string(substring) by copying the original string from position a to b, not include b

        size_t start = position + 1;                // use a start variable to create a start position right after the first space
        position = line.find(" ", start);           // use to find the next space start at the variable we set above (after the first space), if there are not next space it will assign the 'string :: npos' to the 'size_t'.
        
        if (position == string :: npos)      // for the one parameter
        {
            parameter = line.substr(start);
        }
    }
    else
    {
        command = line;         // there is no space, so only contain command in the line we got
    }
}


void check_command()
{   
    // cout << "CMD: " << command << endl;
    if(command == "load")
    {
        trie.command_load("corpus.txt");
    }
    if(command == "i")
    {
        trie.command_i(parameter);
    }
    if(command == "c")
    {
        trie.command_c(parameter);
    }
    if(command == "e")
    {
        trie.command_e(parameter);
    }
    if(command == "p")
    {
        trie.command_p();
    }
    if(command == "spellcheck")
    {
        trie.command_spellcheck(parameter);
    }
    if(command == "empty")
    {
        trie.command_empty();
    }
    if(command == "clear")
    {
        trie.command_clear();
        cout << "success" << endl;
    }
    if(command == "size")
    {
        trie.command_size();
    }
    if(command == "exit")
    {
        trie.command_exit();
    }  
}

int main()
{
    // your code goes here...
    string line; 
    while (getline(cin, line))
    {
        split_command_parameter(line);
        check_command();
    }
}
