#pragma once

template <typename TYPE>
class linkedStack
{
private:
	class Node
	{
	public:
		Node * next, *prev;
		TYPE data;
		Node(TYPE x)
		{
			data = x;
		}
	};
	Node * head, * tail;
	int numItems{ 0 };
public:
	linkedStack()
	{
		head = nullptr;
		tail = nullptr;
	}

	void push(TYPE x) //adds to back.
	{
		Node * tmp = new Node(x);
		if (head == nullptr) // empty
		{
			head = tmp;
			tail = tmp;
		}
		else
		{
			tail->next = tmp;
			tmp->prev = tail;
			tail = tmp;
		}
		numItems++;
	}

	TYPE pop() //removes from back
	{
		TYPE output = tail->data;
		Node * doomed = tail;

		if (head == tail)
		{
			tail = nullptr;
			head = nullptr;
		}
		else
		{
			tail = tail->prev;
			tail->next = nullptr;
		}

		delete doomed;
		numItems--;
		return output;
	}

	bool empty()
	{
		if (numItems == 0)
		{
			return true;
		}
		return false;
	}
};