#include <cmath>
#include <sstream>
#include <iostream>

int main()
{
    int len = 10;
    for (int i = 0; i < len; i++)
    {
        std::stringstream ss;
        for (int k = 0; k < len - i; k++)
        {
            ss << " ";
        }
        for (int l = 0; l < 2 * i + 1; l++)
        {
            ss << "*";
        }
        std::cout << ss.str() << std::endl;
    }
}