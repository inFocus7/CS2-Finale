#pragma once
#include <iostream>
#include <algorithm>
#include "dictionary.h"

template <typename T>
class minHeap
{
private:
	T * items;
	int numItems;

	//return index of index i's parent
	int parent(int i)
	{
		return (i - 1) / 2;
	}

	int lchild(int i)
	{
		return 2 * i + 1;
	}

	int rchild(int i)
	{
		return lchild(i) + 1;
	}

	int findIndex(T x) // O(n)
	{
		for (int index{ 0 }; index < numItems; index++)
		{
			if (x->word == items[index]->word)
			{
				return index;
			}
		}
		return 0;
	}


public:
	minHeap()
	{
		items = new T[100];
		numItems = 0;
	}

	minHeap(int cap)
	{
		items = new T[cap];
		numItems = 0;
	}

	bool updateNeeded(int index, T x)
	{
		if (items[parent(index)]->distance > x->distance)
		{
			return true;
		}
		else
		{
			return childProblem(index);
		}

	}

	//is item at index i
	//in violation with
	//either of it's children
	bool childProblem(int i)
	{
		if (lchild(i) >= numItems) //  0 children)
		{
			return false;
		}
		else if (rchild(i) == numItems) // 1 child)
		{
			if (items[lchild(i)]->distance < items[i]->distance)
				return true;
			else
				return false;
		}
		else //2 children
		{
			int smallerVal = std::min(items[lchild(i)]->distance, items[rchild(i)]->distance);
			if (smallerVal < items[i]->distance)
				return true;
			else
				return false;
		}
	}

	bool empty()
	{
		if (numItems == 0)
		{
			return true;
		}
		return false;
	}

	//add x to the min heap
	//O(log n) worst case run time
	void insert(T x)
	{
		//step 1: put x at bottom of heap
		items[numItems] = x;
		numItems++;

		//step 2: bubble x up heap
		//until there is no more violation
		int current = numItems - 1;
		while (items[current]->distance < items[parent(current)]->distance)
		{
			std::swap(items[current], items[parent(current)]);
			current = parent(current);
		}
	}

	//O(log n) worst case run time
	T extractMin() //Did this delete it though..?
	{
		//write down root item for output
		int minVal = items[0]->distance;
		T minT = items[0];

		//put bottom heap item at root
		//decrement numItems
		items[0] = items[numItems - 1];
		numItems--;

		//bubble current item down heap
		//until there is no more violation
		int current = 0;
		while (childProblem(current))
		{
			//swap current with smaller child
			if (rchild(current) == numItems) // 1 child)
			{
				std::swap(items[current], items[lchild(current)]);
				current = lchild(current);
			}
			else //2 children case
			{
				if (items[lchild(current)]->distance < items[rchild(current)]->distance)
				{
					std::swap(items[current], items[lchild(current)]);
					current = lchild(current);
				}
				else
				{
					std::swap(items[current], items[rchild(current)]);
					current = rchild(current);
				}
			}
		}

		return minT;
	}

	void testDisplay()
	{
		for (int i = 0; i < numItems; i++)
		{
			std::cout << items[i]->distance << " ";
		}
		std::cout << '\n';
	}

	void relax(T &V, unsigned int updatedMin) //relaxor function
	{
		//update
		V->distance = updatedMin; //Does it update it overall??

								  // Check if these functions even work...

		int index = findIndex(V);

		while (updateNeeded(index, V)) //Update minHeap based on change
		{
			if (items[parent(index)]->distance > V->distance)
			{
				std::swap(items[index], items[parent(index)]);
				index = parent(index);
			}
			//swap current with smaller child
			else if (rchild(index) == numItems) // 1 child)
			{
				std::swap(items[index], items[lchild(index)]);
				index = lchild(index);
			}
			else //2 children case
			{
				if (items[lchild(index)]->distance < items[rchild(index)]->distance)
				{
					std::swap(items[index], items[lchild(index)]);
					index = lchild(index);
				}
				else
				{
					std::swap(items[index], items[rchild(index)]);
					index = rchild(index);
				}
			}
		}

	}
};