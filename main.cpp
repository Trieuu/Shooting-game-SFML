#include"Game.h"
#include<time.h>

int main() {
	//srand(time(0)); //??
	srand(static_cast<unsigned>(time(0)));
	Game game;

	game.run();
	//End application
	return 0;
}