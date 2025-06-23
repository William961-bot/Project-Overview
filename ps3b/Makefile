
CC      = g++
CFLAGS = -std=c++17 -Wall -Werror -pedantic -g
LDFLAGS  = -lboost_unit_test_framework -lsfml-graphics -lsfml-window -lsfml-system

MAIN_EXE  = NBody
STATICLIB = NBody.a
TEST_EXE  = test

LIB_SRCS  = Universe.cpp CelestialBody.cpp
LIB_OBJS  = $(LIB_SRCS:.cpp=.o)

MAIN_SRCS = main.cpp
MAIN_OBJS = $(MAIN_SRCS:.cpp=.o)

TEST_SRCS = test.cpp
TEST_OBJS = $(TEST_SRCS:.cpp=.o)



.PHONY: all clean lint test-run valgrind valgrind-test

# Default target: Build main executable, static library, and test executable
all: $(MAIN_EXE) $(STATICLIB) $(TEST_EXE)

# Create static library "NBody.a"
$(STATICLIB): $(LIB_OBJS)
	ar rcs $(STATICLIB) $(LIB_OBJS)

# Build main executable "NBody" using the static library
$(MAIN_EXE): $(MAIN_OBJS) $(STATICLIB)
	$(CC) $(CFLAGS) -o $(MAIN_EXE) $(MAIN_OBJS) $(STATICLIB) $(LDFLAGS)

# Build test executable separately from static library
$(TEST_EXE): $(TEST_OBJS) $(LIB_OBJS)
	$(CC) $(CFLAGS) -o $(TEST_EXE) $(TEST_OBJS) $(LIB_OBJS) $(LDFLAGS)

# Compile object files
Universe.o: Universe.cpp Universe.hpp CelestialBody.hpp
	$(CC) $(CFLAGS) -c Universe.cpp -o Universe.o

CelestialBody.o: CelestialBody.cpp CelestialBody.hpp
	$(CC) $(CFLAGS) -c CelestialBody.cpp -o CelestialBody.o

main.o: main.cpp Universe.hpp CelestialBody.hpp
	$(CC) $(CFLAGS) -c main.cpp -o main.o

test.o: test.cpp Universe.hpp CelestialBody.hpp
	$(CC) $(CFLAGS) -c test.cpp -o test.o

# Run Valgrind to check for memory leaks
valgrind: $(MAIN_EXE)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./NBody

valgrind-test: $(TEST_EXE)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./test

# Clean target to remove compiled files
clean:
	rm -f *.o $(MAIN_EXE) $(TEST_EXE) $(STATICLIB)

# Run cpplint for style checking
lint:
	cpplint *.cpp *.hpp
