#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <numeric>
#include <cctype>
#include <deque>

#include "../utils.h"

using namespace std;

struct hash_pair
{
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2> &p) const
    {
        // Hash the first element
        size_t hash1 = hash<T1>{}(p.first);
        // Hash the second element
        size_t hash2 = hash<T2>{}(p.second);
        // Combine the two hash values
        return hash1 ^ (hash2 + 0x9e3779b9 + (hash1 << 6) + (hash1 >> 2));
    }
};

int num_len(long long int n)
{
    return to_string(n).length();
}

// monstrous
long long int solve(long long int input, int steps, unordered_map<pair<long long int, int>, long long int, hash_pair> &dp)
{
    if (steps == 0)
        return 1;

    if (dp.find(pair(input, steps)) == dp.end())
    {
        long long int result = 0;
        if (input == 0)
        {
            result = solve(1, steps - 1, dp);
        }
        else if (num_len(input) % 2 == 0)
        {
            string inp = utils::to_string(input);
            result += solve(stoll(inp.substr(0, inp.length() / 2.0)), steps - 1, dp);
            result += solve(stoll(inp.substr(inp.length() / 2.0, inp.length() / 2.0)), steps - 1, dp);
        }
        else
        {
            result = solve(input * 2024, steps - 1, dp);
        }

        dp[pair(input, steps)] = result;
    }

    return dp[pair(input, steps)];
}

int main()
{
    vector<string> input_f = utils::readInputLines(string("input.txt"));
    string input = input_f[0];

    vector<string> splitted = utils::splitString(input, ' ');
    vector<long long int> actInput;

    unordered_map<pair<long long int, int>, long long int, hash_pair> dp;

    for (auto l : splitted)
        actInput.push_back(stoll(l));

    long long int result = 0;
    for (auto ai : actInput)
        result += solve(ai, 75, dp);

    cout << result << endl;

    return 0;
}