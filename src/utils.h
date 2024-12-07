#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <cctype>

namespace utils
{
    std::string readInput(const std::string &fname)
    {
        std::ifstream input_file(fname);

        // Read the file line by line into a string
        std::string line;
        std::stringstream ss;

        while (std::getline(input_file, line))
        {
            ss << line << std::endl;
        }

        // Close the file
        input_file.close();

        return ss.str();
    }

    std::vector<std::string> readInputLines(const std::string &fname)
    {
        std::ifstream input_file(fname);
        std::vector<std::string> output;

        // Read the file line by line into a vector
        std::string line;

        while (std::getline(input_file, line))
            output.push_back(line);

        // Close the file
        input_file.close();

        return output;
    }

    std::vector<std::string> splitString(std::string &toSplit, const char del)
    {
        std::string s;
        std::vector<std::string> res;
        std::stringstream ss(toSplit);
        while (std::getline(ss, s, del))
        {
            res.push_back(s);
        }
        return res;
    }

    std::string strip(const std::string &inpt)
    {
        auto start_it = inpt.begin();
        auto end_it = inpt.rbegin();
        while (std::isspace(*start_it))
            ++start_it;
        while (std::isspace(*end_it))
            ++end_it;
        return std::string(start_it, end_it.base());
    }

    template <typename A>
    void printVec(std::vector<A> &vec, bool nls)
    {
        for (auto val : vec)
        {
            if (nls)
                std::cout << val << std::endl;
            else
                std::cout << val << " ";
        }
    }

    template <typename C, typename F>
    auto apply(C &&container, F &&func)
    {
        using std::begin;
        using std::end;

        using E = std::decay_t<decltype(std::forward<F>(func)(
            *begin(std::forward<C>(container))))>;

        std::vector<E> result;
        auto first = begin(std::forward<C>(container));
        auto last = end(std::forward<C>(container));

        result.reserve(std::distance(first, last));
        for (; first != last; ++first)
        {
            result.push_back(std::forward<F>(func)(*first));
        }
        return result;
    }

}