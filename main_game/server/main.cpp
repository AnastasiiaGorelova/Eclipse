#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <mutex>
#include "crow.h"
#include "json.hpp"

using json = nlohmann::json;

const size_t LEADERBOARD_TOP_SIZE = 100;
std::mutex mutex;

struct LeaderboardRecord {
    std::string uuid;
    std::string username;
    int64_t score;
};

struct jsonresponse : crow::response {
    jsonresponse(const nlohmann::json &_body) : crow::response{_body.dump()} {
        add_header("Access-Control-Allow-Origin", "*");
        add_header("Access-Control-Allow-Headers", "Content-Type");
        add_header("Content-Type", "application/json");
    }
};

int main() {
    crow::SimpleApp app;

    std::vector<LeaderboardRecord> records;

    CROW_ROUTE(app, "/")([]() { return "Hello world"; });

    CROW_ROUTE(app, "/submit_score")
        .methods("POST"_method)([&records](const crow::request &req) {
            std::unique_lock lock(mutex);
            auto x = crow::json::load(req.body);
            if (!x) {
                return crow::response(400);
            }

            std::string username;
            int64_t score;
            try {
                username = x["username"].s();
                score = x["score"].operator int();
            } catch (const std::runtime_error &e) {
                return crow::response(400, e.what());
            }

            std::string uuid =
                boost::uuids::to_string(boost::uuids::random_generator()());
            LeaderboardRecord record{uuid, username, score};
            records.push_back(record);
            std::sort(records.begin(), records.end(),
                      [](const auto &lhs, const auto &rhs) {
                          if (lhs.score == rhs.score) {
                              return lhs.uuid < rhs.uuid;
                          }
                          return lhs.score > rhs.score;
                      });

            auto it = std::find_if(
                records.begin(), records.end(),
                [&](const auto &elem) { return elem.uuid == uuid; });
            assert(it != records.end());

            json return_json{
                {"uuid", uuid},
                {"place", it - records.begin()},
            };
            return crow::response(jsonresponse(return_json));
        });

    CROW_ROUTE(app, "/leaderboard_top").methods("GET"_method)([&records]() {
        std::unique_lock lock(mutex);
        size_t slice_size = std::min(LEADERBOARD_TOP_SIZE, records.size());
        std::vector<json> top_records;
        for (auto it = records.begin(); it != records.begin() + slice_size;
             ++it) {
            json record{
                {"username", it->username},
                {"score", it->score},
            };
            top_records.emplace_back(std::move(record));
        }
        return jsonresponse(json(top_records));
    });

    app.port(23917).multithreaded().run();
}
