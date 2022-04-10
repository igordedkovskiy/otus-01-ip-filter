#include "gtest/gtest.h"
#include "ip_filter.h"

//#ifdef WIN32
//constexpr unsigned long long md5_h = 0x36b72c25de983078;
//constexpr unsigned long long md5_l = 0xb68625b7610e7673;
//#else
//constexpr unsigned long long md5_h = 0x24e7a7b2270daee8;
//constexpr unsigned long long md5_l = 0x9c64d3ca5fb3da1a;
//#endif

TEST(TEST_FILTER, test_ip_filter)
{
    ASSERT_TRUE(true);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
