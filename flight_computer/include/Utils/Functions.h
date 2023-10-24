//
// Created by TDKua on 2023/10/23.
//

#ifndef FLIGHT_COMPUTER_FUNCTIONS_H
#define FLIGHT_COMPUTER_FUNCTIONS_H
#include <algorithm>
#include <cstdint>

/* =============================================================
 * 						FIND MAX CONSTEXPR
 * ============================================================= */
template <typename T>
T constexpr Max(T a) { return a; }

template <typename T, typename ... Args>
T constexpr Max(T a, Args ... args) { return a > Max(args...)? a : Max(args...); }
// =============================================================

#endif //FLIGHT_COMPUTER_FUNCTIONS_H
