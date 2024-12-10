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

int followTrail(pair<int, int> cpos, vector<string> &input)
{
    int x = cpos.second;
    int y = cpos.first;

    int n = input.size();
    int m = input[0].size();

    if (input[y][x] == '9')
    {
        return 1;
    }

    vector<pair<int, int>> directions = {
        pair(-1, 0),
        pair(1, 0),
        pair(0, -1),
        pair(0, 1),
    };

    int sum = 0;

    for (auto dir : directions)
    {
        pair<int, int> newPos = pair(cpos.first + dir.first, cpos.second + dir.second);
        if (newPos.first < 0 || newPos.first >= n || newPos.second < 0 || newPos.second >= m)
            continue;

        int currValue = ((int)input[y][x] - '0');
        int newValue = ((int)input[newPos.first][newPos.second] - '0');

        if (newValue == currValue + 1)
            sum += followTrail(newPos, input);
    }

    return sum;
}

int solve(vector<string> &input)
{
    int n = input.size();
    int m = input[0].size();

    // Store positions that are part of a valid trail
    deque<pair<int, int>> spos;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (input[i][j] == '0')
                spos.push_back(pair(i, j));

    int total = 0;
    while (spos.size() > 0)
    {
        pair<int, int> curr = spos.front();
        spos.pop_front();
        total += followTrail(curr, input);
        cout << total << endl;
    }
    return total;
}

int main()
{
    vector<string> input_f = utils::readInputLines(string("test.txt"));
    cout << solve(input_f) << endl;
    return 0;
}