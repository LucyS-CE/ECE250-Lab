#include "graph.h"
#include <iostream>
#include <string>
#include <fstream>  // for read txt
#include <vector>
#include <set>      // for visited node set
#include <queue>    // for prioritu queue
#include <limits>   // for numeric_limits
#include <cmath>    // for isinf()
#include <iomanip>  // for setprecision()

// implement classes' member functions here...
void Graph :: command_insert(const int & a, const int & b, const double & d, const double & s)
{
    // check if both vertex exist in the adjacent list, true for exist
    bool aExist = adjacentList.find(a) != adjacentList.end();
    bool bExist = adjacentList.find(b) != adjacentList.end();
    // bool have_edge = adjacentList[a].find(b) != adjacentList[a].end();

    // cout << "have edge: " << have_edge << endl;
    
    // it won't update adjustment factor to 1 when a and b both exist and there is already an edge between them
    if(!(aExist && bExist && (adjacentList[a].find(b) != adjacentList[a].end())))  
    {
        // cout << "updated adjustment" << endl;
        adjacentList[a][b].adjustmentFactor = 1.0;
        adjacentList[b][a].adjustmentFactor = 1.0;
    }
    // cout << "adjustment factor after: " << adjacentList[a][b].adjustmentFactor << endl;

    adjacentList[a][b].distance = d;
    adjacentList[a][b].speedLimit = s;
    adjacentList[b][a].distance = d;
    adjacentList[b][a].speedLimit = s;

    // cout << "success insert" << endl;
}

void Graph :: command_load(const string & filename)
{
    ifstream file(filename);
    if(!file.is_open())
    {
        cout << "error opening file" << endl;
        return;
    }

    string str1, str2, str3, str4;
    while (file >> str1 >> str2 >> str3 >> str4) 
    {
        command_insert(stoi(str1), stoi(str2), stod(str3), stod(str4));
    }

    file.close();
    // cout << "success load" << endl;
}

void Graph :: command_traffic(const int & a, const int & b, const double & A)
{
    bool aExist = adjacentList.find(a) != adjacentList.end();
    bool bExist = adjacentList.find(b) != adjacentList.end();

    // if a, b exist, their edge also exist
    if(aExist && bExist && adjacentList[a].find(b) != adjacentList[a].end())  
    {
        adjacentList[a][b].adjustmentFactor = A;
        adjacentList[b][a].adjustmentFactor = A;

        traffic_success = true;     // for update command
    }
}

void Graph :: command_update(const string & filename)
{
    ifstream file(filename);
    if(!file.is_open())
    {
        cout << "error opening file" << endl;
        return;
    }

    string str1, str2, str3;
    while (file >> str1 >> str2 >> str3) 
    {
        command_traffic(stoi(str1), stoi(str2), stod(str3));
    }

    file.close();

    if(traffic_success)
    {
        cout << "success" << endl;
    }
    else
    {
        cout << "failure" << endl;
    }
}

void Graph :: command_print(const int & a)
{
    bool aExist = adjacentList.find(a) != adjacentList.end();
    if(aExist)
    {
        for(auto & pair : adjacentList[a])  // the hash table of adjacent vertex of a, it constains (key: adjacent vertex's ID) and (value: edge between adjacent vertex and a)
        {
            cout << pair.first << " ";  // .first refers to key of the pair which is the ID of adjacent vertex
        }
        cout << endl;
    }
    else
    {
        cout << "failure" << endl;
    }
}

void Graph :: command_delete(const int & a)
{
    bool aExist = adjacentList.find(a) != adjacentList.end();
    if(aExist)
    {
        for(auto & pair : adjacentList)  // the hash table of existing nodes and the hash table of their adjacent vertex, it contains (key: existing node) and (value: hash table for adjacent node)
        {
            pair.second.erase(a);   // erase the key a in hash table for adjacent nodes
        }
        adjacentList.erase(a);  // erase the key a in hash table for the graph(existing vertex)
        cout << "success" << endl;
    }
    else
    {
        cout << "failure" << endl;
    }
}

bool Graph :: dijkstra(const int & a, const int & b)
{
    set<int> visited;   // a set to mark all the visited node
    priority_queue<pair<double, vector<int>>, vector<pair<double, vector<int>>>, ComparePaths> todo;  // it is a min heap, so that lower priority is on the top, which implies that shortest path length goes out first

    // initialize the set and priority queue
    visited.clear();
    while (!todo.empty())
    {
        todo.pop();
    }
    
    vector<int> from(1, a);  // set the from node?1 for number of element in the vector
    
    todo.push({0.000, from});   // push the from node to todo, 0.000 for the initialized path length at from node
    while(!todo.empty())    // as long as todo is non-empty
    {
        vector<int> currentPath = todo.top().second;    // let the top entry be the current path (with shortest path length)
        double currentLength = todo.top().first;           // get the current length of the current path
        todo.pop();                                     // pop out the top element
        int currentNode = currentPath.back();           // get the last node of the path
        // cout << "current length: " << currentLength << endl;

        if(isinf(currentLength))
        {
            return false;
        }

        if(currentNode == b)  // find the "to" node
        {
            shortestPath = currentPath;
            lowestLength = currentLength;
            // cout << "success Dijkstra" << endl;
            return true;        // path found
        }
        if(visited.count(currentNode) == 0)             // if current node is not visited
        {
            visited.insert(currentNode);                // add the node to visited set, so we won't visited it again
            for(auto & adjacentPair : adjacentList[currentNode])
            {
                vector<int> path = currentPath;
                double T = 0.000;
                
                double d = adjacentPair.second.distance;
                double S = adjacentPair.second.speedLimit;
                double A = adjacentPair.second.adjustmentFactor;
                // cout << "d: " << d << ", S: " << S << ", A: " << A << endl;
                if(A != 0.0)
                {
                    T = d/(S*A);
                    // cout << "T: " << T << endl;
                }
                else
                {
                    T = numeric_limits<double> :: infinity();
                    // cout << "infinity T" << endl;
                }

                path.push_back(adjacentPair.first);

                todo.push({T + currentLength, path});
            }
        }
    }
    // cout << "failure Dijkstra" << endl;
    return false;       // path not found
}

void Graph :: command_path(const int & a, const int & b)
{
    bool aExist = adjacentList.find(a) != adjacentList.end();
    bool bExist = adjacentList.find(b) != adjacentList.end();

    if(aExist && bExist && dijkstra(a,b))
    {
        for(int ID : shortestPath)
        {
            cout << ID << " ";
        }
        cout << endl;
    }
    else
    {
        cout << "failure" << endl;
    }
}

void Graph :: command_lowest(const int & a, const int & b)
{
    bool aExist = adjacentList.find(a) != adjacentList.end();
    bool bExist = adjacentList.find(b) != adjacentList.end();

    if(aExist && bExist && dijkstra(a,b))
    {
        cout << fixed << setprecision(3) << lowestLength << endl;
    }
    else
    {
        cout << "failure" << endl;
    }
}

void Graph :: command_exit()
{
    cout << endl;
    exit(0);
}