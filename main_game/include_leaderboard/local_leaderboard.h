#ifndef LOCAL_LEADERBOARD_H
#define LOCAL_LEADERBOARD_H

#include <ctime>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <strstream>
#include <utility>
#include <vector>

struct Player {
    std::string name;
    std::string time;
};

struct Time {
    int mm;
    int ss;
};

void update_local_leaderboard(const Player &cur_player);

struct LocalLeaderboard {
    std::fstream leaderboard_file{};  // file
    std::vector<Player> leaderboard_array;

    void open_to_read();
    void open_to_write();
    void close_file();
    static bool comp(Player p1, Player p2);
    void add_player_to_leaderboard(const Player &cur_player);
    void deserialization();
    void serialization();
};

#endif  // LOCAL_LEADERBOARD_H
