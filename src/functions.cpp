#include <catch2/catch.hpp>
#include "functions.h"
#include <iostream>
#include <string>
#include <vector>
#include <tuple>

using namespace std;

tuple<int, int> convert_negative_fields(tuple<int, int> negInts, int sizeOf){
	tuple<int, int> converted_fields = make_tuple(get<0>(negInts) + sizeOf, get<1>(negInts) + sizeOf);
	return converted_fields;
}

vector<string> delimit_line(string str, string delimiter){
	vector<string> delimitedString;
	size_t pos = 0;
	string token;
	while ((pos = str.find(delimiter)) != string::npos){
		token = str.substr(0, pos);
		delimitedString.push_back(token);
		str.erase(0, pos + delimiter.length());
	}
	// Due to the str.erase(), the remaining string contains the last bit of delimited text.
	delimitedString.push_back(str);
	return delimitedString;
}

vector<string> get_fields(vector<string> delimitedStr, tuple<int, int> startAndEnd){
	int start, end;
	tie(start, end) = startAndEnd;
	if (start < 0 || end < 0){
		tie(start, end) = convert_negative_fields(startAndEnd, delimitedStr.size());
	}
	vector<string> fields;
	if (start > end){
		for (int i = delimitedStr.size()-1; i >= 0; i--){
			if (i <= start && i >= end){
			
			fields.push_back(delimitedStr.at(i));
		}}
	}
	else{
	for(int i = 0; i < delimitedStr.size(); i++){
		if (i >= start && i <= end){
			fields.push_back(delimitedStr.at(i));
		}
	}}
	return fields;
}

vector<vector<string>> delimit_multiline(string str, string delimiter){
	vector<vector<string>> delimitedString;
	vector<string> lines = delimit_line(str, "\n");
	for (string line : lines){
		delimitedString.push_back(delimit_line(line, delimiter));
	}
	return delimitedString;
}
