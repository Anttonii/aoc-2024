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
    bool rules = true;

    std::unordered_map<int, std::vector<int>> ruleMap;
    std::vector<std::vector<int>> pages;

    for (auto line : input)
    {
        if (line == "")
        {
            rules = false;
            continue;
        }

        if (rules)
        {
            auto splitted = utils::splitString(line, '|');
            ruleMap[std::stoi(splitted[1])].push_back(std::stoi(splitted[0]));
        }
        else
        {
            auto splitted = utils::splitString(line, ',');
            std::vector<int> values;

            for (auto num : splitted)
                values.push_back(std::stoi(num));

            pages.push_back(values);
        }
    }

    int pageCount = 0;
    for (auto vec : pages)
    {
        std::vector<int> forbidden;
        bool validPageOrder = true;

        for (int i = 0; i < vec.size(); i++)
        {
            int po = vec[i];

            if (ruleMap.find(po) == ruleMap.end())
                continue;

            auto orderedPages = ruleMap[po];
            for (int j = i; j < vec.size(); j++)
            {
                if (std::find(orderedPages.begin(), orderedPages.end(), vec[j]) != orderedPages.end())
                {
                    std::swap(vec[i], vec[j]);
                    validPageOrder = false;

                    // negate the increment of one
                    // this is so that we can evaluate the order again after the swap until
                    // all values are in their correct places.
                    i--;
                    break;
                }
            }
        }

        if (!validPageOrder)
        {
            int middle = std::floor(vec.size() / 2);
            pageCount += vec[middle];
        }
    }

    std::cout << pageCount << std::endl;

    return 0;
}