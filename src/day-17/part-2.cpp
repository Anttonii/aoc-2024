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

int step(long long int v, vector<long long int> &registers)
{
    registers[0] = v;
    registers[1] = 0;
    registers[2] = 0;

    registers[1] = registers[0] % 8;
    registers[1] = registers[1] ^ 3;
    registers[2] = registers[0] >> registers[1];
    registers[0] = registers[0] >> 3;
    registers[1] = (registers[1] ^ registers[2]) ^ 5;
    return registers[1] % 8;
}

vector<long long int> validAvalues(long long int valA, vector<int> &program, vector<long long int> &registers)
{
    vector<long long int> results;
    for (int i = 0; i < 8; i++)
    {
        long long int nv = (valA << 3) + i;
        int b = step(nv, registers);
        int index = program.size() - (floor(utils::bit_count(nv) / 3) + 1);

        if (b == program[index])
            results.push_back(nv);
    }
    return results;
}

int main()
{
    vector<string> input = utils::readInputLines("input.txt");

    vector<long long int> registers;
    vector<int> program;
    bool parseProgram = false;

    for (auto l : input)
    {
        if (l.empty())
        {
            parseProgram = true;
            continue;
        }

        if (!parseProgram)
        {
            vector<string> splitted = utils::splitString(l, ':');
            registers.push_back(stoll(utils::strip(splitted[1])));
        }
        else
        {
            vector<string> splitted = utils::splitString(l, ':');
            for (auto v : utils::splitString(splitted[1], ','))
                program.push_back(stoi(utils::strip(v)));
        }
    }

    long long int minval = ((long long int)1) << 45;

    priority_queue<long long int, vector<long long int>, greater<long long int>> values;
    values.push(0);

    long long int best = ((long long int)1) << 54;

    while (!values.empty())
    {
        long long int curr = values.top();
        values.pop();

        if (curr > minval)
        {
            cout << curr << endl;
            return 0;
        }

        if ((floor(utils::bit_count(curr) / 3) + 1) < program.size())
            for (auto x : validAvalues(curr, program, registers))
                values.push(x);
    }

    return 0;
}