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
    pair<int, int> pos;
    int steps;
    vector<pair<int, int>> path;
    int dist;
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

int distance(pair<int, int> p1, pair<int, int> p2)
{
    return abs(p1.first - p2.first) + abs(p1.second - p2.second);
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

int findPath(vector<string> &map)
{
    int n = map.size();
    int m = map[0].size();

    pair<int, int> start(0, 0);
    pair<int, int> end(n - 1, m - 1);

    priority_queue<Track, vector<Track>, Compare> queue;
    queue.push(Track{start, 0, vector{start}, distance(start, end)});

    set<pair<int, int>> visited;

    while (!queue.empty())
    {
        auto curr = queue.top();
        queue.pop();

        int steps = curr.steps;
        pair<int, int> pos = curr.pos;
        int x = pos.second;
        int y = pos.first;

        cout << curr.dist << endl;

        if (visited.count(pos))
            continue;

        visited.insert(pos);

        if (pos == end)
        {
            for (auto v : curr.path)
            {
                int x = v.second;
                int y = v.first;
                map[y][x] = 'O';
            }
            return steps;
        }

        auto directions = get_dirs(map, pos);
        for (auto d : directions)
        {
            auto newPos = utils::add_pairs(pos, d);
            int dist = distance(newPos, end);
            vector<pair<int, int>> path{curr.path};
            path.push_back(newPos);

            queue.push(Track{newPos, steps + 1, path, dist});
        }
    }

    return -1;
}

int main()
{
    string inputfile = "input.txt";
    vector<string> input = utils::readInputLines(inputfile);

    int w = 71;
    int h = 71;
    int bytes = 1024;

    if (inputfile == "test.txt")
    {
        w = 7;
        h = 7;
        bytes = 12;
    }

    vector<string> map;
    for (int i = 0; i < h; i++)
    {
        map.push_back("");
        for (int j = 0; j < w; j++)
        {
            map[i].append(".");
        }
    }

    for (int i = 0; i < bytes; i++)
    {
        auto l = input[i];
        vector<string> splitted = utils::splitString(l, ',');

        int x = stoi(splitted[0]);
        int y = stoi(splitted[1]);

        map[y][x] = '#';
    }

    cout << findPath(map) << endl;

    for (auto l : map)
    {
        cout << l << endl;
    }

    return 0;
}