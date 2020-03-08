//============================================================================
// Name        : Assignment.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "binarySearchTree.h"
#include "word.h"
#include <string>
//adds the newItem actual string data to the existing item's vector
void duplicateItem(word &existingItem, const word &newItem)
{
	std::string str = newItem.getActualValue();
	existingItem.insertInVect(newItem.getActualValue());
}
//print the vector of the word if the node is found
void foundNode(const word& anotherWord)
{
	anotherWord.printVect();
}
//main method, first stores all the english words in a tree and tests the user's data
//with the data already stored in the tree and gives values accordingly
int main()
{
	std::cout << "Test of find words" << "\n";
	std::cout << "\n";
	binarySearchTree<word> mainTree;
	std::ifstream myfile ("english_words.txt");
	std::string input;
	if(myfile.is_open())
	{
		while(myfile >> input)
		{
			word newWord(input);
			mainTree.insert(newWord, duplicateItem);
		}
	}
	std::cout << "The dictionary has been built with 32180 keys in the dictionary" << "\n";
	std::string userInput = "";
	while(userInput.compare("quit-now") != 0)
	{
		std::cout << "Word to unscramble (quit-now to stop):" << "\n";
		std::cout << "\n";
		std::cin >> userInput;
		if(userInput.compare("quit-now") != 0)
		{
			word newWord(userInput);
			std::cout << "Scrambled word " << userInput;
			bool isFound = mainTree.find(newWord, foundNode);
			if(!isFound)
				std::cout << " was not found" << std::endl << std::endl;
		}
	}
	myfile.close();
	return 0;
}
