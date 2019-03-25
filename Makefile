CUTS = cuts
COMP=g++
CXX_FLAGS=-g -Wall
CXX_LIB_FLAGS=-I./lib/Catch2/single_include/ -I/usr/include/ -L/usr/lib/ -lboost_regex

test:
	(cd tests && ../runtests -c $(CUTS) tests.spec)
buildtestlibs:
	$(COMP) $(CXX_FLAGS) $(CXX_LIB_FLAGS) -c src/tests-main.cpp -o lib/tests-main.o
buildtests:
	test -d bin || mkdir bin
	$(COMP) $(CXX_FLAGS) $(CXX_LIB_FLAGS) -c src/classes.cpp -o lib/classes.o
	$(COMP) $(CXX_FLAGS) $(CXX_LIB_FLAGS) -c src/functions.cpp -o lib/functions.o
	$(COMP) $(CXX_FLAGS) $(CXX_LIB_FLAGS) lib/tests-main.o lib/functions.o lib/classes.o src/test-functions.cpp -o bin/tests.out
build:
	test -d bin || mkdir bin
	$(COMP) $(CXX_FLAGS) $(CXX_LIB_FLAGS) -c src/classes.cpp -o lib/classes.o
	$(COMP) $(CXX_FLAGS) -c -o lib/functions.o src/functions.cpp
	$(COMP) $(CXX_FLAGS) lib/functions.o lib/classes.o -o bin/cuts.out src/cuts.cpp
clean:
	rm -r bin
