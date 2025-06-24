# Compiler and flags
CC       = g++
CFLAGS   = -std=c++17 -Wall -Werror -pedantic -g
LDFLAGS  = -lsfml-graphics -lsfml-window -lsfml-system
TESTFLAGS = -lboost_unit_test_framework

# Executables and objects
MAIN_EXE    = Sokoban
TEST_EXE    = test
STATICLIB   = Sokoban.a

# Source files
LIB_OBJS    = Sokoban.o
MAIN_OBJS   = main.o
TEST_OBJS   = test.o

# Level for valgrind testing
TEST_LEVEL  = level1.lvl

.PHONY: all clean lint run-tests valgrind valgrind-test

# Default build
all: $(MAIN_EXE) $(TEST_EXE) $(STATICLIB)

# Static library
$(STATICLIB): $(LIB_OBJS)
	ar rcs $@ $^

# Main executable
$(MAIN_EXE): $(MAIN_OBJS) $(STATICLIB)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Test executable
$(TEST_EXE): $(TEST_OBJS) $(STATICLIB)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(TESTFLAGS)

# Object file rules
Sokoban.o: Sokoban.cpp Sokoban.hpp
	$(CC) $(CFLAGS) -c Sokoban.cpp -o $@

main.o: main.cpp Sokoban.hpp
	$(CC) $(CFLAGS) -c main.cpp -o $@

test.o: test.cpp Sokoban.hpp
	$(CC) $(CFLAGS) -c test.cpp -o $@

# Run tests
run-tests: $(TEST_EXE)
	./$(TEST_EXE)

# Valgrind runs
valgrind: $(MAIN_EXE)
	valgrind --leak-check=full --track-origins=yes ./$(MAIN_EXE) $(TEST_LEVEL)

valgrind-test: $(TEST_EXE)
	valgrind --leak-check=full --track-origins=yes ./$(TEST_EXE)

# Clean up
clean:
	rm -f *.o $(MAIN_EXE) $(TEST_EXE) $(STATICLIB)

# Lint
lint:
	cpplint *.cpp *.hpp
