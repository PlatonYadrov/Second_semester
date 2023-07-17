#ifndef ISPRIME
#define ISPRIME
#include <iostream>

template <uint64_t Argument, uint64_t L, uint64_t R, uint64_t Mid = (R + L + 1) / 2>
struct Sqrt : Sqrt<Argument, (((R <= 3000000000) && (Mid * Mid <= Argument)) ? Mid : L),
                   (((R <= 3000000000) && (Mid * Mid <= Argument)) ? R : Mid - 1)> {};

template <uint64_t Argument, uint64_t Ans>
struct Sqrt<Argument, Ans, Ans, Ans> : std::integral_constant<uint64_t, Ans> {};

template <uint64_t Argument>
inline const uint64_t kSqrtV = Sqrt<Argument, 0, Argument>::value;

template <uint64_t Argument, uint64_t L, uint64_t R, uint64_t Mid = (R + L + 1) / 2>
struct HasDivisor : std::bool_constant<HasDivisor<Argument, Mid, R>::value || HasDivisor<Argument, L, Mid - 1>::value> {
};

template <uint64_t Argument, uint64_t Ans>
struct HasDivisor<Argument, Ans, Ans, Ans> : std::bool_constant<(Argument % Ans) == 0> {};

template <uint64_t Argument>
struct HasDivisor<Argument, 0, 0, 0> : std::bool_constant<false> {};

template <uint64_t Argument, uint64_t L, uint64_t R>
inline const bool kHasDivisorOnV = HasDivisor<Argument, L, R>::value;

template <uint64_t Argument>
struct IsPrimeV : std::bool_constant<!kHasDivisorOnV<Argument, 2, kSqrtV<Argument>>> {};

template <>
struct IsPrimeV<1> : std::bool_constant<false> {};

template <>
struct IsPrimeV<2> : std::bool_constant<true> {};

template <>
struct IsPrimeV<3> : std::bool_constant<true> {};

template <uint64_t Argument>
inline const bool kIsPrimeV = IsPrimeV<Argument>::value;
#endif
