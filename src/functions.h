#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <vector>
#include <tuple>
#include <string>
#include <boost/regex.hpp>

using namespace std;

int test_get_1();
string get_input();

vector<string> delimit_string(string str, string delimiter);

vector<string> get_fields(vector<string> ds, vector<int> cols);

vector<vector<string>> delimit_multiline(string str, string delimiter);
vector<vector<string>> get_multiline_fields(vector<vector<string>> dms, vector<int> fields);
bool file_exists(const string &filename);
string get_file_contents(string filename);
vector<string> delimit_string_regex(string str, boost::regex re);
vector<string> regex_string(string str, boost::regex re);

vector<int> convert_columns(string selection);

class FieldsAndColumns {
	vector<int> filter_nums;
	vector<string> fields;
	vector<string> filtered_fields;
	string data;
	string str_delimiter;
	boost::regex re_delimiter;
	public:
		void set_fields(vector<string> new_fields);
		void set_filter_nums(vector<int> new_columns);
		void set_string_delimiter(string new_str_delimiter);
		void set_data(string new_data);
		void set_regex_delimiter(boost::regex re);

		vector<string> get_fields();
		string get_data();
		boost::regex get_regex_delimiter();
		vector<string> delimit_data_by_string();
		vector<int> get_filter_nums();
		string get_string_delimiter();

		vector<string> delimit_data_by_regex();
		vector<string> match_data_by_regex(boost::regex re);
		vector<string> get_filtered_fields();
};
#endif
