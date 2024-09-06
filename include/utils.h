#pragma once

#include <algorithm>
#include <random>
#include <array>
#include <cmath>

namespace utils {

    template<typename Value>
    concept Numeric = std::integral<Value> || std::floating_point<Value>;

    namespace funcs {

        template<std::floating_point Value>
        [[maybe_unused]] auto unary_func(Value x) -> Value {
            return std::sin(x)
                   + std::cos(x) * std::exp(x)
                   - std::log(x)
                   + 1 / std::sqrt(std::legendre(3, x))
                   + std::pow(x, 2.5) * std::exp2(x)
                   - std::cbrt(std::tgamma(x + 1))
                   + std::sinh(std::log(x))
                   - std::cosh(std::exp(x))
                   + std::tan(std::atan(x))
                   + std::lgamma(x);
        }

        template<std::floating_point Value>
        [[maybe_unused]] auto binary_func(Value x, Value y) -> Value {
            return std::sin(x * y)
                   + std::cos(x) * std::exp(y)
                   - std::log(x + y)
                   + 1 / std::sqrt(std::legendre(3, x))
                   + std::pow(x + y, 3.5)
                   - std::cbrt(std::tgamma(x * y + 1))
                   + std::sinh(std::log(x * y))
                   - std::cosh(std::exp(x + y))
                   + std::tan(std::atan(x * y))
                   + std::lgamma(x * y);
        }

        template<Numeric Value>
        [[maybe_unused]] auto num_sin_integration(Value x) -> Value {
            const std::size_t n = 1'000;
            const Value h = x / n;
            Value sum = 0.0;
            for (std::size_t i = 1; i < n; ++i) {
                const Value xi = i * h;
                sum += std::sin(xi);
            }
            sum += (std::sin(0) + std::sin(x)) / 2;
            return sum * h;
        }

        template<std::floating_point Value>
        auto newton_sqrt(Value x) -> Value {
            const Value eps = 1e-10;
            const std::size_t n = 1'000;
            auto guess = x;
            for (std::size_t i = 0; i < n; ++i) {
                const auto f = guess * guess - x;
                const auto f_prime = 2 * guess;
                const auto next_guess = guess - f / f_prime;
                if (std::abs(next_guess - guess) < eps) {
                    break;
                }
                guess = next_guess;
            }
            return guess;
        }

        template<std::floating_point Value>
        constexpr auto gauss_elimination(Value a, Value b) -> Value {
            const std::size_t n = 50;
            std::vector<std::vector<Value>> matrix(n, std::vector<Value>(n, a));
            std::vector<Value> rhs(n, b);
            for (std::size_t i = 0; i < n; ++i) {
                for (std::size_t j = i + 1; j < n; ++j) {
                    const auto ratio = matrix[j][i] / matrix[i][i];
                    for (std::size_t k = i; k < n; ++k) {
                        matrix[j][k] -= ratio * matrix[i][k];
                    }
                    rhs[j] -= ratio * rhs[i];
                }
            }
            return rhs[0];
        }

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
    auto fill_rnd_range(
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

        while (first != last) {
            *first++ = characters[gen_rnd_num<std::size_t>(0, characters.size() - 1)];
        }
    }

}