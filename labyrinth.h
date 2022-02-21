//Can Kupeli
//Date: 2020-05-11
//Attempting for grade: C
#ifndef LABYRINTH_H
#define LABYRINTH_H 
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include <stack>
#include <limits>
void returnMenu(); // returns user to menu after valid input
bool inputChecker(int length); //checks that argument is odd and greater than 2

class labyrinth {
public:
    void createBase(int x, int y); //creates the container (cell-vector in vector)
    void startEnd(int position); //implements a start or end position in the container
    void createPath(); //randomly generates a maze within the container through a DFS algorithm
    void solve(); //solves the maze
    void print(); //prints the maze
    bool hasNeighbours(int x, int y); //checks neighbouring cells; aiding the DFS generation
private:
    struct cell //cell structure to determine whether or not it has been visited, and its type
    {
        cell (bool status, int type); // contructor for cell
        bool status; //represents cells visited or not status
        int type; //represents cells type, used to aid maze printing and solving
    };
std::vector<std::vector<cell> > labyrinth; 
};
#endif