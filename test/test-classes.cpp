#include "catch.hpp"
#include "classes.h"

using namespace std;

string INPUT1 = "Test1,Test2,Test3";
string DEL1 = ",";
vector<string> OUTPUT1 = {"Test1", "Test2", "Test3"};

string INPUT2 = "Hello, my name is Tait\nAnd    I am  very  tired\nWeeee this    is   ,   fun.";
vector<string> OUTPUT2 = {"Hello", "my", "name", "is", "Tait", "And", "I", "am", "very", "tired", "Weeee", "this", "is", "fun."};
boost::regex REGEX2 ("[, \n]+");
vector<string> OUTPUT2_REGEX_MATCH = {", ", " ", " ", " ", "\n", "    ", " ", "  ", "  ", "\n", " ", "    ", "   ,   "};

TEST_CASE("FieldsAndColumns::delimit_data_by_string tests.", "[FieldsAndColumns::delimit_data_by_string]"){
	FieldsAndColumns fac;
	fac.set_data(INPUT1);
	fac.set_string_delimiter(DEL1);
	REQUIRE(fac.delimit_data_by_string() == OUTPUT1);
}

TEST_CASE("FieldsAndColumns::get_filtered_fields tests.", "[FieldsAndColumns::get_filtered_fields]"){
	FieldsAndColumns fc;
	fc.set_data(INPUT1);
	fc.set_string_delimiter(DEL1);
	vector<int> filter_nums = {1, 3};
	vector<string> OUTPUT1_2 = {"Test1", "Test3"};
	fc.set_filter_nums(filter_nums);
	fc.delimit_data_by_string();
	REQUIRE(fc.get_filtered_fields() == OUTPUT1_2);
}

TEST_CASE("FieldsAndColumns::get_filtered_fields tests with non-referenceable columns.", "[FieldsAndColumns::get_filtered_fields]"){
	FieldsAndColumns fc;
	fc.set_data(INPUT1);
	fc.set_string_delimiter(DEL1);
	vector<int> filter_nums = {1, 8};
	vector<string> OUTPUT1_3 = {"Test1", ""};
	fc.set_filter_nums(filter_nums);
	fc.delimit_data_by_string();
	REQUIRE(fc.get_filtered_fields() == OUTPUT1_3);
}

TEST_CASE("FieldsAndColumns::delimit_data_by_regex tests.", "[FieldsAndColumns::delimit_data_by_regex]"){
	FieldsAndColumns fc;
	fc.set_data(INPUT2);
	fc.set_regex_delimiter(REGEX2);
	REQUIRE(fc.delimit_data_by_regex() == OUTPUT2);
}

TEST_CASE("FieldsAndColumns::match_data_to_regex tests.", "[FieldsAndColumns::match_data_to_regex]"){
	FieldsAndColumns fc;
	fc.set_data(INPUT2);
	REQUIRE(fc.match_data_by_regex(REGEX2) == OUTPUT2_REGEX_MATCH);
}
