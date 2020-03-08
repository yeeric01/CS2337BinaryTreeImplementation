/*
 * word.cpp
 *
 *  Created on: Nov 6, 2019
 *      Author: Eric
 */
#include "word.h"
//print the words in the vetors of the world class accordingly to how many
//elements are in the vecotr
void word::printVect() const
{
	if(vect.size() != 0)
	{
		if(static_cast<int>(vect.size()) > 1)
			std::cout << " maps to words: ";
		else
			std::cout << " maps to word: ";
		int size = static_cast<int>(vect.size());
		for(int i = 0; i < size; ++i)
		{
			std::cout << vect.at(i);
			if(i != size - 1)
				std::cout << " ";
		}
		std::cout << std::endl;
		std::cout << std::endl;
	}
	else
	{
		std::cout << " was not found" << "\n";
		std::cout << "\n";
	}
}
//constructor
word::word(std::string str)
{
	vect.push_back(str);
	actualValue = str;
	data = str;
	transform(data.begin(), data.end(), data.begin(), ::tolower);
	std::sort(data.begin(), data.end());
}
//copy assignment operator
word& word::operator=(const word& other)
{
	this->data = other.data;
	this->vect = other.vect;
	return *this;
}
//operator overload for ostream
std::ostream& operator<<(std::ostream& out, const word& outputWord)
{
	out<<"[" << outputWord.data << ", " << "{";
	int size = static_cast<int>(outputWord.vect.size());
	for(int i = 0; i < size; ++i)
	{
		out << outputWord.vect.at(i);
		if(i != size - 1)
			out << ", ";
	}
	out << "}" << "]";
	return out;
}



