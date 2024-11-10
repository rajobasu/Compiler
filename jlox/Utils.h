//
// Created by rajarshi on 10/11/24.
//

#pragma once

#include "Base.h"

template <typename... Ts> struct overload : Ts... { using Ts::operator()...; };
template <typename... Ts> overload(Ts...) -> overload<Ts...>;

template <typename VariantT, typename ObjectT, typename... Args>
inline std::unique_ptr<VariantT> make_variant_upointer(Args&&... args) {
    return std::make_unique<VariantT>(std::in_place_type<ObjectT>, std::forward<Args>(args)...);
}

