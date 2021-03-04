#ifndef MAIN_GAME_UTIL_H
#define MAIN_GAME_UTIL_H

#include <random>
#include <string>

std::string new_uuid() {
    static auto &chrs =
        "0123456789"
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    thread_local static std::mt19937 gen{std::random_device{}()};
    thread_local static std::uniform_int_distribution<std::string::size_type>
        dis(0, sizeof(chrs) - 2);
    std::string str;
    int length = 10;
    str.reserve(length);
    while (length--)
        str += chrs[dis(gen)];

    return str;
}

#endif  // MAIN_GAME_UTIL_H
