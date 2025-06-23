// Copyright 2022 By Dr. Rykalova
// Editted by Dr. Daly
// Modified by William Nosike
// test.cpp for PS1a
// updated 1/8/2024

#include <iostream>
#include <stdexcept>
#include <string>
#include "FibLFSR.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>

using PhotoMagic::FibLFSR;

// Test step function with given seed
BOOST_AUTO_TEST_CASE(testStepInstr) {
    FibLFSR l("1011011000110110");
    BOOST_REQUIRE_EQUAL(l.step(), 0);
    BOOST_REQUIRE_EQUAL(l.step(), 0);
    BOOST_REQUIRE_EQUAL(l.step(), 0);
    BOOST_REQUIRE_EQUAL(l.step(), 1);
    BOOST_REQUIRE_EQUAL(l.step(), 1);
    BOOST_REQUIRE_EQUAL(l.step(), 0);
    BOOST_REQUIRE_EQUAL(l.step(), 0);
    BOOST_REQUIRE_EQUAL(l.step(), 1);
}

// Test generate function
BOOST_AUTO_TEST_CASE(testGenerateInstr) {
    FibLFSR l("1011011000110110");
    BOOST_REQUIRE_EQUAL(l.generate(9), 51);
}

// Test step function with a different seed
BOOST_AUTO_TEST_CASE(testStepWithDifferentSeed) {
    FibLFSR l("1100101010110111");
    BOOST_REQUIRE_EQUAL(l.step(), 1);
    BOOST_REQUIRE_EQUAL(l.step(), 1);
    BOOST_REQUIRE_EQUAL(l.step(), 1);
    BOOST_REQUIRE_EQUAL(l.step(), 0);
}
// Test generate function with a single bit
BOOST_AUTO_TEST_CASE(testGenerateSingleBit) {
    FibLFSR l("0100100100111011");
    BOOST_REQUIRE_EQUAL(l.generate(1), 0);
}

  // Test generate function with multiple values
BOOST_AUTO_TEST_CASE(testGenerateMultipleValues) {
    FibLFSR l("1000111110111110");
    int first = l.generate(3);
    int second = l.generate(3);
  BOOST_REQUIRE_EQUAL(first, 1);
  BOOST_REQUIRE_EQUAL(second, 6); }














