#include "main.h"

using namespace std;

int main(){
	string line;
	ifstream myfile("../pinyin-curated.txt");
	if(myfile.is_open()){
		while(getline(myfile, line)){
			lines.push_back(line);
		}
		myfile.close();
	}else{
		cout << "Unable to open file" << endl;
	}

	outfile.open("../chinese_2to3.txt");
	recursivePair(&lines, 2, 3, &outfile);
	outfile.close();

	return 0;
}

//------------------------------------------------------------------------------
void recursivePair(vector<string>* lines, int min, int max, ofstream* outfile, string currentLine, int depth){
	for(int i=0; i<lines->size(); i++){
		int wordDepth = depth + 1;
		string word = currentLine + lines->at(i);

		if(wordDepth >= min){
			// can start writing to file
			*outfile << word << endl;
		}

		if(wordDepth < max){
			// recusrion
			recursivePair(lines, min, max, outfile, word, wordDepth);
		}
	}
}