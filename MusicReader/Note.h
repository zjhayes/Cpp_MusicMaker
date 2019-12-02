#pragma once

#ifndef NOTE_H
#define NOTE_H

#include <string>
#include <windows.h>

enum Beat
{
	WHOLE = 3200,
	HALF = 1600,
	QUARTER = 800,
	EIGHTH = 400
};

class Note
{
private:

	std::string pitch;
	int frequency; // hz.

public:

	Note(std::string _pitch, int _frequency);
	void play(int duration);
	void play(int duration, int octave);
	void setPitch(std::string _pitch);
	std::string getPitch() const;
	void setFrequency(int _frequency);
};

#endif