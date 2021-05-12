#ifndef LOCAL_LEADERBOARD_H
#define LOCAL_LEADERBOARD_H

#include <ctime>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>


struct Player {
    std::string name;
    std::string time;
};

void update_local_leaderboard(Player cur_player);

struct LocalLeaderboard {
    std::fstream leaderboard_file;  // file
    std::vector<Player> leaderboard_array;

    LocalLeaderboard();

    bool comp (Player p1, Player p2);

    void add_player_to_leaderboard(Player cur_player);

    void deserialization();

    void serialization();
};

bool is_file_empty(const std::string &filename);

#endif  // LOCAL_LEADERBOARD_H
