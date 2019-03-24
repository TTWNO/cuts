#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <boost/regex.hpp>
#include <fstream>
#include <unistd.h>
#include <sys/stat.h>
#include <stdexcept>
#include "functions.h"

using namespace std;

const boost::regex COLUMN_REGEX ("(?:(?<=-))-?\\d+|^-?\\d+");
//const boost::regex COLUMN_REGEX ("\\d+");

void FieldsAndColumns::set_fields(vector<string> new_fields){
	fields = new_fields;
}
void FieldsAndColumns::set_columns(vector<int> new_columns){
	columns = new_columns;
}
void FieldsAndColumns::set_data(string new_data){
	data = new_data;
}
void FieldsAndColumns::set_string_delimiter(string new_str_delimiter){
	str_delimiter = new_str_delimiter;
}
void FieldsAndColumns::set_regex_delimiter(boost::regex new_re_delimiter){
	re_delimiter = new_re_delimiter;
}
vector<string> FieldsAndColumns::get_fields(){return fields;};
vector<int> FieldsAndColumns::get_columns(){return columns;};
string FieldsAndColumns::get_data(){return data;};
string FieldsAndColumns::get_string_delimiter(){return str_delimiter;};
boost::regex FieldsAndColumns::get_regex_delimiter(){return re_delimiter;};

vector<string> FieldsAndColumns::get_filtered_fields(){
	vector<string> filtered_fields;
	filtered_fields.reserve(this.fields.length());
	for (int f : this.fields){
		filtered_fields.push_back(this.columns.get(f));
	}
}

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

vector<string> FieldsAndColumns::delimit_data_by_string(){
	string local_data = data;
	size_t pos = 0;
	string token;
	while ((pos = local_data.find(str_delimiter)) != string::npos){
		token = local_data.substr(0, pos);
		cout << "LOCAL_DATA: " << local_data << endl;
		cout << "TOKEN: " << token << endl;
		fields.push_back(token);
		local_data.erase(0, pos + str_delimiter.length());
	}
	fields.push_back(local_data);
	return fields;
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

vector<string> delimit_string_regex(string str, boost::regex re){
	boost::smatch match;
	boost::sregex_iterator i1(str.begin(), str.end(), re);
	boost::sregex_iterator i2;
	vector<string> delimited_by_regex;
	
	//for_each(i1, i2, [&delimited_by_regex](const boost::match_results<string::const_iterator>& results){
				
	//		prev_match = results;
	//		});

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
	cout << "SELECTION: '" << selection << "'" << endl;
	for (string sub_selection : delimit_string(selection, ",")){
		if (sub_selection.find("-") != string::npos){
		cout << "SUBSELECTION(N-): '" << sub_selection << "'" << endl;
		vector<string> column_strings = regex_string(sub_selection, COLUMN_REGEX);
		cout << "SC: '" << column_strings.at(0) << "'\nEC: '" << column_strings.at(1) << endl;;
		int start_col = stoi(column_strings.at(0));
		int end_col = stoi(column_strings.at(1));
		if (start_col > end_col){
			for (int i = start_col; i >= end_col; i--){
				cols.push_back(i);
			}
		} else {
			for (int i = start_col; i <= end_col; i++){
				cols.push_back(i);
			}	
		}}
		else {
			cols.push_back(stoi(sub_selection));
		}
	}
	return cols;
}
