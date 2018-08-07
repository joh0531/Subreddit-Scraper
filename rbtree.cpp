#include "map.h"
#include <algorithm>

void        RBTreeMap::insert(const int &key, std::string subred, const int &art_num, const int &max, const int &min, const int &range) {
    //fprintf(stderr, "inserting\n");
    //std::cout << "inserting\n";
    entries.insert(std::pair<int, std::tuple<std::string, int, int, int ,int> >(key, std::make_tuple(subred, art_num, max, min, range)));
}

const Entry RBTreeMap::search(const int &key) {
    auto result = entries.find(key);
    if (result == entries.end())
        return NONE;
    else    
        return *result;
}

void        RBTreeMap::dump(std::ostream &os, Dumpflag flag) {
    for (auto it = entries.rbegin(); it != entries.rend(); it++) {
        //os << "potato\n";
        os << std::get<0>(it->second) << ":\n Articles_Extracted: " << std::get<1>(it->second) << "\n Mean: "  << it->first << "\n Max: " << std::get<2>(it->second) << "\n Min: " << std::get<3>(it->second) << "\n Range: " << std::get<4>(it->second) << "\n" << std::endl; 

        /*
        switch (flag) {
            case DUMP_KEY:          os << it->first << std::endl; break;
            case DUMP_VALUE:        os << std::get<0>(it->second) << std::get<1>(it->second) << std::get<2>(it->second) << std::get<3>(it->second) << std::endl; break;
            case DUMP_KEY_VALUE:    
                os << it->first << ":\n\tArticles Extracted: " << std::get<0>(it->second) << "\n\tMean: "  << std::get<1>(it->second) << "\n\tMax: " << std::get<2>(it->second) << "\n\tMin: " << std::get<3>(it->second) << "\n\tRange: " << std::get<4>(it->second) << "\n" << std::endl; 
                break;
            case DUMP_VALUE_KEY:    os << std::get<0>(it->second) << std::get<1>(it->second) << std::get<2>(it->second) << std::get<3>(it->second) << "\t" << it->first << std::endl; break;
        }
        */
    }
}

