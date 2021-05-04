#include "../include_leaderboard/local_leaderboard.h"

void local_leaderboard::serialization(Player p) {
    json jp{};

    jp["name"] = p.name;
    jp["time"] = p.time;

    std::string s = jp.dump();

    if (leaderboard_file.is_open()) {
        leaderboard_file << jp.dump(4) << std::endl;
    } else {
        throw std::runtime_error("Can't open leaderboard");
    }
}

bool is_file_empty(const std::string &filename) {
    return std::ifstream(filename).peek() == EOF;
}
// namespace eclipse