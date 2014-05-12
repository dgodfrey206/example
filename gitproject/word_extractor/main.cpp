#include <iostream>
#include <sstream>

int main()
{
    std::stringstream ss("1 Bob Marely 22");
    int a, b;
    std::string name;
    if (ss >> a >> word_extractor<2>(name) >> b)
    {
        std::cout << name;
    }
}