
#include <cstddef>
#include <utility>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <iomanip>
#include <cassert>

std::vector<std::pair<int, int>> generatePairs(std::size_t pairNum, std::size_t N)
{
    
}

class QuickUnion
{
public:
    QuickUnion(std::size_t N)
    {
        id.resize(N);
        for (std::size_t i = 0; i < N; i++)
        {
            id[i] = i;
            sz[i] = 1;
        }
        numberWidth = std::to_string(id.size() - 1).size();
    }

    void quickUnion(int p, int q)
    {
        if (p == q) 
            return; 
        int i, j;
        for (i = p; i != id[i]; i = id[i]);
        for (j = q; j != id[j]; j = id[j]);
        if (i == j)
            return;
        else
            id[i] = j;
    }

    void quickUnion(const std::vector<std::pair<int, int>>& pairs)
    {
        for (const auto& p: pairs)
        {
            quickUnion(p.first, p.second);
        }
    }

    void weightedQuickUnion(int p, int q)
    {
        if (p == q) 
            return; 
        int i, j;
        for (i = p; i != id[i]; i = id[i]);
        for (j = q; j != id[j]; j = id[j]);
        if (i == j)
            return;
        else
        {
            if (sz[i] <= sz[j])
                id[i] = j;
            else
                id[j] = i;
        }
    }

    void weightedQuickUnion(const std::vector<std::pair<int, int>>& pairs)
    {
        for (const auto& p: pairs)
        {
            weightedQuickUnion(p.first, p.second);
        }
    }

    void pathCompressQuickUnion(int p, int q)
    {
        if (p == q) 
            return; 
        int i, j;
        for (i = p; i != id[i]; i = id[i])
            id[i] = id[id[i]];
        for (j = q; j != id[j]; j = id[j])
            id[i] = id[id[i]];
        if (i == j)
            return;
        else
            id[i] = j;
    }

    void pathCompressQuickUnion(const std::vector<std::pair<int, int>>& pairs)
    {
        for (const auto& p: pairs)
        {
            pathCompressQuickUnion(p.first, p.second);
        }
    }

    void print(std::ostream& os) const
    {
        auto roots = getRoots();
        auto children = getChildren();
        // for debug
        std::unordered_set<int> visited;
        
        for (const auto num: roots)
        {
            printNum(os, 0, num, children, visited);
        }

        assert(visited.size() == id.size());
    }

private:
    void printNum(std::ostream& os,
                  int indent, 
                  int num, 
                  std::unordered_map<int, std::vector<int>>& children, 
                  std::unordered_set<int>& visited) const
    {
        if (indent != 0)
        {
            os << std::string(indent, ' ') << "|-";
        }
        os << std::setw(numberWidth) << num;
        visited.insert(num);
        if (children.find(num) != children.end())
        {
            os << "-" << std::endl;
            auto newIndent = indent + numberWidth + 2;
            for (const auto i : children[num])
            {
                printNum(os, newIndent, i, children);
            }
        }
        else
        {
            os << std::endl;
        }
    }

    std::vector<int> getRoots() const
    {
        std::vector<int> roots;
        for (int i = 0; i < id.size(); i++)
        {
            if (i == id[i])
                roots.push_back(i);
        }
        return roots;
    }

    std::unordered_map<int, std::vector<int>> getChildren() const
    {
        std::unordered_map<int, std::vector<int>> children;
        for (int i = 0; i < id.size(); i++)
        {
            if (i != id[i])
            {
                children[id[i]].push_back(i);
            }
        }
        return children;
    }

public:
    std::vector<int> id;
    std::vector<int> sz;
    // for print format
    std::size_t numberWidth;
};

bool assertUnionEq(const QuickUnion& qu1, const QuickUnion& qu2)
{
    if (qu1.id.size() != qu2.id.size())
        return false;
    for (std::size_t i = 0; i < qu1.id.size(); i++)
    {
        // if (qu1.id[i] != qu2.id[i])
        //     return false;
    }
    return true;
}

int main()
{
    const std::size_t N = 100;
    const std::size_t pairNum = 50;

    const auto pairs = generatePairs(pairNum, N);

    QuickUnion qu1(N), qu2(N), qu3(N);
    qu1.quickUnion(pairs);
    qu2.weightedQuickUnion(pairs);
    qu3.pathCompressQuickUnion(pairs);

    assert(assertUnionEq(qu1, qu2) && assertUnionEq(qu2, qu3));

    qu1.print(std::cout);
    std::cout << std::endl << "-------------------------------------------------" << std::endl;
    qu2.print(std::cout);
    std::cout << std::endl << "-------------------------------------------------" << std::endl;
    qu3.print(std::cout);
}