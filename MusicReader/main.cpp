// A program module for creating music that accepts plugins.

// Zachary Hayes - October 10th, 2019 - zachary.j.hayes@gmail.com

#include "MusicPlayer.h"
#include "MusicReader/MusicReader.h"
#include "MusicWriter/MusicWriter.h"

int main()
{
	std::cout << "Music Maker is running . . . ." << std::endl;
	MusicPlayer music = MusicPlayer();
	MusicReader* readerPlugin = new MusicReader();
	MusicWriter* writerPlugin = new MusicWriter();
	music.installPlugin(readerPlugin);
	music.installPlugin(writerPlugin);
	music.run();

	std::cout << "Program exiting . . . ." << std::endl;
	return 0;
}


/** How to use..

	Run program, the music library is empty. You have to use a plugin to load
	in songs. Use the MusicReader plugin to do read from a text file.

	Put your text file in the MyMelodies folder, it should follow the following format..

	NOTE,BEAT,OCTAVE
	
	ex...

	A#,W,1
	D
	X,H
	C,W

	You don't have to include the beat and octave, they will default. 
	But if you set the octave, you have to set the beat.

	Use 'X' to represent a rest.

	You can use the following beats...

	W -> Whole note
	H -> Half
	Q -> Quarter
	E -> Eighth

	Example songs have been preloaded.

	Run the Music Reader plugin and enter the name of your file.

	Return to the music library, and your song will be there.
*/