#pragma once
#include <iostream>
#include "priorityQueue.h"

template <typename T>
class binarySearchTree
{
private:
	class node
	{
	public:
		T data;
		node * left;
		node * right;
		bool newRow{ false };

		node(T x)
		{
			data = x;
			left = nullptr;
			right = nullptr;
		}
	};

	//attributes?
	node * root;

	bool str_small(int x1, int x2, int y1, int y2) //compares to insert position coordinates correctly (not by ascii comparison)
	{

		if (x1 < x2)
		{
			return true;
		}
		else
		{

			if (x1 == x2)
			{
				if (y1 < y2)
				{
					return true;
				}
			}
			return false;
		}
	}

	//insert x into tree rooted at p
	void recInsert(node * &p, T x) //insert based on position in graph
	{

		if (p == nullptr)
		{
			p = new node(x);
		}
		else
		{
			if (str_small(x->xPosition, p->data->xPosition, x->yPosition, p->data->yPosition)) // if insertion is smaller 
			{
				recInsert(p->left, x);
			}
			else // if insertion is greater or equal
			{
				recInsert(p->right, x);
			}
		}
	}

	void inOrder(node * p)
	{
		if (p == nullptr)
		{
			return;
		}
		else
		{
			if (p->newRow == true)
			{
				std::cout << '\n';
			}
			inOrder(p->left);
			std::cout << p->data->data;
			inOrder(p->right);
		}

	}

	void rec_0(node * p, minHeap<T> &Q)
	{
		if (p == nullptr)
		{
			return;
		}
		else
		{
			rec_0(p->left, Q);
			if (p->data->data != '#') // DO NOT INSERT WALLS
			{
				Q.insert(p->data);
			}
			rec_0(p->right, Q);
		}
	}

	unsigned int count;

public:

	binarySearchTree()
	{
		count = 0;
		root = nullptr;
	}

	void step_0(minHeap<T> &Q)
	{
		rec_0(root, Q);
	}

	void insert(T x)
	{
		count++;
		recInsert(root, x);
	}

	node * recfindNode(node * p, int xP, int yP) 
	{
		if (p == nullptr)
		{
			return nullptr;
		}
		else if (p->data->xPosition == xP && p->data->yPosition == yP)
		{
			return p;
		}
		else
		{
			if (str_small(xP, p->data->xPosition, yP, p->data->yPosition))
			{
				return recfindNode(p->left, xP, yP);
			}
			else
			{
				return recfindNode(p->right, xP, yP);
			}
		}
	}

	T findVinN(int xP, int yP)
	{
		return (recfindNode(root, xP, yP))->data;
	}

	bool empty()
	{
		if (count == 0)
		{
			return true;
		}
		return false;
	}

	void display()
	{
		for (int i = 1; i <= maxRowIndex; i++) //don't set first row as "new row"
		{
			recfindNode(root, i, 0)->newRow = true;
		}

		inOrder(root);

		std::cout << '\n';
	}
};
