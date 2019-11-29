#include "MusicMaker.h"

MusicMaker::MusicMaker()
{
	loadNotes();
	loadSongs();
	listSongs();
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

		Note newNote = Note(pitch, stoi(frequency));

		scale.push_back(newNote);
	}
} // Frequencies of notes thanks to https://www.youtube.com/watch?v=zVV9CmzL-Go

// Returns Note object of a given pitch notation.
Note MusicMaker::getNoteByPitch(std::string _pitch)
{
	for (auto& note : scale)
	{
		// If the correct pitch, return Note object.
		if (!note.getPitch().compare(_pitch))
		{
			return note;
		}
	}
}

// Loads songs into Melody repo.
void MusicMaker::loadSongs()
{
	Melody newSong = Melody();
	newSong.addNote(getNoteByPitch("C"), WHOLE);
	newSong.setName("Test song");

	songs.push_back(newSong);
}

// Print Melody repo to console.
void MusicMaker::listSongs()
{
	int index = 1;

	for (auto& song : songs)
	{
		std::cout << index << ". " << song.getName() << std::endl;
	}
}