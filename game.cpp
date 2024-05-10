#include "game.h"
#include <iostream>
#include <string>
#include <cmath>
using namespace std;
// implement classes' member functions here...

List :: ~List()
{
   Player * current = head;
   while(current != nullptr)        // while it is not the empty list, keep looping
   {
      Player * temp = current -> next;
      delete current;
      current = temp;
   }
   head = nullptr;
}

 //SPAWN x y: add to list if x y in first quadrant
void List :: spawn_player(double x, double y) 
{
   //4test Player ** curr = &head;
   //4test curr = &((*curr) -> next);
   if((0 < x && x <= 500) && (0 < y && y <= 500))     // x > 0, y > 0 for first quadrant
   {
      Player * new_player = new Player(x, y);

      // add player to the front of the linked list
      new_player -> next = head;          // set the next to nullptr when adding it in order
      head = new_player;                  // set the list head

      cout << "success" << endl;
      count++;
   }
   else        // player attempt to start outside first quadrant
   {
      cout << "failure" << endl;
   }
}  
        
//TIME t: move all players toward wolf, also check if some one is going out of the first quadrant
void List :: update_position(double t) 
{
   Player * current_player = head;
   Player * prev_of_delete_player = nullptr;

   while(current_player != nullptr)
   {
      double x = current_player -> player_position_x;
      double y = current_player -> player_position_y;

      current_player -> player_position_x -= t * cos(atan2(y, x));
      current_player -> player_position_y -= t * sin(atan2(y, x));

      double x_changed = current_player -> player_position_x;
      double y_changed = current_player -> player_position_y;
      //cout << "original: " << x << " " << y << ", changed: " << x_changed << " " << y_changed << endl;

      if((0 < x_changed && x_changed <= 500) && (0 < y_changed && y_changed <= 500))      // x > 0, y > 0 for first quadrant 
      {
         prev_of_delete_player = current_player;
         //cout << "prev linked list for time: " << prev_of_delete_player -> player_position_x << " " << prev_of_delete_player -> player_position_y << endl;
         current_player = current_player -> next;
         //cout << "linked list for time: " << current_player -> player_position_x << " " << current_player -> player_position_y << endl;
      }
      else     // player leave the first quadrant
      {
         if(current_player == head)       // when we want to delete the first node
         {
            //cout << "deleted first node: " << current_player -> player_position_x << " " << current_player -> player_position_y << endl;
            head = head -> next;
            delete current_player;
            current_player = head;
            //cout << "after deleted first node: " << current_player -> player_position_x << " " << current_player -> player_position_y << endl;
         }
         else        // when we want to delete the node on the other position of the list
         {
            //cout << "deleted other node: " << current_player -> player_position_x << " " << current_player -> player_position_y << endl;
            //cout << "prev linked list for time: " << prev_of_delete_player -> player_position_x << " " << prev_of_delete_player -> player_position_y << endl;
            if(prev_of_delete_player != nullptr)
            {
               prev_of_delete_player -> next = current_player -> next;
            }
            current_player = current_player -> next;
         }
         count--;
      }
   }
   cout << "num of players: " << count << endl;
}   
        
//LUNCH: delete if distance < 1 from (0,0)
void List :: delete_player() 
{
   Player * current_player = head;
   Player * prev_of_delete_player = nullptr;

   while(current_player != nullptr)
   {
      double distance = sqrt(pow(current_player -> player_position_x, 2) + pow(current_player -> player_position_y, 2));
      //cout << "distance: " << distance << endl;
      
      if(distance >= 1)
      {
         prev_of_delete_player = current_player;
         //cout << "prev deleted other node: " << prev_of_delete_player -> player_position_x << " " << prev_of_delete_player -> player_position_y << endl;
         current_player = current_player -> next;
      }
      else
      {
         if(current_player == head)       // when we want to delete the first node
         {
            //cout << "deleted first node: " << current_player -> player_position_x << " " << current_player -> player_position_y << endl;
            head = head -> next;
            delete current_player;
            current_player = head;
            //cout << "after deleted first node: " << current_player -> player_position_x << " " << current_player -> player_position_y << endl;
         }
         else        // when we want to delete the node at the other position of the list
         {
            //cout << "deleted other node: " << current_player -> player_position_x << " " << current_player -> player_position_y << endl;
            if(prev_of_delete_player != nullptr)
            {
               prev_of_delete_player -> next = current_player -> next;
            }
            current_player = current_player -> next;
         }
         count--;
      }
   }
   cout << "num of players: " << count << endl;
} 

//NUM: print the number of survive players
void List :: count_player()
{
   cout << "num of players: " << count << endl;
}

//PRT d: print coordinate of all players within a distance of < d from (0,0) if any
void List :: print_player(double d)
{
   Player * current = head;
   int count_for_not_print = 0;
   
   while(current != nullptr)
   {
      double x = current -> player_position_x;
      double y = current -> player_position_y;
      //cout << "print xy: " << x << ", " << y << endl;

      double distance = sqrt(pow(x, 2) + pow(y, 2));
      //cout << "distance print: " << distance << endl;

      if(distance < d)
      {
         cout << current -> player_position_x << " " << current -> player_position_y << " ";
      }
      else
      {
         count_for_not_print++;                 // count for invalid nodes number in this condition
      }
      current = current -> next;
   }
   if(count == count_for_not_print)       // see if all the nodes in not valid in this condition
   {
      cout << "no players found";
   }
   cout << endl;
}

//OVER: determine winner
void List :: game_over()
{
   if(count == 0)
   {
      cout << "wolf wins" << endl;
   }
   else
   {
      cout << "players win" << endl;
   }
   this -> ~List();  // ~List() is not a valid command alone, it needs to add 'this ->' to be used
}