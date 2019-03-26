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

vector<string> filter_fields(vector<string> ds, vector<int> cols, bool one_based_indexing=true);

vector<vector<string>> delimit_multiline(string str, string delimiter);
vector<vector<string>> get_multiline_fields(vector<vector<string>> dms, vector<int> fields);
bool file_exists(const string &filename);
string get_file_contents(string filename);
vector<string> delimit_string_regex(string str, boost::regex re);
vector<string> regex_string(string str, boost::regex re);

vector<int> convert_columns(string selection);
#endif
