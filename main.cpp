#include "labyrinth.h"

int main()
{
    srand((int) time(0));
    while (true)
    {
        int width, height;
        std::string choice, solution;
        std::cout << " Press 1 to generate a standard 11x11 maze\n";
        std::cout << " Press 2 to generate a custom sized maze\n";
        std::cout << " Press 3 to end program\n";
        std::cout << " Enter your choice by entering the corrosponding number: ";
        getline(std::cin, choice);
        while ((choice != "2") && (choice != "1") && (choice != "3")) //checks if input is valid
        {
            std::cout << " Invalid input. Please try again: ";
            getline(std::cin, choice);
        }
        if (choice == "1") //default values
        {
            width = 11;
            height = 11;
        }
        if (choice == "2")
        {
            std::cout << " What width would you like the maze to be? [Must be an odd number equal to or greater than 3]: ";
            std::cin >> width;
            while (inputChecker(width) == false || std::cin.fail()) // checks if input value is numerical, odd and greater than 2
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                std::cout << " Invalid width, must be an odd number equal to or greater than 3. Please try again: ";
                std::cin >> width;
            }

            std::cout << " What height would you like the maze to be? [Must be an odd number equal to or greater than 3]: ";
            std::cin >> height;
            while (inputChecker(height) == false || std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                std::cout << " Invalid width, must be an odd number equal to or greater than 3. Please try again: ";
                std::cin >> height;
            }
            std::cin.ignore();
        }
        if (choice == "3") 
        {
            return 0;
        }
        labyrinth maze;
        maze.createBase(width, height);
        maze.startEnd(2);
        maze.startEnd(3);
        maze.createPath();
        maze.print();
        std::cout << "Enter [E] if you would like to see the solution, else enter anything to go back to main menu:";
        getline(std::cin, choice);
        if (choice == "E")
        {
            maze.solve();
            maze.print();
            returnMenu();
        }
    }
    return 0;
}