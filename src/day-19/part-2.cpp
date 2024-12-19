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

vector<int> possibleDesigns(vector<string> &patterns, vector<string> &designs)
{
    vector<int> possibleIndices;
    for (int i = 0; i < designs.size(); i++)
    {
        auto d = designs[i];
        if (isPossible(patterns, d, 0))
            possibleIndices.push_back(i);
    }

    return possibleIndices;
}

long long int calcPossibilities(unordered_map<char, vector<string>> &swpatterns, string &design, int index, string curr, unordered_map<string, long long int> &cache)
{
    if (index >= design.length())
        return 1;

    if (cache.find(curr) != cache.end())
        return cache[curr];

    long long int possibilities = 0;

    for (auto &p : swpatterns[design[index]])
    {
        if (design.find(p, index) == index)
            possibilities += calcPossibilities(swpatterns, design, index + p.length(), design.substr(0, index + p.length()), cache);
    }
    cache[curr] = possibilities;

    return possibilities;
}

long long int calcAllPossibilities(unordered_map<char, vector<string>> &swpatterns, vector<string> &patterns, vector<string> &designs)
{
    vector<int> possibleIndices = possibleDesigns(patterns, designs);
    long long int possible = 0;
    for (auto &d : designs)
    {
        unordered_map<string, long long int> cache;
        possible += calcPossibilities(swpatterns, d, 0, "", cache);
        cout << d << " " << possible << endl;
    }

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

    unordered_map<char, vector<string>> startsWith;
    for (auto &p : patterns)
        startsWith[p[0]].push_back(p);

    cout << calcAllPossibilities(startsWith, patterns, designs) << endl;

    return 0;
}