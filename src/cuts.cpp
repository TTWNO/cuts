#include <iostream>
#include <string>
#include "functions.h"

using namespace std;

int main(int argc, char* argv[]){
	for (int i = 1; i< argc; i++){
		string arg = argv[i];
		if(arg == "-d" || arg == "-t" || arg == "-s"){
			if (i+1 < argc){
				string dlim = argv[++i];
				cout << "Input delimiter: '" << dlim << "'" << endl;
			}
		}
		if (arg == "-D" || arg == "-T" || arg == "-S"){
			if (i+1 < argc){
				string dlim = argv[++i];
				cout << "Output delimiter: '" << dlim << "'" << endl;
			}
		}
		// Last option always. For performance sake.
		if (arg.find(":") != string::npos){
			cout << "Colon mode!" << endl;
			vector<string> info = delimit_string(arg, ":");
			string colomns = info.at(1);
			string filename = info.at(0);
			if (file_exists(filename)){
				cout << "File: " << filename << endl;
				cout << "Coloumns: " << colomns << endl;
			}
		}
		if (file_exists(arg)){
			cout << "File: " << arg << endl;
		}
	}
	return 0;
}
