#pragma once

#ifndef MUSIC_MAKER_H
#define MUSIC_MAKER_H

#include "Note.h"
#include "Melody.h"
#include <fstream>
#include <iostream>
#include <vector>

class MusicMaker
{
protected:

	const std::string NOTE_REPOSITORY_PATH = "notes.csv";
	std::vector<Note> scale;
	std::vector<Melody> songs;

	void loadNotes();
	Note getNoteByPitch(std::string);
	void loadSongs();

public:

	MusicMaker();
	void listSongs();

};

#endif