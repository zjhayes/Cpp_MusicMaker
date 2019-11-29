#include "Note.h"

Note::Note(std::string _pitch, int _frequency)
{
	pitch = _pitch;
	frequency = _frequency;
}

// Play Note.
void Note::play(int duration)
{
	Beep(frequency, duration);
}

// Play Note with adjusted octave.
void Note::play(int duration, int octave)
{
	Beep(pow(frequency, octave), duration);
}

void Note::setPitch(std::string _pitch)
{
	pitch = _pitch;
}

std::string Note::getPitch() const
{
	return std::string();
}

void Note::setFrequency(int _frequency)
{
	frequency = _frequency;
}
