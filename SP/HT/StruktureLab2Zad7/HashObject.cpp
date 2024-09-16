#include"HashObject.h"

HashObject::HashObject() {
	//ne mozemo da iskoristimo
	//strcpy jer key nije u statickoj zoni memorije
	//morali bismo prvo da zauzemo memoriju za njega
	// pa tek onda da upotrebimo fju
	this->mac = nullptr;
	this->ip = nullptr;
	free = true;
}
HashObject::HashObject(char* mac, char* ip)
{
	this->mac = mac;
	this->ip = ip;
	this->free = false;
}
HashObject::~HashObject()
{ 
	if (this->mac != NULL)
	{
		mac = NULL;
		ip = NULL;
		this->free = NULL;
	}
}
HashObject& HashObject::operator=(HashObject& obj) 
{
	this->mac = obj.mac;
	this->ip = obj.ip;
	this->free = obj.free;
	return *this;
}
bool HashObject:: operator==(HashObject& obj) 
{
	return isEqualKey(obj.mac);
}
void HashObject::deleteRecord() { 
	mac= nullptr; 
	ip = nullptr;
	free = true; 
}
void HashObject::print() 
{
	cout << "MacAddress -> " << getKey() << " IPaddress -> " << getValue();
}
