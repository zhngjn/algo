#pragma once
#include <array>
#include <cstddef>
#include <cassert>
#include <algorithm>
#include <numeric>
#include <cmath>

namespace data
{

template <typename T, std::size_t Dim>
class Point
{
public:
    Point() = default;

    Point(std::initializer_list<T> args)
    {
        assert(args.size() == Dim);
        std::copy(args.begin(), args.end(), data.begin());
    }

    template <typename U, typename = std::enable_if_t<std::is_convertible<U, T>>>
    Point(U... args)
    {
        static_assert(sizeof...(args) == Dim, "args number does not match the point dimension!");
        assignElement(0, args);
    }

    T& operator[](std::size_t i)
    {
        return data[i];
    }

    const T& operator[](std::size_t i) const
    {
        return data[i];
    }

private:
    template <std::size_t Index, typename U>
    void assignElement(U arg, U... rest)
    {
        data[index] = arg;
        assignElement<Index + 1, U>(rest);
    }

    template <typename U>
    void assignElement<Dim - 1, U>(U arg)
    {
        data[Dim - 1] = arg;
    }

private:
    std::array<T, Dim> data;
};

template <typename T, std::size_t Dim>
T euclideanDistance(const Point<T, Dim>& p1, const Point<T, Dim>& p2)
{
    T dist = T(0);
    for (std::size_t i = 0; i < Dim; i++)
    {
        dist += (p1[i] - p2[i]) * (p1[i] - p2[i]);
    }
    return std::sqrt(dist);
}

} // namespace data