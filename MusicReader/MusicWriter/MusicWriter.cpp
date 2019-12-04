#include "MusicWriter.h"

// Run the plugin.
void MusicWriter::run()
{
	std::cout << "Welcome to Music Writer. ";
	std::cout << "Write each note like this: NOTE,BEAT,OCTAVE. Ex. 'A#,H,2'. Type each note, and press enter." << std::endl;
	std::cout << "Type '0' to finish the song." << std::endl;
	std::cout << "BEATS--" << std::endl;
	std::cout << "W - Whole" << std::endl;
	std::cout << "H - Half" << std::endl;
	std::cout << "Q - Quarter" << std::endl;
	std::cout << "E - Eighth" << std::endl;
	bool valid; // Is input valid?
	std::string file;

	try
	{
		std::vector<std::string> rawNoteData = requestUserWriteSong();
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

// Ask user to write music.
std::vector<std::string> MusicWriter::requestUserWriteSong()
{

	std::vector<std::string> songData;
	std::string userInput;

	do
	{
		userInput.clear();
		getline(std::cin, userInput);
		songData.push_back(userInput);

	} while (userInput.compare("0") != 0);

	return songData;
}

// Ask user for title of song.
std::string MusicWriter::requestSongTitle()
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
std::string MusicWriter::getDescription()
{
	return "Music Writer - type notes into the console to create songs.";
}

// Return and erase songs from vector.
std::vector<Melody*> MusicWriter::getPluginSongs()
{
	std::vector<Melody*> _pluginSongs = pluginSongs;
	pluginSongs.clear();
	return _pluginSongs;
}

// Parses data from text file into objects, returned as a vector of MusicalEntity objects.
Melody* MusicWriter::parseDataIntoMelody(std::vector<std::string> _data)
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
std::string* MusicWriter::parseLine(std::string _line)
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
MusicalEntity MusicWriter::translateNoteData(std::string* _noteData)
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
Note* MusicWriter::translateToNote(std::string _noteString)
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
Beat MusicWriter::translateToBeat(std::string _beatString)
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