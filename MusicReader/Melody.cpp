#include "Melody.h"

// Plays each Note in a song, taking the duration from the time array.
void Melody::playSong()
{
	for (Note& note : song)
	{
		note.play(time.front());
	}
}

// Add note and duration to end of Melody.
void Melody::addNote(Note _note, Beat _beat)
{
	song.push_back(_note);
	time.push_back(WHOLE);
}

std::string Melody::getName() const
{
	return name;
}

void Melody::setName(std::string _name)
{
	name = _name;
}

std::vector<Note> Melody::getSong() const
{
	return song;
}

void Melody::setSong(std::vector<Note> _song)
{
	song = _song;
}

std::vector<Beat> Melody::getTime() const
{
	return time;
}

void Melody::setTime(std::vector<Beat> _time)
{
	time = _time;
}
