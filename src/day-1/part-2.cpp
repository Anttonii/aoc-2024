#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <unordered_map>

#include "../utils.h"

int main()
{
    std::string input = utils::readInput(std::string("input.txt"));

    std::vector<int> firstList;
    firstList.reserve(100);

    std::unordered_map<int, int> idMap;

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
                    idMap[std::stoi(res)] += 1;
                }
                count++;
            }
        }
    }

    std::sort(firstList.begin(), firstList.end());

    int similarityScore = 0;
    for (int i = 0; i < firstList.size(); i++)
    {
        if (idMap.find(firstList[i]) == idMap.end())
        {
            continue;
        }

        similarityScore += firstList[i] * idMap[firstList[i]];
    }

    std::cout << similarityScore << std::endl;

    return 0;
}