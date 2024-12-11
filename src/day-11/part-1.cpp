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

int num_len(long long int n)
{
    return to_string(n).length();
}

vector<long long int> solve(vector<long long int> input)
{
    vector<long long int> output;

    for (auto n : input)
    {
        if (n == 0)
            output.push_back(1);
        else if (num_len(n) % 2 == 0)
        {
            string inp = utils::to_string(n);
            output.push_back(stoll(inp.substr(0, inp.length() / 2.0)));
            output.push_back(stoll(inp.substr(inp.length() / 2.0, inp.length() / 2.0)));
        }
        else
            output.push_back(n * 2024);
    }

    return output;
}

int main()
{
    vector<string> input_f = utils::readInputLines(string("input.txt"));
    string input = input_f[0];

    vector<string> splitted = utils::splitString(input, ' ');
    vector<long long int> actInput;

    for (auto l : splitted)
        actInput.push_back(stoll(l));

    vector<long long int> output = actInput;
    for (int i = 0; i < 25; i++)
    {
        output = solve(output);
    }
    cout << output.size() << endl;

    return 0;
}