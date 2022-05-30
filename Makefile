all: world snake window game compile link

world:
	g++ -Isrc/include -c World.cpp

snake:
	g++ -Isrc/include -c Snake.cpp

window:
	g++ -Isrc/include -c Window.cpp

game:
	g++ -Isrc/include -c Game.cpp

compile:
	g++ -Isrc/include -c main.cpp


link:
	g++ main.o Game.o Window.o Snake.o World.o -o main -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system
