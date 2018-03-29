#include <random>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest/doctest.h"

#include "../osrandom.hpp"

TEST_CASE("direct usage")
{
    Chocobo1::OSRandom rand;

    int counter = 0;
    for (int i = 0; i < 100; ++i)
    {
        if (rand() == 0)
            ++counter;
    }
    CHECK(counter <= 2);  // very unlikely condition
}

TEST_CASE("interface")
{
    Chocobo1::OSRandom rand;

    const uint64_t min = 4294968295;
    const uint64_t max = 5294968295;
    std::uniform_int_distribution<uint64_t> dist(min, max);
    for (int i = 0; i < 100; ++i)
    {
        const uint64_t val = dist(rand);
        CHECK(((min <= val) && (val <= max)));
    }
}

TEST_CASE("error reporting")
{
    Chocobo1::OSRandom rand;

    for (int i = 0; i < 100; ++i)
    {
        rand();

#ifndef _WIN32
        CHECK(rand.good());
        CHECK(!rand.eof());
        CHECK(rand.ferror() == 0);
#endif
    }
}
