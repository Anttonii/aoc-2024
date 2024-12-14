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

struct Robot
{
    int px;
    int py;
    int vx;
    int vy;
};

bool tick(vector<Robot> &r, vector<vector<int>> &board)
{
    int n = board.size();
    int m = board[0].size();

    set<pair<int, int>> seen;

    for (int i = 0; i < r.size(); i++)
    {
        board[r[i].py][r[i].px] -= 1;

        r[i].px = r[i].px + r[i].vx;
        if (r[i].px < 0)
        {
            r[i].px = m + r[i].px;
        }
        else if (r[i].px >= m)
        {
            r[i].px = r[i].px - m;
        }

        r[i].py = r[i].py + r[i].vy;
        if (r[i].py < 0)
        {
            r[i].py = n + r[i].py;
        }
        else if (r[i].py >= n)
        {
            r[i].py = r[i].py - n;
        }

        board[r[i].py][r[i].px] += 1;
        seen.insert(pair(r[i].py, r[i].px));
    }

    return seen.size() == r.size();
}

int calculateQuadrants(vector<vector<int>> &board)
{
    int n = board.size();
    int m = board[0].size();

    int q1 = 0;
    int q2 = 0;
    int q3 = 0;
    int q4 = 0;

    for (int i = 0; i < floor(m / 2); i++)
    {
        for (int j = 0; j < floor(n / 2); j++)
        {
            if (board[j][i] > 0)
                q1 += board[j][i];
        }

        for (int j = floor(n / 2) + 1; j < n; j++)
        {
            if (board[j][i] > 0)
                q2 += board[j][i];
        }
    }

    for (int i = floor(m / 2) + 1; i < m; i++)
    {
        for (int j = 0; j < floor(n / 2); j++)
        {
            if (board[j][i] > 0)
                q3 += board[j][i];
        }

        for (int j = floor(n / 2) + 1; j < n; j++)
        {
            if (board[j][i] > 0)
                q4 += board[j][i];
        }
    }

    return q1 * q2 * q3 * q4;
}

int main()
{
    string inputFile = "input.txt";
    vector<string> input = utils::readInputLines(inputFile);

    int w = 11;
    int h = 7;

    if (inputFile == "input.txt")
    {
        w = 101;
        h = 103;
    }

    vector<vector<int>> board(h, vector<int>(w, 0));
    vector<Robot> robots;

    for (auto l : input)
    {
        Robot curr;

        vector<string> lsplit = utils::splitString(l, ' ');

        vector<string> psplit = utils::splitString(lsplit[0], '=');
        vector<string> psplit2 = utils::splitString(psplit[1], ',');

        curr.px = stoi(psplit2[0]);
        curr.py = stoi(psplit2[1]);

        board[curr.py][curr.px] += 1;

        vector<string> vsplit = utils::splitString(lsplit[1], '=');
        vector<string> vsplit2 = utils::splitString(vsplit[1], ',');

        curr.vx = stoi(vsplit2[0]);
        curr.vy = stoi(vsplit2[1]);

        robots.push_back(curr);
    }

    for (int i = 0; i < 10000; i++)
    {
        if (tick(robots, board))
        {
            cout << i + 1 << endl;
            break;
        }
    }

    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[i].size(); j++)
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}