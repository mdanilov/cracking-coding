#pragma once

#include <type_traits>

namespace utils {
template <class T>
inline T logicalShift(T t1, T t2) {
  return static_cast<typename std::make_unsigned<T>::type>(t1) >> t2;
}
}  // namespace utils
