#include "MusicPlayer.h"

MusicPlayer::MusicPlayer()
{
	
}

// Run program.
void MusicPlayer::run()
{
	bool exit;

	do
	{
		exit = runOptionMenu();
	} while (!exit);
}

// Print Melody repo to console.
void MusicPlayer::runSongMenu()
{
	loadPluginSongs();

	if (songs.empty())
	{
		std::cout << "No songs in Music Library." << std::endl;
		return;
	}

	int index = 1;

	for (auto& song : songs)
	{
		std::cout << index++ << ". " << song.getName() << std::endl;
	}

	int choice = takeUserInput(index) - 1; // One less than printed index.

	songs[choice].playSong();
}

// List off all options available to users, returns true if exited.
bool MusicPlayer::runOptionMenu()
{
	std::cout << std::endl << "--MAIN MENU--" << std::endl << std::endl;

	int index = 1;

	std::cout << index++ << ". Play a song." << std::endl;

	// Only show this option if plugins exist.
	if (!plugins.empty())
	{
		std::cout << index++ << ". Run a plugin." << std::endl;
	}

	std::cout << "Enter '0' to exit the program." << std::endl;

	int choice = takeUserInput(index);

	switch (choice)
	{
	case 0:
		return true;
		break;
	case 1:
		runSongMenu();
		break;
	case 2:
		runPluginsMenu();
		break;
	}

	return false; // Do not exit.
}

// List plugins by their description, take user input.
void MusicPlayer::runPluginsMenu()
{
	std::cout << "--PLUGINS--" << std::endl << std::endl;
	int index = 1;

	// Print plugin descriptions to console for user to choose from.
	for (auto& plugin : plugins)
	{
		std::cout << index++ << ". " << plugin->getDescription() << std::endl;
	}

	int choice = takeUserInput(index) - 1; // One less than printed index.
	
	plugins[choice]->run(); // Run plugin.
}

// Take input and validate that choice is legal.
int MusicPlayer::takeUserInput(unsigned long numberOfChoices)
{
	int userInput;
	std::cout << std::endl << "Choose an option: ";
	std::cin >> userInput;
	std::cin.clear();
	std::cin.ignore(INT_MAX, '\n');
	
	if (userInput > 0 && userInput < numberOfChoices)
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

// Add plugin songs to music library.
void MusicPlayer::loadPluginSongs()
{
	for (auto& plugin : plugins)
	{
		std::vector<Melody*> pluginSongs = plugin->getPluginSongs();
		for (auto song : pluginSongs)
		{
			songs.push_back(*song);
		}
	}
}