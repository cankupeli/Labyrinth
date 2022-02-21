//Can Kupeli
//Date: 2020-05-11
//Attempting for grade: C
#include "labyrinth.h"
void returnMenu() //waits for input to go back to menu
{
    std::cout << "Press [E] to go back to the main menu: ";
    std::string input;
    while (std::getline(std::cin, input))
    {
        if (input == "E")
            break;
        else
            std::cout << "Invalid input, please try again: ";
    }
}
bool inputChecker(int length) //checks whether or not cin input is an odd number greater than or equal to 3
{
    if (!(length % 2) || length < 3)
    {
        return false;
    }
    else
    {
        return true;
    }
}

void labyrinth::solve()
{
    int startPositionX;
    int startPositionY;
    //iterates through vector in vector container to find start position.
    //figures out which side the position is and creates a position one cell more centered
    for (int j = 0; j < labyrinth[0].size(); j++) 
    {
        for (int i = 0; i < labyrinth.size(); i++)
        {
            if (labyrinth[i][j].type == 2)
            {
                if (i == 0)
                {
                    startPositionX = i + 1;
                    startPositionY = j;
                }
                if (i == labyrinth.size()-1)
                {
                    startPositionX = i - 1;
                    startPositionY = j;
                }
                if (j == 0)
                {
                    startPositionX = i;
                    startPositionY = j + 1;
                }
                if (j == labyrinth[0].size()-1)
                {
                    startPositionX = i;
                    startPositionY = j - 1;
                }
            }
        }
    }
    std::stack< std::pair<int,int> > visited;
    visited.push(std::make_pair(startPositionX, startPositionY));
    while (!visited.empty())
    {
        std::pair<int, int> current = visited.top();
        labyrinth[current.first][current.second].type = 4;
        //if a neighbouring position is end, end function as the maze solution is complete.
        if ((labyrinth[current.first+1][current.second].type == 3) || (labyrinth[current.first-1][current.second].type == 3) || (labyrinth[current.first][current.second+1].type == 3) || (labyrinth[current.first][current.second-1].type == 3))
        {
            break;
        }
        //checks every neighbour if they're unvisited, if so adds them to stack
        if (labyrinth[current.first+1][current.second].type == 1)
        {
            visited.push(std::make_pair(current.first+1, current.second));
        }
        if (labyrinth[current.first-1][current.second].type == 1)
        {
            visited.push(std::make_pair(current.first-1, current.second));
        }
        if (labyrinth[current.first][current.second+1].type == 1)
        {
            visited.push(std::make_pair(current.first, current.second+1));
        }
        if (labyrinth[current.first][current.second-1].type == 1)
        {
            visited.push(std::make_pair(current.first, current.second-1));
        }
        //if no neighbours are unvisited, backtrack one position.
        if (labyrinth[current.first][current.second-1].type != 1 && labyrinth[current.first][current.second+1].type != 1 && labyrinth[current.first-1][current.second].type != 1 && labyrinth[current.first+1][current.second].type != 1)
        {
            labyrinth[current.first][current.second].type = 5;
            visited.pop();
        }
        
    }
}
void labyrinth::print() //iterates through all vector in vector cells and prints a representation of their type value
{
    for (int j = 0; j < labyrinth[0].size(); j++)
    {
        for (int i = 0; i < labyrinth.size(); i++)
        {
            if (labyrinth[i][j].type == 0)
            {
                std::cout << "█";
            }
            if (labyrinth[i][j].type == 1)
            {
                std::cout << " ";
            }
            if (labyrinth[i][j].type == 2)
            {
                std::cout << "S";
            }
            if (labyrinth[i][j].type == 3)
            {
                std::cout << "E";
            }
            if (labyrinth[i][j].type == 4)
            {
                std::cout << "░";
            }
            if (labyrinth[i][j].type == 5)
            {
                std::cout << " ";
            }
            if (i == labyrinth.size()-1)
            {
                std::cout << "\n";
            }
        }
    }
}
bool labyrinth::hasNeighbours(int x, int y)
{
    if ((x+2) < labyrinth.size()) //checks if neighbouring position is inbound
    {
        if (labyrinth[x+2][y].status == false) //checks if neighbouring position is unvisited
        {
            return true;
        }
    }
    if ((x-2) > 0)
    {
        if (labyrinth[x-2][y].status == false)
        {
            return true;
        }
    }
    if ((y+2) < labyrinth[0].size())
    {
        if (labyrinth[x][y+2].status == false)
        {
            return true;
        }
    }
    if ((y-2) > 0)
    {
        if (labyrinth[x][y-2].status == false)
        {
            return true;
        }
    }
    return false;
}
void labyrinth::createPath()
{
    std::stack< std::pair<int,int> > visited;
    int startPositionX = 1 + (2 * rand ()) %(labyrinth.size()-1); //randomize a start cell for generation
    int startPositionY = 1 + (2 * rand ()) %(labyrinth[0].size()-1);
    visited.push(std::make_pair(startPositionX, startPositionY)); //add start cell to stack
    while (!visited.empty())
    {
        std::pair<int, int> current = visited.top();
        labyrinth[current.first][current.second].status = true;
        if (hasNeighbours(current.first, current.second))
        {
            visited.push(std::make_pair(current.first, current.second));
            while (true) //incase randomization picks a neighbour thats visited, redo
            {
                int direction = rand() % 4; //pick a random neighbour
                if (direction == 0 && (current.first+2 < labyrinth.size())) //if picked and next position in-bound
                {
                    if (!labyrinth[current.first+2][current.second].status) //if next position is unvisited make it visted and convert between position to path
                    {
                        labyrinth[current.first+1][current.second].type = 1;
                        labyrinth[current.first+2][current.second].status = true;
                        visited.push(std::make_pair(current.first+2, current.second));
                        break;
                    }
                }
                if (direction == 1 && (current.first-2 > 0))
                {
                    if (!labyrinth[current.first-2][current.second].status)
                    {
                        labyrinth[current.first-1][current.second].type = 1;
                        labyrinth[current.first-2][current.second].status = true;
                        visited.push(std::make_pair(current.first-2, current.second));
                        break;
                    }
                }
                if (direction == 2 && (current.second+2 < labyrinth[0].size()))
                {
                    if (!labyrinth[current.first][current.second+2].status)
                    {
                        labyrinth[current.first][current.second+1].type = 1;
                        labyrinth[current.first][current.second+2].status = true;
                        visited.push(std::make_pair(current.first, current.second+2));
                        break;
                    }
                }
                if (direction == 3 && (current.second-2 > 0))
                {
                    if (!labyrinth[current.first][current.second-2].status)
                    {
                        labyrinth[current.first][current.second-1].type = 1;
                        labyrinth[current.first][current.second-2].status = true;
                        visited.push(std::make_pair(current.first, current.second-2));
                        break;
                    }
                }
            }
        }
        else // if no neighbours are avaliable, backtrack one step
        {
            visited.pop();
        }
    } 
}
void labyrinth::startEnd(int position)
{
    while(true)
    {
        int startingAxis = rand() % 2; //used to determine if position will be top/bottom or left/right
        int Xposition;
        int Yposition;
        if (startingAxis == 0)
        {
            int randomizer = rand() % 2; //used to determine top or bottom
            if (randomizer == 0)
            {
                Xposition = 0;
            }
            else 
            {
                Xposition = labyrinth.size()-1;
            }
            Yposition = 1 + (2 * rand ()) %(labyrinth[0].size()-1); //used to determine width
        }
        else
        {
            int randomizer = rand() % 2; //used to determine left or right
            if (randomizer == 0)
            {
                Yposition = 0;
            }
            else 
            {
                Yposition = labyrinth[0].size()-1;
            }
            Xposition = 1 + (2 * rand ()) %(labyrinth.size()-1); //used to determine height
        }
        if (labyrinth[Xposition][Yposition].type != 2 && labyrinth[Xposition][Yposition].type != 3) //checks if position is avaliable
        {
            labyrinth[Xposition][Yposition].type = position;
            break;
        }
    }
}
void labyrinth::createBase(int x, int y) //creates a vector in vector container 
{
    std::vector<cell> labyrinthCollum;
    for (int i = 0; i < x; i++) //fills outer vector with vectors equal to that of the mazes width
    {
        labyrinth.push_back(labyrinthCollum);
        for(int j = 0; j < y; j++) //fills inner vector with cells equal to that of the mazes height
        {
            if ((i % 2) && (j % 2)) //if (x, y) position is odd, the position is an unvisited path otherwise visited wall
            {
                labyrinth[i].push_back(cell(false, 1)); 
            }
            else
            {
                labyrinth[i].push_back(cell(true, 0));
            }
        }
    } 
}
labyrinth::cell::cell(bool status, int type)
{
    this->status = status;
    this->type = type;
    // status false = unvisited
    // status true = visited

    // type 0 = wall
    // type 1 = path
    // type 2 = start
    // type 3 = end
    // type 4 = correct path
    // type 5 = incorrect path
}
