//Melissa Ng, S10177744H | Jeremy John, S10177825B
#include "stdafx.h"
#include "trie.h"
#include <fstream>
#include <algorithm>

using namespace std;

string alphabetList[26] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"};
int countSearches = 0; //count the number of searches

//creating struc for tree
struct TrieNode *new_node() {
	TrieNode *node = new TrieNode;

	for (auto &i : node->children)
	{
		i = nullptr;
	}
    node->leaf = false;
	return node;
}

//creating a tree
Trie::Trie() {
    root = new_node();
}

//inserting into the tree
void Trie::insert(string str) { //get input
	TrieNode *node = root; //creating a temp node

    for (char &i : str) { //for a letters in the string
        int index = i - 'a'; //getting the position of the letter
		
        if (index < 0 || index > DOMAIN_SIZE) continue; //checking the ranges

        if (!node->children[index]) //if letter doesnt exist in the tree
            node->children[index] = new_node(); //create a new branch

        node = node->children[index]; //point node to that letter
    }

    node->leaf = true; //return true when done wth all letters in the word
}

//search the tree 
bool Trie::search(string str) { //get input 
	TrieNode *node = root; //create a temp node

	for (char &i : str) { //for all letters in the string
		i = tolower(i);
		int index = i - 'a'; //getting the position of the letter

		if (index < 0 || index > DOMAIN_SIZE) continue; //checking the ranges

		if (!node->children[index])
		{
			return false;
		}
		node = node->children[index];//point to the next node
	}
	return (node != nullptr && node->leaf);;
}

//moving the node through the list
void traverse(TrieNode *node, const string &str, vector<string> *content) {
    if (node->leaf) content->push_back(str); //adds an elements to the end of a vector
    for (int i = 0; i < DOMAIN_SIZE; i++) { 
        auto child = node->children[i]; 
		if (child != nullptr) {
			traverse(child, str + static_cast<char>(i + 'a'), content);
		}
    }
}

//Traversing through a list
vector<string> *Trie::all() {
    auto result = new vector<string>();
    traverse(root, "", result);
    return result;
}

//Traversing through a list with an indicated starting letter
vector<string> *Trie::all_with_prefix(string str) {
    auto result = new vector<string>();
	TrieNode *node = root;

    for (char &i : str) {
        int index = i - 'a';

		if (!node->children[index]) { return result; }
        node = node->children[index];
    }

    traverse(node, str, result);
    return result;
}

// insertion error
bool Trie::insertion(string str) { //get input 
	bool check = false;
	countSearches = 0;
	if (search(str))
	{
		return false;
	}
	else
	{
		for (int i = 0; i < str.length(); i++)
		{
			string insertionString = str;
			countSearches++;
			insertionString.erase(i, 1);
			if (search(insertionString))
			{
				cout << "Insertion error detected. ";
				cout << "Instead of " + str +", did you mean: " + insertionString + "?" << endl;
				check = true;
				//break;
			}
		}
			deletion(str);
		return true;
	}
}

// deletion error
bool Trie::deletion(string str) { //get input 
	bool check = false;

	for (int i = 0; i < str.length(); i++)
	{
		for (int a = 0; a < 26; a++) {
			countSearches++;
			string deletionString = str;
			deletionString.insert(i, alphabetList[a]);
			if (search(deletionString))
			{
				cout << "Deletion error detected. ";
				cout << "Instead of " + str + ", did you mean: " + deletionString + "?" << endl;
				check = true;
				//goto here;
			}
		}
	}
	//here:
		substitution(str);
	return true;
}

// substitution error
bool Trie::substitution(string str) { //get input 
	bool check = false;

	for (int i = 0; i < str.length(); i++)
	{
		for (int a = 0; a < 26; a++) {
			countSearches++;
			string substitutionString = str;
			substitutionString.replace(i, 1, alphabetList[a]);
			if (search(substitutionString))
			{
				cout << "Substitution error detected. ";
				cout << "Instead of " + str + ", did you mean: " + substitutionString + "?" << endl;
				check = true;
				//break;
			}
		}
	}
		transposition(str);
	return true;
}

// transposition error
bool Trie::transposition(string str) { //get input 
	bool check = false;

	for (int i = 0; i < str.length()-1; i++)
	{
		countSearches++;
		string transpositionString = str;
		swap(transpositionString[i], transpositionString[1+i]);
		if (search(transpositionString))
		{
			cout << "Transposition error detected. ";
			cout << "Instead of " + str + ", did you mean: " + transpositionString + "?" << endl;
			check = true;
			break;
		}
	}
	if (!check)
	{
		cout << str + " is not found." << endl;
		cout << "Number of Comparisons done: " << countSearches << endl << endl;
		return false;
	}
	cout << "Number of Comparisons done: " << countSearches << endl << endl;
	return true;
}

