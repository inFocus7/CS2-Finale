#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <string>
#include "dictionary.h"
#include "bst.h"
#include "heap.h"
#include "stack.h"

/*
Loading in 5th letter words adds ~6seconds to boot time.
*/

bool inputProblem(std::string start, std::string target, dictionaryGraph dictionary)
{
	if (start.size() != target.size() || target.size() > 4 || target.size() == 0 || !dictionary.inDictionary(start, target))
	{
		return true;
	}
	return false;
}

void to_lower(std::string &str)
{
	std::transform(str.begin(), str.end(), str.begin(), std::tolower);
}


/* WILL THIS EVEN HELP? MOST LIKELY. */
/* */
// Can't use normal recursion due to stack overflows, must do manually... learn to do this in hopes to increase speed of making vertices...
void balancedTree(std::vector<std::string> vector, dictionaryGraph &dictionary) // divide and conquer into tree?
{
	linkedStack<int> lindx, rindx;
	unsigned int l_Index{ 0 }, r_Index{ vector.size() - 1 }, mid{ 0 };
	lindx.push(l_Index);
	rindx.push(r_Index);
	
	while (!lindx.empty())
	{
		l_Index = lindx.pop();
		r_Index = rindx.pop();

		if (l_Index > r_Index || r_Index > vector.size())
		{

		}
		else
		{
			mid = (l_Index + r_Index) / 2;
			dictionary.addVertex(vector[mid]);

			lindx.push(l_Index);
			rindx.push(mid - 1);

			lindx.push(mid + 1);
			rindx.push(r_Index);
		}
	}
}

int main()
{
	std::ifstream dictionaryWord;
	dictionaryWord.open("largedictionary.txt");
	dictionaryGraph dictionary;
	char retry{ 'n' };
	bool aProblem{ false };
	std::vector<std::string> WL1, WL2, WL3, WL4;

	/* !!!NEW VERSION. MAYBE INCREASES SPEEDS THROUGH BALANCED TREE SINCE PREVIOUS WAS RIGHT LEANING! */
	for (std::string line; std::getline(dictionaryWord, line);)
	{
		if (line.size() <= 4) // Saves space, hinders speed due to added comparison n times... I think it's worth the cost.
		{
			switch (line.size())
			{
			case 1:
				WL1.push_back(line);
				break;
			case 2:
				WL2.push_back(line);
				break;
			case 3:
				WL3.push_back(line);
				break;
			case 4:
				WL4.push_back(line);
				break;
			default:
				break;
			}
		}
	}
	balancedTree(WL1, dictionary);
	std::cout << "done loading and connecting lenght 1\n";
	balancedTree(WL2, dictionary);
	std::cout << "done loading and connecting lenght 2\n";
	balancedTree(WL3, dictionary);
	std::cout << "done loading and connecting lenght 3\n";
	balancedTree(WL4, dictionary);
	std::cout << "done loading and connecting lenght 4\n";

	do
	{
		system("cls");
		std::string start, target;
		do {
			std::cout << "Input words \"<start> <target>\"...\n";
			std::cin >> start >> target;
			std::cout << "Starting at " << start << " and ending at " << target << '\n';

			aProblem = inputProblem(start, target, dictionary);

			if (aProblem)
			{
				std::cout << "Please make sure to insert two words withing 1-4 word length and with equal lengths...\n\n";
			}
		} while (aProblem);
		// Make lowercased for easier comparisons with dictionary
		to_lower(start);
		to_lower(target);
		// 3) Display Shortest Path
		dictionary.shortestPath(start, target);
		std::cout << "Would you like to try two other words? (Y/y/N/n)\n";
		std::cin >> retry;
	} while (retry == 'y' || retry == 'Y');

    return 0;
}