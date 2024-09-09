#include"HashObject.h"

HashObject::HashObject() {
	//ne mozemo da iskoristimo
	//strcpy jer key nije u statickoj zoni memorije
	//morali bismo prvo da zauzemo memoriju za njega
	// pa tek onda da upotrebimo fju
	this->mac = nullptr;
	this->ip = nullptr;
	status = 0;
}
HashObject::HashObject(char* mac, char* ip)
{
	this->mac = mac;
	this->ip = ip;
	this->status = 1;
}
HashObject::~HashObject()
{ 
	if (this->mac != NULL)
	{
		mac = NULL;
		this->status = 0;
	}
}
HashObject& HashObject::operator=(HashObject& obj) 
{
	this->mac = obj.mac;
	this->ip = obj.ip;
	this->status = obj.status;
	return *this;
}
bool HashObject:: operator==(HashObject& obj) 
{
	return isEqualKey(obj.mac);
}
void HashObject::deleteRecord() { 
	mac= nullptr; 
	ip = nullptr;
	status = 3; 
}
void HashObject::print() 
{
	cout << getKey() << " " << getValue();
}
