#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <numeric>
#include <cctype>

#include "../utils.h"

int evaluate(std::string multiply)
{
    std::string newS = multiply.substr(1, multiply.length() - 2);
    std::stringstream helper;

    int nums[2] = {0, 0};
    int index = 0;

    for (auto c : newS)
    {
        if (c == '(')
            continue;

        if (isdigit(c))
        {
            helper << c;
        }
        else if (c == ',' || c == ')')
        {
            nums[index] = std::stoi(helper.str());
            helper.str("");
            index++;
        }
        else
        {
            return 0;
        }
    }

    return nums[0] * nums[1];
}

int main()
{
    std::string input = utils::readInput(std::string("input.txt"));
    std::string sub("mul");

    size_t pos = input.find(sub, 0);
    int sum = 0;
    while (pos != std::string::npos)
    {
        int send = pos + 3;
        if (input[send] != '(')
        {
            pos = input.find(sub, pos + 1);
            continue;
        }

        while (input[send] != ')')
        {
            // 12 is in case we have mul(999,999), any longer string is invalid.
            if (input[send] == 'm' || send - pos > 12)
                break;

            send++;
        }

        if (input[send] == ')')
        {
            sum += evaluate(input.substr(pos + 2, send - pos));
        }

        pos = input.find(sub, pos + 1);
    }
    std::cout << sum << std::endl;
    return 0;
}