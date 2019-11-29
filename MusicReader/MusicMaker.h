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

	void loadNotes();
	Note getNoteByPitch(std::string);

public:

	MusicMaker();
};

#endif