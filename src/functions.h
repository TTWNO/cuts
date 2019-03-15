#include <vector>
#include <tuple>
#include <string>

using namespace std;

int test_get_1();
string get_input();

tuple<int, int> convert_negative_fields(tuple<int, int> negInts, int sizeOf);

vector<string> delimit_line(string str, string delimiter);

vector<string> get_fields(vector<string> ds, tuple<int, int> startAndEnd);

vector<vector<string>> delimit_multiline(string str, string delimiter);
vector<vector<string>> get_multiline_fields(vector<vector<string>> dms, tuple<int, int> fields);
string get_file_contents(string filename);
