#include <string>
#include <vector>
#include <boost/regex.hpp>

using namespace std;

class FieldsAndColumns {
	vector<signed int> filter_nums;
	vector<string> fields;
	vector<string> filtered_fields;
	string data;
	string str_delimiter;
	boost::regex re_delimiter;
	public:
		bool one_based_indexing = false;
		void set_fields(vector<string> new_fields);
		void set_filter_nums(vector<int> new_columns);
		void set_string_delimiter(string new_str_delimiter);
		void set_data(string new_data);
		void set_regex_delimiter(boost::regex re);

		vector<string> get_fields();
		string get_data();
		boost::regex get_regex_delimiter();
		vector<string> delimit_data_by_string();
		vector<signed int> get_filter_nums();
		string get_string_delimiter();

		vector<string> delimit_data_by_regex();
		vector<string> match_data_by_regex(boost::regex re);
		vector<string> get_filtered_fields();
};


class File {
	public:
		string name;
		string contents;
		FieldsAndColumns fields_and_columns;
};
