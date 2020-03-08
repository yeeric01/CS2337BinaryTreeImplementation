/*
 * word.h
 *
 *  Created on: Nov 6, 2019
 *      Author: Eric
 */

#ifndef WORD_H_
#define WORD_H_
#include <string>
#include <algorithm>
#include <cstring>
#include <iostream>
#include "binarySearchTree.h"
#include <vector>
#include <iterator>
class word
{
	//friend declaration for the << operator method to access the contents inside the word class
	friend std::ostream& operator<<(std::ostream&, const word&);
public:
	//constructor, assignment operator, empty constructor
	word(std::string str);
	word& operator=(const word& other);
	word()
	{
	}
	//==, <, > assignment operator
	bool operator==(const word& other)
	{
		return data.compare(other.data) == 0;
	}
	bool operator<(const word& other)
	{
		return data.compare(other.data) < 0;
	}
	bool operator>(const word& other)
	{
		return data.compare(other.data) > 0;
	}
	//insert a string into the vect of the word
	void insertInVect(std::string str)
	{
		vect.push_back(str);
	}
	//get the "key" of the word, the alphabetized characters
	std::string getData() const
	{
		return data;
	}
	//get the value of the unalphabetized series of characters that was last stored
	std::string getActualValue() const
	{
		return actualValue;
	}
	//print the whole vect according to how many elements are in the vector
	void printVect() const;
private:
	//instance variables
	std::string data;
	std::string actualValue;
	std::vector<std::string> vect;
};
std::ostream& operator<<(std::ostream& out, const word& outputWord);

#endif /* WORD_H_ */
