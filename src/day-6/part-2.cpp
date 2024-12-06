#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <numeric>
#include <cctype>
#include <set>

#include "../utils.h"

int walk(int x, int y, std::pair<int, int> dir, std::vector<std::string> &input, std::vector<std::pair<int, int>> &directions)
{
    int n = input.size();
    int m = input[0].size();

    int steps = 0;
    bool moving = true;

    while (moving)
    {
        std::pair<int, int> newPos(x + dir.first, y + dir.second);

        if (newPos.first < 0 || newPos.first >= n || newPos.second < 0 || newPos.second >= m)
        {
            moving = false;
            steps += 1;
            continue;
        }

        int cdir = std::find(directions.begin(), directions.end(), dir) - directions.begin();
        if (input[newPos.first][newPos.second] == '#')
            dir = directions[(cdir + 1) % 4];
        else
        {
            x = newPos.first;
            y = newPos.second;
            steps += 1;

            if (steps > n * n)
            {
                return steps;
            }
        }
    }

    return steps;
}

int get_loops(int x, int y, std::pair<int, int> dir, std::vector<std::string> input, std::vector<std::pair<int, int>> &directions)
{
    int n = input.size();
    int m = input[0].size();

    int loops = 0;
    bool moving = true;

    std::set<std::pair<int, int>> seen;

    while (moving)
    {
        std::pair<int, int> newPos(x + dir.first, y + dir.second);

        if (newPos.first < 0 || newPos.first >= n || newPos.second < 0 || newPos.second >= m)
        {
            moving = false;
            continue;
        }

        int cdir = std::find(directions.begin(), directions.end(), dir) - directions.begin();
        if (input[newPos.first][newPos.second] == '#')
            dir = directions[(cdir + 1) % 4];
        else
        {
            seen.insert(std::pair<int, int>(x, y));
            if (!seen.count(newPos))
            {
                input[newPos.first][newPos.second] = '#';
                if (walk(x, y, dir, input, directions) > n * n)
                {
                    loops += 1;
                }
                input[newPos.first][newPos.second] = '.';
            }

            x = newPos.first;
            y = newPos.second;
        }
    }

    return loops;
}

int main()
{
    std::vector<std::string> input = utils::readInputLines(std::string("input.txt"));

    int n = input.size();
    int m = input[0].size();

    std::vector<std::pair<int, int>> directions = {
        std::pair<int, int>(1, 0),
        std::pair<int, int>(0, -1),
        std::pair<int, int>(-1, 0),
        std::pair<int, int>(0, 1),
    };

    int gx, gy = 0;
    std::pair<int, int> gdir;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (input[i][j] == '^' || input[i][j] == '<' || input[i][j] == '>' || input[i][j] == 'v')
            {
                gx = i;
                gy = j;

                if (input[i][j] == '^')
                    gdir = directions[2];
                if (input[i][j] == 'v')
                    gdir = directions[0];
                if (input[i][j] == '<')
                    gdir = directions[1];
                if (input[i][j] == '>')
                    gdir = directions[3];
            }
        }
    }

    std::cout << get_loops(gx, gy, gdir, input, directions) << std::endl;

    return 0;
}