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

struct Region
{
    char plant;
    int area;
    int perimeter;
};

int handleRegion(int x, int y, unordered_map<pair<int, int>, bool, utils::hash_pair> &vis, vector<string> &input)
{
    char reg = input[y][x];
    vector<pair<int, int>> regionTiles{pair(y, x)};

    int n = input.size();
    int m = input[0].size();

    int area = 0;
    int perimeter = 0;

    vector<pair<int, int>> dirs = {
        pair(-1, 0),
        pair(1, 0),
        pair(0, -1),
        pair(0, 1)};

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
            {
                perimeter += 1;
                continue;
            }

            if (input[newPos.first][newPos.second] == reg)
                regionTiles.push_back(newPos);
            else
                perimeter += 1;
        }
    }

    cout << "Area for " << reg << " is: " << area << " and perimeter is: " << perimeter << endl;
    return area * perimeter;
}

int main()
{
    vector<string> input = utils::readInputLines(string("input.txt"));
    unordered_map<pair<int, int>, bool, utils::hash_pair> visited;

    long long int result = 0;

    for (int i = 0; i < input.size(); i++)
        for (int j = 0; j < input[0].size(); j++)
            if (visited.find(pair(j, i)) == visited.end())
                result += handleRegion(i, j, visited, input);

    cout << result << endl;

    return 0;
}