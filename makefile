CXX = gcc
# -Wall turns on many, but not all, warning flags
# -Wextra turns on additional warning flags which Wall does not
CXXFLAGS = -Wall -Wextra

all:	main

tests: test_str

test_str: test_str.o str.o
	$(CXX) $(CXXFLAGS) -o $@ $^

run:	all
	./main

run_tests: tests
	./test_str

run_test_str: test_str
	./test_str

main: main.c str.o
	$(CXX) $(CXXFLAGS) -o $@ $^

str.o: str.h str.c
	$(CXX) $(CXXFLAGS) -c str.c

test_str.o: test_str.c test.o str.o
	$(CXX) $(CXXFLAGS) -c test_str.c

clean:
	rm -Rf *.o \
		main \
		test_str

# compiles any .c file, assumes no dependencies
%.o: %.c
	$(CXX) $(CXXFLAGS) -c $*.c -o $*.o
