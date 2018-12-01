
LIBS = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system
CXXFLAGS = -std=c++11 -Wall 
CXX = g++

all: main

main.o: main.cpp
	g++ -c $(CXXFLAGS) "main.cpp" -o main.o

pacman.o: pacman.cpp
	g++ -c $(CXXFLAGS) "pacman.cpp" -o pacman.o

enemies.o: enemies.cpp
	g++ -c $(CXXFLAGS) "enemies.cpp" -o enemies.o

UI.o: UI.cpp
	g++ -c $(CXXFLAGS) "UI.cpp" -o UI.o

math.o: math.cpp
	g++ -c $(CXXFLAGS) "math.cpp" -o math.o

map.o: map.cpp
	g++ -c $(CXXFLAGS) "map.cpp" -o map.o

main: main.o enemies.o pacman.o UI.o math.o map.o
	@echo "** Building the game"
	$(CXX) main.o enemies.o pacman.o UI.o math.o map.o -o main $(LIBS)

clean:
	@echo "** Removing object files and executable..."
	rm -f main *.o
