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

struct hash_pair
{
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2> &p) const
    {
        // Hash the first element
        size_t hash1 = hash<T1>{}(p.first);
        // Hash the second element
        size_t hash2 = hash<T2>{}(p.second);
        // Combine the two hash values
        return hash1 ^ (hash2 + 0x9e3779b9 + (hash1 << 6) + (hash1 >> 2));
    }
};

int main()
{
    std::vector<std::string> input = utils::readInputLines(std::string("input.txt"));

    int n = input.size();
    int m = input[0].size();

    unordered_map<char, vector<pair<int, int>>> antennas;
    unordered_map<pair<int, int>, bool, hash_pair> antinodes;
    int uniqueAntinodes = 0;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (input[i][j] != '.')
                antennas[input[i][j]].push_back(pair(i, j));

    for (auto const &ant : antennas)
    {
        int ac = ant.second.size();

        if (ac < 2)
            continue;

        uniqueAntinodes += ac;

        for (int i = 0; i < ac; i++)
        {
            for (int j = i + 1; j < ac; j++)
            {
                pair<int, int> ant1 = ant.second[j];
                pair<int, int> ant2 = ant.second[i];

                int distX = ant1.first - ant2.first;
                int distY = ant1.second - ant2.second;

                int an1X, an2X = ant1.first;
                int an1Y, an2Y = ant1.second;

                if (distX != 0)
                {
                    an1X = ant1.first + distX;
                    an2X = ant2.first - distX;
                }

                if (distY != 0)
                {
                    an1Y = ant1.second + distY;
                    an2Y = ant2.second - distY;
                }

                while (an1X >= 0 && an1X < m && an1Y >= 0 && an1Y < n)
                {
                    if (an1X >= 0 && an1X < m && an1Y >= 0 && an1Y < n)
                    {
                        if (!antinodes[pair(an1X, an1Y)] && input[an1X][an1Y] == '.')
                            uniqueAntinodes++;

                        antinodes[pair(an1X, an1Y)] = true;
                        input[an1X][an1Y] = '#';
                    }

                    an1X = an1X + distX;
                    an1Y = an1Y + distY;
                }

                while (an2X >= 0 && an2X < m && an2Y >= 0 && an2Y < n)
                {
                    if (an2X >= 0 && an2X < m && an2Y >= 0 && an2Y < n)
                    {
                        if (!antinodes[pair(an2X, an2Y)] && input[an2X][an2Y] == '.')
                            uniqueAntinodes++;

                        antinodes[pair(an2X, an2Y)] = true;
                        input[an2X][an2Y] = '#';
                    }

                    an2X = an2X - distX;
                    an2Y = an2Y - distY;
                }
            }
        }
    }

    cout << uniqueAntinodes << endl;

    return 0;
}