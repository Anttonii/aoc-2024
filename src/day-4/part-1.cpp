#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <numeric>
#include <cctype>

#include "../utils.h"

int main()
{
    std::vector<std::string> input = utils::readInputLines(std::string("test.txt"));

    int n = input.size();
    int m = input[0].length();

    int sum = 0;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            std::stringstream ssvert;
            std::stringstream sshor;

            std::stringstream ssdiag;
            std::stringstream ssdiag2;

            for (int k = 0; k < 4; k++)
            {
                if (i <= n - 4)
                {
                    ssvert << input[i + k][j];
                }

                if (j <= m - 4)
                {
                    sshor << input[i][j + k];
                }

                if (i <= n - 4 && j <= m - 4)
                {
                    ssdiag << input[i + k][j + k];
                }

                if (i <= n - 4 && j >= 3)
                {
                    ssdiag2 << input[i + k][j - k];
                }
            }

            std::string vert = ssvert.str();
            if (vert == "XMAS" || vert == "SAMX")
                sum++;
            std::string hor = sshor.str();
            if (hor == "XMAS" || hor == "SAMX")
                sum++;
            std::string diag = ssdiag.str();
            if (diag == "XMAS" || diag == "SAMX")
                sum++;
            std::string diag2 = ssdiag2.str();
            if (diag2 == "XMAS" || diag2 == "SAMX")
                sum++;
        }
    }

    std::cout << sum << std::endl;

    return 0;
}