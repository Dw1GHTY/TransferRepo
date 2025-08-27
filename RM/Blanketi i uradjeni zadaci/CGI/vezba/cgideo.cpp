#include<iostream>
#include<string.h>
#include<stdio.h>


string parse(string requestMethod){
    //parse string
}

int main() {

    std::string reqmethod = getenv('REQUEST_METHOD');
    std::string q_string = getenv('QUERY_STRING');
    int br_byte = atoi(getenv('CONTENT_LENGTH'));

    std::string postInputString;

    if(reqmethod == "GET")
    {
        if(!q_string.empty())
            parse(q_string);   
    } else if(reqmethod == "POST"){
        if(!q_string.empty())
            parse(q_string);

        if(br_byte > 0)
        {
            std::cin >> postInputString;
            parse(postInputString);
        }
    }


    return 0;
}