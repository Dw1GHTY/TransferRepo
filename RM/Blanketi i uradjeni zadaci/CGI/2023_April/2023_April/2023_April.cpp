#include <iostream>
#include<string>
using namespace std;

string parse(string query)
{
    int pos1 = query.find("x=", 0);
    int pos2 = query.find("&", pos1);
    int x = stoi(query.substr(pos1 + 2, pos2-pos1+2));
    int pos3 = query.find("y=", pos2);
    int y = stoi(query.substr(pos3 + 2));

    if (x + y < 200)
    {
        return "prazan deo";
    }
    else
    {
        return "tackasti deo";
    }
}


int main()
{
    string method = getenv("REQUEST_METHOD");
    string q_string = getenv("QUERY_STRING");
    int br_byte = atoi(getenv("CONTENT_LENGTH"));

    cout << "Content-type : text/html\n\n";
    cout << "<html>\n";
    cout << "<head>\n";

    if (method == "GET")
    {
        if (!q_string.empty())
        {
            string res = parse(q_string);
            cout << "<title>Uspesno</title>\n";
            cout << "</head>\n";
            cout << "<body><p>Klinkuto je na " << res << "!</p></body?\n";
            cout << "</html>\n";
        }
        else
        {
            cout << "<title>Neuspesno</title>\n";
            cout << "</head>\n";
            cout << "<body><p>Doslo do neke greske!</p></body?\n";
            cout << "</html>\n";
        }
    }
    else if (method == "POST")
    {
        char buf[100];
        memset(buf, 0, 100);
        std::cin.read(buf, br_byte);
        q_string = (string)buf;

        if (!q_string.empty())
        {
            string res = parse(q_string);
            cout << "<title>Uspesno</title>\n";
            cout << "</head>\n";
            cout << "<body><p>Klinkuto je na " << res << "!</p></body?\n";
            cout << "</html>\n";
        }
        else
        {
            cout << "<title>Neuspesno</title>\n";
            cout << "</head>\n";
            cout << "<body><p>Doslo do neke greske!</p></body?\n";
            cout << "</html>\n";
        }
    }

    return 0;
}