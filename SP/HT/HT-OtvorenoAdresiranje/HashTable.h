#pragma once
#include"HashObject.h"
class HashTable
{
protected:
	unsigned int m; // velicina tablice
	unsigned int count;  //broj elemenata u tablici
protected:
	//hash funkcija
	unsigned int h(unsigned int key);

	// primarna transformacija 
	unsigned int f(unsigned int key);
	// sekundarna transformacija
	unsigned int g(unsigned int key);
public:
	unsigned int getLength() { return m; }
	
};

