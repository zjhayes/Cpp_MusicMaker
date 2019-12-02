#include "MusicMaker.h"

MusicMaker::MusicMaker()
{
	loadNotes();
}

// Loads note data from note repository path and creates Note objects.
void MusicMaker::loadNotes()
{
	std::fstream in;
	in.open(NOTE_REPOSITORY_PATH);

	std::cout << "Loading notes into repository. . . ." << std::endl;

	// Iterate note data file and parse into note properties.
	while (!in.eof())
	{
		std::string pitch;
		std::string frequency;

		getline(in, pitch, ',');
		getline(in, frequency, '\n');

		std::cout << pitch << " " << frequency << std::endl;

		Note* newNote = new Note(pitch, stoi(frequency));

		scale.push_back(newNote);
	}
} // Frequencies of notes thanks to https://www.youtube.com/watch?v=zVV9CmzL-Go

// Returns Note object of a given pitch notation.
Note* MusicMaker::getNoteByPitch(std::string _pitch)
{
	for (auto& note : scale)
	{
		// If the correct pitch, return Note object.
		if (note->getPitch().compare(_pitch) == 0)
		{
			return note;
		}
	}

	throw pitch_not_found();
}