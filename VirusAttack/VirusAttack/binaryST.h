#pragma once
#include <iostream>
#include <vector>

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

	//insert x into tree rooted at p
	void recInsert(node * &p, T x)
	{
		
		if (p == nullptr)
		{
			p = new node(x);
		}
		else
		{
			if (x->data < p->data->data) // if insertion is smaller 
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
			//nothing!
		}
		else
		{
			inOrder(p->left);
			std::cout << p->data->data << ' ';
			inOrder(p->right);
		}
	}

	void recDisplayAllData(node * p)
	{
		if (p == nullptr)
		{
			return;
		}
		else
		{
			recDisplayAllData(p->left);
			std::cout << "Course: " << p->data->data << "\n\t Pre-Requsites: "; 
			p->data->prereqs.display();
			std::cout << '\n';
			recDisplayAllData(p->right);
		}
	}
	unsigned int count;

public:

	binarySearchTree()
	{
		count = 0;
		root = nullptr;
	}

	void insert(T x)
	{
		count++;
		recInsert(root, x);
	}

	T recfindNode(node * p, std::string x)
	{
		if (p == nullptr)
		{
			return nullptr;
		}
		else if (p->data->data == x)
		{
			return p->data;
		}
		else
		{
			if (x < p->data->data)
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
		return recfindNode(root, x);
	}

	void displayAllData()
	{
		recDisplayAllData(root);
	}

	bool empty()
	{
		if (count == 0)
		{
			return true;
		}
		return false;
	}

	void inOrderFinder(std::vector<T> &found, node * p)
	{
		if (p == nullptr)
		{
			return;
		}
		else
		{
			inOrderFinder(found, p->left);
			if (p->data->prereqs.empty())
			{
				found.push_back(p->data);
			}
			inOrderFinder(found, p->right);
		}
	}

	std::vector<T> findEasy()
	{
		std::vector<T> easyCourses;
		inOrderFinder(easyCourses, root);
		return easyCourses;
	}

	void display()
	{
		inOrder(root);
	}
};
