// include libraries here
#include <iostream>
#include <string>
#include <sstream>  // for istringstream, so we can treat a string in sequence of chars
#include <vector>   // for vector<data_type>, to store tokens in a dynamic array
#include "graph.h"
using namespace std;

vector<string> tokens;
string command;
vector<string> parameters;
Graph graph;

vector<string> split_command_parameter(const string & line, char delimiter)
{
    istringstream iss(line);    // initialize variable iss as line
    string token;
    tokens.clear();
    while(getline(iss, token, delimiter))   // getline(iss, token, delimeter): it reads from the input stream 'iss' until it encounters the 'delimiter', then it stores the extracted chars in to the string variable 'token'
    {
        tokens.push_back(token);    // store token into dynamic array tokens
    }
    return tokens;
}

void check_command()
{   
    if(command == "insert")
    {
        graph.command_insert(stoi(parameters[0]), stoi(parameters[1]), stod(parameters[2]), stod(parameters[3]));
        cout << "success" << endl;
    }
    if(command == "load")
    {
        graph.command_load(parameters[0]);
        cout << "success" << endl;
    }
    if(command == "traffic")
    {
        graph.command_traffic(stoi(parameters[0]), stoi(parameters[1]), stod(parameters[2]));
        if(graph.traffic_success)
        {
            cout << "success" << endl;
        }
        else
        {
            cout << "failure" << endl;
        }
    }
    if(command == "update")
    {
        graph.command_update(parameters[0]);
    }
    if(command == "print")
    {
        graph.command_print(stoi(parameters[0])); 
    }
    if(command == "delete")
    {
        graph.command_delete(stoi(parameters[0]));
    }
    if(command == "path")
    {
        graph.command_path(stoi(parameters[0]), stoi(parameters[1]));
    }
    if(command == "lowest")
    {
        graph.command_lowest(stoi(parameters[0]), stoi(parameters[1]));
    }
    if(command == "exit")
    {
        graph.command_exit();
    }  
}

int main()
{
    // your code goes here...  
    string line; 
    while(getline(cin,line)) 
    {
        split_command_parameter(line, ' ');

        command = tokens[0];
        parameters.assign(tokens.begin() + 1, tokens.end()); // tokens.begin() + 1 is to skip the first entry which is command

        // cout << "command: " << command;
        // cout << ", parameters: ";
        // for (const auto & param : parameters) {
        //     cout << param << " ";
        // }
        // cout << endl;

        check_command();
    }
    return 0;
}