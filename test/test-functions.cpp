#include "catch.hpp"
#include "functions.h"

using namespace std;

const string INPUT1="Test1,Test2,Test3";
const string DEL1=",";
const vector<string> OUTPUT1 = {"Test1", "Test2", "Test3"};
const vector<int> INPUT1_FIELDS = {0, 1, 7};
const vector<string> OUTPUT1_FILTERED = {"Test1", "Test2", ""};
const vector<int> INPUT1_FIELDS2 = {0, 2};
const vector<string> OUTPUT1_FILTERED2 = {"Test1", "Test3"};
const vector<int> INPUT1_OVERLY_NEG_FIELDS = {-4, -3};
const vector<int> INPUT1_OVERLY_NEG_FIXED_FIELDS = {2, 0};
const vector<string> OUTPUT1_OVERLY_NEG_FIELDS = {"Test3", "Test1"};

const string INPUT2="Testw/longdelimitTest2w/longdelimitTest3w/longdelimitTest4";
const string DEL2="w/longdelimit";
const vector<string> OUTPUT2 = {"Test", "Test2", "Test3", "Test4"};

const string INPUT3="Test1,Test2,Test3,";
const string DEL3=",";
const vector<string> OUTPUT3 = {"Test1", "Test2", "Test3", ""};

const string INPUT4="Test7,Test8,Test9,";
const string DEL4=",";
const vector<string> OUTPUT4 = {"Test7", "Test8", "Test9", ""};
const vector<int> F_INPUT4_1_INDEXES = {0, 1, 2};
const vector<string> F_OUTPUT4 = {"Test7", "Test8", "Test9"};
const vector<int> F_INPUT4_2_INDEXES = {1};
const vector<string> F_OUTPUT4_2 = {"Test8"};
const vector<int> F_INPUT4_3_INDEXES = {-3, -2};
const vector<string> F_OUTPUT4_3 = {"Test8", "Test9"};
const vector<int> F_INPUT4_4_INDEXES = {-2, -3};
const vector<string> F_OUTPUT4_4 = {"Test9", "Test8"};

const vector<int> NEG_FIELDS1 = {-1, -3};
const int FIELDS_SIZE1 = 15;
const vector<int> POS_FIELDS1 = {14, 12};

const vector<int> NEG_FIELDS2 = {-12, -2};
const int FIELDS_SIZE2 = 13;
const vector<int> POS_FIELDS2 = {0, 11};

const vector<int> NEG_FIELDS3 = {-5, -2};
const int FIELDS_SIZE3 = 4;
const vector<int> POS_FIELDS3 = {3, 2};

const string MULTILINE_INPUT1 = "Test1,Test2\nTest3,Test4";
const string MULTILINE_DEL1 = ",";
const vector<vector<string>> MULTILINE_OUTPUT1 = {
	{"Test1", "Test2"},
	{"Test3", "Test4"}
};
const vector<int> MULTILINE_FIELDS1 = {1};
const vector<vector<string>> MULTILINE_OUTPUT1_FIELDED = {
	{"Test1"},
	{"Test3"}
};


const string FILE1_NAME = "test_file1.txt";
const string FILE1_TEXT = "I, Tait, am getting old.\nPlease, I beg, take care of my children.";
const vector<vector<string>> FILE1_OUTPUT = {
	{"I", " Tait", " am getting old."},
	{"Please", " I beg", " take care of my children."}
};

const string REGEX_INPUT1 = "Hello, my name is Fernando. Please see to it that my, may I say quite exquisite, horses are attended to.";
// This boost::regex finds any comma or period followed by 0 or 1 spaces.
const boost::regex REGEX_INPUT1_REGEX ("[,.] ?");
const vector<string> REGEX_OUTPUT1 = {"Hello", "my name is Fernando", "Please see to it that my", "may I say quite exquisite", "horses are attended to"};

