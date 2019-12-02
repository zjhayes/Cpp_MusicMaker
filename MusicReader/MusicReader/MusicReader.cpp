#include "MusicReader.h"

// Run the plugin.
void MusicReader::run()
{
	std::cout << "Welcome to Music Reader. ";
	std::cout << "Place your composition text file in the MyMelodies folder, and provide the file name. ";
	std::cout << "Then you'll be able to play your song in the Music Player." << std::endl;
	bool valid; // Is input valid?
	std::string file;

	file = requestFile();
	try
	{
		std::vector<std::string> rawNoteData = readFile(file);
		Melody* newMelody = parseDataIntoMelody(rawNoteData);

		// Request song title from user.
		newMelody->setName(requestSongTitle());

		pluginSongs.push_back(newMelody);
	}
	catch (const std::exception & exc)
	{
		// Print exception, return to main menu.
		std::cout << exc.what() << std::endl;
	}

}

// Ask user for title of song.
std::string MusicReader::requestSongTitle()
{
	std::string title;
	std::cout << "Name of song: ";
	getline(std::cin, title);

	if (std::cin.fail() || title.empty())
	{
		std::cout << "Invalid input, try again. ";
		return requestSongTitle();
	}

	return title;
}

// Returns the description of this plugin, which is shown in the menu.
std::string MusicReader::getDescription()
{
	return "Music Reader - play music from text files.";
}

// Return and erase songs from vector.
std::vector<Melody*> MusicReader::getPluginSongs()
{
	std::vector<Melody*> _pluginSongs = pluginSongs;
	pluginSongs.clear();
	return _pluginSongs;
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

// Reads file and returns vector of each line.
std::vector<std::string> MusicReader::readFile(std::string file)
{
	Melody* song = new Melody();
	std::string filePath = "MusicReader/MyMelodies/" + file;
	std::ifstream reader(filePath);
	std::vector<std::string> data;

	// If can't find file, returns to main menu.
	if (!reader)
	{
		std::cout << "File not found." << std::endl;
		throw file_not_found();
	}
	
	while (reader.good())
	{
		std::string line;
		getline(reader, line);
		data.push_back(line);
	}

	return data;
}

// Parses data from text file into objects, returned as a vector of MusicalEntity objects.
Melody* MusicReader::parseDataIntoMelody(std::vector<std::string> _data)
{
	Melody* newMelody = new Melody();

	for (std::string line : _data)
	{
		std::string* noteData = parseLine(line);
		MusicalEntity musicEntity = translateNoteData(noteData);
		newMelody->addNote(musicEntity.note, musicEntity.beat, musicEntity.octave);
	}

	return newMelody;
}

// Parse line from file into Melody object.
std::string* MusicReader::parseLine(std::string _line)
{
	std::string const DELIMITER = ",";
	std::string const DEFAULT_DURATION = "Q";
	std::string DEFAULT_OCTAVE = "1"; // Don't make const.
	std::string* noteData = new std::string[3];

	int firstDelimiter = _line.find(DELIMITER);
	int secondDelimiter = _line.find(DELIMITER, firstDelimiter + 1);

	// Parse up to first delimiter.
	noteData[0] = _line.substr(0, firstDelimiter); // Notation

	if (firstDelimiter != -1) // If there is a delimiter..
	{
		if (secondDelimiter != -1) // If there is a second delimiter..
		{
			// Parse between first and second delimiter.
			noteData[1] = _line.substr(firstDelimiter + 1, secondDelimiter - firstDelimiter - 1 ); // Duration
			// Parse after second delimiter.
			noteData[2] = _line.substr(secondDelimiter + 1); // Octave
		}
		else
		{
			// Parse after first delimiter.
			noteData[1] = _line.substr(firstDelimiter + 1); // Duration
			noteData[2] = DEFAULT_OCTAVE; // Octave
		}
	}
	else
	{
		noteData[1] = DEFAULT_DURATION; // Duration
		noteData[2] = DEFAULT_OCTAVE; // Octave
	}

	return noteData;
}

// Translates note data into objects, returned as MusicalEntity.
MusicalEntity MusicReader::translateNoteData(std::string* _noteData)
{
	MusicalEntity entity;

	std::string notation = _noteData[0];
	std::string duration = _noteData[1];
	std::string octave = _noteData[2];

	entity.note = translateToNote(notation);
	entity.beat = translateToBeat(duration);
	entity.octave = stoi(octave);

	return entity;
}

// Translate string into Note object.
Note* MusicReader::translateToNote(std::string _noteString)
{
	try
	{
		return music.getNoteByPitch(_noteString);
	}
	catch (pitch_not_found)
	{
		throw error_reading_file();
	}
}

// Translate Beat from string, or return default.
Beat MusicReader::translateToBeat(std::string _beatString)
{
	char beatChar = toupper(_beatString[0]);
	const Beat DEFAULT_BEAT = QUARTER;

	switch (beatChar)
	{
	case 'W':
		return WHOLE;
	case 'H':
		return HALF;
	case 'Q':
		return QUARTER;
	case 'E':
		return EIGHTH;
	default:
		return DEFAULT_BEAT;
	}
}