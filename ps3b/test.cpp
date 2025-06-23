// Copyright 2025 William Nosike

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE NBodyTests
#include <sstream>
#include <string>
#include <cmath>
#include <algorithm>
#include "CelestialBody.hpp"
#include "Universe.hpp"
#include <boost/test/unit_test.hpp>

using NB::CelestialBody;
using NB::Universe;

BOOST_AUTO_TEST_CASE(CelestialBody_IO) {
    // Input line: x y vx vy mass imageFile
    std::string inputData = "1.5 2.5 0.5 1.0 10 earth.gif";
    std::istringstream iss(inputData);

    CelestialBody body;
    iss >> body;  // Reads the celestial body from the stream

    // Round-trip: serialize the body back to a string.
    std::ostringstream oss;
    oss << body;  // Uses operator<< for CelestialBody
    BOOST_CHECK_EQUAL(oss.str(), "1.5 2.5 0.5 1 10 earth.gif");
}

BOOST_AUTO_TEST_CASE(Universe_IO) {
    // Universe data:
    //   2 1e10
    //   1.0 2.0 0.0 0.0 5.0 earth.gif
    //   3.0 4.0 0.1 0.2 6.0 mars.gif
    std::string inputData = "2 1e10\n1.0 2.0 0.0 0.0 5.0 earth.gif\n3.0 4.0 0.1 0.2 6.0 mars.gif\n";
    std::istringstream iss(inputData);

    Universe uni;
    iss >> uni;  // Reads the Universe from the stream

    std::ostringstream oss;
    oss << uni;  // Writes the Universe back to a string

    std::string outStr = oss.str();

    // Confirm that output contains "2" and the correct radius ("1e10" or "1e+10")
    BOOST_CHECK_MESSAGE(
        outStr.find("2") != std::string::npos &&
        (outStr.find("1e10") != std::string::npos || outStr.find("1e+10") != std::string::npos),
        "Output did not contain expected values for n and radius");

    // Confirm that both image file names are present.
    BOOST_CHECK_MESSAGE(
        outStr.find("earth.gif") != std::string::npos &&
        outStr.find("mars.gif")  != std::string::npos,
        "Output did not contain expected body lines");
}
// Unit tests for physics simulation
BOOST_AUTO_TEST_CASE(ValidateCorrectPhysics) {
    NB::Universe universe;
    std::stringstream in;

    // Define a solar system with Earth slightly above the X-axis (ensures orbital curve)
    in << "2\n"
       << "2.5e+11\n"  // Universe radius
       << "1.496e+11 -1.0e+10 0 29800 5.974e+24 earth.gif\n"  // Earth
       << "0 0 0 0 1.989e+30 sun.gif\n";  // Sun at origin

    in >> universe;

    // Save initial position and velocity
    double initial_x = universe[0].position().x;
    double initial_vy = universe[0].velocity().y;


    // time step
    double dt = 86400;
    universe.step(dt);


    // Check gravity pulls Earth toward the Sun
    BOOST_CHECK_MESSAGE(universe[0].position().x < initial_x,
                       "Earth should move left due to gravity");

    // Check velocity increases in the correct direction (orbital curve)
    BOOST_CHECK_MESSAGE(universe[0].velocity().y > initial_vy,
                       "VY should increase due to orbital path");
}

