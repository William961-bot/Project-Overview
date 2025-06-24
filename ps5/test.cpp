// Copyright 2025 <Jordan Charlot>
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE EDistanceTest
#include <boost/test/unit_test.hpp>
#include "EDistance.hpp"

BOOST_AUTO_TEST_CASE(penalty_test) {
    BOOST_CHECK_EQUAL(EDistance::penalty('A', 'A'), 0);
    BOOST_CHECK_EQUAL(EDistance::penalty('A', 'T'), 1);
    BOOST_CHECK_EQUAL(EDistance::penalty('G', 'C'), 1);
    BOOST_CHECK_EQUAL(EDistance::penalty('T', 'T'), 0);
}

BOOST_AUTO_TEST_CASE(min3_test) {
    BOOST_CHECK_EQUAL(EDistance::min3(1, 2, 3), 1);
    BOOST_CHECK_EQUAL(EDistance::min3(5, 2, 4), 2);
    BOOST_CHECK_EQUAL(EDistance::min3(3, 3, 3), 3);
    BOOST_CHECK_EQUAL(EDistance::min3(0, -1, 1), -1);
}

BOOST_AUTO_TEST_CASE(empty_strings_test) {
    EDistance ed("", "");
    BOOST_CHECK_EQUAL(ed.optDistance(), 0);
    BOOST_CHECK_EQUAL(ed.alignment(), "");
}

BOOST_AUTO_TEST_CASE(one_empty_string_test) {
    EDistance ed1("A", "");
    BOOST_CHECK_EQUAL(ed1.optDistance(), 2);
    BOOST_CHECK_EQUAL(ed1.alignment(), "A - 2\n");

    EDistance ed2("", "T");
    BOOST_CHECK_EQUAL(ed2.optDistance(), 2);
    BOOST_CHECK_EQUAL(ed2.alignment(), "- T 2\n");
}

BOOST_AUTO_TEST_CASE(simple_alignment_test) {
    EDistance ed("A", "T");
    BOOST_CHECK_EQUAL(ed.optDistance(), 1);
    BOOST_CHECK_EQUAL(ed.alignment(), "A T 1\n");
}

BOOST_AUTO_TEST_CASE(example_alignment_test) {
    EDistance ed("AACAGTTACC", "TAAGGTCA");
    BOOST_CHECK_EQUAL(ed.optDistance(), 7);

    std::string expected =
        "A T 1\n"
        "A A 0\n"
        "C - 2\n"
        "A A 0\n"
        "G G 0\n"
        "T G 1\n"
        "T T 0\n"
        "A - 2\n"
        "C C 0\n"
        "C A 1\n";

    BOOST_CHECK_EQUAL(ed.alignment(), expected);
}
