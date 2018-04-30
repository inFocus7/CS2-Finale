#pragma once
#include <iostream>
#include <sstream>
#include "heap.h"

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

		node(T x)
		{
			data = x;
			left = nullptr;
			right = nullptr;
		}
	};

	//attributes?
	node * root;

	// RECURSION CAUSES 
	void recInsert(node * &p, T x)
	{
		while(p != nullptr) {
			if (x->word < p->data->word) // if insertion is smaller 
			{
				p = p->left;
			}
			else // if insertion is greater or equal
			{
				p = p->right;
			}
		}
		p = new node(x);
	}

	void inOrder(node * p)
	{
		if (p == nullptr)
		{
			return;
		}
		else
		{
			inOrder(p->left);
			std::cout << p->data->word;
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
			Q.insert(p->data);
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

	node * recfindNode(node * p, std::string x)
	{
		if (p == nullptr)
		{
			return nullptr;
		}
		else if (p->data->word == x)
		{
			return p;
		}
		else
		{
			if (x < p->data->word)
			{
				return recfindNode(p->left, x);
			}
			else
			{
				return recfindNode(p->right, x);
			}
		}
	}

	T findVinN(std::string x)
	{
		return (recfindNode(root, x))->data;
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
		inOrder(root);

		std::cout << '\n';
	}
};
