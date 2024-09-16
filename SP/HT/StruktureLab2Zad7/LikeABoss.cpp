#include"HashTable.h"
void main() 
{
	try
	{
		HashTable Tablica(320);
		HashObject o1("34A6A13C1818", "192168121");
		HashObject o2("59E463F22675", "168110");
		HashObject o3("21FE33DC3740", "12810121");
		HashObject o4("61B2B29978DB", "10000");
		HashObject o5("7D8705D46436", "192177201");

		HashObject o6("7D8705D46436", "666177111");

		Tablica.insert(o1);
		Tablica.insert(o2);
		Tablica.insert(o3);
		Tablica.insert(o4);
		Tablica.insert(o5);
		cout << Tablica.findMatch("7D8705D46436") << endl;
		Tablica.printAll();
		Tablica.insertOrUpdate(o6.mac, o6.ip);
		Tablica.insertOrUpdate("111133DC3740", "12123123");
		Tablica.printAll();

	}
	catch (char* izuzetak)
	{
		cout << izuzetak;
	}

}