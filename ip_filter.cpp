#include <algorithm>
#include <type_traits>
#include <algorithm>
#include <stdexcept>
#include "ip_filter.h"

namespace ip_filter
{

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
    if(addr.empty())
        throw ParseErr::incorrect_format;

    const auto delim1 = addr.find_first_of('.');
    if(delim1 == std::string::npos || delim1 < 1)
        throw ParseErr::incorrect_format;

    const auto delim2 = addr.find_first_of('.', delim1 + 1);
    if(delim2 == std::string::npos || delim2 < delim1 + 2)
        throw ParseErr::incorrect_format;

    const auto delim3 = addr.find_first_of('.', delim2 + 1);
    if(delim3 == std::string::npos || delim3 < delim2 + 2 || delim3 == addr.size() - 1)
        throw ParseErr::incorrect_format;

    try
    {
        const auto n1 = static_cast<unsigned char>(stoi(addr.substr(0, delim1)));
        const auto n2 = static_cast<unsigned char>(stoi(addr.substr(delim1+1, delim2 - delim1 - 1)));
        const auto n3 = static_cast<unsigned char>(stoi(addr.substr(delim2+1, delim3 - delim2 - 1)));
        const auto n4 = static_cast<unsigned char>(stoi(addr.substr(delim3+1, addr.size() - delim3 - 1)));
        return address_t{n1, n2, n3, n4};
    }
    catch(std::logic_error& e)
    {
        throw ParseErr::incorrect_format;
    }
}


void sort(addr_collection_t& col)
{
    auto comp = [](const address_t& l, const address_t& r)
    {
        return !std::lexicographical_compare(std::begin(l),std::end(l),std::begin(r),std::end(r));
    };
    sort(col, comp);
}

}
