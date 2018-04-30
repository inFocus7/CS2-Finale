#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <string>
#include "dictionary.h"
#include "bst.h"
#include "heap.h"

bool inputProblem(std::string start, std::string target)
{
	if (start.size() != target.size() || target.size() > 4 || target.size() == 0)
	{
		return true;
	}
	return false;
}

void to_lower(std::string &str)
{
	std::transform(str.begin(), str.end(), str.begin(), std::tolower);
}

int main()
{
	std::ifstream dictionaryWord;
	dictionaryWord.open("largedictionary.txt");
	dictionaryGraph dictonary;
	//Tried storing for making balanced BST, but didn't work since it involved recursion ---> Stack Overflow...

	// 1) Store every word into graph. 
	for (std::string line; std::getline(dictionaryWord, line);)
	{
		if (line.size() <= 4) // Saves space, hinders speed due to added comparison n times... I think it's worth the cost.
		{
			dictonary.addVertex(line, line.size());
		}
	}

	// 2) Connect based on first character (alphabeticaly) AND word length?
		// The reason for word length connection is because you don't have to look at other lengths.
		// The reason for alphabetical connection is because it could make it 


	// 3) Ask User For Start && Target
	std::string start, target;
	do {
		std::cout << "Input words \"<start> <target>\"...\n";
		std::cin >> start >> target;
		std::cout << "Starting at " << start << " and ending at " << target << '\n';
		if (inputProblem(start, target))
		{
			std::cout << "Please make sure to insert two words within 2-4 characters long with equal lengths...\n";
		}
	} while (inputProblem(start, target));
		// Make lowercased for easier comparisons with dictionary
	to_lower(start);
	to_lower(target);

	// 4) Display Shortest Path


	std::cout << "Done!\n";

    return 0;
}