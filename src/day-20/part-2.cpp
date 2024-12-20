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

struct Track
{
    int steps;
    int dist;
    pair<int, int> pos;
};

class Compare
{
public:
    bool operator()(Track below, Track above)
    {
        if (below.steps > above.steps)
        {
            return true;
        }
        else if (below.steps == above.steps && below.dist > above.dist)
        {
            return true;
        }

        return false;
    }
};

struct Map
{
    pair<int, int> start;
    pair<int, int> end;
};

int distance(pair<int, int> p1, pair<int, int> p2)
{
    return abs(p1.first - p2.first) + abs(p1.second - p2.second);
}

vector<pair<int, int>> get_dirs(vector<string> &input, pair<int, int> pos, int factor)
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
        int dx = factor * d.second;
        int dy = factor * d.first;

        if (y + dy < 0 || y + dy >= n || x + dx < 0 || x + dx >= m)
            continue;

        if (input[y + dy][x + dx] == '#')
            continue;

        res.push_back(pair(dy, dx));
    }

    return res;
}

int findPath(vector<string> &input, Map &map, vector<vector<int>> &costs)
{
    int n = input.size();
    int m = input[0].size();

    pair<int, int> start = map.start;
    pair<int, int> end = map.end;

    priority_queue<Track, vector<Track>, Compare> queue;
    queue.push(Track{0, distance(start, end), start});

    set<pair<int, int>> visited;

    while (!queue.empty())
    {
        auto curr = queue.top();
        queue.pop();

        int steps = curr.steps;
        pair<int, int> pos = curr.pos;
        int x = pos.second;
        int y = pos.first;

        costs[y][x] = min(costs[y][x], steps);

        if (visited.count(pos))
            continue;

        visited.insert(pos);

        if (pos == end)
            return steps;

        auto directions = get_dirs(input, pos, 1);
        for (auto d : directions)
        {
            auto newPos = utils::add_pairs(pos, d);
            int dist = distance(newPos, end);

            queue.push(Track{steps + 1, dist, newPos});
        }
    }

    return -1;
}

vector<pair<int, int>> get_positions(vector<string> &input, pair<int, int> s, int x, int y)
{
    vector<pair<int, int>> positions;

    int n = input.size();
    int m = input[0].size();

    int sx = max(0, s.second - x);
    int sy = max(0, s.first - y);

    int ex = min(s.second + x, m - 1);
    int ey = min(s.first + y, n - 1);

    for (int i = sy; i <= ey; i++)
        for (int j = sx; j <= ex; j++)
            if (input[i][j] != '#' && distance(s, pair(i, j)) <= 20)
                positions.push_back(pair(i, j));

    return positions;
}

vector<int> findCheats(vector<string> &input, vector<vector<int>> &costs)
{
    int n = costs.size();
    int m = costs[0].size();

    vector<int> cheats;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (costs[i][j] != INT_MAX)
            {
                for (auto p : get_positions(input, pair(i, j), 20, 20))
                {
                    int save = costs[p.first][p.second] - costs[i][j];
                    int dist = distance(p, pair(i, j));

                    if (save > dist)
                        cheats.push_back(save - dist);
                }
            }
        }
    }

    return cheats;
}

int main()
{
    vector<string> input = utils::readInputLines("input.txt");

    int n = input.size();
    int m = input[0].size();

    Map map;
    vector<vector<int>> costs(m, vector(n, 0));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (input[i][j] == 'S')
                map.start = pair(i, j);
            else if (input[i][j] == 'E')
                map.end = pair(i, j);

            costs[i][j] = INT_MAX;
        }
    }

    cout << findPath(input, map, costs) << endl;
    vector<int> cheats = findCheats(input, costs);
    vector<int> validCheats;

    copy_if(cheats.begin(), cheats.end(), back_inserter(validCheats), [](int i)
            { return i >= 100; });
    cout << validCheats.size() << endl;

    return 0;
}