#include <algorithm>
#include <type_traits>
#include "filter.h"

namespace filter
{

//address_t parse_address(const std::string &addr)
//{
//    const auto first = addr.find_first_of('.');
//    const auto second = addr.find_first_of('.', first + 1);
//    const auto third = addr.find_first_of('.', second + 1);

//    const address_t a = std::make_tuple(stoi(addr.substr(0, first)),
//                                        stoi(addr.substr(first+1, second - first - 1)),
//                                        stoi(addr.substr(second+1, third - second - 1)),
//                                        stoi(addr.substr(third+1, addr.size() - third - 1))
//                                        );
//    return a;
//}

//void sort(addr_collection_t& col)
//{
//    auto comp = [](const address_t& l, const address_t& r)
//    {
//        if(std::get<0>(l) > std::get<0>(r))
//            return true;
//        else if(std::get<0>(l) == std::get<0>(r))
//        {
//            if(std::get<1>(l) > std::get<1>(r))
//                return true;
//            else if(std::get<1>(l) == std::get<1>(r))
//            {
//                if(std::get<2>(l) > std::get<2>(r))
//                    return true;
//                else if(std::get<2>(l) == std::get<2>(r))
//                {
//                    if(std::get<3>(l) > std::get<3>(r))
//                        return true;
//                }
//            }
//        }
//        return false;
//    };
//    std::sort(std::begin(col), std::end(col), comp);
//}

namespace
{

template<typename T, typename C> void sort(T& col, C comp)
{
    if constexpr(std::is_same_v<std::remove_reference_t<decltype(col)>, std::vector<address_t>>)
        std::sort(std::begin(col), std::end(col), comp);
    else if constexpr(std::is_same_v<std::remove_reference_t<decltype(col)>, std::list<address_t>>)
        col.sort(comp);
}

}

address_t parse_address(const std::string &addr)
{
    const auto first = addr.find_first_of('.');
    const auto second = addr.find_first_of('.', first + 1);
    const auto third = addr.find_first_of('.', second + 1);

    const address_t a{static_cast<unsigned char>(stoi(addr.substr(0, first))),
                      static_cast<unsigned char>(stoi(addr.substr(first+1, second - first - 1))),
                      static_cast<unsigned char>(stoi(addr.substr(second+1, third - second - 1))),
                      static_cast<unsigned char>(stoi(addr.substr(third+1, addr.size() - third - 1)))
                      };
    return a;
}


void sort(addr_collection_t& col)
{
    auto comp = [](const address_t& l, const address_t& r)
    {
        return !std::lexicographical_compare(std::begin(l),std::end(l),std::begin(r),std::end(r));
//        if(l[0] > r[0])
//            return true;
//        else if(l[0] == r[0])
//        {
//            if(l[1] > r[1])
//                return true;
//            else if(l[1] == r[1])
//            {
//                if(l[2] > r[2])
//                    return true;
//                else if(l[2] == r[2])
//                {
//                    if(l[3] > r[3])
//                        return true;
//                }
//            }
//        }
//        return false;
    };
//    std::sort(std::begin(col), std::end(col), comp);
//    col.sort(comp);
    sort(col, comp);
}

}
