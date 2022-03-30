#include "TexturePack.h"

void TexturePack::init() {
	{
		if (!bird.loadFromFile("content/bird.png")) {
			std::cerr << "Failed to load bird texture." << std::endl;
		}
		if (!ground.loadFromFile("content/ground.png")) {
			std::cerr << "Failed to load ground texture." << std::endl;
		}
		if (!background.loadFromFile("content/background.png")) {
			std::cerr << "Failed to load background texture." << std::endl;
		}
		if (!pipe.loadFromFile("content/pipe.png")) {
			std::cerr << "Failed to load pipe texture." << std::endl;
		}
		if (!font.loadFromFile("content/font.ttf")) {
			std::cerr << "Failed to load font." << std::endl;
		}
	}
}