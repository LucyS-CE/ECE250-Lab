#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_map>
#include <vector>
using namespace std;

// define your classes here...
class Graph
{
    private:
        struct Edge
        {
            double distance;
            double speedLimit;
            double adjustmentFactor;

            Edge() : distance(0), speedLimit(0), adjustmentFactor(0) {};
        };
        unordered_map<int, unordered_map<int, Edge>> adjacentList;  

        struct ComparePaths
        {
            bool operator()(const pair<double, vector<int>> & p1, const pair<double, vector<int>> & p2)   // need a empty () before two stuff that need to compare
            {
                return p1.first > p2.first; // '>' for min-heap; return true if p1.first greater than p2.first, which means that p1 has lower priority
            }
        };
    
    public:
        void command_insert(const int & a, const int & b, const double & d, const double & s);
        void command_load(const string & filename);
        void command_traffic(const int & a, const int & b, const double & A);
        void command_update(const string & filename);
        void command_print(const int & a);
        void command_delete(const int & a);
        void command_path(const int & a, const int & b);
        void command_lowest(const int & a, const int & b);
        void command_exit();

        bool dijkstra(const int & a, const int & b);
        // for update command
        bool traffic_success = false; // flag to track if any traffic update succeeds, start at false
        vector<int> shortestPath;   // for record the shortest path
        double lowestLength;        // for record the shortest path length
};

#endif