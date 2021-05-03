#ifndef LOCAL_LEADERBOARD_H
#define LOCAL_LEADERBOARD_H

#include <ctime>
#include <fstream>
//#include <nlohmann/json.hpp>
#include <string>
#include <utility>

//using json = nlohmann::json;

namespace eclipse {

struct Player {
    std::string name;
    time_t time;
};

struct local_leaderboard {
//    std::ofstream leaderboard_file;  // in file
//    json leaderboard;
//
//    local_leaderboard()
//        : leaderboard_file("LeaderBoard.json", std::ios::app),
//          leaderboard(json::parse("LeaderBoard.json")) {
//    }
//
    void serialization(Player p);
};

}  // namespace eclipse

#endif  // LOCAL_LEADERBOARD_H
