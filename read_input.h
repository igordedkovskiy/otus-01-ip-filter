#ifndef READ_INPUT_H
#define READ_INPUT_H

#include <utility>
#include <sstream>
#include "ip_filter.h"

namespace ip_filter
{

std::pair<addr_collection_t, std::size_t> read_input(std::istream& in_stream);

}

#endif //#define READ_INPUT_H
