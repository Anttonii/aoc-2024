#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <numeric>
#include <cctype>

#include "../utils.h"

int main()
{
    std::vector<std::string> input = utils::readInputLines(std::string("test.txt"));

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

    int steps = 0;
    bool moving = true;

    while (moving)
    {
        std::pair<int, int> newPos(gx + gdir.first, gy + gdir.second);

        if (newPos.first < 0 || newPos.first >= n || newPos.second < 0 || newPos.second >= m)
        {
            moving = false;
            steps += 1;
            continue;
        }

        int cdir = std::find(directions.begin(), directions.end(), gdir) - directions.begin();
        if (input[newPos.first][newPos.second] == '#')
            gdir = directions[(cdir + 1) % 4];
        else
        {
            input[gx][gy] = 'X';

            gx = newPos.first;
            gy = newPos.second;

            if (input[gx][gy] != 'X')
                steps += 1;
        }
    }

    std::cout << steps << std::endl;

    return 0;
}