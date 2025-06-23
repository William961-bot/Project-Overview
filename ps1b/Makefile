# Compiler and Flags
CC = g++
CFLAGS = -std=c++20 -Wall -Werror -pedantic -g

# Libraries
LIBS = -lboost_unit_test_framework -lsfml-graphics -lsfml-window -lsfml-system

# Source files for the static library (only the shared code)
LIB_SRC = FibLFSR.cpp PhotoMagic.cpp
LIB_OBJS = $(LIB_SRC:.cpp=.o)

# Static library name
LIBRARY = PhotoMagic.a

# Source files for the main executable
SRC = FibLFSR.cpp PhotoMagic.cpp main.cpp
DEPS = FibLFSR.hpp PhotoMagic.hpp
OBJS = $(SRC:.cpp=.o)

# Executable name for the main program
EXEC = PhotoMagic

# Test files
TEST_SRC = test.cpp
TEST_OBJ = $(TEST_SRC:.cpp=.o)
TEST_PROGRAM = test

.PHONY: all clean lint

# Default target builds the main executable and the static library.
all: $(EXEC) $(LIBRARY) $(TEST_PROGRAM)

# Build the static library from LIB_OBJS.
$(LIBRARY): $(LIB_OBJS)
	@echo "Building static library $(LIBRARY)..."
	ar rcs $@ $^

# Build the main executable.
$(EXEC): $(OBJS)
	@echo "Linking main executable $(EXEC)..."
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS) $(LIBS)

# Build the test executable by linking test objects with the static library.
test: $(TEST_OBJ) $(LIBRARY)
	@echo "Building test executable $(TEST_PROGRAM)..."
	$(CC) $(CFLAGS) -o $(TEST_PROGRAM) $(TEST_OBJ) -L. -l:$(LIBRARY) $(LIBS)

# Compile each .cpp file into .o
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

# Clean target: remove all generated files.
clean:
	rm -f $(LIB_OBJS) $(OBJS) $(EXEC) $(TEST_OBJ) $(TEST_PROGRAM) $(LIBRARY)

# Run cpplint for style checks.
lint:
	cpplint *.cpp *.hpp
