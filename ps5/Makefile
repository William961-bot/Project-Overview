CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -pedantic -std=c++11 -g -O2
LDFLAGS = -lboost_unit_test_framework -lsfml-system

SRC = EDistance.cpp
OBJ = $(SRC:.cpp=.o)
LIB = EDistance.a
EXEC = EDistance test

all: $(LIB) $(EXEC)

$(LIB): $(OBJ)
	ar rcs $@ $^

EDistance: $(LIB) main.o
	$(CXX) $(CXXFLAGS) -o $@ main.o $(LIB) $(LDFLAGS)

test: $(LIB) test.o
	$(CXX) $(CXXFLAGS) -o $@ test.o $(LIB) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ) $(EXEC) $(LIB) *.o

lint:
	cpplint --filter=-runtime/references,-build/include_subdir $(SRC) EDistance.hpp

.PHONY: all clean lint