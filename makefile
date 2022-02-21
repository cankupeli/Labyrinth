progam: main.cpp labyrinth.cpp
	g++ -std=c++17 main.cpp labyrinth.cpp -o main 

run: main
	./main

del: program
	rm main