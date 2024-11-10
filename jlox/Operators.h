//
// Created by rajarshi on 10/11/24.
//
#pragma once

#include "Base.h"
#include "Utils.h"
#include "tokens.h"
#include "errors.h"

inline auto get_unary_minus_operator_visitor(const Token &_operator) {
    return overload{
            [](const double &value) -> Literal { return -value; },
            [](const bool &value) -> Literal { return !value; },
            [=]<typename T>(const T &) -> Literal {
                throw error_handling::runtime_exception(
                        _operator,
                        "Cannot do unary minus on " + get_literal_type_as_string<T>()
                );
            },
    };
}

inline auto get_unary_plus_operator_visitor(const Token &_operator) {
    return overload{
            [](const double &value) -> Literal { return value; },
            [](const bool &value) -> Literal { return value; },
            [](const nullptr_t &value) -> Literal { return value; },
            [=]<typename T>(const T &) -> Literal {
                throw error_handling::runtime_exception(
                        _operator,
                        "Cannot do unary plus on " + get_literal_type_as_string<T>()
                );
            },
    };
}

inline auto get_unary_bang_operator_visitor(const Token &_operator) {
    return overload{
            [](const bool &value) -> Literal { return !value; },
            [=]<typename T>(const T &) -> Literal {
                throw error_handling::runtime_exception(
                        _operator,
                        "Cannot apply unary bang on " + get_literal_type_as_string<T>()
                );
            },
    };
}

inline auto get_plus_operator_visitor(const Token &_operator) {
    return overload{
            [](const double &value1, const double &value2) -> Literal { return value1 + value2; },
            [](const string &value1, const string &value2) -> Literal { return value1 + value2; },
            [=]<typename T, typename U>(const T &, const U &) -> Literal {
                throw error_handling::runtime_exception(
                        _operator,
                        "Cannot apply plus operator on " + get_literal_type_as_string<T>() + " and " +
                        get_literal_type_as_string<U>()
                );
            },
    };
}


inline auto get_multiply_operator_visitor(const Token &_operator) {
    return overload{
            [](const double &value1, const double &value2) -> Literal { return value1 * value2; },
            [=]<typename T, typename U>(const T &, const U &) -> Literal {
                throw error_handling::runtime_exception(
                        _operator,
                        "Cannot apply multiply operator on " + get_literal_type_as_string<T>() + " and " +
                        get_literal_type_as_string<U>()
                );
            },
    };
}

inline auto get_le_operator_visitor(const Token &_operator) {
    return overload{
            [](const double &value1, const double &value2) -> Literal { return value1 < value2; },
            [=]<typename T, typename U>(const T &, const U &) -> Literal {
                throw error_handling::runtime_exception(
                        _operator,
                        "Cannot apply less than operator on " + get_literal_type_as_string<T>() + " and " +
                        get_literal_type_as_string<U>()
                );
            },
    };
}

inline auto get_leq_operator_visitor(const Token &_operator) {
    return overload{
            [](const double &value1, const double &value2) -> Literal { return value1 <= value2; },
            [=]<typename T, typename U>(const T &, const U &) -> Literal {
                throw error_handling::runtime_exception(
                        _operator,
                        "Cannot apply less than or equal operator on " + get_literal_type_as_string<T>() + " and " +
                        get_literal_type_as_string<U>()
                );
            },
    };
}

inline auto get_ge_operator_visitor(const Token &_operator) {
    return overload{
            [](const double &value1, const double &value2) -> Literal { return value1 > value2; },
            [=]<typename T, typename U>(const T &, const U &) -> Literal {
                throw error_handling::runtime_exception(
                        _operator,
                        "Cannot apply greater than operator on " + get_literal_type_as_string<T>() + " and " +
                        get_literal_type_as_string<U>()
                );
            },
    };
}

inline auto get_geq_operator_visitor(const Token &_operator) {
    return overload{
            [](const double &value1, const double &value2) -> Literal { return value1 >= value2; },
            [=]<typename T, typename U>(const T &, const U &) -> Literal {
                throw error_handling::runtime_exception(
                        _operator,
                        "Cannot apply greater than or equal operator on " + get_literal_type_as_string<T>() + " and " +
                        get_literal_type_as_string<U>()
                );
            },
    };
}

inline auto get_eq_operator_visitor(const Token &_operator) {
    return overload{
            []<typename T>(const T &value1, const T &value2) -> Literal { return value1 == value2; },
            [] (const auto &, const auto &) -> Literal { return false; },
    };
}

inline auto get_neq_operator_visitor(const Token &_operator) {
    return overload{
            []<typename T>(const T &value1, const T &value2) -> Literal { return value1 != value2; },
            [] (const auto &, const auto &) -> Literal { return true; },
    };
}





