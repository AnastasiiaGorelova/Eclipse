#include "../include_leaderboard/local_leaderboard.h"

int main() {
    LocalLeaderboard ll{};

    if (is_file_empty("LeaderBoard.json")) {
        for (int i = 0; i < 10; i++) {
            Player p;
            p.name = "Player: " + std::to_string(i);
            p.time = "12:00:9";
            //                Players.push_back(p);
            //                json leaderboard(Players);
            ll.serialization(p);
        }
    } else {
    }

    std::ifstream file("LeaderBoard.json");
    json j = json::parse(file);
}