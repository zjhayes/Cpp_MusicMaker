#pragma once

#ifndef SONG_DATA_H
#define SONG_DATA_H


#include "Melody.h"
#include "Note.h"
#include <vector>
#include "MusicMaker.h"

class SongData : public MusicMaker
{
private:
	std::vector<Melody> songs;
	void initializeSongs();
public:
	SongData();
	std::vector<Melody> getSongs();
};

#endif