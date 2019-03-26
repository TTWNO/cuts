#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <boost/regex.hpp>
#include <fstream>
#include <unistd.h>
#include <sys/stat.h>
#include <stdexcept>
#include <cmath>
#include "functions.h"

using namespace std;

const boost::regex COLUMN_REGEX ("(?:(?<=-))-?\\d+|^-?\\d+");

void log(string info){
	ofstream log_file("log.txt", ios_base::app);
	log_file << info;
	log_file.close();
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

vector<string> filter_fields(vector<string> ds, vector<int> cols, bool one_based_indexing){
	vector<string> filtered_cols;
	filtered_cols.resize(cols.size());

	transform(cols.begin(), cols.end(), filtered_cols.begin(),
			[&,ds](int col) -> string {
				if (col < 0){
					//TODO handle overly negative ints e.g. -4 when ds.size()==3.
					return ds.at(-(abs(col) % ds.size()) + ds.size()-1);
				} else if (col > ds.size()){
					return "";
				} else {
					return one_based_indexing ? ds.at(col-1) : ds.at(col);
				}
			}
		     );
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
		fielded_multiline.push_back(filter_fields(deline, cols));
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

vector<string> delimit_string_regex(string str, boost::regex re){
	boost::smatch match;
	boost::sregex_iterator i1(str.begin(), str.end(), re);
	boost::sregex_iterator i2;
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

vector<string> regex_string(string str, boost::regex re){
	boost::smatch match;
	boost::sregex_iterator i1(str.begin(), str.end(), re);
	boost::sregex_iterator i2;
	vector<string> regexed_segments;

	for_each(i1, i2, [&regexed_segments](const boost::match_results<string::const_iterator>& results){
				regexed_segments.push_back(results[0]);
			});
	return regexed_segments;
}

vector<int> convert_columns(string selection){
	vector<int> cols;
	for (string sub_selection : delimit_string(selection, ",")){
		int find_dash = sub_selection.find("-", 1);
		if (find_dash != string::npos && find_dash != 0){
			vector<string> column_strings = regex_string(sub_selection, COLUMN_REGEX);
			int start_col = stoi(column_strings.at(0));
			cout << "SC: " << start_col << endl;
			int end_col = stoi(column_strings.at(1));
			if (start_col > end_col){
				for (int i = start_col; i >= end_col; i--){
					cols.push_back(i);
				}
			} else {
				for (int i = start_col; i <= end_col; i++){
					cols.push_back(i);
				}	
			}
		} else {
			cout << "SL: " << sub_selection << endl;
			cols.push_back(stoi(sub_selection));
		}
	}
	return cols;
}
