#include <iostream>
#include <string>
#include "classes.h"
#include "functions.h"

using namespace std;

vector<FieldsAndColumns> facs;

int main(int argc, char* argv[]){
	string FILENAME = "";
	string INPUT_DELIMITER;
	boost::regex DEFAULT_INPUT_DELIMITER ("[, \\t]+");
	string OUTPUT_DELIMITER = " ";
	vector<int> FIELDS;
	bool ONE_BASED_INDEXING = true;

	for (int i = 1; i< argc; i++){
		string arg = argv[i];
		cout << "ARG: '" << arg << "'" << endl;
		if (arg == "-0"){
			ONE_BASED_INDEXING = false;
		}
		else if (get_option_value("-d", arg) != ""){
			INPUT_DELIMITER = get_option_value("-d", arg);
		}
		else if (get_option_value("-D", arg) != ""){
			OUTPUT_DELIMITER = get_option_value("-D", arg);
		}
		else if (get_option_value("-f", arg) != ""){
			FIELDS = convert_columns(get_option_value("-f", arg));
			for (int f : FIELDS){
				cout << "F: " << f << endl;
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
			for (string sub_data : delimit_string(get_file_contents(FILENAME), "\n")){
				if (sub_data != ""){
					FieldsAndColumns fc;
					fc.set_data(sub_data);
					fc.one_based_indexing = ONE_BASED_INDEXING;
					if (INPUT_DELIMITER != ""){
						fc.set_string_delimiter(INPUT_DELIMITER);
						fc.delimit_data_by_string();
					} else {
						fc.set_regex_delimiter(DEFAULT_INPUT_DELIMITER);
						fc.delimit_data_by_regex();
					}
					fc.set_filter_nums(FIELDS);
					facs.push_back(fc);
				}
			}
		}
	}
	cout << "Outputting data!" << endl;
	for (FieldsAndColumns fc : facs){
		const vector<string> FILTERED_FIELDS = fc.get_filtered_fields();
		for (int i = 0; i < FILTERED_FIELDS.size(); i++){
			i == FILTERED_FIELDS.size()-1 ? cout << FILTERED_FIELDS.at(i) : cout << FILTERED_FIELDS.at(i) << OUTPUT_DELIMITER;
		}
		cout << endl;
	}
	return 0;
}
