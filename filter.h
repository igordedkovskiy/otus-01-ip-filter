#ifndef FILTER_H
#define FILTER_H

#include <vector>
#include <list>
#include <tuple>
#include <string>

namespace filter
{
//using address_t = std::tuple<unsigned char, unsigned char, unsigned char, unsigned char>;
using address_t = std::vector<unsigned char>;
using addr_collection_t = std::vector<address_t>;
//using addr_collection_t = std::list<address_t>;

address_t parse_address(const std::string& addr);

void sort(addr_collection_t& col);

}

#endif //#define FILTER_H
