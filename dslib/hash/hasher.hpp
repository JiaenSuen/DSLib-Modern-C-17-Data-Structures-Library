#pragma once
#ifndef DS_LIB_HASHING_HASHER_HPP
#define DS_LIB_HASHING_HASHER_HPP

#include <type_traits>
#include <cstdint>
#include <string>
#include <array>
#include <tuple>
#include <cstring>
#include <utility>

namespace dslib {
namespace hashing {

    // Router Define
    template <typename T>
    struct Hash_Transform;




    // General numeric → unsigned int
    template <typename T>
    struct NumericHasher {
        static_assert(std::is_integral_v<T> || std::is_floating_point_v<T>,
                    "NumericHasher: unsupported type.");
        unsigned int operator()(const T& value) const {
            if constexpr (std::is_integral_v<T>) {
                return static_cast<unsigned int>(value);
            } else {
                if constexpr (sizeof(T) == 4) {
                    uint32_t bits;
                    std::memcpy(&bits, &value, sizeof(bits));
                    return bits;
                } else {  
                    uint64_t bits;
                    std::memcpy(&bits, &value, sizeof(bits));
                    return static_cast<unsigned int>(bits ^ (bits >> 32));
                }
            }
        }
    };

    // string Hash with DJBX33A Algorithm
    struct StringHasher {
        unsigned int operator()(const std::string& s) const {
            unsigned int h = 5381;
            for (unsigned char c : s) {
                h = ((h << 5) + h) + c; // h * 33 + c
            }
            return h;
        }
    };

    // Array Hash Process Each One by one
    template <typename T, std::size_t N>
    struct ArrayHasher {
        unsigned int operator()(const std::array<T, N>& arr) const {
            unsigned int h = 0;
            for (auto const& e : arr) 
                h ^= dslib::hashing::Hash_Transform<T>()(e);
            return h;
        }
    };



    // Routing Assignation ::  Responsible for determining the type and directing it to a dedicated hasher.
    template <typename T>
    struct Hash_Transform {
        unsigned int operator()(const T& key) const {
            if constexpr (std::is_integral_v<T> || std::is_floating_point_v<T>) {
                return NumericHasher<T>()(key);
            } else if constexpr (std::is_same_v<T, std::string>) {
                return StringHasher()(key);
            } else {
                static_assert(sizeof(T) == 0, "Hash_Transform: unsupported type.");
            }
        }
    };

    // Define NULL Function For Hash Structure Type Data By Hash All of Data In Structure
    #define DEFINE_HASH_FOR(Type, ...)                                                        \
    template <>                                                                               \
    struct dslib::hashing::Hash_Transform<Type> {                                             \
        unsigned int operator()(const Type& value) const {                                    \
            unsigned int h = 0;                                                               \
            using dslib::hashing::Hash_Transform;                                             \
            auto members = std::make_tuple(__VA_ARGS__);                                      \
            std::apply([&](auto... memberPtrs) {                                              \
                ((h ^= Hash_Transform<std::decay_t<decltype(value.*memberPtrs)>>()(value.*memberPtrs)), ...); \
            }, members);                                                                      \
            return h;                                                                         \
        }                                                                                     \
    };

    template <typename T, std::size_t N>
    struct Hash_Transform<std::array<T, N>> {
        unsigned int operator()(const std::array<T, N>& arr) const {
            return ArrayHasher<T, N>()(arr);
        }
    };


}} // namespace dslib::hashing

#endif // DS_LIB_HASHING_HASHER_HPP
