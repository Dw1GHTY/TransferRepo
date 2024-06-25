#pragma once
#include "BSNode.h"
class Queue
{
	BSNode** niz;
	int f, l;
	int size;
public:
	Queue(int s) : size(s) { niz = new BSNode*[s]; f = 0; l = 0; }

	bool isFull() { return l == (f - 1) % size; }
	bool isEmpty() { return f == l; }

	void enqueue(BSNode* el)
	{
		if (!isFull())
		{
			niz[l] = el;
			l = (l + 1) % size;
		}
	}

	BSNode* dequeue()
	{
		if (!isEmpty())
		{
			BSNode* rez = niz[f];
			f = (f + 1) % size;
			return rez;
		}
		else
		{
			f = l = 0;
		}
		return nullptr;
	}
};

