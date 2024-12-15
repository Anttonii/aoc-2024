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

struct Map
{
    int m;
    int n;

    int rx;
    int ry;
    vector<pair<int, int>> objects;
    vector<pair<int, int>> obstacles;
};

void printMap(Map &map)
{
    vector<string> mapVec;
    stringstream maps;
    for (int i = 0; i < map.n; i++)
    {
        for (int j = 0; j < map.m; j++)
        {
            maps << '.';
        }
        mapVec.push_back(maps.str());
        maps.str("");
    }

    for (auto o : map.objects)
    {
        int x = o.second;
        int y = o.first;
        mapVec[y][x] = 'O';
    }
    for (auto o : map.obstacles)
    {
        int x = o.second;
        int y = o.first;
        mapVec[y][x] = '#';
    }
    mapVec[map.ry][map.rx] = '@';
    for (auto l : mapVec)
        cout << l << endl;
}

long long int getGPS(Map &map)
{
    long long int result = 0;
    for (auto o : map.objects)
    {
        result += (100 * o.first) + o.second;
    }
    return result;
}

void moveRobot(Map &map, pair<int, int> dir)
{
    bool canMove = true;

    pair<int, int> rnpos = pair(map.ry + dir.first, map.rx + dir.second);
    pair<int, int> iterPos = rnpos;
    vector<ptrdiff_t> iters;

    while (true)
    {
        auto isObj = find(map.objects.begin(), map.objects.end(), iterPos);
        auto isObs = find(map.obstacles.begin(), map.obstacles.end(), iterPos);

        if (isObj == map.objects.end() && isObs == map.obstacles.end())
            break;

        if (isObj != map.objects.end())
        {
            iters.push_back(isObj - map.objects.begin());
        }
        else if (isObs != map.obstacles.end())
        {
            canMove = false;
            break;
        }

        iterPos = pair(iterPos.first + dir.first, iterPos.second + dir.second);
    }

    if (canMove)
    {
        map.rx = rnpos.second;
        map.ry = rnpos.first;

        for (auto i : iters)
            map.objects[i] = pair(map.objects[i].first + dir.first, map.objects[i].second + dir.second);
    }
}

void simulate(Map &map, string &instructions)
{
    vector<pair<int, int>> directions = {
        pair(-1, 0),
        pair(1, 0),
        pair(0, -1),
        pair(0, 1),
    };

    for (auto c : instructions)
    {
        switch (c)
        {
        case '<':
            moveRobot(map, directions[2]);
            break;
        case '^':
            moveRobot(map, directions[0]);
            break;
        case '>':
            moveRobot(map, directions[3]);
            break;
        case 'v':
            moveRobot(map, directions[1]);
            break;
        }
    }
}

Map parseMap(vector<string> &input, int end)
{
    vector<string> sinput = vector<string>(input.begin(), input.begin() + end);
    int m = sinput[0].length();
    int n = end;

    Map map;
    map.m = m;
    map.n = n;

    for (int i = 0; i < sinput.size(); i++)
    {
        for (int j = 0; j < sinput[i].length(); j++)
        {
            char c = sinput[i][j];
            if (c == 'O')
            {
                map.objects.push_back(pair(i, j));
            }
            else if (c == '@')
            {
                map.rx = j;
                map.ry = i;
            }
            else if (c == '#')
            {
                map.obstacles.push_back(pair(i, j));
            }
        }
    }

    return map;
}

string parseInstructions(vector<string> &input, int start)
{
    vector<string> sinput = vector<string>(input.begin() + start, input.end());
    stringstream ss;
    for (auto l : sinput)
    {
        for (auto c : l)
        {
            ss << c;
        }
    }
    return ss.str();
}

int main()
{
    vector<string> input = utils::readInputLines("test.txt");

    int mapEnd = 0;
    int i = 0;
    for (auto l : input)
    {
        cout << l << endl;
        if (l.empty())
        {
            mapEnd = i;
        }
        i++;
    }

    Map map = parseMap(input, mapEnd);
    string instructions = parseInstructions(input, mapEnd + 1);

    simulate(map, instructions);
    printMap(map);
    cout << getGPS(map) << endl;

    return 0;
}