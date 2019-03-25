#include "classes.h"
#include <iostream>

void FieldsAndColumns::set_fields(vector<string> new_fields){
	fields = new_fields;
}
void FieldsAndColumns::set_filter_nums(vector<int> new_filter_nums){
	filter_nums = new_filter_nums;
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
vector<int> FieldsAndColumns::get_filter_nums(){return filter_nums;};
string FieldsAndColumns::get_data(){return data;};
string FieldsAndColumns::get_string_delimiter(){return str_delimiter;};
boost::regex FieldsAndColumns::get_regex_delimiter(){return re_delimiter;};

vector<string> FieldsAndColumns::get_filtered_fields(){
	vector<string> filtered_columns;
	filtered_columns.reserve(filter_nums.size());
	for (int f : filter_nums){
		try{
			filtered_columns.push_back(fields.at(f-1));
		} catch (const exception& ex) {
			filtered_columns.push_back("");
		}
	}
	return filtered_columns;
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
