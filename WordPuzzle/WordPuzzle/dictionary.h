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

		vertex(std::string x)
		{
			word = x;
			wordLength = x.length();
		}
	};

	binarySearchTree<vertex *> WL1Master, WL2Master, WL3Master, WL4Master;  // Since only involving 4 lengths of equal sizes, made a forest.
	std::vector<vertex *> letterPointer;
	int numItems{ 0 }, attempt{ 0 }; //Total

public:

	dictionaryGraph()
	{

	}

	vertex * findVertex(std::string x, int y)
	{
		switch (y)
		{
		case 1:
			return WL1Master.findVinN(x);
			break;
		case 2:
			return WL2Master.findVinN(x);
			break;
		case 3:
			return WL3Master.findVinN(x);
			break;
		case 4:
			return WL4Master.findVinN(x);
			break;
		default:
			break;
		}
	}

	void addVertex(std::string x) // Adding makes connections. really really slow because connections... 
	{
		switch (x.length())
		{
		case 1:
			WL1Master.insert(new vertex(x)); // n
			WL1Master.connector(x); //*** Should work from the beginning since going through list every time a new vertice is added... I think.
			break;
		case 2:
			WL2Master.insert(new vertex(x));
			WL2Master.connector(x);
			break;
		case 3:
			WL3Master.insert(new vertex(x));
			WL3Master.connector(x);
			break;
		case 4:
			WL4Master.insert(new vertex(x));
			WL4Master.connector(x);
			break;
		default:
			break;
		}

		numItems++;
	}

	void addEdge(std::string x, std::string y) // Strings are "positions"
	{
		vertex * xVertex = findVertex(x, x.length());
		vertex * yVertex = findVertex(y, y.length());

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

	bool inDictionary(std::string x, std::string y)
	{
		switch (x.length())
		{
		case 1:
			return (WL1Master.inDictionary(x) && WL1Master.inDictionary(y));
			break;
		case 2:
			return (WL2Master.inDictionary(x) && WL2Master.inDictionary(y));
			break;
		case 3:
			return (WL3Master.inDictionary(x) && WL3Master.inDictionary(y));
			break;
		case 4:
			return (WL4Master.inDictionary(x) && WL4Master.inDictionary(y));
			break;
		default:
			break;
		}
	}

	void shortestPath(std::string x, std::string y)
	{
		attempt++;
		// Priority Queue (make everything UINT_MAX if needed)
		if (attempt > 1) //if done more than once, made this so that the first try could be fast and the rest would be normal since reinitializatio stuff
		{
			switch (x.length()) //max all
			{
			case 1:
				WL1Master.makeMax();
				break;
			case 2:
				WL2Master.makeMax();
				break;
			case 3:
				WL3Master.makeMax();
				break;
			case 4:
				WL4Master.makeMax();
				break;
			default:
				break;
			} //dont need to reset prior since they'll change
		}

		minHeap<vertex *> Q(numItems);
		findVertex(x, x.length())->distance = 0; // set start to 0
		switch (x.length()) // push 'em into bag
		{
		case 1:
			WL1Master.step_0(Q);
			break;
		case 2:
			WL2Master.step_0(Q);
			break;
		case 3:
			WL3Master.step_0(Q);
			break;
		case 4:
			WL4Master.step_0(Q);
			break;
		default:
			break;
		}

		while (!Q.empty())
		{
			// 1) Get min
			vertex * min = Q.extractMin();
			min->visited = true;
			// 2) Update its neighbors if needed
			for (unsigned int i{ 0 }; i < min->neighbors.size(); i++)
			{
				if (min->neighbors[i]->visited == false && (min->distance + 1) < min->neighbors[i]->distance)
				{
					Q.relax(min->neighbors[i], (min->distance + 1));
					min->neighbors[i]->prior = min;
				}
			}
		}

		linkedStack<vertex *> path;
		for (vertex * curr = findVertex(y, y.length()); curr != findVertex(x, x.length()); curr = curr->prior)
		{
			path.push(curr);
		}
		// 4) Show solved ladder
			//start (since not stored from the previous for loop)
		std::cout << x << '\n';
			//rest to goal
		while (!path.empty())
		{
			std::cout << path.pop()->word << '\n';
		}
	}

};