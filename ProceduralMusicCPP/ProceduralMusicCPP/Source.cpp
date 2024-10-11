#include <iostream>
#include <vector>
#include <algorithm>
#include "Header.h"

using namespace std;

const int octaveSize = 12;
const string chromaticScale[octaveSize] = {"C","C#","D","D#","E","F","F#","G","G#","A","A#","B"};
const int integer2Ascii = 48;
int octave = 5;
int currentBar = 0;
vector<vector<int>> scales= {
	{0,2,4,5,7,9,11},	//Major
	
	{0,2,3,5,7,9,11},	//Melodic minor

	{0,2,3,5,7,8,11},	//Harmonic minor

	{0,2,4,6,8,10},		//Wholetone

	{0,1,3,4,6,7,9,10},	//Half Diminished

	{0,2,4,7,9},		//Major Pentatonic

	{0,3,4,7,8,11},		//Augmented
};

void propagate_scales() {
	vector<vector<int>> res;
	//Major, Melodic Minor, Harmonic Minor
	boost_scale(res,0,2,octaveSize);

	//Wholetone
	boost_scale(res, 3, 4, 2);

	//Diminished
	boost_scale(res, 4, 5, 3);

	//Pentatonic
	boost_scale(res, 5, 6, octaveSize);

	scales.insert(scales.end(), res.begin(), res.end());
}

void boost_scale(std::vector<std::vector<int>>& res, int start, int end, int loopTime)
{
	for (size_t i = 1; i < loopTime; i++)
	{
		for (auto it = scales.begin() + start; it != scales.begin() + end; ++it) {
			vector<int> tempScale = *it;
			for_each(tempScale.begin(), tempScale.end(), [i](int& n) {n += i; n %= octaveSize;});
			res.push_back(tempScale);
		}
	}
}

string id_to_note(int id) {
	string res;
	res = chromaticScale[id % octaveSize];
	res.push_back(id / octaveSize + integer2Ascii);
	return res;
}

int note_to_id(string note) {
	for (int i = 0; i < octaveSize; i++)
	{
		if (note == chromaticScale[i])
		{
			return i;
		}
	}
	return -1;
}

Chord::Chord(vector<string> inputNotes) {
	for (string note : inputNotes) {
		notes.push_back(note_to_id(note));
	}
	for (int note : notes) {
		if (count(notes.begin(), notes.end(), (note + 1) % octaveSize) == 0) {
			avoidNotes.push_back((note + 1) % octaveSize);
		}

	}
}

vector<int> ChordProgression::generate_bar(enum Dissonance dis) {
	switch (dis)
	{
		case ARPEGGIATE:
			return arpeggiate_chords();
			break;
	}
	return { -1 };
}

vector<int> ChordProgression::arpeggiate_chords() {
	vector<int> res;
	int count = 0;
	for (int i : bounce_num(chords[currentBar % chords.size()].notes.size(), 8)) {
		res.push_back(chords[currentBar % chords.size()].notes[i] + octave * octaveSize);
	}
	return res;
}

vector<int> bounce_num(const int limit, int length) {
	vector<int> res;
	int countDir = 1;
	int i = 0;
	while (length > 0) {
		res.push_back(i);
		i += countDir;
		length--;
		if (i >= limit || i < 0)
		{
			countDir *= -1;
			i += countDir*2;
		}
	}
	return res;
}

vector<int> ChordProgression::find_common_scale() {
	vector<int> commonNotes;
	vector<int> commonAvoidNotes;
	for (Chord chord : chords) {
		
		for (int avoidNote : chord.avoidNotes) {
			commonAvoidNotes.push_back(avoidNote);
		}
		for (int note : chord.notes) {
			commonNotes.push_back(note);
		}
	}

	
	vector<vector<int>> res;
	int maxCount = 0;
	for (const vector<int> vec : scales) {
		check_scale_similarity(vec, commonNotes, maxCount, res, commonAvoidNotes);
	}
	return res[rand() % res.size()];
}

void ChordProgression::check_scale_similarity(vector<int> vec, vector<int> commonNotes, int& maxCount, vector<vector<int>>& res, vector<int> commonAvoidNotes)
{
	int count = 0;
	for (const int i : vec) {
		if (find(commonNotes.begin(), commonNotes.end(), i) != commonNotes.end()) {
			count++;
		}
		if (find(commonAvoidNotes.begin(), commonAvoidNotes.end(), i) != commonAvoidNotes.end()) {
			count--;
		}
		if (count > maxCount)
		{
			maxCount = count;
			res.clear();
		}
		if (count == maxCount){
			res.push_back(vec);
		}
	}
}
