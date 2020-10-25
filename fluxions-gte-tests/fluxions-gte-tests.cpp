// fluxions-gte-tests.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>

#include <iostream>
#include <hatchetfish.hpp>

#pragma comment(lib, "hatchetfish.lib")

TEST_CASE("Test Hatchetfish", "[hatchetfish]") {
    HFLOGDEBUG("Hello, world!\n");
}
