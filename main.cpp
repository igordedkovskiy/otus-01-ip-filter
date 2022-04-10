#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "ip_filter.h"

//using namespace ip_filter;

int main()
{
    ip_filter::addr_collection_t ip_list;
    std::string read;
    unsigned int cntr = 0;
    while(std::cin >> read)
    {
        if(cntr++ % 3 == 0)
        {
            ip_list.emplace_back(ip_filter::parse_address(read));
            read.clear();
        }
    }

    ip_filter::sort(ip_list);

    auto print = [](const ip_filter::address_t& el)
    {
        std::cout << (int)el[0] << '.' << (int)el[1] << '.'
                  << (int)el[2] << '.' << (int)el[3] << '\n';
    };

    for(const auto& it:ip_list)
        print(it);

    {
        auto first = std::find_if(std::begin(ip_list), std::end(ip_list),
                                  [](const ip_filter::address_t& el){ return el[0] == 1; });
        auto last = std::find_if(first, std::end(ip_list), [](const ip_filter::address_t& el){ return el[0] < 1; });
        std::for_each(first, last, print);
//        auto it = ip_filter::find_if(ip_list, 0, 1);
//        std::for_each(it.first, it.second, print);
    }
    {
        auto first = std::find_if(std::begin(ip_list), std::end(ip_list),
                                  [](const ip_filter::address_t& el){ return el[0] == 46 && el[1] == 70; });
        auto last = std::find_if(first, std::end(ip_list),
                                 [](const ip_filter::address_t& el){ return el[0] < 46 || el[1] != 70; });
        std::for_each(first, last, print);
//        auto it = ip_filter::find_if(ip_list, 0, 46, 1, 70);
//        std::for_each(it.first, it.second, print);
    }
    {
        auto comp = [](const ip_filter::address_t& el)
        {
            for(auto it:el)
            {
                if(it == 46 )
                    return true;
            }
            return false;
        };
        std::for_each(std::begin(ip_list), std::end(ip_list),
                      [&comp, &print](const ip_filter::address_t& el){ if(comp(el)) print(el); });
    }
    return 0;
}
