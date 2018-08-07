// bst.cpp: BST Map

#include "map.h"

#include <stdexcept>

// Prototypes ------------------------------------------------------------------

Node *insert_r(Node *node, const int &key, std::string subred, const int &art_num, const int &max, const int &min, const int &range);
Node *search_r(Node *node, const int &key);
void    dump_r(Node *node, std::ostream &os, Dumpflag flag);

// Methods ---------------------------------------------------------------------

void BSTMap::destroy_r(Node* node)
{
    if (node){
        destroy_r(node->left);
        destroy_r(node->right);
        delete node;
    }
}
BSTMap::~BSTMap(){
    destroy_r(root);
}

void            BSTMap::insert(const int &key, std::string subred, const int &art_num, const int &max, const int &min, const int &range) {
        root = insert_r(root, key, subred, art_num, max, min, range);
}

const Entry     BSTMap::search(const int &key) {
        Node* node = search_r(root, key);   
        if (node == nullptr) return NONE;
        return node->entry;       
}

void            BSTMap::dump(std::ostream &os, Dumpflag flag) {
        dump_r(root, os, flag);
}

// Internal Functions ----------------------------------------------------------

Node *insert_r(Node *node, const int &key, std::string subred, const int &art_num, const int &max, const int &min, const int &range)
{
    std::tuple<std::string, int, int, int, int> tup = std::make_tuple(subred, art_num, max, min, range);
    if (node == nullptr){
        Node* newNode = new Node(Entry(key,tup),0,nullptr,nullptr); 
        /*
        newNode->entry = Entry(key,value);
        newNode->left = nullptr;
        newNode->right = nullptr;
        newNode->priority = 0; */
        return newNode;
    } /*else if (key.compare(node->entry.first) == 0) {
        node->entry.second = tup;
        return node;
    }*/

    if (key > node->entry.first){
        node->left = insert_r(node->left, key, subred, art_num, max, min, range);
    } else {
        node->right = insert_r(node->right, key, subred, art_num, max, min, range);
    }
    return node;
}

Node *search_r(Node *node, const int &key) {
    if (node == nullptr || key == node->entry.first) return node;
    if (key > node->entry.first) return search_r(node->right, key);
    return search_r(node->left, key);
}

void dump_r(Node *node, std::ostream &os, Dumpflag flag) {
    if (node == nullptr) return;
    dump_r(node->left, os, flag);

    os << std::get<0>(node->entry.second) << ":\n Articles_Extracted: " << std::get<1>(node->entry.second) << "\n Mean: " << node->entry.first << "\n Max: " << std::get<2>(node->entry.second) << "\n Min: " << std::get<3>(node->entry.second) << "\n Range: " << std::get<4>(node->entry.second) << "\n" << std::endl; 

    /*
    switch (flag) {
        case DUMP_KEY:          os << node->entry.first  << std::endl; break;
        case DUMP_VALUE:        os << std::get<0>(node->entry.second) << std::get<1>(node->entry.second) << std::get<2>(node->entry.second) << std::get<3>(node->entry.second) << std::endl; break;
        case DUMP_KEY_VALUE:    
            os << node->entry.first  << ":\n\tArticles Extracted: " << std::get<0>(node->entry.second) << "\n\tMean: " << std::get<1>(node->entry.second) << "\n\tMax: " << std::get<2>(node->entry.second) << "\n\tMin: " << std::get<3>(node->entry.second) << "\n\tRange: " << std::get<4>(node->entry.second) << "\n" << std::endl; 
            break;
        case DUMP_VALUE_KEY:    os << std::get<0>(node->entry.second) << std::get<1>(node->entry.second) << std::get<2>(node->entry.second) << std::get<3>(node->entry.second) << "\t" << node->entry.first  << std::endl; break;
    }*/
    dump_r(node->right, os, flag);
}

// vim: set sts=4 sw=4 ts=8 expandtab ft=cpp:
