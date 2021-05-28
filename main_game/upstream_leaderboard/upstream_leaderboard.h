#ifndef MAIN_GAME_UPSTREAM_LEADERBOARD_H
#define MAIN_GAME_UPSTREAM_LEADERBOARD_H

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <strstream>
#include <utility>
#include <vector>
#include "local_leaderboard.h"

void upload_json_from_server_to_file(const Player &cur_player);

struct UpstreamLeaderboard {
private:
    std::ofstream leaderboard_file{};  // file
    std::string file_name = "ServerLeaderBoard.json";
    int64_t score;

public:
    void call_client(const Player &cur_player);
    void open_to_write();
    void make_score(const Player &cur_player);
};

#endif  // MAIN_GAME_UPSTREAM_LEADERBOARD_H
