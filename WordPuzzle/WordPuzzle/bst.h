#pragma once
#include <iostream>
#include <vector>
#include <queue>
//#include <sstream>
#include "stack.h"
#include "heap.h"

bool one_char_diff(std::string x, std::string y)
{
	unsigned int differences{ 0 };
	for (unsigned int i{ 0 }; i < x.length(); i++)
	{
		if (x[i] != y[i])
		{
			differences++;
		}
	}

	if (differences == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

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
		bool visited{ false };

		node(T x)
		{
			data = x;
			left = nullptr;
			right = nullptr;
		}
	};

	node * root;

	std::vector<node *> letterIndex;
	// RECURSION CAUSES STACK OVERFLOW (I THINK THIS WORKS) WAIT I COULD DO BFS SINCE NO STACK NEEDED
	char currentCh{ '0' }, previousCh{ '0' }; //random initializer to start
	void recInsert(node * p, T x)
	{
		currentCh = x->word[0];
		while (p != nullptr) {
			if (x->word < p->data->word) // if insertion is smaller 
			{
				if (p->left == nullptr)
				{
					if (currentCh != previousCh)
					{
						letterIndex.push_back(p->left);
					}
					p->left = new node(x);
					break;
				}
				p = p->left;
			}
			else // if insertion is greater or equal
			{
				if (p->right == nullptr)
				{
					if (currentCh != previousCh)
					{
						letterIndex.push_back(p->right);
					}
					p->right = new node(x);
					break;
				}
				p = p->right;
			}
		}
		if (p == nullptr) // will only happen if it starts at nullptr due to break statement.
		{
			letterIndex.push_back(p); //0 (letterindex[0])
			root = new node(x);
		}

		previousCh = currentCh; 
		//SWITCH TO BFS IF NEEDED, SINCE NO STACK OVERFLOW WOULD HAPPEN
	}

	void recMakeMax(node * p) // initialize all to max.
	{
		linkedStack<node *> P;
		//p->visited = true;
		P.push(p);
		while (!P.empty())
		{
			node * curr = P.pop();
			
			curr->data->distance = UINT_MAX;
			curr->data->visited = false;

			if (curr->left != nullptr)
			{
				P.push(curr->left);
				//curr->left->visited = true;
			}
			if (curr->right != nullptr)
			{
				P.push(curr->right);
				//curr->right->visited = true;
			}
		}
	}
	
	// FIND FASTER SOLUTION...
	void recConnector(node * x, T y) // x goes through, y is inputted to get connected.
	{
		//MANUAL STACK EQUIVALENCE
		linkedStack<node *> S;
		//x->visited = true;
		S.push(x);
		//int counter{ 0 };
		while (!S.empty())
		{
			node * curr = S.pop();
			if (one_char_diff(y->word, curr->data->word)) // If theres a one character difference, connect.
			{
				//connect
				T currVert = findVinN(curr->data->word);
				//std::cout << "Connection between " << y->word << " and " << currVert->word << '\n';
				y->neighbors.push_back(currVert);
				currVert->neighbors.push_back(y);
			}

			if (curr->left != nullptr)
			{
				S.push(curr->left);
				//curr->left->visited = true;
			}
			if (curr->right != nullptr)
			{
				S.push(curr->right);
				//curr->right->visited = true;
			}
		}
	}

	void rec_0(node * p, minHeap<T> &Q) //non-recursively store into minheap
	{
		linkedStack<node *> S;
		S.push(p);

		while (!S.empty())
		{
			node * curr = S.pop();
			Q.insert(curr->data);

			if (curr->left != nullptr)
			{
				S.push(curr->left);
			}
			if (curr->right != nullptr)
			{
				S.push(curr->right);
			}
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

	node * recfindNode(node * p, std::string x) // stack overflow if recursive
	{
		while (p != nullptr)
		{
			if (p->data->word == x)
			{
				return p;
			}
			else
			{
				if (x < p->data->word)
				{
					p = p->left;
				}
				else
				{
					p = p->right;
				}
			}
		}
		return nullptr;
	}

	void makeMax()
	{
		recMakeMax(root);
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

	void connector(std::string x)
	{
		recConnector(root, findVinN(x));
	}

	void display()
	{
		inOrder(root);

		std::cout << '\n';
	}
};
