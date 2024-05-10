// include libraries here (STL not allowed)
#include <iostream>
#include <string>
#include <cctype>       // for checking the non-alphabetic characters 
#include "tokenize.h"

string command;                         // string to store the splitted command
int para_num; 

Dictionary dictionary;

// function for resize parameters array if needed, since if there is no words in the dictionary then we don't know the max size of the parameter
void resize_para()
{
    para_num *= 2;
    string * newArray = new string[para_num];
    for(int i = 0; i < dictionary.para_count; i++)
    {
        newArray[i] = dictionary.parameters[i];
    }
    delete[] dictionary.parameters;
    dictionary.parameters = newArray;
}

// asked chatgpt for the operations within string headers to realize the function of finding a specific character (space here)
// reference to cplusplus.com for operations of string header, 'string :: find', 'string :: npos', 'string :: substr'
void split_command_parameter(const string & line)       // we can use 'const string &' here is to avoid make changes to the line we processed, referred from cplusplus.com forum
{
    para_num = dictionary.key_value_pairs;  
    dictionary.para_count = 0;
    size_t position = 0;            // record the position of space
    // int para_count = 0;             // record the number of parameters we get from line
    if(para_num != 0)
    {
        dictionary.parameters = new string[para_num];
    }
    else    // no word in the dictionary
    {
        dictionary.para_count = 0;
        para_num = 40;     // give a number so we can create the string to store parameters
        dictionary.parameters = new string[para_num];
    }

    position = line.find(" ");      // 'string :: find' to find the position of the first space, by default start at position 0
    // "if no matches were found, the function returns 'string :: npos'" referenced from cplusplus.com
    
    if(position != string :: npos)                  // 'string :: npos' is like 'len' to check the max length of the string, it is a static member constant value with the greatest possible value for an element of type 'size_t'
    {
        command = line.substr(0, position);         // 'string :: substr(a, b)' is to create a new string(substring) by copying the original string from position a to b, not include b

        size_t start = position + 1;                // use a start variable to create a start position right after the first space
        position = line.find(" ", start);           // use to find the next space start at the variable we set above (after the first space), if there are not next space it will assign the 'string :: npos' to the 'size_t'.
        
        while(position != string :: npos && dictionary.para_count < para_num)         // space position is not reach the end of string and parameters count(start at 0) are less than para_num
        {
            dictionary.parameters[dictionary.para_count] = line.substr(start, position - start);    // 'substr(start, position - start)' create the substring
            start = position + 1;                   // same reason as above
            position = line.find(" ", start);       // same reason as above
            dictionary.para_count++;                           // add parameters' count by 1 for every loop
            if(dictionary.para_count == para_num)
            {
                resize_para();
            }
        }

        if (position == string::npos && dictionary.para_count < para_num)     // for the last parameter
        {
            dictionary.parameters[dictionary.para_count] = line.substr(start);      // set substring(from start to the end)
            dictionary.para_count++;       // add parameters' count
        }
    }
    else
    {
        command = line;         // there is no space, so only contain command in the line we got
        dictionary.para_count = 0;         // no parameters
    }
}

void check_command()
{   
    // cout << "CMD: " << command << endl;
    if(command == "create")
    {
        dictionary.command_create(stoi(dictionary.parameters[0]));
    }
    if(command == "insert")
    {
        dictionary.command_insert(dictionary.parameters[0]);
        //dictionary.print_table();
        //dictionary.print_array();
    }
    if(command == "load")
    {
        dictionary.command_load(dictionary.parameters[0]);
        //dictionary.print_array();
        //dictionary.print_table();
        
    }
    if(command == "tok")
    {
        cout << dictionary.command_tok(dictionary.parameters[0]) << endl;
    }
    if(command == "ret")
    {
        cout << dictionary.command_ret(stoi(dictionary.parameters[0])) << endl;
    }
    if(command == "tok_all")
    {
        dictionary.command_tok_all();
    }
    if(command == "ret_all")
    {
        dictionary.command_ret_all();
    }
    if(command == "print")
    {
        dictionary.command_print(stoi(dictionary.parameters[0]));
    }
    if(command == "exit")
    {
        dictionary.command_exit();
    }  
}

int main()
{
    // your code goes here...
    string line; 
    while (getline(cin, line))
    {
        split_command_parameter(line);
        // cout << "command: " << command << endl;
        // for(int i = 0; i < dictionary.para_count; i++)
        // {
        //     cout << "parameters: [" << dictionary.parameters[i] << "] ";
        // }
        check_command();
    }
}