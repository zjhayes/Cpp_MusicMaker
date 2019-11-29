#include "MusicPlayer.h"
#include "SongData.h"

MusicPlayer::MusicPlayer()
{
	loadSongs();
}

// Run program.
void MusicPlayer::run()
{
	runOptionMenu();
}

// Loads songs into Melody repo.
void MusicPlayer::loadSongs()
{
	SongData data = SongData();
	for (auto& song : data.getSongs())
	{
		songs.push_back(song);
	}
}

// Print Melody repo to console.
void MusicPlayer::runSongMenu()
{
	int index = 1;

	for (auto& song : songs)
	{
		std::cout << index << ". " << song.getName() << std::endl;
	}

	int choice = takeUserInput(index) - 1; // One less than printed index.

	songs[choice].playSong();
}

// List off all options available to users.
void MusicPlayer::runOptionMenu()
{
	int index = 1;

	std::cout << index++ << ". Play a song." << std::endl;

	// Only show this option if plugins exist.
	if (!plugins.empty())
	{
		std::cout << index++ << ". Run a plugin." << std::endl;
	}

	int choice = takeUserInput(index);

	switch (choice)
	{
	case 1:
		runSongMenu();
		break;
	case 2:
		runPluginsMenu();
		break;
	}

}

// List plugins by their description.
void MusicPlayer::runPluginsMenu()
{
	int index = 1;

	for (auto& plugin : plugins)
	{
		std::cout << index++ << ". " << plugin->getDescription() << std::endl;
	}
}

// Take input and validate that choice is legal.
int MusicPlayer::takeUserInput(unsigned long numberOfChoices)
{
	int userInput;
	std::cout << "Choose an option: ";
	std::cin >> userInput;
	std::cin.clear();
	std::cin.ignore(INT_MAX, '\n');

	if (userInput > 0 && userInput <= numberOfChoices)
	{
		std::cout << std::endl;
		return userInput;
	}
	{
		std::cout << "Invalid choice, try again. ";
		return takeUserInput(numberOfChoices);
	}
}

// Add a plugin to the plugins vector.
void MusicPlayer::installPlugin(IPlugin* _plugin)
{
	plugins.push_back(_plugin);
}