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
void MusicReader::readFile(std::string filePath)
{
	std::ifstream reader(filePath);

	if (!reader)
	{
		std::cout << "File not found." << std::endl;
		return;
	}
	else
	{
		std::cout << "File found." << std::endl;
	}
	/*
	try
	{
		while (reader.good())
		{
			std::string line;
			getline(reader, line);
			parseLine(line);
		}
	}
	catch (std::out_of_range)
	{
		return;
	}*/
}

// Parse line from file into trait name and color properties.
void MusicReader::parseLine(std::string _line)
{
	std::string const DELIMITER = ",";
	std::string traitName = _line.substr(0, _line.find(DELIMITER));
	std::string traitColor = _line.substr(_line.find(DELIMITER) + 1);

	//test.addTrait(traitName, traitColor);
}