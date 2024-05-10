#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
using namespace std;

// define your classes here...
class List
{
    private:
        class Player        // encapsulating class "Player" with in "List"
        {
            public:
                double player_position_x;
                double player_position_y;
                
                Player * next;
               
                // constructor
                Player(double pos_x, double pos_y) : player_position_x(pos_x), player_position_y(pos_y), next(nullptr){};   
                // ~Player();                           // destructor, but there is no dynamic allocated memory that needs to be cleaned up
        };
        Player * head;

    public:
        List() : head(nullptr){};   // constructor
        ~List();                    // destructor

        //SPAWN x y: add to list if x y in first quadrant
        void spawn_player(double x, double y);  
        
        //TIME t: move all players toward wolf
        void update_position(double t);  
        
        //LUNCH: delete if distance < 1 from (0,0)
        void delete_player();  

        //NUM: print the number of survive players
        void count_player();

        //PRT d: print coordinate of all players within a distance of < d from (0,0) if any
        void print_player(double d);

        //OVER: determine winner
        void game_over();

        int count = 0;

        double parameters[2];         // array to store parameters but at most there are 2 parameters
};

#endif