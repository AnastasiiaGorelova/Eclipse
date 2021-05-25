#include "local_leaderboard.h"

bool LocalLeaderboard::comp(Player p1, Player p2) {
    std::ostringstream first_m;
    std::ostringstream first_s;
    std::ostringstream second_m;
    std::ostringstream second_s;
    first_m << p1.time[0] << p1.time[1];
    first_s << p1.time[3] << p1.time[4];
    second_m << p2.time[0] << p2.time[1];
    second_s << p2.time[3] << p2.time[4];
    Time t1{std::stoi(first_m.str()), std::stoi(first_s.str())};
    Time t2{std::stoi(second_m.str()), std::stoi(second_s.str())};

    return (t1.mm > t2.mm) or (t1.mm == t2.mm and t1.ss > t2.ss);
}

void LocalLeaderboard::open_to_read() {
    std::ofstream create_file("LocalLeaderBoard.txt", std::ios_base::app);
    create_file.close();

    leaderboard_file.open("LocalLeaderBoard.txt", std::ios_base::in);

    if (!leaderboard_file) {
        throw std::runtime_error("Can't open leaderboard");
    }
}

void LocalLeaderboard::deserialization() {
    std::cerr << "(deserialization) What is in file:" << std::endl;
    assert(leaderboard_file.is_open());
    while (!leaderboard_file.eof()) {
        std::string s_n;
        std::string s_t;
        leaderboard_file >> s_n >> s_t;
        std::cerr << s_n << " " << s_t << std::endl;
        if (!s_n.empty() and !s_t.empty()) {
            Player my_player{s_n, s_t};
            leaderboard_array.push_back(my_player);
        }
        assert(leaderboard_array.size() <= 10);
    }
}

void LocalLeaderboard::add_player_to_leaderboard(Player &cur_player) {
    leaderboard_array.push_back(cur_player);
    sort(leaderboard_array.begin(), leaderboard_array.end(), comp);
    assert(leaderboard_array.size() <= 11);
}

void LocalLeaderboard::close_file() {
    leaderboard_file.close();
}

void LocalLeaderboard::open_to_write() {
    leaderboard_file.open("LocalLeaderBoard.txt", std::ios_base::out);

    if (!leaderboard_file) {
        throw std::runtime_error("Can't open leaderboard");
    }
}

void LocalLeaderboard::serialization() {
    std::cerr << "(serialization) What is in sorted arr:" << std::endl;
    for (const auto &u : leaderboard_array) {
        std::cerr << u.name << " " << u.time << std::endl;
    }

    for (unsigned int i = 0; i < 10 and i < leaderboard_array.size(); i++) {
        leaderboard_file << leaderboard_array[i].name << " "
                         << leaderboard_array[i].time << std::endl;
    }
}
void LocalLeaderboard::delete_spaces_from_name(Player &cur_player) {
    for (char &i : cur_player.name) {
        if (i == ' ') {
            i = '_';
        }
    }
}

void update_local_leaderboard(Player &cur_player) {
    // открыть/создать файл
    LocalLeaderboard my_leaderboard;
    my_leaderboard.open_to_read();
    // десериальзовать данные в массив
    LocalLeaderboard::delete_spaces_from_name(cur_player);
    my_leaderboard.deserialization();
    // добавить новый результат в массив, отсортировать массив
    my_leaderboard.add_player_to_leaderboard(cur_player);
    my_leaderboard.close_file();
    my_leaderboard.open_to_write();
    // сериализовать в файл первые 10
    my_leaderboard.serialization();
}
// namespace eclipse