#include <string>
#include <sstream>
#include "gtest/gtest.h"
#include "ip_filter.h"
#include "read_input.h"

//#ifdef WIN32
// //ip_filter.exe < .\ip_filter.tsv | md5sum
//const char* md5 = "36b72c25de983078b68625b7610e7673";
//#else
// //cat ip_filter.tsv | ip_filter | md5sum
//const char* md5 = "24e7a7b2270daee89c64d3ca5fb3da1a";
//#endif

using namespace ip_filter;

TEST(TEST_ADDR_SORT, test_addr_sort)
{
    std::istringstream input{"7\n"
                             "113.162.145.156	111	0\n"
                             "1.39.22.221	5	6\n"
                             "113.55.46.91	0	2\n"
                             "113.55.46.98	0	2\n"
                             "113.55.42.91	0	2\n"
                             "1.39.22.224	5	6\n"
                             "46.39.22.224	5	6\n"
                           };
    addr_collection_t ans{{113,162,145,156},
                          {113,55,46,98},
                          {113,55,46,91},
                          {113,55,42,91},
                          {46,39,22,224},
                          {1,39,22,224},
                          {1,39,22,221}
                         };
    auto [ip_list, failed_line] = ip_filter::read_input(input);
    sort(ip_list);
    ASSERT_TRUE(ip_list == ans);
}

TEST(TEST_ADDR, verify_input_format)
{
    {
        std::istringstream input{"3\n"
                                 "162.145.156 111 0\n"
                                 "113.162.145.156 111 0\n"
                                 "113.162.145.156 111 0\n"
                                 "113.162.145.156 111 0\n"
                                };
        auto [ip_list, failed_line] = ip_filter::read_input(input);
        ASSERT_TRUE(failed_line == 1);
        ASSERT_TRUE(ip_list.size() == 3);
    }
    {
        std::istringstream input{"3\n"
                                 "113.162.145.156 111 0\n"
                                 "113.162.145156 111 0\n"
                                 "113.162.145.156 111 0\n"
                                 "113.162.145.156 111 0\n"
                                };
        auto [ip_list, failed_line] = ip_filter::read_input(input);
        ASSERT_TRUE(failed_line == 2);
        ASSERT_TRUE(ip_list.size() == 3);
    }
    {
        std::istringstream input{"3\n"
                                 "113.162.145.156 111 0\n"
                                 "113.162.145.156 111 0\n"
                                 "113.s.145.156 111 0\n"
                                 "113.162.145.156 111 0\n"
                                };
        auto [ip_list, failed_line] = ip_filter::read_input(input);
        ASSERT_TRUE(failed_line == 3);
        ASSERT_TRUE(ip_list.size() == 3);
    }
    {
        std::istringstream input{"3\n"
                                 "113.162.145.156\n"
                                 "113.123.145.156 0\n"
                                 "113.162.145.156 111 0\n"
                                };
        auto [ip_list, failed_line] = ip_filter::read_input(input);
        ASSERT_TRUE(failed_line == std::numeric_limits<decltype(failed_line)>::max());
        ASSERT_TRUE(ip_list.size() == 3);
    }
    {
        std::istringstream input{"3\n"
                                 "113.162.145.156\n"
                                 "113.123.145.156 0\n"
                                 "113.162.145.156 111 0\n"
                                 "113.162.145.156 111 0\n"
                                 "113.162.145.156 111 0\n"
                                 "113.162.145.156 111 0\n"
                                };
        auto [ip_list, failed_line] = ip_filter::read_input(input);
        ASSERT_TRUE(failed_line == std::numeric_limits<decltype(failed_line)>::max());
        ASSERT_TRUE(ip_list.size() == 3);
    }
    {
        std::istringstream input{"0\n"};
        auto [ip_list, failed_line] = ip_filter::read_input(input);
        ASSERT_TRUE(failed_line == std::numeric_limits<decltype(failed_line)>::max());
        ASSERT_TRUE(ip_list.size() == 0);
    }
    {
        std::istringstream input{"-10\n"
                                 "q\n"
                                 "3\n"
                                 "113.162.145.156\n"
                                 "113.123.145.156 0\n"
                                 "113.162.145.156 111 0\n"
                                };
        auto [ip_list, failed_line] = ip_filter::read_input(input);
        ASSERT_TRUE(failed_line == std::numeric_limits<decltype(failed_line)>::max());
        ASSERT_TRUE(ip_list.size() == 3);
    }
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
