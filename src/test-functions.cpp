#include <catch2/catch.hpp>
#include "functions.h"

using namespace std;

const string INPUT1="Test1,Test2,Test3";
const string DEL1=",";
const vector<string> OUTPUT1 = {"Test1", "Test2", "Test3"};

const string INPUT2="Testw/longdelimitTest2w/longdelimitTest3w/longdelimitTest4";
const string DEL2="w/longdelimit";
const vector<string> OUTPUT2 = {"Test", "Test2", "Test3", "Test4"};

const string INPUT3="Test1,Test2,Test3,";
const string DEL3=",";
const vector<string> OUTPUT3 = {"Test1", "Test2", "Test3", ""};

const string INPUT4="Test7,Test8,Test9,";
const string DEL4=",";
const vector<string> OUTPUT4 = {"Test7", "Test8", "Test9", ""};
const tuple<int, int> F_INPUT4_1_INDEXES = make_tuple(0, 2);
const vector<string> F_OUTPUT4 = {"Test7", "Test8", "Test9"};
const tuple<int, int> F_INPUT4_2_INDEXES = make_tuple(1, 1);
const vector<string> F_OUTPUT4_2 = {"Test8"};
const tuple<int, int> F_INPUT4_3_INDEXES = make_tuple(-3, -2);
const vector<string> F_OUTPUT4_3 = {"Test8", "Test9"};
const tuple<int, int> F_INPUT4_4_INDEXES = make_tuple(-2, -3);
const vector<string> F_OUTPUT4_4 = {"Test9", "Test8"};

const tuple<int, int> NEG_FIELDS1 = make_tuple(-1, -3);
const int FIELDS_SIZE1 = 15;
const tuple<int, int> POS_FIELDS1 = make_tuple(14, 12);

const tuple<int, int> NEG_FIELDS2 = make_tuple(-12, -2);
const int FIELDS_SIZE2 = 13;
const tuple<int, int> POS_FIELDS2 = make_tuple(1, 11);

const tuple<int, int> NEG_FIELDS3 = make_tuple(-5, -2);
const int FIELDS_SIZE3 = 4;
const tuple<int, int> POS_FIELDS3 = make_tuple(-1, 2);

const string MULTILINE_INPUT1 = "Test1,Test2\nTest3,Test4";
const string MULTILINE_DEL1 = ",";
const vector<vector<string>> MULTILINE_OUTPUT1 = {
	{"Test1", "Test2"},
	{"Test3", "Test4"}
};
const tuple<int, int> MULTILINE_FIELDS1 = make_tuple(0, 0);
const vector<vector<string>> MULTILINE_OUTPUT1_FIELDED = {
	{"Test1"},
	{"Test3"}
};


const string FILE1_NAME = "tests/test_file1.txt";
const string FILE1_TEXT = "I, Tait, am getting old.\nPlease, I beg, take care of my children.";
const vector<vector<string>> FILE1_OUTPUT = {
	{"I", " Tait", " am getting old."},
	{"Please", " I beg", " take care of my children."}
};

const string REGEX_INPUT1 = "Hello, my name is Fernando. Please see to it that my, may I say quite exquisite, horses are attended to.";
// This regex finds any comma or period followed by 0 or 1 spaces.
const regex REGEX_INPUT1_REGEX ("[,.] ?");
const vector<string> REGEX_OUTPUT1 = {"Hello", "my name is Fernando", "Please see to it that my", "may I say quite exquisite", "horses are attended to"};

// This regex finds any alphabet characters with 2 or more in sequential order.
const regex REGEX_INPUT1_REGEX2 ("([A-Za-z])\\1+");
const vector<string> REGEX_OUTPUT1_REGEX2 = {"He", "o, my name is Fernando. Please s", " to it that my, may I say quite exquisite, horses are a", "ended to."};

const string REGEX_INPUT2 = "I. am. not. pleased.";
// This regex find any period followed by one or zero spaces.
const regex REGEX_INPUT2_REGEX ("[.] ?");
const vector<string> REGEX_OUTPUT2 = {"I", "am", "not", "pleased"};

