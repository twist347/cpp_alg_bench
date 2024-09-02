#pragma once

#include <algorithm>
#include <random>
#include <array>
#include <cmath>

namespace utils {

    template<typename T>
    concept Numeric = std::is_integral_v<T> || std::is_floating_point_v<T>;

    template<typename Numeric>
    auto hard_func(Numeric x) -> Numeric {
        return std::sin(x) + std::cos(x) * std::exp(x) - std::log(x) + 1 / std::sqrt(std::legendre(3, x));
    }

    namespace detail {

        template<Numeric Value>
        struct RndDis {
            using type = std::conditional_t<
                std::is_integral_v<Value>,
                    std::uniform_int_distribution<Value>,
                    std::uniform_real_distribution<Value>
            >;
        };

    }

    template<typename Value>
    requires Numeric<Value>
    auto gen_rnd_num(Value min, Value max) -> Value {
        static std::mt19937 gen(std::random_device{}());
        return typename detail::RndDis<Value>::type{min, max}(gen);
    }

    template<typename Iter>
    requires Numeric<typename std::iterator_traits<Iter>::value_type>
    auto fill_data(
        Iter first, Iter last,
        typename std::iterator_traits<Iter>::value_type min_val,
        typename std::iterator_traits<Iter>::value_type max_val
    ) -> void {
        std::generate(first, last, [min_val, max_val]() { return gen_rnd_num(min_val, max_val); });
    }

    template<typename Iter>
    auto fill_rnd_str(Iter first, Iter last) -> void {
        static const std::array<char, 62> characters = {
            'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
            'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
            'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
            'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
            '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'
        };

        for (auto it = first; it != last; ++it) {
            *it = characters[gen_rnd_num<std::size_t>(0, characters.size() - 1)];
        }
    }

}