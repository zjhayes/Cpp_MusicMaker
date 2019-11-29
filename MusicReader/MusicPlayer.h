#pragma once

#ifndef MUSIC_PLAYER_H
#define MUSIC_PLAYER_H

#include "Melody.h"
#include <fstream>
#include <iostream>
#include <vector>
#include "IPlugin.h"

static class MusicPlayer
{
protected:

	std::vector<Melody> songs;
	std::vector<IPlugin*> plugins;

	void loadSongs();
	void runSongMenu();
	void runOptionMenu();
	void runPluginsMenu();
	int takeUserInput(unsigned long numberOfChoices);

public:

	MusicPlayer();
	void run();
	void installPlugin(IPlugin* _plugin);
};

#endif