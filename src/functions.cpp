#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <algorithm>
#include <regex>
#include <fstream>
#include <unistd.h>
#include <sys/stat.h>

using namespace std;

tuple<int, int> convert_negative_fields(tuple<int, int> negInts, int sizeOf){
	tuple<int, int> converted_fields = make_tuple(get<0>(negInts) + sizeOf, get<1>(negInts) + sizeOf);
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

vector<string> get_fields(vector<string> ds, tuple<int, int> startAndEnd){
	int start, end;
	tie(start, end) = startAndEnd;
	if (start < 0 || end < 0){
		tie(start, end) = convert_negative_fields(startAndEnd, ds.size());
	}
	vector<string> fielded;
	if (start > end){
		for (int i = ds.size()-1; i >= 0; i--){
			if (i <= start && i >= end){
				fielded.push_back(ds.at(i));
			}
		}
	}else{
		for(int i = 0; i < ds.size(); i++){
			if (i >= start && i <= end){
				fielded.push_back(ds.at(i));
			}
		}
	}
	return fielded;
}

vector<vector<string>> delimit_multiline(string str, string delimiter){
	vector<vector<string>> delimited_string;
	vector<string> lines = delimit_string(str, "\n");
	for (string line : lines){
		delimited_string.push_back(delimit_string(line, delimiter));
	}
	return delimited_string;
}

vector<vector<string>> get_multiline_fields(vector<vector<string>> dms, tuple<int, int> fields){
	vector<vector<string>> fielded_multiline;
	for (vector<string> deline : dms){
		fielded_multiline.push_back(get_fields(deline, fields));
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
