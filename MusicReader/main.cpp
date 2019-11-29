// A program module for creating music that accepts plugins.

// Zachary Hayes - October 10th, 2019 - zachary.j.hayes@gmail.com

#include "MusicPlayer.h"
#include "MusicReader.h"

int main()
{
	std::cout << "Music Maker is running . . . ." << std::endl;
	MusicPlayer music = MusicPlayer();
	MusicReader* readerPlugin = new MusicReader();
	music.installPlugin(readerPlugin);
	music.run();

	std::cout << "Program exiting . . . ." << std::endl;
	return 0;
}
