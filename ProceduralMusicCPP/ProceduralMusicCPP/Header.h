#include <iostream>
#include <vector>

using namespace std;

string id_to_note(int id);
int note_to_id(std::string note);
vector<int> bounce_num(int limit, int length);
void propagate_scales();

void boost_scale(std::vector<std::vector<int>>& res, int start, int end, int loopTime);

class Chord {
	public:
		vector<int> notes;
		vector<int> avoidNotes;
		Chord(vector<string> inputNotes);
};
class ChordProgression {
	vector<int> arpeggiate_chords();
	void check_scale_similarity(vector<int> vec, vector<int> commonNotes, int& maxCount, vector<vector<int>>& res, vector<int> commonAvoidNotes);

	public:
		vector<int> commonScale;
		vector<Chord> chords;
		vector<int> generate_bar(enum Dissonance dis);
		vector<int> find_common_scale();
		
		
};
enum Dissonance {
	ARPEGGIATE
};