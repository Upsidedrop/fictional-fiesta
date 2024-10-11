#include <iostream>
#include "Header.h"
#include <vector>

int main()
{
	srand(time(NULL));

	ChordProgression chP;
	propagate_scales();
	chP.chords.push_back(Chord({"D", "F", "A", "C"}));
	chP.chords.push_back(Chord({"D#", "G", "A#", "C#"}));
	chP.chords.push_back(Chord({"C", "E","G","B"}));
	chP.chords.push_back(Chord({"C#", "F","G#","B"}));
	chP.chords.push_back(Chord({"A", "C#","E","G"}));

	chP.commonScale = chP.find_common_scale();
}

