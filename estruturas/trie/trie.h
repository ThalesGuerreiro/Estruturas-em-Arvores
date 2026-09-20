#ifndef TRIE_H
#define TRIE_H
#include <string>

namespace trie{

class TrieNode {
public:
    TrieNode* children[26];
    bool isEndofWorld;

    TrieNode(){
        isEndofWorld = false;
        for (int i = 0; i < 26; i++){
            children[i] = nullptr;
        }
    }
};

void insert(TrieNode* root, const std::string& key);

bool search(TrieNode* root, const std::string& key);

bool isPrefix(TrieNode* root, const std::string& prefix);

bool isEmpty(TrieNode* root);

TrieNode* removeRecursive(TrieNode* root, const std::string& key, int depth = 0);

bool remove(TrieNode*& root, const std::string& key);

void clear(TrieNode* root);

}

#endif