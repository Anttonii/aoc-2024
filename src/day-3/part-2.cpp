#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <numeric>
#include <cctype>
#include <utility>

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

    std::string doString("do()");
    std::string dontString("don't()");
    std::vector<std::pair<int, int>> validSequences;

    size_t start = 0;
    size_t end = input.find(dontString);

    while (end != std::string::npos && start != std::string::npos)
    {
        validSequences.push_back(std::pair(start, end));

        start = input.find(doString, end + 1);
        end = input.find(dontString, start + 1);
    }
    validSequences.push_back(std::pair(start, input.length()));

    std::vector<std::string> splittedInput;
    for (auto s : validSequences)
        splittedInput.push_back(input.substr(s.first, s.second - s.first));

    std::string sub("mul");
    int sum = 0;

    for (auto inputSeq : splittedInput)
    {
        size_t pos = inputSeq.find(sub, 0);

        while (pos != std::string::npos)
        {
            int send = pos + 3;
            if (inputSeq[send] != '(')
            {
                pos = inputSeq.find(sub, pos + 1);
                continue;
            }

            while (inputSeq[send] != ')')
            {
                // 12 is in case we have mul(999,999), any longer string is invalid.
                if (inputSeq[send] == 'm' || send - pos > 12)
                    break;

                send++;
            }

            if (inputSeq[send] == ')')
            {
                sum += evaluate(inputSeq.substr(pos + 2, send - pos));
            }

            pos = inputSeq.find(sub, pos + 1);
        }
    }

    std::cout << sum << std::endl;
    return 0;
}