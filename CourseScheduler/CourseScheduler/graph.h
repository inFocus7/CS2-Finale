#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <fstream>
#include <sstream>
#include "binaryST.h"

/* NOTES
vertex: course
neighbors: what you can take after this vertex
visited: taken
prereqs: prerequisites for this vertex
NOTES */

class digraph
{
private:
	class vertex
	{
	public:
		std::string data;
		std::vector<vertex *> neighbors;
		std::vector<vertex *> prereqs;

		bool visited;

		vertex(std::string x)
		{
			data = x;
			visited = false;
		}

		bool canTake()
		{
			for (int i = 0; i < prereqs.size(); i++)
			{
				if (prereqs[i]->visited == false) // If any pre-requisite has not been taken/visited. return can't take (false).
				{
					return false;
				}
			}
			return true;
		}
	};

	void bfs(vertex * p)
	{

	}

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

	void addDirectedEdge(std::string x, std::string y)  //X is prereq of Y O(log(n))
	{
		vertex * xVertex = findVertex(x);
		vertex * yVertex = findVertex(y);

		if (xVertex != nullptr && yVertex != nullptr)
		{
				//Made two for now to see how I would traverse, then will erase one if it isn't needed.
			xVertex->neighbors.push_back(yVertex); // After X, you can take (can go to) Y (a neighbor)
			yVertex->prereqs.push_back(xVertex); // X is a prerequisite of Y.
			//std::cout << xVertex->data << " is a pre-requisite of " << yVertex->data << '\n'; Test code.
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

		while (!Q.empty())
		{
			vertex * x = Q.front();
			Q.pop();

			std::cout << x->data << '\n';

			for (int i = 0; i < x->neighbors.size(); i++) //check all of p's neighbors
			{
				if (x->neighbors[i]->canTake() && x->neighbors[i]->visited == false) //push em in if all prereqs taken
				{
					Q.push(x->neighbors[i]);
					x->neighbors[i]->visited = true;
				}
			}
		}
	}

	void displaySchedule()
	{
		// 1) Insert dummy vertex to connect any w/o prereqs. Didn't do this as default const since you won't know until after.		
				//DISPLAY DATA TEST
				//masterList.displayAllData(); 
		std::vector<vertex*> noPrereqs = masterList.findEasy();
		addVertex("DUMMY CONNECTOR");
		for (unsigned int i = 0; i < noPrereqs.size(); i++)
		{
			addDirectedEdge("DUMMY CONNECTOR", noPrereqs[i]->data);
		}
		noPrereqs.~vector();
			//BFS FROM DUMMY CONNECTOR AND ONLY SHOW VERTEX WHERE PREREQS ARE ALL MARKED VISITED
		BFS(findVertex("DUMMY CONNECTOR"));
	}
};