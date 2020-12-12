#pragma once
#include <vector>
#include <ostream>
#include <algorithm>

namespace util
{
namespace detail
{

} // namespace detail

template <typename T>
void printArrayLateral(std::ostream& os, const std::vector<T>& array, char c = '*', int heightLimit = -1)
{
    if (array.empty())
        return os;

    auto maxValue = *std::max_element(array.begin(), array.end());
    double scalingFactor = (heightLimit == -1) ? 1 : (heightLimit / maxValue);
    std::vector<int> heights(array.size());
    for (std::size_t i = 0; i < array.size(); i++) 
    {
        heights[i] = static_cast<int>(array[i] * scalingFactor);
    }
    
    int height = *std::max_element(heights.begin(), heights.end()) + 1;
    for (std::size_t i = 0; i < height; i++)
    {
        for (std::size_t j = 0; j < heights.size(); j++)
        {
            os << ((i < height - heights[j]) ? ' ' : c);
        }
        os << std::endl;
    }
}

} // namespace util