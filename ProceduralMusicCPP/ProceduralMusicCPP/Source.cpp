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
	//Major Scales
	{0,2,4,5,7,9,11}, //C Ionian
	{0,2,3,5,7,9,10}, //C Dorian
	{0,1,3,5,7,8,10}, //C Phrygian
	{0,2,4,6,7,9,11}, //C Lydian
	{0,2,4,5,7,9,10}, //C Mixolydian
	{0,2,3,5,7,8,10}, //C Aeolian
	{0,1,3,5,6,8,10}, //C Locrian
	
	
	//Melodic Minor Scales
	{0,2,3,5,7,9,11}, //C Melodic minor
	{0,1,3,5,7,9,10}, //C Phrygian natural 6
	{0,2,4,6,8,9,11}, //C Lydian Augmented
	{0,2,4,6,7,9,10}, //C Lydian Dominant
	{0,2,4,5,7,8,10}, //C Mixolydian b6
	{0,2,3,5,6,8,10}, //C Half-diminished
	{0,1,3,4,6,8,10}, //C Altered

	//Other Scales
	{0,2,3,5,7,8,11} //C Harmonic minor

};

void propagate_scales() {
	vector<vector<int>> res;
	for (size_t i = 1; i < octaveSize; i++)
	{
		for (vector<int> scale : scales) {
			for_each(scale.begin(), scale.end(), [i](int& n) {n+= i; n %= octaveSize;});
			res.push_back(scale);
		}
	}

	scales.insert(scales.end(), res.begin(), res.end());
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
	for (int i : bounce_num(chords[currentBar % 4].notes.size(), 8)) {
		res.push_back(chords[currentBar % 4].notes[i] + octave * octaveSize);
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
	for (Chord chord : chords) {
		commonNotes.push_back(chord.notes[0]);
		commonNotes.push_back(chord.notes[1]);
		commonNotes.push_back(chord.notes[3]);
	}
	sort(commonNotes.begin(), commonNotes.end());
	auto iterator = unique(commonNotes.begin(), commonNotes.end());
	commonNotes.erase(iterator, commonNotes.end());
	
	vector<int> res;
	int maxCount = 0;
	for (const vector<int> vec : scales) {
		check_scale_similarity(vec, commonNotes, maxCount, res);
	}
	return res;
}

void ChordProgression::check_scale_similarity(const std::vector<int>& vec, std::vector<int>& commonNotes, int& maxCount, std::vector<int>& res)
{
	int count = 0;
	for (const int i : vec) {
		if (find(commonNotes.begin(), commonNotes.end(), i) != commonNotes.end()) {
			count++;
		}
		if (count > maxCount)
		{
			maxCount = count;
			res = vec;
		}
	}
}
