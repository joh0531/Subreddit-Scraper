#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>

typedef enum {
    DUMP_KEY,
    DUMP_VALUE,
    DUMP_KEY_VALUE,
    DUMP_VALUE_KEY,
} Dumpflag;

typedef std::pair<int, std::tuple<std::string, int, int, int, int> > Entry;

extern const Entry NONE;

struct Node { 
    Node() {
        priority = 0;
        left = nullptr;
        right = nullptr;
        entry=NONE;
    }
    Node(Entry entry, int priority, Node* left, Node*right)
    {
        this->entry = entry;
        this->priority = priority;
        this->left = left;
        this->right = right;
    }
    
    Entry entry;
    int priority;
    Node * left;
    Node * right;

};

class Map {
    public:
        virtual void            insert(const int &key, std::string subred, const int &art_num, const int &max, const int &min, const int &range) {}
        virtual const Entry     search(const int &key) {return NONE; }
        virtual void            dump(std::ostream &os, Dumpflag flag) {}
        virtual                 ~Map() {}
};

class RBTreeMap : public Map {
    public:
        void            insert(const int &key, std::string subred, const int & art_num, const int &max, const int &min, const int &range);
        const Entry     search(const int &key);
        void            dump(std::ostream &os, Dumpflag flag);
    private:
        std::multimap<int, std::tuple<std::string, int, int, int, int> > entries;
};

class BSTMap : public Map {
    public:
        void            destroy_r(Node* node);
        ~BSTMap();
        void            insert(const int &key, std::string subred, const int &art_num, const int &max, const int &min, const int &range);
        const Entry     search(const int &key);
        void            dump(std::ostream &os, Dumpflag flag);
    private:
        Node* root = nullptr;
};

class TreapMap : public Map {
    public:
        void            destroy_r(Node* node);
        ~TreapMap();
        void            insert(const int &key, std::string subred, const int &art_num, const int &max, const int &min, const int &range);
        const Entry     search(const int &key);
        void            dump(std::ostream &os, Dumpflag flag);
    private:
        Node* root = nullptr;
};

