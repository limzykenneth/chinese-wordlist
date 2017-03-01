#include "main.h"

using namespace std;

static void show_usage(string name){
    cerr << "\nUsage: " << name << " <option(s)> \n\n"
		 << "Options:\n"
		 << "--min MINIMUM\tLower bound for number of words per line\n"
		 << "--max MAXIMUM\tUpper bound for number of words per line\n"
		 << "-i INFILE\tSpecify input file\n"
		 << "-o OUTFILE\tSpecify output file\n"
		 << endl;
}

int main(int argc, char* argv[]){
	unsigned int min;
	unsigned int max;
	string inputFile;
	string outputFile;

	if (argc < 9) {
		show_usage(argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; ++i) {
    	string arg = argv[i];

        if (arg == "--min") {
            if (i + 1 < argc) { // Make sure we aren't at the end of argv!
                min = atoi(argv[++i]); // Increment 'i' so we don't get the argument as the next argv[i].
            } else { // Uh-oh, there was no argument to the destination option.
                cerr << "--min option requires one argument." << std::endl;
                return 1;
            }
        } else if (arg == "--max") {
        	if (i + 1 < argc) { // Make sure we aren't at the end of argv!
                max = atoi(argv[++i]); // Increment 'i' so we don't get the argument as the next argv[i].
            } else { // Uh-oh, there was no argument to the destination option.
                cerr << "--max option requires one argument." << std::endl;
                return 1;
            }
        } else if (arg == "-i") {
        	if (i + 1 < argc) { // Make sure we aren't at the end of argv!
                inputFile = argv[++i]; // Increment 'i' so we don't get the argument as the next argv[i].
            } else { // Uh-oh, there was no argument to the destination option.
                cerr << "-i option requires one argument." << std::endl;
                return 1;
            }
        } else if (arg == "-o") {
        	if (i + 1 < argc) { // Make sure we aren't at the end of argv!
                outputFile = argv[++i]; // Increment 'i' so we don't get the argument as the next argv[i].
            } else { // Uh-oh, there was no argument to the destination option.
                cerr << "--max option requires one argument." << std::endl;
                return 1;
            }
        }
    }

	string line;
	ifstream myfile(inputFile);
	if(myfile.is_open()){
		while(getline(myfile, line)){
			lines.push_back(line);
		}
		myfile.close();
	}else{
		cout << "Unable to open file" << endl;
	}

	outfile.open(outputFile);
	recursivePair(&lines, min, max, &outfile);
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