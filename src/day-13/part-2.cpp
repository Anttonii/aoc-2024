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
    pair<long long int, long long int> prizeLocation;
};

long long int solve(Game &g)
{
    long long int targetX = g.prizeLocation.first;
    long long int targetY = g.prizeLocation.second;

    int aX = g.xJumpA;
    int aY = g.yJumpA;
    int bX = g.xJumpB;
    int bY = g.yJumpB;

    long long int result = INT_MAX;

    // Solving x=A^-1*b
    long long int det = (aX * bY) - (bX * aY);

    long long int x = floor(((bY * targetX) + (-bX * targetY)) / det);
    long long int y = floor(((-aY * targetX) + (aX * targetY)) / det);

    if ((aX * x + bX * y) == targetX && (aY * x + bY * y) == targetY)
        result = (x * 3) + y;

    return result;
}

long long int get_num(string &inp, char denom)
{
    vector<string> splitted = utils::splitString(inp, denom);
    return stoll(splitted[1]);
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
            curr.prizeLocation = pair(get_num(x, '=') + 10000000000000, get_num(y, '=') + 10000000000000);
        }
    }

    games.push_back(curr);

    long long int result = 0;
    for (auto g : games)
    {
        long long int solved = solve(g);
        if (solved != INT_MAX)
            result += solved;
    }

    cout << result << endl;

    return 0;
}