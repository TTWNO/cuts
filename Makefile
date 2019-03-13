CUTS = cuts
COMP=g++
CXX_FLAGS=-I./lib/Catch2/single_include/ -g -Wall -O3

test:
	(cd tests && ../runtests -c $(CUTS) tests.spec)
buildtestlibs:
	$(COMP) $(CXX_FLAGS) -c src/tests-main.cpp -o lib/tests-main.o
buildtests:
	test -d bin || mkdir bin
	$(COMP) $(CXX_FLAGS) -c src/functions.cpp -o lib/functions.o
	$(COMP) $(CXX_FLAGS) lib/tests-main.o lib/functions.o src/test-functions.cpp -o bin/tests.out
build:
	test -d bin || mkdir bin
	$(COMP) $(CXX_FLAGS) -c -o lib/functions.o src/functions.cpp
	$(COMP) $(CXX_FLAGS) lib/functions.o -o bin/cuts.out src/cuts.cpp
clean:
	rm -r bin
