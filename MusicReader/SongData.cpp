#include "SongData.h"
#include "MusicMaker.h"

SongData::SongData()
{
	initializeSongs();
}

std::vector<Melody> SongData::getSongs()
{
	return songs;
}

void SongData::initializeSongs()
{
	Melody newSong = Melody();
	//newSong.addNote(getNoteByPitch("C"), WHOLE);
	newSong.setName("TEST SONG!!!");

	songs.push_back(newSong);
}