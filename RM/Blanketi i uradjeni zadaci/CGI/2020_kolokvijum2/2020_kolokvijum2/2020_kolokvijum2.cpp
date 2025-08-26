#include<iostream>
#include<string>
#include<fstream>
#include<fcntl.h>
#include<io.h>
using namespace std;

void prikazi(string fajl, string ext);
void parse(string s)
{
    int pos1 = s.find("fajl=", 0);
    int pos2 = s.find("&", pos1 + 5);
    string fajl = s.substr(pos1 + 5, pos2 - pos1 - 5);

    pos1 = s.find("ext=", pos2);
    string ext = s.substr(pos1 + 4);

    prikazi(fajl, ext);
}

void prikazi(string fajl, string ext)
{
    string s = fajl + ext;
    for (int i = 0; i < ext.length(); i++)
    {
        ext[i] = ext[i + 1];
    }
    ifstream f(s, ios::in | ios::binary | ios::ate);
    if (f.good())
    {
        int size = f.tellg();
        cout << "Content-Type: image/" << ext << "\n";
        cout << "Content-Length: " << size << "\n";
        cout << "Connection: Keep-Alive\n\n";
        f.seekg(ios_base::beg);
        _setmode(_fileno(stdout), _O_BINARY);
        char c;

        while (!f.eof())
        {
            f.read(&c, 1);
            cout << c;
        }
    }
    else
    {
        cout << "Content-Type: text/html\n\n";
        cout << "<html><head></head><body>\n";
        cout << "<h1>Slika '" << s << "' nije pronadjena</h1>\n";
        std::cout << "<h2>Slika pronadjena:</h2>\n";
        std::cout << "<img src='" << s << "' alt='Slika'>\n";
        cout << "</body></html>\n";
    }
    f.close();
}

int main()
{
    string req = getenv("REQUEST_METHOD");
    string s;

    if (req == "POST")
    {
        int br_bytes = atoi(getenv("CONTENT_LENGTH"));
        if (br_bytes > 0)
        {
            char* buffer = new char[br_bytes];
            cin.read(buffer, br_bytes);
            s.assign(buffer, br_bytes);
            delete[] buffer;
            parse(s);
        }
    }

    return 0;
}
