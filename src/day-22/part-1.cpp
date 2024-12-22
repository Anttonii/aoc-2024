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

long long int calculateSecretNumber(long long int initial, int nth)
{
    long long int pruneMod = 16777216;
    long long int curr = initial;

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
    }

    return curr;
}

int main()
{

    vector<string> input = utils::readInputLines("input.txt");

    long long int result = 0;
    for (const auto &l : input)
    {
        long long int num = stoll(l);
        result += calculateSecretNumber(num, 2000);
        cout << calculateSecretNumber(num, 2000) << endl;
    }
    cout << result << endl;

    return 0;
}