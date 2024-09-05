#pragma once
#include <iostream>
using namespace std;

class Elem {
public:
	int key;
	Elem* prev;
	Elem* next;

	Elem(int key) 
	{
		this->prev = nullptr;
		this->next = nullptr;
		this->key = key;
	}
};