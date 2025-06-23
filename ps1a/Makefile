# Compiler and Flags
CC = g++
CFLAGS = -std=c++20 -Wall -Werror -pedantic -g
LIBS = -lboost_unit_test_framework -lsfml-graphics -lsfml-window -lsfml-system

# Source files for the static library
LIB_SRC = FibLFSR.cpp 
LIB_OBJS = $(LIB_SRC:.cpp=.o)

# Static library name
LIBRARY = PhotoMagic.a

# Test files
TEST_SRC = test.cpp
TEST_OBJ = $(TEST_SRC:.cpp=.o)
TEST_PROGRAM = test

# Main program 
MAIN_OBJ = $(MAIN_SRC:.cpp=.o)
PROGRAM = PhotoMagic

.PHONY: all clean lint

# Builds static library and test program
all: $(LIBRARY) $(TEST_PROGRAM)



# Creates the static library
$(LIBRARY): $(LIB_OBJS)
	ar rcs $@ $^

# Builds the test program
$(TEST_PROGRAM): $(TEST_OBJ) $(LIBRARY)
	$(CC) $^ -o $@ -L. -l:$(LIBRARY) $(LIBS)


# Generates object files (with .hpp dependencies)
%.o: %.cpp FibLFSR.hpp
	$(CC) $(CFLAGS) -c -o $@ $<

# Clean compiled files
clean:
	rm -f $(LIB_OBJS) $(TEST_OBJ) $(MAIN_OBJ) $(PROGRAM) $(TEST_PROGRAM) $(LIBRARY)

# Run cpplint for style checks
lint:
	cpplint *.cpp *.hpp

