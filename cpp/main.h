#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <thread>

using namespace std;

vector<string> lines;
ofstream outfile;

void recursivePair(vector<string>* lines, int min, int max, ofstream* outfile, string currentLine="", int depth=0);