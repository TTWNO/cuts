#include "functions.h"
#include "classes.h"
#include <iostream>

void FieldsAndColumns::set_fields(vector<string> new_fields){
	fields = new_fields;
}
void FieldsAndColumns::set_filter_nums(vector<int> new_filter_nums){
	filter_nums = convert_neg_ints(new_filter_nums, fields.size());
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
	return filter_fields(this->fields, this->filter_nums);
}

vector<string> FieldsAndColumns::delimit_data_by_string(){
	this->fields = delimit_string(this->data, this->str_delimiter);
	return this->fields;
}

vector<string> FieldsAndColumns::delimit_data_by_regex(){
	this->fields = delimit_string_regex(this->data, this->re_delimiter);
	return this->fields;
}

vector<string> FieldsAndColumns::match_data_by_regex(boost::regex re){
	this->fields = regex_string(this->data, re);
	return this->fields;
}
