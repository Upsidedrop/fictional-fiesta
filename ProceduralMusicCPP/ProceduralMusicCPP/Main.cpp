#include "Header.h"
#include <iostream>
#include <vector>

int main()
{
	srand(time(NULL));

	ChordProgression chP;
	propagate_scales();
	chP.chords.push_back(Chord({ "D", "F", "A", "C" }));
	chP.chords.push_back(Chord({ "D#", "G", "A#", "C#" }));
	chP.chords.push_back(Chord({ "C", "E","G","B" }));
	chP.chords.push_back(Chord({ "C#", "F","G#","B" }));
	chP.chords.push_back(Chord({ "A", "C#","E","G" }));
	chP.chords.push_back(Chord({ "E", "G","B","D" }));

	chP.commonScale = chP.find_common_scale();
	for (int note : chP.generate_bar(RUN_SCALE)) {
		std::string noteName = id_to_note(note);
		noteName.pop_back();
		std::cout << noteName << " ";
	}
}

