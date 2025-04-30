// ds_utils.hpp
#pragma once
#include <iostream>
#include <array>

namespace dslib {


    // cout<< array;
    template <typename T, std::size_t N>
    std::ostream& operator<<(std::ostream& os, const std::array<T, N>& arr) {
        os << "[";
        for (std::size_t i = 0; i < N; ++i) {
            os << arr[i];
            if (i + 1 < N) os << ", ";
        }
        os << "]";
        return os;
    }


} // namespace dslib
