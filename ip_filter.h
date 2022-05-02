#ifndef IP_FILTER_H
#define IP_FILTER_H

#include <vector>
#include <list>
#include <string>
#include <utility>
#include <sstream>

namespace ip_filter
{
using address_t = std::vector<unsigned char>;
using addr_collection_t = std::vector<address_t>;
//using addr_collection_t = std::list<address_t>;

enum class ParseErr: std::uint8_t
{
    incorrect_format
};

/// \throws  ParseErr in case of incorrect address format
/// \returns std::vector of four numbers of which an address consists
address_t parse_address(const std::string& addr);

void sort(addr_collection_t& col);

}

#endif //#define IP_FILTER_H
