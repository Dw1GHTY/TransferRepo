#include"OpenScatterTable.h"

void main()
{
	OpenScatterTable tablica(53);
	ScatterObject o("2907982", "luka ilic");
	tablica.insert(o);
	ScatterObject o1("2706985", "Pera Peric");
	ScatterObject o2("2907981", "Nikola Davidovic");
	tablica.insert(o2);
	tablica.insert(o2);
	tablica.insert(o1);
	tablica.print();
	/*ScatterObject p = tablica.find("2907982");
	p.print();*/
}