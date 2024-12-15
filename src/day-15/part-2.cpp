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

struct Object
{
    bool obstacle;
    int side;
    pair<int, int> pos;
};

struct Map
{
    int m;
    int n;

    int rx;
    int ry;
    vector<Object> objects;
};

int findObject(vector<Object> &objects, pair<int, int> pos)
{
    for (int i = 0; i < objects.size(); i++)
    {
        if (objects[i].pos == pos)
        {
            return i;
        }
    }
    return -1;
}

void printMap(Map &map)
{
    vector<string> mapVec;
    stringstream maps;
    for (int i = 0; i < map.n; i++)
    {
        for (int j = 0; j < map.m; j++)
        {
            maps << ".";
        }
        mapVec.push_back(maps.str());
        maps.str("");
    }

    for (auto o : map.objects)
    {
        int x = o.pos.second;
        int y = o.pos.first;

        if (o.obstacle)
            mapVec[y][x] = '#';
        else if (!o.obstacle)
        {
            if (o.side == 0)
            {
                mapVec[y][x] = '[';
            }
            else
            {
                mapVec[y][x] = ']';
            }
        }
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
        if (!o.obstacle && o.side == 0)
            result += (100 * o.pos.first) + o.pos.second;
    }
    return result;
}

void moveRobot(Map &map, pair<int, int> dir)
{
    bool canMove = true;

    pair<int, int> rnpos = pair(map.ry + dir.first, map.rx + dir.second);
    vector<pair<int, int>> indices;

    auto obstructed = findObject(map.objects, rnpos);
    if (obstructed != -1)
    {
        Object o = map.objects[obstructed];
        if (o.obstacle)
            canMove = false;
        else
        {
            int offset = 0;
            if (o.side == 1)
                offset = -1;
            else
                offset = 1;

            Object pairObj = map.objects[findObject(map.objects, pair(o.pos.first, o.pos.second + offset))];
            deque<Object> queue{o, pairObj};
            set<pair<int, int>> seen;

            while (!queue.empty())
            {
                Object curr = queue.front();
                queue.pop_front();

                if (seen.count(curr.pos))
                    continue;

                seen.insert(curr.pos);

                if (curr.obstacle)
                {
                    canMove = false;
                    break;
                }

                indices.push_back(pair(findObject(map.objects, curr.pos), 1));

                int next = findObject(map.objects, pair(curr.pos.first + dir.first, curr.pos.second + dir.second));
                if (next != -1)
                {
                    Object n = map.objects[next];
                    queue.push_back(n);

                    int offset = 0;
                    if (n.side == 1)
                        offset = -1;
                    else
                        offset = 1;

                    int pairIndex = findObject(map.objects, pair(n.pos.first, n.pos.second + offset));
                    Object pairObj = map.objects[pairIndex];
                    queue.push_back(pairObj);
                }
            }
        }
    }

    if (canMove)
    {
        map.rx = rnpos.second;
        map.ry = rnpos.first;

        for (auto index : indices)
        {
            int i = index.first;
            int o = index.second;

            map.objects[i].pos = pair(map.objects[i].pos.first + (o * dir.first), map.objects[i].pos.second + (o * dir.second));
        }
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
    map.m = 2 * m;
    map.n = n;

    for (int i = 0; i < sinput.size(); i++)
    {
        for (int j = 0; j < sinput[i].length(); j++)
        {
            char c = sinput[i][j];
            if (c == 'O')
            {
                map.objects.push_back(Object{false, 0, pair(i, 2 * j)});
                map.objects.push_back(Object{false, 1, pair(i, (2 * j) + 1)});
            }
            else if (c == '@')
            {
                map.rx = 2 * j;
                map.ry = i;
            }
            else if (c == '#')
            {
                map.objects.push_back(Object{true, 0, pair(i, 2 * j)});
                map.objects.push_back(Object{true, 1, pair(i, (2 * j) + 1)});
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
    vector<string> input = utils::readInputLines("input.txt");

    int mapEnd = 0;
    int i = 0;
    for (auto l : input)
    {
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