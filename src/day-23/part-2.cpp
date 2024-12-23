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

void dfs(unordered_map<string, Node> &map, set<string> &visited, string key)
{
    cout << key << endl;
    visited.insert(key);
    for (auto const &neighbor : map[key].edges)
        if (!visited.count(neighbor->val))
            dfs(map, visited, neighbor->val);
}

// Apparently there is a single connected component.
vector<string> findConnectedComponents(unordered_map<string, Node> &map)
{
    vector<string> result;
    set<string> visited;

    int ccCount = 0;

    for (auto &[key, val] : map)
    {
        cout << visited.count(key) << endl;
        if (!visited.count(key))
        {
            dfs(map, visited, key);
            ccCount++;
        }
    }

    cout << ccCount << endl;

    return result;
}

bool isClique(unordered_map<string, Node> &map, vector<string> &vertices)
{
    for (auto v : vertices)
    {
        for (auto v2 : vertices)
        {
            if (v == v2)
                continue;

            bool found = false;
            for (auto e : map[v].edges)
            {
                if (e->val == v2)
                {
                    found = true;
                    break;
                }
            }
            if (!found)
                return false;
        }
    }

    return true;
}

vector<string> findCliques(unordered_map<string, Node> &map, vector<string> current, set<string> &visited)
{
    int i = current.size() - 1;
    auto vals = map[current[i]].edges;

    if (visited.count(current[i]))
        return current;

    visited.insert(current[i]);

    int mxClique = 0;
    vector<string> mxCliqueVec(current.begin(), current.end());

    for (auto e : vals)
    {
        if (find(current.begin(), current.end(), e->val) != current.end())
            continue;

        current.push_back(e->val);

        if (isClique(map, current))
        {
            auto result = findCliques(map, current, visited);
            if (result.size() > mxClique)
            {
                mxClique = result.size();
                mxCliqueVec = vector(result.begin(), result.end());
            }
        }

        current.pop_back();
    }

    return mxCliqueVec;
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

    // findConnectedComponents(graph);
    int maxCliqueSize = 0;
    vector<string> maxClique;
    set<string> visited;

    for (auto &[key, val] : graph)
    {
        vector<string> current = findCliques(graph, vector<string>{key}, visited);
        if (current.size() > maxCliqueSize)
        {
            maxClique = vector<string>(current.begin(), current.end());
            maxCliqueSize = current.size();
        }
    }

    cout << maxCliqueSize << endl;
    sort(maxClique.begin(), maxClique.end());
    stringstream out;
    for (auto x : maxClique)
        out << x << ',';
    cout << out.str().substr(0, out.str().length() - 1) << endl;

    return 0;
}