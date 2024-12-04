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
    std::vector<std::string> input = utils::readInputLines(std::string("input.txt"));

    int n = input.size();
    int m = input[0].length();

    int sum = 0;
    std::pair<int, int> positions[4] = {
        std::pair(-1, -1),
        std::pair(-1, 1),
        std::pair(1, -1),
        std::pair(1, 1)};

    for (int i = 1; i < n - 1; i++)
    {
        for (int j = 1; j < m - 1; j++)
        {
            if (input[i][j] == 'A')
            {
                int addition = 1;
                int count = 0;

                for (auto pos : positions)
                {
                    int x = pos.second;
                    int y = pos.first;

                    if (input[i + x][j + y] != 'M' && input[i + x][j + y] != 'S')
                    {
                        addition = 0;
                        break;
                    }

                    // Check for opposite corners of X
                    // the letters should be different.
                    if (count > 1)
                    {
                        std::pair<int, int> opposite = positions[1 - count % 2];

                        int oppX = opposite.second;
                        int oppY = opposite.first;

                        if (input[i + x][j + y] == input[i + oppX][j + oppY])
                        {
                            addition = 0;
                            break;
                        }
                    }

                    count++;
                }

                sum += addition;
            }
        }
    }

    std::cout << sum << std::endl;

    return 0;
}