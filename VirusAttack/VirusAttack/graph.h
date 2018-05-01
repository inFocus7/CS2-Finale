#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <fstream>
#include "binaryST.h"

class digraph
{
private:
	class vertex
	{
	public:
		std::string data;
		std::vector<vertex *> neighbors;

		bool visited;

		vertex(std::string x)
		{
			data = x;
			visited = false;
		}

	};

	//std::vector<vertex*> vertexList; //switch to bst later...
	binarySearchTree<vertex *> masterList;

public:

	digraph()
	{

	}

	vertex * findVertex(std::string x) // O(log(|v|))
	{
		return masterList.findVinN(x);
	}

	void addVertex(std::string x) //add vertex into master masterList
	{
		masterList.insert(new vertex(x));
	}

	void addEdge(std::string x, std::string y)  
	{
		vertex * xVertex = findVertex(x);
		vertex * yVertex = findVertex(y);

		if (xVertex != nullptr && yVertex != nullptr)
		{
				//Made two for now to see how I would traverse, then will erase one if it isn't needed.
			xVertex->neighbors.push_back(yVertex);
			yVertex->neighbors.push_back(xVertex);
		}
		else
		{
			std::cout << "You misspelled something.\n";
		}
	}

	void BFS(vertex * p)
	{
		std::queue<vertex *> Q;
		p->visited = true;
		Q.push(p);
		
		std::cout << "Infected Computers: ";

		while (!Q.empty())
		{
			vertex * x = Q.front();
			Q.pop();

			std::cout << x->data << ' ';

			for (int i = 0; i < x->neighbors.size(); i++) // the neighbors are the computers connected through it.
			{
				if (x->neighbors[i]->visited == false) // if not visited, visit.
				{
					Q.push(x->neighbors[i]);
					x->neighbors[i]->visited = true;
				}
			}
		}

		std::cout << '\n';
	}

	void displayInfected(std::string infected)
	{
		BFS(findVertex(infected));
	}
};