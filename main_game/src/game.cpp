#include "game.h"
#include "game_fwd.h"
#include "util.h"
#include <vector>

#include "God.h"
extern ::God damn;


namespace eclipse {
    namespace {
        int random_number(int l, int r) {
            std::mt19937 gen{std::random_device{}()};
            std::uniform_int_distribution<> dist(l, r);
            return dist(gen);
        }

    }// namespace

    void Game::recover_ship() {
        change_field(ship.get_coordinates().first,
                     ship.get_coordinates().first + ship.get_size(),
                     ship.get_coordinates().second,
                     ship.get_coordinates().second + ship.get_size(),
                     "abcd");
    }

    std::string Game::checker_for_nothing(int x_start,
                                          int x_finish,
                                          int y_start,
                                          int y_finish) const {
        for (int i = x_start; i < x_finish; i++) {
            for (int j = y_start; j < y_finish; j++) {
                if (j >= kHeight || j < 0) {
                    return "edge";
                }
                if (get_field_state(i, j) != default_id) {
                    return get_field_state(i, j);
                }
            }
        }
        return default_id;
    }

    void Game::check_for_living() {
        --lives;
        //std::cerr << "- ";
        if (lives <= 0) {// dead
            game_state = kFinished;
            changes.emplace_back(Changes{Finish_game});
        } else {
            changes.emplace_back(Changes{Decrease_lives});
        }
    }

    GameState Game::get_game_state() const {
        return game_state;
    }

    std::string Game::get_field_state(int x, int y) const {
        return field[x][y];
    }

    void Game::change_field(int x_start,
                            int x_finish,
                            int y_start,
                            int y_finish,
                            const std::string &value) {
        for (int i = x_start; i < x_finish; i++) {
            for (int j = y_start; j < y_finish; j++) {
                field[i][j] = value;
            }
        }
    }

    void Game::shoot() {
        int x = ship.get_coordinates().first + ship.get_size() / 2 - shot_size / 2;
        int y = ship.get_coordinates().second - 1;
        Shot new_shot(x, y, new_uuid());
        changes.emplace_back(Changes{Create_shot,
                                     new_shot.get_id(),
                                     {new_shot.get_coordinates().first, new_shot.get_coordinates().second},
                                     new_shot.get_size()});
        change_field(x, x + new_shot.get_size(), y, y + new_shot.get_size(), new_shot.get_id());
        shots_in_the_field.push_back(std::move(new_shot));
    }

    void Game::generate_asteroid() {
        if (random_number(0, 90) == 5 && asteroids_in_the_field.size() < 3) {
            int size = random_number(70, 120);
            int x = random_number(0, kWidth - size);
            while (checker_for_nothing(x, x + size, 0, size) != default_id) {
                x = random_number(0, kWidth - size);
            }
            Asteroid new_asteroid(x, size, new_uuid());
            changes.emplace_back(Changes{Create_asteroid,
                                         new_asteroid.get_id(),
                                         {new_asteroid.get_coordinates().first,
                                          new_asteroid.get_coordinates().second},
                                         new_asteroid.get_size()});
            change_field(x, x + size, 0, size, new_asteroid.get_id());
            asteroids_in_the_field.push_back(std::move(new_asteroid));
        }
    }

    void Game::generate_bonus() {
        if (random_number(0, 400) == 5) {//coin
            int x = random_number(0, kWidth - bonus_size);
            if (checker_for_nothing(x, x + bonus_size, 0, bonus_size) == default_id) {
                Coin new_coin(x, new_uuid());
                changes.emplace_back(Changes{Create_coin, new_coin.get_id(), new_coin.get_coordinates(), bonus_size});
                change_field(x, x + bonus_size, 0, bonus_size, new_coin.get_id());
                coins_in_the_field.push_back(std::move(new_coin));
            }
        }
        if (random_number(0, 500) == 5) {//heart
            int x = random_number(0, kWidth - bonus_size);
            if (checker_for_nothing(x, x + bonus_size, 0, bonus_size) == default_id) {
                Heart new_heart(x, new_uuid());
                changes.emplace_back(Changes{Create_heart, new_heart.get_id(), new_heart.get_coordinates(), bonus_size});
                change_field(x, x + bonus_size, 0, bonus_size, new_heart.get_id());
                hearts_in_the_field.push_back(std::move(new_heart));
            }
        }
    }

