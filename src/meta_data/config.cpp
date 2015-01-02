#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <cassert>
#include <exception>
#include <iostream>
#include <string>
#include "rpc.hpp"
int constructOSD(const char *file)
{
    try
    {
 
        boost::property_tree::ptree pt;
        boost::property_tree::read_json(file, pt);
 
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, 
		      pt.get_child("OSD"))
        {
            std::cout << "OSD :" << v.second.data() << std::endl;
	    add_client(v.second.data().c_str());

        }
        return 0;
    }
    catch (std::exception const& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return -1;
}
