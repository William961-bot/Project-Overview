# Compiler and flags
CC       = g++
CFLAGS   = -std=c++17 -Wall -Werror -pedantic -g
TESTFLAGS = -lboost_unit_test_framework

# Executables and objects
MAIN_EXE    = TextWriter
TEST_EXE    = test
STATICLIB   = TextWriter.a

# Source files
LIB_OBJS    = RandWriter.o
MAIN_OBJS   = TextWriter.o
TEST_OBJS   = test.o

# Test input file
TEST_INPUT  = romeo.txt

.PHONY: all clean lint run-tests valgrind valgrind-test

# Default build
all: $(MAIN_EXE) $(TEST_EXE) $(STATICLIB)

# Static library
$(STATICLIB): $(LIB_OBJS)
	ar rcs $@ $^

# Main executable
$(MAIN_EXE): $(MAIN_OBJS) $(STATICLIB)
	$(CC) $(CFLAGS) -o $@ $^

# Test executable
$(TEST_EXE): $(TEST_OBJS) $(STATICLIB)
	$(CC) $(CFLAGS) -o $@ $^ $(TESTFLAGS)

# Object file rules
RandWriter.o: RandWriter.cpp RandWriter.hpp
	$(CC) $(CFLAGS) -c RandWriter.cpp -o $@

TextWriter.o: TextWriter.cpp RandWriter.hpp
	$(CC) $(CFLAGS) -c TextWriter.cpp -o $@

test.o: test.cpp RandWriter.hpp
	$(CC) $(CFLAGS) -c test.cpp -o $@

# Run tests
run-tests: $(TEST_EXE)
	./$(TEST_EXE)

# Valgrind runs
valgrind: $(MAIN_EXE)
	valgrind --leak-check=full --track-origins=yes ./$(MAIN_EXE) 5 100 $(TEST_INPUT)

valgrind-test: $(TEST_EXE)
	valgrind --leak-check=full --track-origins=yes ./$(TEST_EXE)

# Clean up
clean:
	rm -f *.o $(MAIN_EXE) $(TEST_EXE) $(STATICLIB)

# Lint
lint:
	cpplint *.cpp *.hpp