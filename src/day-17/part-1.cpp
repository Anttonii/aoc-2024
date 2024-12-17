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

long long int parseCombo(vector<long long int> &registers, int operand)
{
    switch (operand)
    {
    case 0:
    case 1:
    case 2:
    case 3:
        return operand;
    case 4:
        return registers[0];
    case 5:
        return registers[1];
    case 6:
        return registers[2];
    }

    return -1;
}

void simulateProgram(vector<int> &program, vector<long long int> &registers)
{
    stringstream output;
    int i = 0;
    while (i < program.size())
    {
        int opcode = program[i];
        int operand = program[i + 1];
        long long int combo = parseCombo(registers, operand);

        switch (opcode)
        {
        case 0:
            registers[0] = trunc(registers[0] / pow(2L, combo));
            break;
        case 1:
            registers[1] = (registers[1] ^ operand);
            break;
        case 2:
            registers[1] = combo % 8;
            break;
        case 3:
            if (registers[0] == 0)
            {
                i += 4;
                continue;
            }

            i = operand;
            continue;
            break;
        case 4:
            registers[1] = (registers[1] ^ registers[2]);
            break;
        case 5:
            output << (combo % 8) << ",";
            break;
        case 6:
            registers[1] = trunc(registers[0] / pow(2L, combo));
            break;
        case 7:
            registers[2] = trunc(registers[0] / pow(2L, combo));
            break;
        }
        i += 2;
    }

    cout << output.str() << endl;
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

    simulateProgram(program, registers);

    return 0;
}