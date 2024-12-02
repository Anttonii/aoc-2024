#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <numeric>

#include "../utils.h"

int main()
{
    std::string input = utils::readInput(std::string("input.txt"));
    std::vector<std::vector<int>> reports;

    int count = 0;
    for (auto splitted : utils::splitString(input, '\n'))
    {
        reports.push_back(std::vector<int>());

        for (auto splitted_2 : utils::splitString(splitted, ' '))
        {
            reports[count].push_back(std::stoi(splitted_2));
        }
        count++;
    }

    int safeCount = 0;
    for (int i = 0; i < reports.size(); i++)
    {
        bool isSafe = true;

        std::vector vec = reports[i];
        isSafe = (std::is_sorted(vec.begin(), vec.end(), std::greater<int>()) || std::is_sorted(vec.begin(), vec.end(), std::less<int>()));

        if (!isSafe)
        {
            continue;
        }

        for (int j = 1; j < vec.size(); j++)
        {
            int diff = std::abs(vec[j - 1] - vec[j]);
            if (diff < 1 || diff > 3)
            {
                isSafe = false;
            }
        }

        safeCount += int(isSafe);
    }

    std::cout << safeCount << std::endl;

    return 0;
}