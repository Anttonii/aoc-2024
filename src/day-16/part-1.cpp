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

struct Reindeer
{
    pair<int, int> pos;
    pair<int, int> dir;
};

class Compare
{
public:
    bool operator()(pair<long long int, Reindeer> below, pair<long long int, Reindeer> above)
    {
        if (below.first > above.first)
        {
            return true;
        }

        return false;
    }
};

int distance(pair<int, int> start, pair<int, int> end)
{
    return abs(start.first - end.first) + abs(start.second - end.second);
}

vector<pair<int, int>> get_dirs(vector<string> &input, pair<int, int> pos)
{
    int n = input.size();
    int m = input[0].size();

    vector<pair<int, int>> res;
    vector<pair<int, int>> directions = {
        pair(1, 0),
        pair(-1, 0),
        pair(0, 1),
        pair(0, -1)};

    int x = pos.second;
    int y = pos.first;

    for (auto d : directions)
    {
        int dx = d.second;
        int dy = d.first;

        if (y + dy < 0 || y + dy >= n || x + dx < 0 || x + dx >= m)
            continue;

        if (input[y + dy][x + dx] == '#')
            continue;

        res.push_back(pair(dy, dx));
    }

    return res;
}

long long int findPath(vector<string> &input, pair<int, int> start, pair<int, int> end)
{
    priority_queue<pair<long long int, Reindeer>, vector<pair<long long int, Reindeer>>, Compare> queue;
    for (auto d : get_dirs(input, start))
    {
        if (d == pair(0, 1))
            queue.push(pair(0, Reindeer{start, d}));
        else
            queue.push(pair(1000, Reindeer{start, d}));
    }

    long long int bestCost = INT_MAX;

    vector<vector<int>> distances;
    for (int i = 0; i < input.size(); i++)
    {
        distances.push_back(vector<int>());
        for (int j = 0; j < input[0].size(); j++)
        {
            distances[i].push_back(INT_MAX);
        }
    }

    while (!queue.empty())
    {
        pair<int, Reindeer> curr = queue.top();
        queue.pop();

        long long int currCost = curr.first;
        pair<int, int> currPos = curr.second.pos;
        pair<int, int> currDir = curr.second.dir;

        if (currPos == end)
        {
            bestCost = min(bestCost, currCost);
            continue;
        }

        vector<pair<int, int>> dirs = get_dirs(input, currPos);
        for (auto d : dirs)
        {
            if (pair(-d.first, -d.second) == currDir)
                continue;

            pair<int, int> newPos = utils::add_pairs(currPos, d);
            int newDist = distance(newPos, end);

            if (d == currDir)
            {
                if (distances[newPos.first][newPos.second] > newDist)
                {
                    distances[newPos.first][newPos.second] = newDist;
                    queue.push(pair(currCost + 1, Reindeer{newPos, d}));
                }
            }
            else
            {
                if (distances[newPos.first][newPos.second] > newDist)
                {
                    distances[newPos.first][newPos.second] = newDist;
                    queue.push(pair(currCost + 1001, Reindeer{newPos, d}));
                }
            }
        }
    }

    return bestCost;
}

int main()
{
    vector<string> input = utils::readInputLines("input.txt");

    pair<int, int> start;
    pair<int, int> end;

    for (int i = 0; i < input.size(); i++)
    {
        for (int j = 0; j < input[0].size(); j++)
        {
            if (input[i][j] == 'S')
                start = pair(i, j);

            if (input[i][j] == 'E')
                end = pair(i, j);
        }
    }

    cout << findPath(input, start, end) << endl;

    return 0;
}