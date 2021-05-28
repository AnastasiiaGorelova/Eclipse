#include "upstream_leaderboard.h"

void UpstreamLeaderboard::call_client(const Player &cur_player) {
    std::string string_req = "python3.9 ../client/main.py " + cur_player.name +
                             " " + std::to_string(score) + " > " + file_name;
    std::cerr << string_req << std::endl;
    const char *request = string_req.c_str();
    try {
        system(request);
    } catch (...) {
        std::cerr << "Server is closed" << std::endl;
    }
}

void UpstreamLeaderboard::open_to_write() {
    leaderboard_file.open(file_name, std::ios_base::out);
    if (!leaderboard_file) {
        throw std::runtime_error("Can't open leaderboard");
    }
}

void UpstreamLeaderboard::make_score(const Player &cur_player) {
    std::string for_changing = cur_player.time;
    std::ostringstream first_m;
    std::ostringstream first_s;
    std::ostringstream second_m;
    std::ostringstream second_s;
    first_m << for_changing[0] << for_changing[1];
    first_s << for_changing[3] << for_changing[4];

    Time for_score{std::stoi(first_m.str()), std::stoi(first_s.str())};
    score = for_score.mm * 60 + for_score.ss;
}

void upload_json_from_server_to_file(const Player &cur_player) {
    UpstreamLeaderboard my_leaderboard;
    my_leaderboard.open_to_write();
    my_leaderboard.make_score(cur_player);
    my_leaderboard.call_client(cur_player);
}