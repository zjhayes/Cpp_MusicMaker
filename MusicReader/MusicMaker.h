#pragma once

#ifndef MUSIC_MAKER_H
#define MUSIC_MAKER_H

#include "Note.h"
#include "Melody.h"
#include <fstream>
#include <iostream>
#include <vector>

static class MusicMaker
{
protected:

	const std::string NOTE_REPOSITORY_PATH = "notes.csv";
	std::vector<Note*> scale;
	void loadNotes();

public:

	MusicMaker();
	Note* getNoteByPitch(std::string);
};

// Custom exception when file can't be found.
struct pitch_not_found : public std::exception
{
	const char* what() const throw ()
	{
		return "Can't find the specified pitch.";
	}
};

#endif