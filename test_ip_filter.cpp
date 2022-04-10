#include "gtest/gtest.h"
#include "ip_filter.h"

TEST(TEST_FILTER, test_ip_filter)
{
    ASSERT_TRUE(true);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
