all: target

target: ammo.o enemy.o game.o main.o starship.o TextBox.o window.o world.o
	g++ ammo.o enemy.o game.o main.o starship.o TextBox.o window.o world.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system

ammo.o: ammo.cpp
	g++ -c ammo.cpp

enemy.o: enemy.cpp
	g++ -c enemy.cpp

game.o: game.cpp
	g++ -c game.cpp

main.o: main.cpp
	g++ -c main.cpp

starship.o: starship.cpp
	g++ -c starship.cpp

TextBox.o: TextBox.cpp
	g++ -c TextBox.cpp

window.o: window.cpp
	g++ -c window.cpp

world.o: world.cpp
	g++ -c world.cpp
