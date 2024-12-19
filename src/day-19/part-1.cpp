#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <numeric>
#include <cctype>
#include <deque>
#include <queue>
#include <set>

#include "../utils.h"

using namespace std;

bool isPossible(vector<string> &patterns, string &design, int index)
{
    if (index >= design.length())
        return true;

    bool rVal = false;
    for (auto &p : patterns)
    {
        if (design.find(p, index) == index)
            rVal = rVal || isPossible(patterns, design, index + p.length());
    }

    return rVal;
}

int possibleDesigns(vector<string> &patterns, vector<string> &designs)
{
    int possible = 0;
    for (auto &d : designs)
        if (isPossible(patterns, d, 0))
            possible++;

    return possible;
}

int main()
{
    vector<string> input = utils::readInputLines("input.txt");

    vector<string> designs;
    vector<string> patterns;

    bool parsePatterns = true;

    for (auto l : input)
    {
        if (l.empty())
        {
            parsePatterns = false;
            continue;
        }

        if (parsePatterns)
        {
            vector<string> splitted = utils::splitString(l, ',');
            for (auto v : splitted)
            {
                patterns.push_back(utils::strip(v));
            }
        }
        else
        {
            designs.push_back(utils::strip(l));
        }
    }

    cout << possibleDesigns(patterns, designs) << endl;

    return 0;
}