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

        for (auto po : vec)
        {
            if (ruleMap.find(po) != ruleMap.end())
                for (auto badPages : ruleMap[po])
                    forbidden.push_back(badPages);

            if (std::find(forbidden.begin(), forbidden.end(), po) != forbidden.end())
                validPageOrder = false;
        }

        if (validPageOrder)
        {
            int middle = std::floor(vec.size() / 2);
            pageCount += vec[middle];
        }
    }

    std::cout << pageCount << std::endl;

    return 0;
}