#include <algorithm>
#include <type_traits>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <limits>

#include "read_input.h"

namespace ip_filter
{

std::pair<addr_collection_t, std::size_t> read_input(std::istream& in_stream)
{
    std::string in_size_s;
    long in_size;
    while(true)
    {
        in_stream >> in_size_s;
        try
        {
            in_size = stoi(in_size_s);
            in_size_s.clear();
            if(in_size < 0)
                continue;
            break;
        }
        catch(std::logic_error& e)
        {
            std::cerr << "Failed to process input size: incorrect format" << std::endl;
        }
    }

    addr_collection_t ip_list;
    ip_list.reserve(in_size);
    std::string read;
    std::size_t lines_cntr = 0;
    std::size_t last_failed_line = std::numeric_limits<decltype(last_failed_line)>::max();
    while(++lines_cntr <= static_cast<std::size_t>(in_size))
    {
        in_stream >> read;
        {
            try
            {
                ip_list.emplace_back(ip_filter::parse_address(read));
                read.clear();
            }
            catch(ip_filter::ParseErr e)
            {
                std::cerr << "Failed to process ip address at line "
                          << lines_cntr << ": incorrect address format" << std::endl;
                last_failed_line = lines_cntr;
                --lines_cntr;
            }
            catch(std::exception& e)
            {
                std::cerr << "Failed to process ip address at line "
                          << lines_cntr << ": " << e.what() << std::endl;
                return std::make_pair(addr_collection_t{}, lines_cntr);
            }
        }
        in_stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return std::make_pair(ip_list, last_failed_line);
}

}
