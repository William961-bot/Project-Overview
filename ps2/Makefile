CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -Werror -std=c++17
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

TARGET = Triangle
SRC = main.cpp triangle.cpp
OBJ = $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(TARGET) $(LDFLAGS)

%.o: %.cpp triangle.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

lint:
	clang-tidy $(SRC) -- -std=c++17

clean:
	rm -f $(OBJ) $(TARGET)

