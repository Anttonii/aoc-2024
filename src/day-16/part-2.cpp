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

int pdistance(pair<int, int> start, pair<int, int> end)
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
    int n = input.size();
    int m = input[0].size();

    vector<pair<int, int>> directions = {
        pair(1, 0),
        pair(-1, 0),
        pair(0, 1),
        pair(0, -1)};

    priority_queue<pair<long long int, Reindeer>, vector<pair<long long int, Reindeer>>, Compare> queue;
    for (auto d : get_dirs(input, start))
    {
        queue.push(pair(0, Reindeer{start, d}));
    }

    long long int bestCost = INT_MAX;

    vector<int> distances(n * m * 4 + 1, 0);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            for (int k = 0; k < 4; k++)
                distances[(i * m * 4) + (j * 4) + k] = 1000000;

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
            pair<int, int> newPos = utils::add_pairs(currPos, d);
            int newDist = pdistance(newPos, end);
            int distIndex = distance(directions.begin(), find(directions.begin(), directions.end(), d));

            int newCost = 1;
            if (d != currDir)
                newCost = 1001;

            int index = (newPos.first * m * 4) + (newPos.second * 4) + distIndex;
            if (distances[index] > currCost + newCost)
            {
                distances[index] = currCost + newCost;
                queue.push(pair(currCost + newCost, Reindeer{newPos, d}));
            }
        }
    }

    // for (int i = 0; i < n; i++)
    // {
    //     for (int j = 0; j < m; j++)
    //     {
    //         bool print = false;
    //         for (int k = 0; k < 4; k++)
    //         {
    //             if (distances[(i * m * 4) + (j * 4) + k] != 1000000)
    //                 print = true;
    //         }

    //         if (print)
    //             cout << '1';
    //         else
    //             cout << 'x';
    //     }
    //     cout << endl;
    // }

    set<int> tiles;
    set<pair<int, int>> tiless;

    deque<pair<pair<int, int>, pair<int, int>>> bt;
    int minDir = INT_MAX;
    int minDirVal = INT_MAX;
    for (int i = 0; i < directions.size(); i++)
    {
        int index = (end.first * m * 4) + (end.second * 4) + i;
        if (distances[index] < minDirVal)
        {
            minDir = i;
            minDirVal = distances[index];
        }
    }
    bt.push_back(pair(end, directions[minDir]));

    while (!bt.empty())
    {
        pair<pair<int, int>, pair<int, int>> curr = bt.front();
        bt.pop_front();

        pair<int, int> currPos = curr.first;
        pair<int, int> currDir = curr.second;

        int distIndex = distance(directions.begin(), find(directions.begin(), directions.end(), currDir));
        int oIndex = (currPos.first * m * 4) + (currPos.second * 4) + distIndex;

        tiless.insert(currPos);

        if (tiles.count(oIndex))
            continue;

        tiles.insert(oIndex);

        if (currPos == start)
            return tiles.size();

        for (auto d : get_dirs(input, currPos))
        {
            pair<int, int> newPos = utils::add_pairs(currPos, d);

            for (int j = 0; j < directions.size(); j++)
            {
                int index = (newPos.first * m * 4) + (newPos.second * 4) + j;
                if (distances[oIndex] - distances[index] == 1 || distances[oIndex] - distances[index] == 1001)
                    bt.push_back(pair(newPos, directions[j]));
            }
        }
    }

    cout << tiless.size() << endl;

    vector<vector<char>> tilesss;
    for (int i = 0; i < n; i++)
    {
        tilesss.push_back(vector<char>());
        for (int j = 0; j < m; j++)
        {
            tilesss[i].push_back('#');
        }
    }

    for (auto x : tiless)
    {
        tilesss[x.first][x.second] = 'O';
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << tilesss[i][j];
        }
        cout << endl;
    }

    return tiless.size() + 1;
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