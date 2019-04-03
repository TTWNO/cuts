#include <iostream>
#include <sstream>
#include <string>
#include "classes.h"
#include "functions.h"

using namespace std;

vector<FieldsAndColumns> facs;

int main(int argc, char* argv[]){
	string FILENAME = "";
	string INPUT_DELIMITER;
	boost::regex RE_INPUT_DELIMITER;
	boost::regex DEFAULT_INPUT_DELIMITER ("[, \\t]+");
	string OUTPUT_DELIMITER = " ";
	vector<int> FIELDS;
	bool ONE_BASED_INDEXING = true;

	for (int i = 1; i< argc; i++){
		string arg = argv[i];
		if (arg == "-0"){
			ONE_BASED_INDEXING = false;
		}
		else if (get_option_value("-d", arg) != ""){
			INPUT_DELIMITER = get_option_value("-d", arg);
		}
		else if (get_option_value("-rd", arg) != ""){
			RE_INPUT_DELIMITER = get_option_value("-rd", arg);
		}
		else if (get_option_value("-D", arg) != ""){
			OUTPUT_DELIMITER = get_option_value("-D", arg);
		}
		else if (get_option_value("-f", arg) != ""){
			FIELDS = convert_columns(get_option_value("-f", arg));
		}
		// Last option always. For performance sake.
		else if (arg.find(":") != string::npos){
			vector<string> info = delimit_string(arg, ":");
			string colomns = info.at(1);
			string filename = info.at(0);
			if (file_exists(filename)){
				FILENAME = filename;
				FIELDS = convert_columns(colomns);
			}
		} else if (file_exists(arg)){
			FILENAME = arg;
		}
		if (FILENAME != ""){
			for (string sub_data : delimit_string(get_file_contents(FILENAME), "\n")){
				if (sub_data != ""){
					FILENAME = "";

					FieldsAndColumns fc;
					fc.set_data(sub_data);
					fc.one_based_indexing = ONE_BASED_INDEXING;
					if (INPUT_DELIMITER != ""){
						fc.set_string_delimiter(INPUT_DELIMITER);
						fc.delimit_data_by_string();
					} else if (RE_INPUT_DELIMITER.str() != "") {
						fc.set_regex_delimiter(RE_INPUT_DELIMITER);
						fc.delimit_data_by_regex();
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
	stringstream output;
	for (FieldsAndColumns fc : facs){
		const vector<string> FILTERED_FIELDS = fc.get_filtered_fields();
		// This reason for this is because I can't jsut clear the sstream to nothing on every loop, otherwise I lose the data. And I need to add a newline AFTER, but only if there was any data to be added. :)
		bool added_text = false;
		for (int i = 0; i < FILTERED_FIELDS.size(); i++){
			i == FILTERED_FIELDS.size()-1 ? output << FILTERED_FIELDS.at(i) : output << FILTERED_FIELDS.at(i) << OUTPUT_DELIMITER;
			added_text = true;
		}
		if (added_text){
			output << endl;
		}
	}
	cout << output.str();
	return 0;
}
