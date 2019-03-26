TESTS = functions_tests classes_tests
check_PROGRAMS = functions_tests classes_tests
functions_tests_SOURCES = test-functions.cpp $(top_builddir)/src/functions.cpp
functions_tests_CPPFLAGS = -I$(top_builddir)/src

classes_tests_SOURCES = test-classes.cpp $(top_builddir)/src/classes.cpp $(top_builddir)/src/functions.cpp
classes_tests_CPPFLAGS = -I$(top_builddir)/src
