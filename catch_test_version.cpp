#include "lib.h"
#define CATCH_CONFIG_MAIN  
#include "catch.hpp"

TEST_CASE("test_valid_version","[test_version]")
{
    REQUIRE(version() > 0);
}
