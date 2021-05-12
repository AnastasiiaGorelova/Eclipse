#include "../include_leaderboard/local_leaderboard.h"

void update_local_leaderboard(Player cur_player) {
    // открыть/создать файл
    LocalLeaderboard my_leaderboard{};
    // десериальзовать данные в массив
    my_leaderboard.deserialization();
    // добавить новый результат, отсортировать массив
    my_leaderboard.add_player_to_leaderboard(cur_player);
    // сериализовать в файл первые 10
}

void LocalLeaderboard::serialization() {
    if (leaderboard_file.is_open()) {
    } else {
        throw std::runtime_error("Can't open leaderboard");
    }
}

void LocalLeaderboard::deserialization() {
    std::string s_n;
    std::string s_t;

    while (!leaderboard_file.eof()) {
        leaderboard_file >> s_n, leaderboard_file >> s_t;
        std::cerr << s_n << " " << s_t << std::endl;
        Player my_player{s_n, s_t};
        leaderboard_array.push_back(my_player);
        assert(leaderboard_array.size() <= 10);
    }
}

LocalLeaderboard::LocalLeaderboard() {
    leaderboard_file.open("LocalLeaderBoard.txt");

    if (!leaderboard_file.is_open()) {
        throw std::runtime_error("Can't open leaderboard");
    }
}

void LocalLeaderboard::add_player_to_leaderboard(Player cur_player) {
    leaderboard_array.push_back(cur_player);
    sort(leaderboard_array.begin(), leaderboard_array.end(), comp());
}

bool LocalLeaderboard::comp(Player p1, Player p2) {
    return false;
}

bool is_file_empty(const std::string &filename) {
    return std::ifstream(filename).peek() == EOF;
}
// namespace eclipse