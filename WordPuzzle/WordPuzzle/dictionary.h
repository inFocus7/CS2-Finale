#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <fstream>
#include <sstream>
#include "bst.h"

class dictionaryGraph
{
private:
	class vertex
	{
	public:
		std::string word;
		int wordLength;
		std::vector<vertex *> neighbors; //Should I replace with up, down, left, right?
		bool visited{ false };
		vertex * prior;
		unsigned int distance{ UINT_MAX };

		vertex(std::string x, int y)
		{
			word = x;
			wordLength = y;
		}
	};

	binarySearchTree<vertex *> masterList;
	int numItems{ 0 };

public:

	dictionaryGraph()
	{

	}

	vertex * findVertex(std::string x)
	{
		return masterList.findVinN(x);
	}

	void addVertex(std::string x, int y)
	{
		masterList.insert(new vertex(x, y));
		numItems++;
	}

	void addEdge(std::string x, std::string y) // Strings are "positions"
	{
		vertex * xVertex = findVertex(x);
		vertex * yVertex = findVertex(y);

		if (xVertex != nullptr && yVertex != nullptr)
		{
			xVertex->neighbors.push_back(yVertex);
			yVertex->neighbors.push_back(xVertex);
			//std::cout << "\tEdge from " << xVertex->position << " to " << yVertex->position << '\n'; //See if edges added
		}
		else
		{
			std::cout << "You misspelled something.\n";
		}
	}

	void shortestPath(std::string x, std::string y)
	{
		// Priority Queue
		minHeap<vertex *> Q(numItems);
		findVertex(x)->distance = 0;
		masterList.step_0(Q);

		while (!Q.empty())
		{
			// 1) Get min
			vertex * min = Q.extractMin();
			min->visited = true;
			// 2) Update its neighbors if needed
			for (unsigned int i{ 0 }; i < min->neighbors.size(); i++)
			{
				if ((min->distance + 1) < min->neighbors[i]->distance)
				{
					Q.relax(min->neighbors[i], (min->distance + 1));
					min->neighbors[i]->prior = min;
				}
			}
		}
		// 3) Make shortest path

		// 4) Show solved maze
	}

};