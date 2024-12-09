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

vector<int> build(string input)
{
    int alternate = 0;
    int currId = 0;

    vector<int> values;

    for (auto c : input)
    {
        int n = (int)(c - '0');
        for (int i = 0; i < n; i++)
        {
            if (!alternate)
            {
                values.push_back(currId);
            }
            else
            {
                values.push_back(-1);
            }
        }

        if (!alternate)
            currId++;

        alternate = !alternate;
    }

    return values;
}

vector<int> organize(vector<int> values)
{
    for (int i = values.size() - 1; i > 0; i--)
    {
        if (values[i] == -1)
            continue;

        int curr = values[i];
        values[i] = -1;

        int index = 0;
        while (values[index] != -1 && index < values.size() - 1)
            index++;

        values[index] = curr;
    }
    return values;
}

long long int checksum(vector<int> vec)
{
    int counter = 0;
    long long int result = 0;
    for (auto c : vec)
    {
        if (c == -1)
            break;

        result += counter * c;
        counter++;
    }

    return result;
}

int main()
{
    vector<string> input_f = utils::readInputLines(string("input.txt"));
    if (input_f.size() > 1)
    {
        cout << "Bad input file." << endl;
    }

    vector b = organize(build(input_f[0]));
    cout << checksum(b) << endl;

    return 0;
}