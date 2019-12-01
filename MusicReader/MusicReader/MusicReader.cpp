#include "MusicReader.h"

// Run the plugin.
void MusicReader::run()
{
	bool valid; // Is input valid?
	std::string file;

	file = requestFile();
	readFile(file);
}

// Returns the description of this plugin, which is shown in the menu.
std::string MusicReader::getDescription()
{
	return "Music Reader - play music from text files.";
}

// Requests file name from user.
std::string MusicReader::requestFile()
{
	std::string file;
	std::cout << "Enter file name (ex. song.txt): ";
	getline(std::cin, file);

	if (std::cin.fail())
	{
		std::cout << "Invalid entry. Try again. ";
		return requestFile();
	}
	return file;
}

// Returns false if file not found.
void MusicReader::readFile(std::string file)
{
	Melody* song = new Melody();
	std::string filePath = "MusicReader/MyMelodies/" + file;
	std::ifstream reader(filePath);

	// If can't find file, returns to main menu.
	if (!reader)
	{
		std::cout << "File not found." << std::endl;
		return;
	}
	
	try
	{	// Parse data into objects.
		while (reader.good())
		{
			std::string line;
			getline(reader, line);
			parseLine(line, song);
		}
	}
	catch (std::out_of_range)
	{
		std::cout << "Error reading file." << std::endl;
		return;
	}
}

// Parse line from file into Melody object.
void MusicReader::parseLine(std::string _line, Melody* _song)
{
	std::string const DELIMITER = ",";

	std::string notation;
	std::string duration;
	std::string octave;

	int firstDelimiter = _line.find(DELIMITER);
	int secondDelimiter = _line.find(DELIMITER, firstDelimiter + 1);

	// Parse up to first delimiter.
	notation = _line.substr(0, firstDelimiter);

	if (firstDelimiter != -1) // If there is a delimiter..
	{
		if (secondDelimiter != -1) // If there is a second delimiter..
		{
			// Parse between first and second delimiter.
			duration = _line.substr(firstDelimiter + 1, secondDelimiter - firstDelimiter - 1 );
			// Parse after second delimiter.
			octave = _line.substr(secondDelimiter + 1);
		}
		else
		{
			// Parse after first delimiter.
			duration = _line.substr(firstDelimiter + 1);
		}
	}

	if (octave.empty())
	{
		octave = "1"; // Default octave.
	}

	Note note = music.getNoteByPitch(notation);
	Beat beat;
	int octaveInt = stoi(octave);

	if (duration.compare("W"))
	{
		beat = WHOLE;
	}
	else if (duration.compare("H"))
	{
		beat = HALF;
	}
	else if (duration.compare("Q"))
	{
		beat = QUARTER;
	}
	else if (duration.compare("E"))
	{
		beat = EIGHT;
	}
	else
	{
		beat = QUARTER; // Default.
	}

	_song->addNote(note, beat, octaveInt);

	note.play(beat, octaveInt);
}