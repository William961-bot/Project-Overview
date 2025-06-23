// Copyright 2025 William Nosike

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE NBodyIOTests
#include <sstream>
#include <string>
#include "CelestialBody.hpp"
#include "Universe.hpp"
#include <boost/test/unit_test.hpp>

using NB::CelestialBody; using NB::Universe;


BOOST_AUTO_TEST_CASE(CelestialBody_IO) {
    // Input line: x y vx vy mass imageFile
    std::string inputData = "2.8 -3.5 0.7 -1.2 25 mercury.gif";
    std::istringstream iss(inputData);

    CelestialBody body;
    iss >> body;  // Reads the celestial body from the stream

    // Round-trip: serialize the body back to a string.
    std::ostringstream oss;
    oss << body;  // Uses operator<< for CelestialBody
    BOOST_CHECK_EQUAL(oss.str(), "2.8 -3.5 0.7 -1.2 25 mercury.gif");
}

BOOST_AUTO_TEST_CASE(Universe_IO) {
    // Test universe with 2 bodies and radius 1e10
    std::string inputData = "2 1e10\n"
                           "1.0 2.0 0.0 0.0 5.0 venus.gif\n"
                           "3.0 4.0 0.1 0.2 6.0 mercury.gif\n";
    std::istringstream iss(inputData);

    Universe uni;
    iss >> uni;

    std::ostringstream oss;
    oss << uni;
    std::string outStr = oss.str();

    // Check header with count and radius
    BOOST_CHECK_MESSAGE(
        outStr.find("2") != std::string::npos &&
        (outStr.find("1e10") != std::string::npos || outStr.find("1e+10") != std::string::npos),
        "Output did not contain expected values for n and radius");

    // Check body data
    BOOST_CHECK_MESSAGE(
        outStr.find("venus.gif") != std::string::npos &&
        outStr.find("mercury.gif")  != std::string::npos,
        "Output did not contain expected body lines");
}