const string REGEX_INPUT3 = "...the decision can be made by people [...] of 18 years or over...";
// This regex will find any set of 3 periods that optionally have either ' [' preceeding, or '] ' secceeding.
const regex REGEX_INPUT3_REGEX ("(\\s\\[)?\\.{3}(\\]\\s)?");
const vector<string> REGEX_OUTPUT3 = {"", "the decition can be made by people of", "18 years and over", ""};


TEST_CASE("convert_negative_fields() tests.", "[convert_negative_fields]"){
	REQUIRE(convert_negative_fields(NEG_FIELDS1, FIELDS_SIZE1) == POS_FIELDS1);
	REQUIRE(convert_negative_fields(NEG_FIELDS2, FIELDS_SIZE2) == POS_FIELDS2);
}
TEST_CASE("convert_negative_fields() tests with overly negative integers", "[convert_negative_fields]"){
	REQUIRE(convert_negative_fields(NEG_FIELDS3, FIELDS_SIZE3) == POS_FIELDS3);
}
TEST_CASE("delimit_line() single character tests.", "[delimit_line]"){
	REQUIRE(delimit_line(INPUT1, DEL1) == OUTPUT1);
}
TEST_CASE("delimit_line() multi character tests.", "[delimit_line]"){
	REQUIRE(delimit_line(INPUT2, DEL2) == OUTPUT2);
}
TEST_CASE("delimit_line() multi character hanging tests.", "[delimit_line]"){
	REQUIRE(delimit_line(INPUT3, DEL3) == OUTPUT3);
}
TEST_CASE("delimit_line() single character hanging tests.", "[delimit_line]"){
	REQUIRE(delimit_line(INPUT4, DEL4) == OUTPUT4);
}
TEST_CASE("get_fields() tests.", "[get_fields]"){
	REQUIRE(get_fields(delimit_line(INPUT4, DEL4), F_INPUT4_1_INDEXES) == F_OUTPUT4);
	REQUIRE(get_fields(delimit_line(INPUT4, DEL4), F_INPUT4_2_INDEXES) == F_OUTPUT4_2);
}
TEST_CASE("get_fields() tests w/ negative ints", "[get_fields]"){
	REQUIRE(get_fields(delimit_line(INPUT4, DEL4), F_INPUT4_3_INDEXES) == F_OUTPUT4_3);
}
TEST_CASE("get_fields() tests w/ negative ints w/ incorrect ordering", "[get_fields]"){
	REQUIRE(get_fields(delimit_line(INPUT4, DEL4), F_INPUT4_4_INDEXES) == F_OUTPUT4_4);
}
TEST_CASE("delimit_multiline_string() tests.", "[delimit_multiline_string]"){
	REQUIRE(delimit_multiline(MULTILINE_INPUT1, MULTILINE_DEL1) == MULTILINE_OUTPUT1);
	REQUIRE(delimit_multiline(FILE1_TEXT, ",") == FILE1_OUTPUT);
}
TEST_CASE("get_multiline_fields() tests.", "[get_multiline_fields]"){
	REQUIRE(get_multiline_fields(MULTILINE_OUTPUT1, MULTILINE_FIELDS1) == MULTILINE_OUTPUT1_FIELDED);
}

TEST_CASE("get_file_contents() tests.", "[get_file_contents]"){
	REQUIRE(get_file_contents(FILE1_NAME) == FILE1_TEXT);
}
TEST_CASE("delimit_string_regex() tests.", "[delimit_string_regex]"){
	REQUIRE(delimit_string_regex(REGEX_INPUT1, REGEX_INPUT1_REGEX) == REGEX_OUTPUT1);
	REQUIRE(delimit_string_regex(REGEX_INPUT1, REGEX_INPUT1_REGEX2) == REGEX_OUTPUT1_REGEX2);
	REQUIRE(delimit_string_regex(REGEX_INPUT2, REGEX_INPUT2_REGEX) == REGEX_OUTPUT2);
}
