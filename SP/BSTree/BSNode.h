#pragma once
#include <iostream>

class BSNode
{
public:
	int key;
	BSNode* left, * right;
public:

	BSNode(int info = 0, BSNode* l = nullptr, BSNode* r = nullptr) : key(info), left(l), right(r) {}

	void print() {
		if(this!=nullptr)	
			std::cout << key << " ";
	}
};