    void Game::moving_shots() {
        std::size_t id = 0;
        while (id < shots_in_the_field.size()) {
            int old_x = shots_in_the_field[id].get_coordinates().first;
            int old_y = shots_in_the_field[id].get_coordinates().second;
            change_field(old_x, old_x + shots_in_the_field[id].get_size(), old_y,
                         old_y + shots_in_the_field[id].get_size(), default_id);
            shots_in_the_field[id].move();
            int new_y = shots_in_the_field[id].get_coordinates().second;
            std::string checker1 = checker_for_nothing(old_x, old_x + shots_in_the_field[id].get_size(), new_y,
                                                       new_y + shots_in_the_field[id].get_size());
            std::string checker2 = checker_for_nothing(old_x, old_x + shots_in_the_field[id].get_size(),
                                                       new_y - game_speed, new_y - game_speed + shots_in_the_field[id].get_size());
            //сейчас врежется астероид
            if (checker1 != default_id || checker2 != default_id) {//если сейчас столкнется с астероидом --> удаляем
                changes.emplace_back(
                        Changes{Delete_object,
                                shots_in_the_field[id].get_id()});
                if (checker1 != default_id) {
                    map.insert({checker1, "asteroid"});
                } else {
                    map.insert({checker2, "asteroid"});
                }
                shots_in_the_field.erase(shots_in_the_field.begin() + id);
            } else {
                change_field(old_x, old_x + shots_in_the_field[id].get_size(), new_y,
                             new_y + shots_in_the_field[id].get_size(), shots_in_the_field[id].get_id());
                changes.emplace_back(Changes{Move_object,
                                             shots_in_the_field[id].get_id(),
                                             {old_x, new_y}});
                id++;
            }
        }
    }

    void Game::moving_asteroids() {
        std::size_t id = 0;
        while (id < asteroids_in_the_field.size()) {
            int old_x = asteroids_in_the_field[id].get_coordinates().first;
            int old_y = asteroids_in_the_field[id].get_coordinates().second;
            int size = asteroids_in_the_field[id].get_size();
            change_field(old_x, old_x + size, old_y, old_y + size,
                         default_id);
            asteroids_in_the_field[id].move(game_speed);
            int new_y = asteroids_in_the_field[id].get_coordinates().second;
            std::string checker = checker_for_nothing(old_x, old_x + size, new_y,
                                                      new_y + size);
            if (checker != default_id || map.find(asteroids_in_the_field[id].get_id()) != map.end()) {
                //не можем спокойно подвинуть астероид
                if (map.find(asteroids_in_the_field[id].get_id()) != map.end()) {
                    map.erase(asteroids_in_the_field[id].get_id());
                }
                asteroids_in_the_field[id].destroy();
                if (new_y + size >= kHeight ||
                    asteroids_in_the_field[id].get_state() ==
                            kDead) {//врезались в землю
                    if (new_y + size >= kHeight || checker == "abcd") {
                        check_for_living();
                    }
                    recover_ship();//убрать костыль
                    // если в корабль врезался астероид, восстанавливаем  корабль
                    changes.emplace_back(Changes{Delete_object,
                                                 asteroids_in_the_field[id].get_id()});
                    asteroids_in_the_field.erase(asteroids_in_the_field.begin() + id);
                    continue;
                } else {// еще не убили, но ранили
                    changes.emplace_back(Changes{Break_asteroid, asteroids_in_the_field[id].get_id(), {-1, -1}, asteroids_in_the_field[id].get_size()});
                }
            } else {
                //пусто, можно двигать
                change_field(old_x, old_x + size, new_y, new_y + size, asteroids_in_the_field[id].get_id());
                changes.emplace_back(Changes{Move_object,
                                             asteroids_in_the_field[id].get_id(),
                                             {old_x, new_y}});
                id++;
            }
        }
    }

