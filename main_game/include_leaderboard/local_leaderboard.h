#ifndef LOCAL_LEADERBOARD_H
#define LOCAL_LEADERBOARD_H

#include <algorithm>
#include <cassert>
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
    int64_t mm;
    int64_t ss;
};

void update_local_leaderboard(Player &cur_player);

struct LocalLeaderboard {
private:
    std::fstream leaderboard_file{};  // file
    std::vector<Player> leaderboard_array;

public:
    void open_to_read();
    void open_to_write();
    void close_file();
    static bool comp(Player p1, Player p2);
    void add_player_to_leaderboard(Player &cur_player);
    void deserialization();
    void serialization();
    static void delete_spaces_from_name(Player &cur_player);
};

#endif  // LOCAL_LEADERBOARD_H
