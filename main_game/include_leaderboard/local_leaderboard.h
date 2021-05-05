#ifndef LOCAL_LEADERBOARD_H
#define LOCAL_LEADERBOARD_H

#include <ctime>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include <utility>

using json = nlohmann::json;

struct Player {
    std::string name;
    std::string time;
};

struct local_leaderboard {
    std::fstream leaderboard_file;  // in file

    local_leaderboard() : leaderboard_file("LeaderBoard.json", std::ios::app) {
    }

    void serialization(Player p);
};

bool is_file_empty(const std::string &filename);

#endif  // LOCAL_LEADERBOARD_H
