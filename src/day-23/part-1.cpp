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

struct Node
{
    string val;
    vector<Node *> edges;
};

unsigned long long str_hash(const std::string &str)
{
    unsigned long long hash = 5381;
    for (size_t i = 0; i < str.size(); ++i)
        hash = 33 * hash + (unsigned char)str[i];
    return hash;
}

vector<string> formConnectedComputers(const unordered_map<string, Node> &map)
{
    vector<string> result;
    set<unsigned long long> seen;
    for (auto &[key, val] : map)
    {
        string curr = key + "-";
        for (auto p : val.edges)
        {
            string inner = curr + p->val + "-";
            for (auto p2 : p->edges)
            {
                for (auto e : p2->edges)
                {
                    unsigned long long hash = str_hash(key) * str_hash(p->val) * str_hash(p2->val);
                    if (e->val == key && !seen.count(hash))
                    {
                        string dinner = inner + p2->val;
                        result.push_back(dinner);

                        seen.insert(hash);
                    }
                }
            }
        }
    }

    utils::printVec(result, true);
    return result;
}

int calculateConnections(const vector<string> &result)
{
    int ans = 0;
    for (auto const &r : result)
    {
        vector<string> splitted = utils::splitString(r, '-');
        for (auto const &s : splitted)
        {
            if (s[0] == 't')
            {
                ans++;
                break;
            }
        }
    }
    return ans;
}

int main()
{
    vector<string> input = utils::readInputLines("input.txt");
    unordered_map<string, Node> graph;

    for (const auto &l : input)
    {
        vector<string> splitted = utils::splitString(l, '-');
        string origin = splitted[0];
        string destination = splitted[1];

        if (graph.find(origin) == graph.end())
            graph[origin] = Node{origin, vector<Node *>{}};

        if (graph.find(destination) == graph.end())
            graph[destination] = Node{destination, vector<Node *>{}};

        graph[origin].edges.push_back(&graph[destination]);
        graph[destination].edges.push_back(&graph[origin]);
    }

    vector<string> connectedComputers = formConnectedComputers(graph);
    cout << calculateConnections(connectedComputers) << endl;

    return 0;
}