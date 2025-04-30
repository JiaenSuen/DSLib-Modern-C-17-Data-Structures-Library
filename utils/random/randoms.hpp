// Random_Generator.hpp
#ifndef RANDOM_GENERATOR_HPP
#define RANDOM_GENERATOR_HPP

#include <iostream>
#include <random>
#include <string>
#include <array>
#include <chrono>

class Random_Generator {
public:
    static Random_Generator& instance() {
        static Random_Generator instance;
        return instance;
    }

    int generate_int(int min = 0, int max = 100) {
        std::uniform_int_distribution<int> dist(min, max);
        return dist(rng);
    }

    float generate_float(float min = 0.0f, float max = 100.0f) {
        std::uniform_real_distribution<float> dist(min, max);
        return dist(rng);
    }

    double generate_double(double min = 0.0, double max = 100.0) {
        std::uniform_real_distribution<double> dist(min, max);
        return dist(rng);
    }

    std::string generate_string(size_t min_length = 5, size_t max_length = 10) {
        std::string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
        std::uniform_int_distribution<size_t> length_dist(min_length, max_length);
        std::uniform_int_distribution<size_t> char_dist(0, chars.size() - 1);
        
        size_t length = length_dist(rng);
        std::string result;
        for (size_t i = 0; i < length; ++i) {
            result += chars[char_dist(rng)];
        }
        return result;
    }

    template <typename T, size_t N>
    std::array<T, N> generate_array(T min, T max) {
        std::array<T, N> arr;
        std::uniform_real_distribution<double> dist(min, max);
        for (size_t i = 0; i < N; ++i) {
            arr[i] = static_cast<T>(dist(rng));
        }
        return arr;
    }

private:
    Random_Generator() {
        rng.seed(std::chrono::steady_clock::now().time_since_epoch().count());
    }

    std::mt19937 rng;
};

#endif // RANDOM_GENERATOR_HPP
