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

struct Result
{
    vector<int> order;
    vector<pair<int, int>> blocks;
};

Result build(string input)
{
    int alternate = 0;
    int currId = 0;
    int pos = 0;

    vector<pair<int, int>> blocks;
    vector<int> values;

    for (auto c : input)
    {
        int n = (int)(c - '0');
        int cpos = pos;

        for (int i = 0; i < n; i++)
        {
            if (!alternate)
                values.push_back(currId);
            else
                values.push_back(-1);

            pos++;
        }

        if (!alternate)
        {
            blocks.push_back(pair(cpos, n));
            currId++;
        }

        alternate = !alternate;
    }

    return Result{
        values, blocks};
}

vector<int> organize(Result result)
{
    vector<int> values = result.order;
    vector<pair<int, int>> blocks = result.blocks;

    for (int i = blocks.size() - 1; i > 0; i--)
    {
        pair<int, int> curr_block = blocks[i];
        int block_len = curr_block.second;

        int ws, we = 0;
        int cp = -1;
        for (int j = 0; j < curr_block.first; j++)
        {
            if (values[j] == -1)
            {
                ws = j;
                we = ws;
                while (values[we] == -1 && we < values.size())
                    we++;
                if (we - ws >= block_len)
                {
                    cp = ws;
                    break;
                }
            }
        }

        if (cp == -1)
        {
            // cout << we - ws << endl;
            // cout << values[curr_block.first] << endl;
            // cout << curr_block.second << endl;
            continue;
        }

        for (int k = 0; k < block_len; k++)
        {
            values[cp + k] = values[curr_block.first + k];
            values[curr_block.first + k] = -1;
        }
    }

    return values;
}

long long int checksum(vector<int> vec)
{
    int counter = -1;
    long long int result = 0;

    for (auto c : vec)
    {
        counter++;

        if (c == -1)
            continue;

        result += counter * c;
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