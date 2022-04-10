#include "gtest/gtest.h"
#include "ip_filter.h"
#include <string>
#include <sstream>

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
    addr_collection_t ip_list;
    std::stringstream input{"113.162.145.156	111	0\n"
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
    unsigned int cntr = 0;
    std::string read;
    while(input >> read)
    {
        if(cntr++ % 3 == 0)
            ip_list.emplace_back(parse_address(read));
    }

    sort(ip_list);

    ASSERT_TRUE(ip_list == ans);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
