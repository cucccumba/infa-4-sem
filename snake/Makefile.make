:all snake_game

snake_game: game.o main.o snake.o TextBox.o window.o world.o 
	g++ game.o main.o snake.o TextBox.o window.o world.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system

game.o: game.cpp
	g++ -c game.cpp

main.o: main.cpp
	g++ -c main.cpp

snake.o: snake.cpp
	g++ -c snake.cpp

TextBox.o: TextBox.cpp
	g++ -c TextBox.cpp

window.o: window.cpp
	g++ -c window.cpp

world.o: world.cpp
	g++ -c world.cpp
