#pragma once

#ifndef MUSIC_READER_H
#define MUSIC_READER_H

#include "../IPlugin.h"
#include <string>
#include <iostream>
#include <fstream>
#include "../Note.h"

// Used to group note data.
struct MusicalEntity
{
	Note* note;
	Beat beat;
	int octave;
};

class MusicReader : public IPlugin
{
protected:
	std::string requestFile();
	std::vector<Melody*> pluginSongs;
	std::vector<std::string> readFile(std::string);
	std::string* parseLine(std::string);
	MusicMaker music = MusicMaker();
	MusicalEntity translateNoteData(std::string*);
	Melody* parseDataIntoMelody(std::vector<std::string>);
	Note* translateToNote(std::string);
	Beat translateToBeat(std::string);
	std::string requestSongTitle();
public:
	void run();
	std::string getDescription();
	std::vector<Melody*> getPluginSongs();

};

// Custom exception when file can't be found.
struct file_not_found : public std::exception
{
	const char* what() const throw ()
	{
		return "File not found.";
	}
};

// Custom exception when file can't be read.
struct error_reading_file : public std::exception
{
	const char* what() const throw ()
	{
		return "Error while reading file.";
	}
};


#endif