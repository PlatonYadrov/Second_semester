#ifndef ARRAY_TRAITS
#define ARRAY_TRAITS
#include <iostream>

// kIsArray<T>
template <class T>
struct kIsArray : std::false_type {};  // NOLINT

template <class T>
struct kIsArray<T[]> : std::true_type {};

template <class T, size_t N>
struct kIsArray<T[N]> : std::true_type {};

template <class T>
inline constexpr bool kIsArrayV = kIsArray<T>::value;
// kRank<T>

template <class T>
struct kRank : std::integral_constant<size_t, 0> {};  // NOLINT

template <class T>
inline constexpr size_t kRankV = kRank<T>::value;

template <class T>
struct kRank<T[]> : std::integral_constant<size_t, kRankV<T> + 1> {};

template <class T, size_t N>
struct kRank<T[N]> : std::integral_constant<size_t, kRankV<T> + 1> {};
// kSize<T>

template <class T>
struct kSize : std::integral_constant<size_t, 1> {};  // NOLINT

template <class T>
struct kSize<T[]> : std::integral_constant<size_t, 0> {};

template <class T, size_t N>
struct kSize<T[N]> : std::integral_constant<size_t, N> {};

template <class T>
inline constexpr size_t kSizeV = kSize<T>::value;
// kTotalSize<T>

template <class T>
struct kTotalSize : std::integral_constant<size_t, 1> {};  // NOLINT

template <class T>
inline constexpr size_t kTotalSizeV = kTotalSize<T>::value;

template <class T>
struct kTotalSize<T[]> : std::integral_constant<size_t, 0> {};

template <class T, size_t N>
struct kTotalSize<T[N]> : std::integral_constant<size_t, N * kTotalSizeV<T>> {};

// RemoveArray<T>
template <class T>
struct RemoveArray {
  using Type = T;
};

template <class T>
struct RemoveArray<T[]> {
  using Type = T;
};

template <class T, size_t N>
struct RemoveArray<T[N]> {
  using Type = T;
};

template <class T>
using RemoveArrayT = typename RemoveArray<T>::Type;

// RemoveAllArrays<T>
template <class T>
struct RemoveAllArrays {
  using Type = T;
};

template <class T>
using RemoveAllArraysT = typename RemoveAllArrays<T>::Type;

template <class T>
struct RemoveAllArrays<T[]> {
  using Type = RemoveAllArraysT<T>;
};

template <class T, size_t N>
struct RemoveAllArrays<T[N]> {
  using Type = RemoveAllArraysT<T>;
};

#endif