// This boost::regex finds any alphabet characters with 2 or more in sequential order.
const boost::regex REGEX_INPUT1_REGEX2 ("([A-Za-z])\\1+");
const vector<string> REGEX_OUTPUT1_REGEX2 = {"He", "o, my name is Fernando. Please s", " to it that my, may I say quite exquisite, horses are a", "ended to."};

const string REGEX_INPUT2 = "I. am. not. pleased.";
// This boost::regex find any period followed by one or zero spaces.
const boost::regex REGEX_INPUT2_REGEX ("[.] ?");
const vector<string> REGEX_OUTPUT2 = {"I", "am", "not", "pleased"};

const string REGEX_INPUT3 = "...the decision can be made by people [...] of 18 years or over...";
// This boost::regex will find any set of 3 periods that optionally have either ' [' preceeding, or '] ' secceeding.
const boost::regex REGEX_INPUT3_REGEX ("(\\s\\[)?\\.{3}(\\]\\s)?");
const vector<string> REGEX_OUTPUT3 = {"", "the decision can be made by people of", "18 years and over", ""};
const boost::regex REGEX_INPUT3_REGEX2 ("\\w+|^.{3}");
const vector<string> REGEX_OUTPUT3_REGEX2 {"...", "the", "decision", "can", "be", "made", "by", "people", "of", "18", "years", "or", "over"};

const string FAKE_FILENAME = "superlongstupidfilename_whywouldanyonehavethisfilename.russia.zip.txt.org.co.uk.gov";

const string COLS1_SELECT = "0-5";
const string COLS2_SELECT = "1,2,6";
const string COLS3_SELECT = "1,5-7";
const string COLS4_SELECT = "7-5,0-1";
const string COLS5_SELECT = "-2-4";
const string COLS6_SELECT = "4--2";
const string COLS7_SELECT = "-2--4";

const vector<int> COLS1_VECTOR = {0, 1, 2, 3, 4, 5};
const vector<int> COLS2_VECTOR = {1, 2, 6};
const vector<int> COLS3_VECTOR = {1, 5, 6, 7};
const vector<int> COLS4_VECTOR = {7, 6, 5, 0, 1};
const vector<int> COLS5_VECTOR = {-2, -1, 0, 1, 2, 3, 4};
const vector<int> COLS6_VECTOR = {4, 3, 2, 1, 0, -1, -2};
const vector<int> COLS7_VECTOR = {-2, -3, -4};

const string COLS1_STRING = "What are you looking for?";
const vector<string> COLS1_DELIMITED = {"What", "are", "you", "looking", "for?"};

const string COLS2_STRING = "I am looking for a good time. A very good time.";
const vector<string> COLS2_DELIMITED = {"am", "looking", "time."};

const string COLS3_STRING = "Then why don't you do something already? Coward!";
const vector<string> COLS3_DELIMITED = {"why", "something", "already?", "Coward!"};

const string COLS4_STRING = "Because I'm scared of rejection. Silly girl!";
const vector<string> COLS4_DELIMITED = {"girl!", "silly", "rejection.", "Because", "I'm"};

TEST_CASE("delimit_string single character tests", "[delimit_string]"){
	REQUIRE(delimit_string(INPUT1, DEL1) == OUTPUT1);
}

TEST_CASE("convert_neg_int tests.", "[convert_neg_int]"){
	REQUIRE(convert_neg_ints(NEG_FIELDS1, FIELDS_SIZE1) == POS_FIELDS1);
	REQUIRE(convert_neg_ints(NEG_FIELDS2, FIELDS_SIZE2) == POS_FIELDS2);
	REQUIRE(convert_neg_ints(NEG_FIELDS3, FIELDS_SIZE3) == POS_FIELDS3);
	REQUIRE(convert_neg_ints(INPUT1_FIELDS2, 4) == INPUT1_FIELDS2);
}

TEST_CASE("convert_neg_int tests with overly negative ints.", "[convert_neg_int]"){
	REQUIRE(convert_neg_ints(INPUT1_OVERLY_NEG_FIELDS, 3) == INPUT1_OVERLY_NEG_FIXED_FIELDS);
}

