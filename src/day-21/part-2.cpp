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
#include <cstdint>

#include "../utils.h"

using namespace std;

const vector<char> numpad = {'7', '8', '9', '4', '5', '6', '1', '2', '3', '#', '0', 'A'};
const vector<char> dirpad = {'#', '^', 'A', '<', 'v', '>'};

pair<int, int> findPosition(const vector<char> &pad, int n, int m, char c)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (pad[i * m + j] == c)
            {
                return pair(i, j);
            }
        }
    }
    return pair(-1, -1);
}

vector<pair<int, int>> get_dirs(const vector<char> &chars, pair<int, int> pos, int n, int m)
{
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

        if (chars[((y + dy) * m) + x + dx] == '#')
            continue;

        res.push_back(pair(dy, dx));
    }

    return res;
}

vector<string> findPaths(const vector<char> &pad, pair<int, int> s, pair<int, int> e, int n, int m)
{
    struct Point
    {
        pair<int, int> pos;
        vector<char> path;
    };

    deque<Point> queue{Point{s, vector<char>()}};
    vector<string> paths;
    int minLength = INT_MAX;

    while (!queue.empty())
    {
        auto point = queue.front();
        queue.pop_front();

        if (point.path.size() > minLength)
            continue;

        if (point.pos == e)
        {
            if (point.path.size() <= minLength)
            {
                minLength = point.path.size();
                paths.push_back(std::string(point.path.begin(), point.path.end()) + "A");
            }
            continue;
        }

        for (auto d : get_dirs(pad, point.pos, n, m))
        {
            char dirChar;
            if (d == pair(1, 0))
            {
                dirChar = 'v';
            }
            else if (d == pair(-1, 0))
            {
                dirChar = '^';
            }
            else if (d == pair(0, 1))
            {
                dirChar = '>';
            }
            else if (d == pair(0, -1))
            {
                dirChar = '<';
            }

            pair<int, int> newPos = utils::add_pairs(point.pos, d);
            vector<char> newPath(point.path.begin(), point.path.end());

            newPath.push_back(dirChar);
            queue.push_back(Point{newPos, newPath});
        }
    }

    return paths;
}

unsigned long long str_hash(const std::string &str)
{
    unsigned long long hash = 5381;
    for (size_t i = 0; i < str.size(); ++i)
        hash = 33 * hash + (unsigned char)str[i];
    return hash;
}

uint64_t hashs(const string &seq, int depth)
{
    uint64_t h = str_hash(seq);
    return h ^ depth;
}

long long int dirKeyPathLength(const string &seq, int depth, unordered_map<uint64_t, long long int> &cache)
{
    uint64_t h = hashs(seq, depth);
    if (cache.find(h) != cache.end())
        return cache[h];

    if (depth == 0)
        return seq.length();

    pair<int, int> s = findPosition(dirpad, 2, 3, 'A');
    long long total = 0;

    for (auto const &c : seq)
    {
        pair<int, int> e = findPosition(dirpad, 2, 3, c);
        vector<string> paths = findPaths(dirpad, s, e, 2, 3);

        long long int minPath = 9223372036854775807;
        for (auto const &p : paths)
            minPath = min(minPath, dirKeyPathLength(p, depth - 1, cache));

        total += minPath;
        s = e;
    }
    cache[hashs(seq, depth)] = total;

    return total;
}

long long int seqLength(const string &code, int depth, unordered_map<uint64_t, long long int> &cache)
{
    pair<int, int> s = findPosition(numpad, 4, 3, 'A');
    long long int total = 0;

    for (auto const &c : code)
    {
        pair<int, int> e = findPosition(numpad, 4, 3, c);

        vector<string> paths = findPaths(numpad, s, e, 4, 3);
        long long int minPath = 9223372036854775807;
        for (auto const &p : paths)
            minPath = min(minPath, dirKeyPathLength(p, depth, cache));
        total += minPath;
        s = e;
    }
    return total;
}

int main()
{
    vector<string> input = utils::readInputLines("input.txt");

    int n = input.size();
    int m = input[0].size();

    vector<string> codes;
    for (auto l : input)
        codes.push_back(l);

    for (int i = 0; i < 26; i++)
    {
        long long int result = 0;

        unordered_map<uint64_t, long long int> cache;
        for (auto const &code : codes)
        {
            string ss = code.substr(0, 3);
            long long int id = stoll(ss);
            result += id * seqLength(code, i, cache);
        }
        cout << result << endl;
    }

    return 0;
}