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

struct Equation
{
    long long int total;
    std::vector<int> nums;
};

long long int evaluateEquation(std::string &s)
{
    int result = 0;
    std::deque<long long int> evalStack;
    std::deque<char> operators;

    int i = 0;
    while (i < s.length())
    {
        if (s[i] == '+' || s[i] == '*')
        {
            operators.push_back(s[i]);
            i++;
        }

        if (std::isdigit(s[i]))
        {
            std::string cur;
            while (i < s.length() && std::isdigit(s[i]))
            {
                cur += s[i];
                i++;
            }
            evalStack.push_back(std::stoll(cur));
        }
    }

    while (evalStack.size() > 1 && operators.size() > 0)
    {
        long long int f = evalStack.front();
        evalStack.pop_front();
        long long int s = evalStack.front();
        evalStack.pop_front();

        char op = operators.front();
        operators.pop_front();

        if (op == '+')
            evalStack.push_front(f + s);
        else if (op == '*')
            evalStack.push_front(f * s);
    }

    return evalStack.front();
}

void builder(std::vector<std::string> &res, std::string curr, std::vector<int> &nums, int index)
{
    // Add in the new number
    curr += std::to_string(nums[index]);

    if (index == nums.size() - 1)
    {
        res.push_back(curr);
        return;
    }

    curr += '+';
    builder(res, curr, nums, index + 1);
    curr.pop_back();
    curr += '*';
    builder(res, curr, nums, index + 1);
}

int main()
{
    std::vector<std::string> input = utils::readInputLines(std::string("input.txt"));

    std::vector<char> operators = {'+', '*'};
    std::vector<Equation> equations;

    for (auto l : input)
    {
        auto splitted = utils::splitString(l, ':');

        long long int total = stoll(splitted[0]);

        auto stripped = utils::strip(splitted[1]);
        auto equation = utils::splitString(stripped, ' ');

        // Transform string values into nums.
        auto equationValues = utils::apply(equation, [](std::string v)
                                           { return std::stoi(v); });

        equations.push_back(Equation{
            total, equationValues});
    }

    long long int totalSum = 0;
    for (auto eq : equations)
    {
        std::vector<std::string> evals;
        builder(evals, "", eq.nums, 0);

        for (auto forEval : evals)
        {
            int evald = evaluateEquation(forEval);

            if (evaluateEquation(forEval) == eq.total)
            {
                totalSum += eq.total;
                break;
            }
        }
    }

    std::cout << totalSum << std::endl;

    return 0;
}