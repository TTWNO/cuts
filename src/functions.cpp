#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <regex>
#include <fstream>
#include <unistd.h>
#include <sys/stat.h>
#include <stdexcept>

using namespace std;

vector<int> convert_negative_fields(vector<int> negCols, int sizeOf){
	vector<int> converted_fields;
	for (int col : negCols){
		if (col < 0){
			converted_fields.push_back(col + sizeOf);
		} else {
			converted_fields.push_back(col);
		}
	}
	return converted_fields;
}

vector<string> delimit_string(string str, string delimiter){
	vector<string> delimited_string;
	size_t pos = 0;
	string token;
	while ((pos = str.find(delimiter)) != string::npos){
		token = str.substr(0, pos);
		delimited_string.push_back(token);
		str.erase(0, pos + delimiter.length());
	}
	// Due to the str.erase(), the remaining string contains the last bit of delimited text.
	delimited_string.push_back(str);
	return delimited_string;
}

vector<string> get_fields(vector<string> ds, vector<int> cols){
	vector<string> filtered_cols;
	for (int col : cols)
	{
		if (col < 0){
			throw invalid_argument("Column cannot be begative.");
		} else if (col > ds.size()-1){
			throw invalid_argument("Column cannot be longer than the columns to choose from.");
		}
		filtered_cols.push_back(ds.at(col));
	}
	return filtered_cols;
}

vector<vector<string>> delimit_multiline(string str, string delimiter){
	vector<vector<string>> delimited_string;
	vector<string> lines = delimit_string(str, "\n");
	for (string line : lines){
		delimited_string.push_back(delimit_string(line, delimiter));
	}
	return delimited_string;
}

vector<vector<string>> get_multiline_fields(vector<vector<string>> dms, vector<int> cols){
	vector<vector<string>> fielded_multiline;
	for (vector<string> deline : dms){
		fielded_multiline.push_back(get_fields(deline, cols));
	}
	return fielded_multiline;
}

bool file_exists(const string& filename){
	struct stat buffer;
	return (stat (filename.c_str(), &buffer) == 0);
}

string get_file_contents(string filename){
	ifstream ifs(filename);
	string content;
	content.assign(
			(istreambuf_iterator<char>(ifs)),
			(istreambuf_iterator<char>()));
	return content;
}

vector<string> delimit_string_regex(string str, regex re){
	smatch match;
	vector<string> delimited_by_regex;
	while(regex_search(str, match, re)){
		delimited_by_regex.push_back(match.prefix());
		str = match.suffix().str();
	}
	if (str != ""){
		delimited_by_regex.push_back(str);
	}
	return delimited_by_regex;
}
