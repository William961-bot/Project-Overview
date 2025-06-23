# Compiler and flags
CC       = g++
CFLAGS   = -std=c++20 -Wall -Werror -pedantic -g
SFMLFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
TESTFLAGS = -lboost_unit_test_framework

# Executables and objects
MAIN_EXE    = NBody
TEST_EXE    = test
STATICLIB   = NBody.a

# Source files
LIB_OBJS    = Universe.o CelestialBody.o
MAIN_OBJS   = main.o
TEST_OBJS   = test.o

# Input file
INPUT_FILE  = planets.txt

.PHONY: all clean lint run-tests valgrind valgrind-test

# Default build
all: $(MAIN_EXE) $(TEST_EXE) $(STATICLIB)

# Static library
$(STATICLIB): $(LIB_OBJS)
	ar rcs $@ $^

# Main executable
$(MAIN_EXE): $(MAIN_OBJS) $(STATICLIB)
	$(CC) $(CFLAGS) -o $@ $^ $(SFMLFLAGS)

# Test executable
$(TEST_EXE): $(TEST_OBJS) $(STATICLIB)
	$(CC) $(CFLAGS) -o $@ $^ $(SFMLFLAGS) $(TESTFLAGS)

# Object file rules
Universe.o: Universe.cpp Universe.hpp
	$(CC) $(CFLAGS) -c Universe.cpp -o $@

CelestialBody.o: CelestialBody.cpp CelestialBody.hpp
	$(CC) $(CFLAGS) -c CelestialBody.cpp -o $@

main.o: main.cpp Universe.hpp CelestialBody.hpp
	$(CC) $(CFLAGS) -c main.cpp -o $@

test.o: test.cpp Universe.hpp CelestialBody.hpp
	$(CC) $(CFLAGS) -c test.cpp -o $@

# Run tests
run-tests: $(TEST_EXE)
	./$(TEST_EXE)

# Run main with input
run: $(MAIN_EXE)
	./$(MAIN_EXE) < $(INPUT_FILE)

# Valgrind runs
valgrind: $(MAIN_EXE)
	valgrind --leak-check=full --track-origins=yes ./$(MAIN_EXE) < $(INPUT_FILE)

valgrind-test: $(TEST_EXE)
	valgrind --leak-check=full --track-origins=yes ./$(TEST_EXE)

# Clean up
clean:
	rm -f *.o $(MAIN_EXE) $(TEST_EXE) $(STATICLIB)


# Lint
lint:
	cpplint *.cpp *.hpp
