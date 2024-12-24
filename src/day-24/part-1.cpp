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

string getZ(int s)
{
    string z;

    if (s < 10)
    {
        z = "z0" + to_string(s);
    }
    else
    {
        z = "z" + to_string(s);
    }

    return z;
}

long long int evalZValues(unordered_map<string, bool> &gates)
{
    long long int result = 0;

    int s = 0;
    string z = getZ(s);
    while (gates.find(z) != gates.end())
    {
        long long int v = (long long int)gates.find(z)->second;
        long long int m = (v << s);
        result |= m;
        z = getZ(++s);
    }
    return result;
}

void evalLazyGates(unordered_map<string, string> &lazyGates, unordered_map<string, bool> &gates)
{
    deque<vector<string>> toEval;
    for (auto const &[key, val] : lazyGates)
    {
        vector<string> splitted = utils::splitString(val, ' ');
        string gate1 = splitted[0];
        string gate2 = splitted[2];
        string instruction = splitted[1];
        string result = key;

        toEval.push_back(vector<string>{gate1, gate2, instruction, result});
    }

    while (!toEval.empty())
    {
        const auto top = toEval.front();
        toEval.pop_front();

        if (gates.find(top[0]) == gates.end() || gates.find(top[1]) == gates.end())
        {
            toEval.push_back(top);
            continue;
        }

        if (top[2] == "AND")
            gates[top[3]] = gates[top[0]] & gates[top[1]];
        if (top[2] == "OR")
            gates[top[3]] = gates[top[0]] | gates[top[1]];
        if (top[2] == "XOR")
            gates[top[3]] = gates[top[0]] ^ gates[top[1]];
    }
}

int main()
{
    vector<string> input = utils::readInputLines("input.txt");

    bool parseGates = true;

    unordered_map<string, bool> gates;
    unordered_map<string, string> lazyGates;

    for (auto l : input)
    {
        if (l.empty())
        {
            parseGates = false;
            continue;
        }

        if (parseGates)
        {
            vector<string> splitted = utils::splitString(l, ':');
            gates[splitted[0]] = (bool)stoi(splitted[1]);
        }
        else
        {
            vector<string> splitted = utils::splitString(l, '-');
            string instruction = utils::strip(splitted[0]);
            string result = utils::strip(splitted[1].substr(1, splitted[1].length() - 1));
            lazyGates[result] = instruction;
        }
    }

    evalLazyGates(lazyGates, gates);
    cout << evalZValues(gates) << endl;

    return 0;
}