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

unsigned long long str_hash(const std::string &str)
{
    unsigned long long hash = 5381;
    for (size_t i = 0; i < str.size(); ++i)
        hash = 33 * hash + (unsigned char)str[i];
    return hash;
}

long long int hashSeq(deque<int> &seq)
{
    stringstream ss;
    for (int i = 0; i < seq.size(); i++)
        ss << seq[i];
    return str_hash(ss.str());
}

long long int calculateSecretNumber(long long int initial, int nth, unordered_map<long long int, long long int> &map)
{
    long long int pruneMod = 16777216;
    long long int curr = initial;

    deque<int> seq;
    long long int lastIter = -1;

    unordered_map<long long int, bool> inner;

    for (int i = 0; i < nth; i++)
    {
        long long int multi = curr * 64;
        curr = curr ^ multi;
        curr = curr % pruneMod;

        long long int div = floor(curr / 32);
        curr = curr ^ div;
        curr = curr % pruneMod;

        long long int lmulti = curr * 2048;
        curr = curr ^ lmulti;
        curr = curr % pruneMod;

        int lastDigit = curr % 10;
        if (i == 0)
        {
            lastIter = lastDigit;
            continue;
        }

        int change = lastDigit - lastIter;
        lastIter = lastDigit;

        if (seq.size() == 4)
            seq.pop_front();
        seq.push_back(change);

        if (i < 4)
            continue;

        long long int h = hashSeq(seq);
        if (inner.find(h) == inner.end())
        {
            map[h] += lastDigit;
            inner[h] = true;
        }
    }

    return curr;
}

int main()
{
    vector<string> input = utils::readInputLines("input.txt");

    unordered_map<long long int, long long int> resultsMap;

    long long int result = 0;
    for (int i = 0; i < input.size(); i++)
    {
        string l = input[i];
        long long int num = stoll(l);
        result += calculateSecretNumber(num, 2000, resultsMap);
    }

    using pair_type = decltype(resultsMap)::value_type;
    auto pr = std::max_element(
        std::begin(resultsMap), std::end(resultsMap),
        [](const pair_type &p1, const pair_type &p2)
        {
            return p1.second < p2.second;
        });

    cout << pr->second << endl;

    return 0;
}