#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <fstream>
#include <sstream>
#include "binaryST.h"

class mazeGraph
{
private:
	class vertex
	{
	public:
		char data;
		//std::string position; //position in graph used to connect.
		int xPosition, yPosition;
		std::vector<vertex *> neighbors; //Should I replace with up, down, left, right?
		bool visited{ false };
		vertex * prior;
		unsigned int distance{ UINT_MAX };

		vertex(char x, int xP, int yP)
		{
			data = x;
			xPosition = xP;
			yPosition = yP;
		}
	};

	binarySearchTree<vertex *> masterList;
	int numItems{ 0 };

public:

	mazeGraph()
	{

	}

	vertex * findVertex(int xPos, int yPos)
	{
		return masterList.findVinN(xPos, yPos);
	}

	void addVertex(char x, int xP, int yP)
	{
		masterList.insert(new vertex(x, xP, yP));
		numItems++;
	}

	void addEdge(int x1, int y1, int x2, int y2) // Strings are "positions"
	{
		vertex * xVertex = findVertex(x1, y1);
		vertex * yVertex = findVertex(x2, y2);

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

	void shortestPath(int sX, int sY, int eX, int eY)
	{
		// Priority Queue
		minHeap<vertex *> Q(numItems);
		findVertex(sX, sY)->distance = 0;
		masterList.step_0(Q);

		while (!Q.empty())
		{
			// 1) Get min
			vertex * min = Q.extractMin();
			min->visited = true;
			// 2) Update its neighbors if needed
			for (int i{ 0 }; i < min->neighbors.size(); i++)
			{
				if (min->neighbors[i]->data != '#' && (min->distance + 1) < min->neighbors[i]->distance)
				{
					Q.relax(min->neighbors[i], (min->distance + 1));
					min->neighbors[i]->prior = min;
				}
			}
		}
		// 3) Make shortest path
		for (vertex * current = findVertex(eX, eY)->prior; current != findVertex(sX, sY); current = current->prior)
		{
			current->data = '.';
		}

		// 4) Show solved maze
		masterList.display();
	}

};