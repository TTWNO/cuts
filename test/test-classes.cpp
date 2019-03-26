#define BOOST_MAIN
#define BOOST_TEST_MODULE FunctionsUnitTest
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include "classes.h"

using namespace std;

string INPUT1 = "Test1,Test2,Test3";
string DEL1 = ",";
vector<string> OUTPUT1 = {"Test1", "Test2", "Test3"};

string INPUT2 = "Hello, my name is Tait\nAnd    I am  very  tired\nWeeee this    is   ,   fun.";
vector<string> OUTPUT2 = {"Hello", "my", "name", "is", "Tait", "And", "I", "am", "very", "tired", "Weeee", "this", "is", "fun."};
boost::regex REGEX2 ("[, \n]+");
vector<string> OUTPUT2_REGEX_MATCH = {", ", " ", " ", " ", "\n", "    ", " ", "  ", "  ", "\n", " ", "    ", "   ,   "};

BOOST_AUTO_TEST_CASE(FieldsAndColumnsCCdelimit_data_by_stringTests){
	FieldsAndColumns fac;
	fac.set_data(INPUT1);
	fac.set_string_delimiter(DEL1);
	BOOST_CHECK(fac.delimit_data_by_string() == OUTPUT1);
}

BOOST_AUTO_TEST_CASE(FieldsAndColumnsCCget_filtered_fieldsTests){
	FieldsAndColumns fc;
	fc.set_data(INPUT1);
	fc.set_string_delimiter(DEL1);
	vector<int> filter_nums = {1, 3};
	vector<string> OUTPUT1_2 = {"Test1", "Test3"};
	fc.set_filter_nums(filter_nums);
	fc.delimit_data_by_string();
	BOOST_CHECK(fc.get_filtered_fields() == OUTPUT1_2);
}

BOOST_AUTO_TEST_CASE(FieldsAndColumnsCCget_filtered_fieldsTestsWithNonReferenceableColumns){
	FieldsAndColumns fc;
	fc.set_data(INPUT1);
	fc.set_string_delimiter(DEL1);
	vector<int> filter_nums = {1, 8};
	vector<string> OUTPUT1_3 = {"Test1", ""};
	fc.set_filter_nums(filter_nums);
	fc.delimit_data_by_string();
	BOOST_TEST(fc.get_filtered_fields() == OUTPUT1_3, boost::test_tools::per_element());
}

BOOST_AUTO_TEST_CASE(FieldsAndColumnsCCget_delimit_by_regex){
	FieldsAndColumns fc;
	fc.set_data(INPUT2);
	fc.set_regex_delimiter(REGEX2);
	BOOST_TEST(fc.delimit_data_by_regex() == OUTPUT2, boost::test_tools::per_element());
}

BOOST_AUTO_TEST_CASE(FieldsAndColumnsCCmatch_data_to_regex){
	FieldsAndColumns fc;
	fc.set_data(INPUT2);
	BOOST_TEST(fc.match_data_by_regex(REGEX2) == OUTPUT2_REGEX_MATCH, boost::test_tools::per_element());
}
