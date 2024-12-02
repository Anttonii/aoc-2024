#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cmath>

#include "../utils.h"

int main()
{
    std::string input = utils::readInput(std::string("test.txt"));

    std::vector<int> firstList;
    firstList.reserve(100);

    std::vector<int> secondList;
    secondList.reserve(100);

    int count = 0;
    for (auto splitted : utils::splitString(input, '\n'))
    {
        for (auto splitted_2 : utils::splitString(splitted, ' '))
        {
            std::string res = utils::strip(splitted_2);
            if (res.length() > 0)
            {
                if (count % 2 == 0)
                {
                    firstList.push_back(std::stoi(res));
                }
                else
                {
                    secondList.push_back(std::stoi(res));
                }
                count++;
            }
        }
    }

    std::sort(firstList.begin(), firstList.end());
    std::sort(secondList.begin(), secondList.end());

    int totalDistance = 0;
    for (int i = 0; i < firstList.size(); i++)
    {
        totalDistance += std::abs(firstList[i] - secondList[i]);
    }

    std::cout << totalDistance << std::endl;

    return 0;
}