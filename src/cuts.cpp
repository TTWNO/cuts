#include <iostream>
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

	for (int i = 1; i< argc; i++){
		string arg = argv[i];
		if (get_option_value("-d", arg) != ""){
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
					FieldsAndColumns fc;
					fc.set_data(sub_data);
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
	for (FieldsAndColumns fc : facs){
		const vector<string> FILTERED_FIELDS = fc.get_filtered_fields();
		for (int i = 0; i < FILTERED_FIELDS.size(); i++){
			i == FILTERED_FIELDS.size()-1 ? cout << FILTERED_FIELDS.at(i) : cout << FILTERED_FIELDS.at(i) << OUTPUT_DELIMITER;
		}
		cout << endl;
	}
	return 0;
}
