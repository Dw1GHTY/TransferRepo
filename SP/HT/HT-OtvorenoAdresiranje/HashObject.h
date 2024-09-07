#pragma once
#include <iostream>
using namespace std;


class HashObject
{
private:
	unsigned int key;
	char* record;
public:
	HashObject();
	HashObject(unsigned int k, char* v);
	HashObject(HashObject const& obj);
	~HashObject();
	HashObject& operator = (HashObject const& obj);
	bool operator == (HashObject const& obj);
	void deleteRecord();
	unsigned int getKey() { return key; }
	char* getRecord() { return record; }
	bool isEqualKey(unsigned int k) { return key == k; }
	void print();
};