    void Game::moving_bonus() {
        int id = 0;
        while (id < coins_in_the_field.size()) {
            int old_x = coins_in_the_field[id].get_coordinates().first;
            int old_y = coins_in_the_field[id].get_coordinates().second;
            change_field(old_x, old_x + bonus_size, old_y, old_y + bonus_size, default_id);
            if (map.find(coins_in_the_field[id].get_id()) != map.end()) {//caught it!
                coins++;
                changes.emplace_back(Changes{Add_coin});
                changes.emplace_back(Changes{Delete_object, coins_in_the_field[id].get_id()});
                map.erase(coins_in_the_field[id].get_id());
                coins_in_the_field.erase(coins_in_the_field.begin() + id);
                continue;
            }
            coins_in_the_field[id].move(game_speed);
            int new_y = coins_in_the_field[id].get_coordinates().second;
            if (checker_for_nothing(old_x, old_x + bonus_size, new_y, new_y + bonus_size) != default_id) {
                changes.emplace_back(Changes{Delete_object, coins_in_the_field[id].get_id()});
                coins_in_the_field.erase(coins_in_the_field.begin() + id);
            } else {
                changes.emplace_back(Changes{Move_object, coins_in_the_field[id].get_id(), coins_in_the_field[id].get_coordinates()});
                change_field(old_x, old_x + bonus_size, new_y, new_y + bonus_size, coins_in_the_field[id].get_id());
                id++;
            }
        }
        id = 0;
        while (id < hearts_in_the_field.size()) {
            int old_x = hearts_in_the_field[id].get_coordinates().first;
            int old_y = hearts_in_the_field[id].get_coordinates().second;
            change_field(old_x, old_x + bonus_size, old_y, old_y + bonus_size, default_id);
            if (map.find(hearts_in_the_field[id].get_id()) != map.end()) {//поймали
                lives = std::min(lives + 1, 3);
                //std::cerr << lives << " ";
                changes.emplace_back(Changes{Add_heart});
                changes.emplace_back(Changes{Delete_object, hearts_in_the_field[id].get_id()});
                map.erase(hearts_in_the_field[id].get_id());
                hearts_in_the_field.erase(hearts_in_the_field.begin() + id);
                continue;
            }
            hearts_in_the_field[id].move(game_speed);
            int new_y = hearts_in_the_field[id].get_coordinates().second;
            if (checker_for_nothing(old_x, old_x + bonus_size, new_y, new_y + bonus_size) != default_id) {
                changes.emplace_back(Changes{Delete_object, hearts_in_the_field[id].get_id()});
                hearts_in_the_field.erase(hearts_in_the_field.begin() + id);
            } else {
                changes.emplace_back(Changes{Move_object, hearts_in_the_field[id].get_id(), hearts_in_the_field[id].get_coordinates()});
                change_field(old_x, old_x + bonus_size, new_y, new_y + bonus_size, hearts_in_the_field[id].get_id());
                id++;
            }
        }
    }

    void Game::moving_ship(MoveDirection direction) {
        int y = ship.get_coordinates().second;
        int old_x = ship.get_coordinates().first;
        change_field(old_x, old_x + ship.get_size(), y, y + ship.get_size(),
                     default_id);
        ship.move(direction);
        int new_x = ship.get_coordinates().first;
        change_field(new_x, new_x + ship.get_size(), y, y + ship.get_size(),
                     "abcd");
        changes.emplace_back(
                Changes{Move_object,
                        ship.get_id(),
                        {new_x, y},
                        ship.get_size()});
    }


    void Game::make_move(MoveDirection direction) {
        moving_ship(direction);
        moving_shots();
        moving_asteroids();
        moving_bonus();
        generate_asteroid();
        generate_bonus();
    }

    void Game::clear_field() {
        for (auto &i : asteroids_in_the_field) {
            changes.emplace_back(Changes{Delete_object, i.get_id()});
        }
        for (auto &i : shots_in_the_field) {
            changes.emplace_back(Changes{Delete_object, i.get_id()});
        }
        for (auto &i : hearts_in_the_field) {
            changes.emplace_back(Changes{Delete_object, i.get_id()});
        }
    }

    std::pair<int, int> get_field_size() {
        return {kWidth, kHeight};
    }

}// namespace eclipse
