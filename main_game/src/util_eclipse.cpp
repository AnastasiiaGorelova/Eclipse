#include "util_eclipse.h"

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

int random_number(int l, int r) {
    std::mt19937 gen{std::random_device{}()};
    std::uniform_int_distribution<> dist(l, r);
    return dist(gen);
}
