#include <vector>
#include <tuple>
#include <string>
#include <regex>

using namespace std;

int test_get_1();
string get_input();

vector<int> convert_negative_fields(vector<int> negCols, int sizeOf);

vector<string> delimit_string(string str, string delimiter);

vector<string> get_fields(vector<string> ds, vector<int> cols);

vector<vector<string>> delimit_multiline(string str, string delimiter);
vector<vector<string>> get_multiline_fields(vector<vector<string>> dms, vector<int> fields);
bool file_exists(const string &filename);
string get_file_contents(string filename);
vector<string> delimit_string_regex(string str, regex re);
