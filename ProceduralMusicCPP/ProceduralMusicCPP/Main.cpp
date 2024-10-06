#include <iostream>
#include "Header.h"
#include <vector>

int main()
{
	ChordProgression chP;
	propagate_scales();
	chP.chords.push_back(Chord({ "A", "C#", "E", "G#"}));
	chP.chords.push_back(Chord({ "D", "F", "A", "C#"}));
	chP.chords.push_back(Chord({ "G#", "B#", "D", "F"}));
	for (int i : chP.find_common_scale()) {
		std::cout << id_to_note(i) << "\n";
	}
}

