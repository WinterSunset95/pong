#include <iostream>
#include "headers/game.hpp"

using namespace std;

int main() {
	Game game;

	if (!game.Init()) {
		std::cerr << "Failed to initialize game\n";
		return -1;
	}

	game.Run();
	game.Clean();

	return 0;
}
