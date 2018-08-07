// treap.cpp: Treap Map

#include "map.h"

#include <climits>
#include <random>

// Prototypes ------------------------------------------------------------------

static Node *insert_r(Node *node, const int &key, std::string subred, const int &art_num, const int &max, const int &min, const int &range);
extern Node *search_r(Node *node, const int &key);
extern void    dump_r(Node *node, std::ostream &os, Dumpflag flag);
static Node *rotate_right(Node *p);
static Node *rotate_left(Node *p);
static int get_random();

// Methods ---------------------------------------------------------------------


void TreapMap::destroy_r(Node* node)
{
        if (node){
                destroy_r(node->left);
                destroy_r(node->right);
                delete node;
        }
}
TreapMap::~TreapMap(){
        destroy_r(root);
}


//TreapMap::~TreapMap() {delete root->left; delete root->right;}

void            TreapMap::insert(const int &key, std::string subred, const int &art_num, const int &max, const int &min, const int &range) {
    root = insert_r(root, key, subred, art_num, max, min, range);
}

const Entry     TreapMap::search(const int &key) {
    Node *node = search_r(root, key);
    if (node == nullptr) return NONE;
    else return node->entry;
}

void            TreapMap::dump(std::ostream &os, Dumpflag flag) {
    dump_r(root, os, flag);
}

// Internal Functions ----------------------------------------------------------

Node *insert_r(Node *node, const int &key, std::string subred, const int &art_num, const int &max, const int &min, const int &range) {
    std::tuple<std::string, int, int, int, int> tup = std::make_tuple(subred, art_num, max, min, range);
    if (node == nullptr) {
        Node *newNode = new Node{Entry(key, tup), get_random(), nullptr, nullptr};
        return newNode;
    }/*
    else if (key.compare(node->entry.first) == 0) {
        node->entry.second = tup;
        return node;
    }
    */
    if (key > node->entry.first /*key.compare(node->entry.first) < 0*/) {
        node->left = insert_r(node->left, key, subred, art_num, max, min, range);
        if (node->left->priority > node->priority) node = rotate_right(node);
    }
    else {
        node->right = insert_r(node->right, key, subred, art_num, max, min, range);
        if (node->right->priority > node->priority) node = rotate_left(node);
    }
    return node;
}

Node *rotate_right(Node *p) {
    Node *c = p->left;
    Node *T2 = c->right;
    c->right = p;
    p->left = T2;
    return c;
}

Node *rotate_left(Node *p) {
    Node *c = p->right;
    Node *T2 = c->left;
    c->left = p;
    p->right = T2;
    return c;
}

int get_random() {
    std::random_device rd;
    std::default_random_engine g(rd());
    std::uniform_int_distribution<int> d(0, INT_MAX);
    return d(g);
}

// vim: set sts=4 sw=4 ts=8 expandtab ft=cpp:
