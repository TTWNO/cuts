#include <iostream>
#include <string>
#include "classes.h"
#include "functions.h"

using namespace std;

vector<FieldsAndColumns> facs;

int main(int argc, char* argv[]){
	string FILENAME = "";
	string INPUT_DELIMITER;
	string OUTPUT_DELIMITER;
	vector<int> FIELDS;

	for (int i = 1; i< argc; i++){
		string arg = argv[i];
		if(arg == "-d" || arg == "-t" || arg == "-s"){
			if (i+1 < argc){
				string dlim = argv[++i];
				INPUT_DELIMITER = dlim;
				cout << "Input delimiter: '" << dlim << "'" << endl;
			}
		}
		else if (arg == "-D" || arg == "-T" || arg == "-S"){
			if (i+1 < argc){
				string dlim = argv[++i];
				OUTPUT_DELIMITER = dlim;
				cout << "Output delimiter: '" << dlim << "'" << endl;
			}
		}
		else if (arg == "-c" || arg == "--columms"){
			if (i+1 < argc){
				string cols = argv[++i];
				cout << "Columns: " << cols << endl;
				FIELDS = convert_columns(cols);
			}
		}
		// Last option always. For performance sake.
		else if (arg.find(":") != string::npos){
			cout << "Colon mode!" << endl;
			vector<string> info = delimit_string(arg, ":");
			string colomns = info.at(1);
			string filename = info.at(0);
			if (file_exists(filename)){
				FILENAME = filename;
				cout << "File: " << filename << endl;
				FIELDS = convert_columns(colomns);
				cout << "Coloumns: " << colomns << endl;
			}
		} else if (file_exists(arg)){
			FILENAME = arg;
			cout << "File: " << arg << endl;
			cout << "Contents: " << get_file_contents(arg) << endl;
		}
		if (FILENAME != ""){
			cout << "Filename: " << FILENAME << endl;
			FieldsAndColumns fc;
			fc.set_data(get_file_contents(FILENAME));
			fc.set_string_delimiter(INPUT_DELIMITER);
			fc.set_filter_nums(FIELDS);
			fc.delimit_data_by_string();
			facs.push_back(fc);
		}
	}
	for (FieldsAndColumns fc : facs){
		for (string s : fc.get_filtered_fields()){
			cout << "S: " << s << endl;
		}
	}
	return 0;
}
