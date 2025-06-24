// Copyright 2025 <Jordan Charlot>
#pragma once

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <SFML/System.hpp>

class EDistance {
 public:
    EDistance(const std::string& s1, const std::string& s2);
    ~EDistance();

    static int penalty(char a, char b);
    static int min3(int a, int b, int c);

    int optDistance();
    std::string alignment();

 private:
    std::string x;
    std::string y;
    int** opt;
    int M;
    int N;

    void initializeMatrix();
    void fillMatrix();
    std::string traceAlignment();
};
