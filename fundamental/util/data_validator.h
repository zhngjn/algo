#pragma once
#include <vector>

namespace util
{

template <typename T>
bool isSorted(const std::vector<T>& array)
{
    if (array.size() < 2)
        return true;
    for (std::size_t i = 0; i < array.size() - 1; i++)
    {
        if (array[i] > array[i + 1])
            return false;
    }
    return true;
}

} // namespace util