#include <iostream>
#include <string>
#include "functions.h"
#include <catch2/catch.hpp>

using namespace std;

int main(int argc, char* argv[]){
	for (int i = 1; i< argc; i++){
		string arg = argv[i];
		if(arg == "-d" || arg == "--delimiter"){
			if (i+1 < argc){
				string dlim = argv[++i];
				cout << "Delimiter: '" << dlim << "'" << endl;
		}}
	}
	return 0;
}
