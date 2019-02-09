//Melissa Ng, S10177744H | Jeremy John, S10177825B
#pragma once

#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int DOMAIN_SIZE = 26;

struct TrieNode
{
    struct TrieNode *children[DOMAIN_SIZE];
    bool leaf;
};


class Trie
{
  private:
    TrieNode *root;

  public:
    Trie();

    void insert(string str);
    bool search(string str);
    vector<string> * all();
    vector<string> * all_with_prefix(string str);
	bool insertion(string str);
	bool deletion(string str);
	bool substitution(string str);
	bool transposition(string str);
};