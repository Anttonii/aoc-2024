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

struct Game
{
    int xJumpA;
    int yJumpA;
    int xJumpB;
    int yJumpB;
    pair<int, int> prizeLocation;
};

int solve(Game &g)
{
    int targetX = g.prizeLocation.first;
    int targetY = g.prizeLocation.second;

    int aX = g.xJumpA;
    int aY = g.yJumpA;
    int bX = g.xJumpB;
    int bY = g.yJumpB;

    int result = INT_MAX;
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 100; j++)
        {
            int x = (aX * i + bX * j);
            int y = (aY * i + bY * j);

            if (x == targetX && y == targetY)
                result = min(result, (3 * i) + j);
        }
    }

    return result;
}

int get_num(string &inp, char denom)
{
    vector<string> splitted = utils::splitString(inp, denom);
    return stoi(splitted[1]);
}

int main()
{
    vector<string> input = utils::readInputLines(string("input.txt"));
    vector<Game> games;

    Game curr;
    for (auto l : input)
    {
        if (l.empty())
        {
            games.push_back(curr);
            curr = Game{};
            continue;
        }

        vector<string> splitted = utils::splitString(l, ':');
        if (splitted[0] == "Button A")
        {
            vector<string> values = utils::splitString(splitted[1], ',');
            string x = utils::strip(values[0]);
            string y = utils::strip(values[1]);
            curr.xJumpA = get_num(x, '+');
            curr.yJumpA = get_num(y, '+');
        }
        else if (splitted[0] == "Button B")
        {
            vector<string> values = utils::splitString(splitted[1], ',');
            string x = utils::strip(values[0]);
            string y = utils::strip(values[1]);
            curr.xJumpB = get_num(x, '+');
            curr.yJumpB = get_num(y, '+');
        }
        else
        {
            vector<string> values = utils::splitString(splitted[1], ',');
            string x = utils::strip(values[0]);
            string y = utils::strip(values[1]);
            curr.prizeLocation = pair(get_num(x, '='), get_num(y, '='));
        }
    }

    games.push_back(curr);

    int result = 0;
    for (auto g : games)
    {
        int solved = solve(g);
        if (solved != INT_MAX)
            result += solved;
    }

    cout << result << endl;

    return 0;
}