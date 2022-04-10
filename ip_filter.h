#ifndef IP_FILTER_H
#define IP_FILTER_H

#include <vector>
#include <list>
#include <string>
#include <utility>

namespace ip_filter
{
using address_t = std::vector<unsigned char>;
using addr_collection_t = std::vector<address_t>;
//using addr_collection_t = std::list<address_t>;

address_t parse_address(const std::string& addr);

void sort(addr_collection_t& col);

//std::pair<addr_collection_t::iterator,addr_collection_t::iterator>
//find_if(addr_collection_t& ip_list, std::size_t elem_num, unsigned char val);

//std::pair<addr_collection_t::iterator,addr_collection_t::iterator>
//find_if(addr_collection_t& ip_list, std::size_t elem1_num, unsigned char val1, std::size_t elem2_num, unsigned char val2);

}

#endif //#define IP_FILTER_H
