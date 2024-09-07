#include"HashTable.h"

unsigned int HashTable::h(unsigned int key)
{
	return f(key);
}

//Jun2_2024
unsigned int HashTable::f(unsigned int key)
{
	return ((key << 4) * 31) % 1000
}

unsigned int HashTable::g(unsigned int key)
{
	

}
//*************
