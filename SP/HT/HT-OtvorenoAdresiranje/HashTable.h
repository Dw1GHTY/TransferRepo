#pragma once
#include"HashObject.h"
class HashTable
{
protected:
	unsigned int m; // velicina tablice
	unsigned int count;  //broj elemenata u tablici
protected:
	//hash funkcija
	unsigned int h(char* key);

	// primarna  
	unsigned int f(char * key);
	// sekundarna 
	unsigned int g(unsigned int key);
public:
	unsigned int getLength() { return m; }
	
};

