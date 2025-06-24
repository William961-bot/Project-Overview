// Copyright 2025 William Nosike
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE RandWriterTest

#include <string>
#include <stdexcept>
#include <boost/test/unit_test.hpp>
#include "RandWriter.hpp"


BOOST_AUTO_TEST_CASE(comprehensive_test) {
    // Test different order k values
    RandWriter writer1("abcdef", 2);
    BOOST_CHECK_EQUAL(writer1.orderK(), 2);

    RandWriter writer2("abcdef", 0);
    BOOST_CHECK_EQUAL(writer2.orderK(), 0);

    RandWriter writer3("abcdef", 3);
    BOOST_CHECK_EQUAL(writer3.orderK(), 3);

    // Test frequencies with an input that has repeating patterns
    RandWriter freqWriter("aaabbc", 1);

    // Test k-gram frequencies
    BOOST_CHECK_EQUAL(freqWriter.freq("a"), 3);
    BOOST_CHECK_EQUAL(freqWriter.freq("b"), 2);
    BOOST_CHECK_EQUAL(freqWriter.freq("c"), 1);
    BOOST_CHECK_EQUAL(freqWriter.freq("z"), 0);

    // Test k-gram followed by character frequencies
    BOOST_CHECK_EQUAL(freqWriter.freq("a", 'a'), 2);
    BOOST_CHECK_EQUAL(freqWriter.freq("a", 'b'), 1);
    BOOST_CHECK_EQUAL(freqWriter.freq("b", 'b'), 1);
    BOOST_CHECK_EQUAL(freqWriter.freq("b", 'c'), 1);


    // Test order 0 Markov model
    RandWriter zeroWriter("aabbc", 0);
    BOOST_CHECK_EQUAL(zeroWriter.freq("", 'a'), 2);
    BOOST_CHECK_EQUAL(zeroWriter.freq("", 'b'), 2);
    BOOST_CHECK_EQUAL(zeroWriter.freq("", 'c'), 1);
    BOOST_CHECK_EQUAL(zeroWriter.freq("", 'z'), 0);

    // Test error handling
    BOOST_CHECK_THROW(RandWriter("abc", 4), std::invalid_argument);
    BOOST_CHECK_THROW(freqWriter.freq("ab"), std::invalid_argument);
    BOOST_CHECK_THROW(freqWriter.freq("", 'a'), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(generation_test) {
    // Test with a deterministic input pattern
    std::string text = "abcabcabc";
    RandWriter writer(text, 2);

    // Test that k-rand returns expected character
    BOOST_CHECK_EQUAL(writer.kRand("ab"), 'c');
    BOOST_CHECK_EQUAL(writer.kRand("ca"), 'b');

    // Test text generation
    std::string result = writer.generate("ab", 7);
    BOOST_CHECK_EQUAL(result.length(), 7);
    BOOST_CHECK_EQUAL(result.substr(0, 2), "ab");
    BOOST_CHECK_EQUAL(result, "abcabca");  // Deterministic output for this input

    // Test error handling for generate and kRand
    BOOST_CHECK_THROW(writer.kRand("xyz"), std::invalid_argument);
    BOOST_CHECK_THROW(writer.generate("xy", 10), std::invalid_argument);
    BOOST_CHECK_THROW(writer.generate("abc", 5), std::invalid_argument);
}
