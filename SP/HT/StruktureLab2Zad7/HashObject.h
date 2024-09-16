#pragma once
#include<iostream>
#include<cstring>
using namespace std;

class HashObject {
public:
	char* mac;
	char* ip;
	bool free; //0-free, 1-zauzeto, 2-deleted
public:
	HashObject();
	HashObject(char* mac, char* ip);
	~HashObject();
	HashObject& operator=(HashObject& obj);
	bool operator==(HashObject& obj);
	void deleteRecord();
	char* getKey() { return mac; }
	char* getValue() { return ip; }
	bool getStatus() { return this->free; }
	bool isEqualKey(char* mac) { return !(strcmp(mac, mac)); }
	void print();
	bool isFree() { return this->free; }
};