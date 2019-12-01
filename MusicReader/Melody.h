#pragma once

#ifndef MELODY_H
#define MELODY_H

#include "Note.h"
#include <string>
#include <vector>

class Melody
{
private:

	std::string name;
	std::vector<Note> song;
	std::vector<Beat> time;
	std::vector<int> octaves;

public:

	void playSong();
	void addNote(Note _note, Beat _beat);
	void addNote(Note _note, Beat _beat, int _octave);
	std::string getName() const;
	void setName(std::string _name);
	std::vector<Note> getSong() const;
	void setSong(std::vector<Note> _song);
	std::vector<Beat> getTime() const;
	void setTime(std::vector<Beat> _time);
};
#endif