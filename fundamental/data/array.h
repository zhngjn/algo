#pragma once

#include <chrono>
#include <random>

namespace data
{

class RandomArrayGenerator
{
public:
    static std::vector<int> genRandomIntArray(int a, int b, std::size_t size)
    {
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        generator.seed(seed);

        std::uniform_int_distribution<int> distribution(a, b);

        std::vector<int> randoms;
        for (std::size_t i = 0; i < size; i++)
        {
            randoms.push_back(distribution(generator));
        }
        return randoms;
    }

    static std::vector<double> genRandomDoubleArray(double a, double b, std::size_t size)
    {
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        generator.seed(seed);

        std::uniform_real_distribution<double> distribution(a, b);

        std::vector<double> randoms;
        for (std::size_t i = 0; i < size; i++)
        {
            randoms.push_back(distribution(generator));
        }
        return randoms;
    }

private:
    static std::minstd_rand0 generator;
};

} // namespace data