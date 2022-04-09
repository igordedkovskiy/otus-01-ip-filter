#include "gtest/gtest.h"
#include "filter.h"

TEST(TEST_VERSION, test_valid_version)
{
    ASSERT_TRUE(true);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
