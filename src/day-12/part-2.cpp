#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <numeric>
#include <cctype>
#include <deque>
#include <set>

#include "../utils.h"

using namespace std;

struct Region
{
    char plant;
    int area;
    vector<pair<int, int>> tiles;
};

bool isValid(pair<int, int> newPos, int n, int m)
{
    return newPos.first >= 0 && newPos.first < n && newPos.second >= 0 && newPos.second < m;
}

void handleRegion(int x, int y, unordered_map<pair<int, int>, bool, utils::hash_pair> &vis, vector<string> &input, vector<Region> &regions)
{
    char reg = input[y][x];
    Region region{
        reg, 0, vector<pair<int, int>>()};

    pair<int, int> start = pair(y, x);
    vector<pair<int, int>> regionTiles{start};
    region.tiles.push_back(start);

    unordered_map<pair<int, int>, bool, utils::hash_pair> sidesMap;

    int n = input.size();
    int m = input[0].size();

    int area = 0;

    vector<pair<int, int>> dirs = {
        pair(1, 0),
        pair(0, 1),
        pair(0, -1),
        pair(-1, 0)};

    while (regionTiles.size() > 0)
    {
        pair<int, int> currTile = regionTiles.back();
        regionTiles.pop_back();

        if (vis.find(currTile) != vis.end())
            continue;

        vis[currTile] = true;
        area += 1;

        for (auto d : dirs)
        {
            pair<int, int> newPos = pair(currTile.first + d.first, currTile.second + d.second);
            if (newPos.first < 0 || newPos.first >= n || newPos.second < 0 || newPos.second >= m)
                continue;

            if (input[newPos.first][newPos.second] == reg)
            {
                regionTiles.push_back(newPos);
                region.tiles.push_back(newPos);
            }
        }
    }

    region.area = area;
    regions.push_back(region);

    cout << "Area for " << reg << " is: " << area << endl;
}

bool inRegion(pair<int, int> p, Region &region)
{
    return find(region.tiles.begin(), region.tiles.end(), p) != region.tiles.end();
}

bool isEdge(pair<int, int> p, pair<int, int> dir, Region &region, vector<string> &input)
{
    int n = input.size();
    int m = input[0].size();

    pair<int, int> curr = pair(p.first + dir.first, p.second + dir.second);
    return !isValid(curr, n, m) || !inRegion(curr, region);
}

int countSides(Region &region, vector<string> &input)
{
    vector<pair<pair<int, int>, pair<int, int>>> visited;
    int sides = 0;

    vector<pair<int, int>> dirs = {
        pair(1, 0),
        pair(0, 1),
        pair(0, -1),
        pair(-1, 0)};

    for (auto t : region.tiles)
    {
        for (auto d : dirs)
        {
            if (isEdge(t, d, region, input) && find(visited.begin(), visited.end(), pair(t, d)) == visited.end())
            {
                visited.push_back(pair(t, d));

                // whether to check x or y
                pair<pair<int, int>, pair<int, int>> ndir = pair(pair(-1, -1), pair(-1, -1));
                if (d == dirs[0] || d == dirs[3])
                {
                    // we moved in y direction, check x.
                    ndir.first = pair(0, 1);
                    ndir.second = pair(0, -1);
                }
                else
                {
                    ndir.first = pair(1, 0);
                    ndir.second = pair(-1, 0);
                }

                pair<int, int> nc = pair(t.first + ndir.first.first, t.second + ndir.first.second);
                while (inRegion(nc, region) && isEdge(nc, d, region, input))
                {
                    visited.push_back(pair(nc, d));
                    nc = pair(nc.first + ndir.first.first, nc.second + ndir.first.second);
                }

                nc = pair(t.first + ndir.second.first, t.second + ndir.second.second);
                while (inRegion(nc, region) && isEdge(nc, d, region, input))
                {
                    visited.push_back(pair(nc, d));
                    nc = pair(nc.first + ndir.second.first, nc.second + ndir.second.second);
                }

                sides += 1;
            }
        }
    }

    cout << region.plant << " has sides: " << sides << endl;

    return region.area * sides;
}

int main()
{
    vector<string> input = utils::readInputLines(string("input.txt"));

    unordered_map<pair<int, int>, bool, utils::hash_pair> visited;
    vector<Region> regions;

    for (int i = 0; i < input.size(); i++)
        for (int j = 0; j < input[0].size(); j++)
            if (visited.find(pair(j, i)) == visited.end())
                handleRegion(i, j, visited, input, regions);

    long long int result = 0;
    for (auto r : regions)
    {
        int add = countSides(r, input);
        result += add;
    }

    cout << result << endl;

    return 0;
}