TEST_CASE("delimit_string multi-character tests.", "[delimit_string]"){
	REQUIRE(delimit_string(INPUT2, DEL2) == OUTPUT2);
}

TEST_CASE("delimit_string multi-character hanging tests.", "[delimit_string]"){
	REQUIRE(delimit_string(INPUT3, DEL3) == OUTPUT3);
}

TEST_CASE("delimit_string single character hanging tests.", "[delimit_string]"){
	REQUIRE(delimit_string(INPUT4, DEL4) == OUTPUT4);
}

TEST_CASE("filter_fields tests.", "[filter_fields]"){
	REQUIRE(filter_fields(OUTPUT1, INPUT1_FIELDS) == OUTPUT1_FILTERED);
	REQUIRE(filter_fields(OUTPUT1, INPUT1_FIELDS2) == OUTPUT1_FILTERED2);
	REQUIRE(filter_fields(delimit_string(INPUT4, DEL4), F_INPUT4_1_INDEXES) == F_OUTPUT4);
	REQUIRE(filter_fields(delimit_string(INPUT4, DEL4), F_INPUT4_2_INDEXES) == F_OUTPUT4_2);
}
TEST_CASE("filter_fields test with overly negative ints tests.", "[filter_fields]"){
	REQUIRE(filter_fields(OUTPUT1, INPUT1_OVERLY_NEG_FIELDS) == OUTPUT1_OVERLY_NEG_FIELDS);
}

TEST_CASE("delimit_multiline_string tests.", "[delimit_multiline_string]"){
	REQUIRE(delimit_multiline(MULTILINE_INPUT1, MULTILINE_DEL1) == MULTILINE_OUTPUT1);
	REQUIRE(delimit_multiline(FILE1_TEXT, ",") == FILE1_OUTPUT);
}

TEST_CASE("get_multiline_fields tests.", "[get_multiline_fields]"){
	REQUIRE(get_multiline_fields(MULTILINE_OUTPUT1, MULTILINE_FIELDS1) == MULTILINE_OUTPUT1_FIELDED);
}

TEST_CASE("get_file_contents tests.", "[get_file_contents]"){
	REQUIRE(get_file_contents(FILE1_NAME) == FILE1_TEXT);
}

TEST_CASE("delimit_string_regex tests.", "[delimit_string]"){
	REQUIRE(delimit_string_regex(REGEX_INPUT1, REGEX_INPUT1_REGEX) == REGEX_OUTPUT1);
	REQUIRE(delimit_string_regex(REGEX_INPUT1, REGEX_INPUT1_REGEX2) == REGEX_OUTPUT1_REGEX2);
	REQUIRE(delimit_string_regex(REGEX_INPUT2, REGEX_INPUT2_REGEX) == REGEX_OUTPUT2);
}

TEST_CASE("regex_string a.k.a. match regex tests", "[regex_string]"){
	REQUIRE(regex_string(REGEX_INPUT3, REGEX_INPUT3_REGEX2) == REGEX_OUTPUT3_REGEX2);
}

TEST_CASE("file_exists tests.", "[file_exists]"){
	REQUIRE(file_exists(FILE1_NAME) == true);
	REQUIRE(file_exists(FAKE_FILENAME) == false);
}

TEST_CASE("convert_columns tests.", "[convert_columns]"){
	REQUIRE(convert_columns(COLS1_SELECT) == COLS1_VECTOR);
	REQUIRE(convert_columns(COLS2_SELECT) == COLS2_VECTOR);
	REQUIRE(convert_columns(COLS3_SELECT) == COLS3_VECTOR);
	REQUIRE(convert_columns(COLS4_SELECT) == COLS4_VECTOR);
}

TEST_CASE("convert_columns tests with negative integer ranges.", "[convert_columns]"){
	REQUIRE(convert_columns(COLS5_SELECT) == COLS5_VECTOR);
	REQUIRE(convert_columns(COLS6_SELECT) == COLS6_VECTOR);
}
