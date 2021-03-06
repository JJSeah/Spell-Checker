//Melissa Ng, S10177744H | Jeremy John, S10177825B
// Assignment.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <string>
#include "trie.h"

using namespace std;
Trie Dict;

//Loading the dictionary into the Trie tree
bool loadDict() {
	ifstream dictionary;
	dictionary.open("dictionary10KR.csv");

	if (!dictionary.is_open()) {
		return false;
	}

	string word;
	while (!dictionary.eof()) {
		getline(dictionary, word);
		Dict.insert(word.c_str());
	}

	dictionary.close();
	return true;
}
// Displays the main menu.
void printMainMenu() {
	cout << "What would you like to do?" << endl;
	cout << " [1] Spell check a word" << endl;
	cout << " [2] Spell check a file" << endl;
	cout << " [3] Add a new word" << endl;
	cout << " [4] Save dictionary " << endl;
	cout << " [5] Search for a word" << endl;
	cout << " [0] Exit" << endl;
	cout << endl;
}

//Spell checks words
void spellCheckWord() {
	string input;
	cout << "What word would you like to check?\n" << endl;
	//cin >> input;
	getline(cin, input);
	getline(cin, input);
	if (!Dict.insertion(input.c_str())) {
		cout << "The word is spelled correctly!\n" << endl;
	};
}

// Spell checks an entire file.
bool spellCheckFile() {
	cout << "Enter the file name: ";

	string filename;
	cin >> filename;

	ifstream test(filename);
	if (!test)
	{
		cout << "The file doesn't exist" << endl;
		return false;
	}
	else {
		ifstream input;
		input.open(filename);

		if (!input.is_open()) {
			return false;
		}

		string word;

		while (!input.eof()) {
			getline(input, word);
			Dict.insertion(word);
		}
		return true;
	}
}

//Addition of words into the dictionary
void addWord() {
	cout << "Enter your word: ";

	string word;
	getline(cin, word);
	getline(cin, word);

	if (!Dict.search(word)) {
		Dict.insert(word);
		cout << word << " added sucessfully\n" << endl;
	}
	else {
		cout << word << " already exists in the dictionary\n" << endl;
	}
	
}

//Save the dictionary
bool saveDictionary() {
	ofstream dictionary;
	dictionary.open("dictionary10KR.csv");

	if (!dictionary.is_open()) {
		return false;
	}
	auto words = Dict.all();
	for (auto &i : *words) {
		dictionary << i << endl;
	}
	cout << "Dictionary saved successfully." << endl << endl;
}

//Print words with indicated starting letter
void printWordsWithPrefix() {
	cout << "Enter the first letter: ";

	string prefix;
	cin >> prefix;

	cout << "Finding words..." << endl;

	// Output each word to the screen.
	auto results = Dict.all_with_prefix(prefix);
	for (auto &i : *results)
		cout << i << endl;

	cout << endl;
}

//Main Function
int main()
{
	// Load the dictionary into the trie.
	if (!loadDict()) {
		cout << "Error: Failed to load dictionary!" << endl;
		return 1;
	}
	// Start the main loop.
	while (true) {
		printMainMenu();

		int option;
		cin >> option;
		cout << endl;

		if (cin.fail())
		{
			cout << "Invalid Entry\nEnter an option from 0-5\n" << std::endl;
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else{
			switch (option) {
			case 1:
				spellCheckWord();
				break;
			case 2:
				if (!spellCheckFile()) {
					cout << "Error: Failed to load file!" << endl << endl;
				}
				break;
			case 3:
				addWord();
				break;
			case 4:
				saveDictionary();
				break;
			case 5:
				printWordsWithPrefix();
				break;
			case 0:
				return 0;
			}
		}
	}
	return 0;
}


bool Stack::pop(int &item)
{
	bool success = (!isEmpty());
	if (success)
	{
		item = array[top];
		top--
	}
	return success
}