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

    bool Game::check_for_borders(int y, int size) const {
        if (y < 0 || y + size >= kHeight) {
            return false;
        }
        return true;
    }

    bool Game::check_for_conflict_with_ship(int x, int y, int size) const {
        if (y + size < ship.get_coordinates().second) {//не пересекаются по y
            return true;
        }
        if (x + size < ship.get_coordinates().first || ship.get_coordinates().first + ship.get_size() < x) {
            return true;
        }
        return false;//столкнулись
    }

    void Game::check_for_living() {
        --lives;
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

    void Game::shoot() {
        int x = ship.get_coordinates().first + ship.get_size() / 2 - shot_size / 2;
        int y = ship.get_coordinates().second - 1;
        Shot new_shot(x, y, new_uuid());
        changes.emplace_back(Changes{Create_shot,
                                     new_shot.get_id(),
                                     {new_shot.get_coordinates().first, new_shot.get_coordinates().second},
                                     new_shot.get_size()});
        shots_in_the_field.insert(std::move(new_shot));
    }

    bool Game::check_for_nothing(int x, int size) const {
        for (auto it1 = asteroids_in_the_field.begin(); it1 != asteroids_in_the_field.end(); it1++) {
            if ((it1->get_coordinates().first >= x && it1->get_coordinates().first <= x + size) ||
                (x >= it1->get_coordinates().first && x <= it1->get_coordinates().first + it1->get_size())) {
                return false;//пересекаются
            }
        }
        for (auto it1 = bonus_in_the_field.begin(); it1 != bonus_in_the_field.end(); it1++) {
            if ((it1->get_coordinates().first >= x && it1->get_coordinates().first <= x + size) ||
                (x >= it1->get_coordinates().first && x <= it1->get_coordinates().first + bonus_size)) {
                return false;//пересекаются
            }
        }
        for (auto it1 = shots_in_the_field.begin(); it1 != shots_in_the_field.end(); it1++) {
            if ((it1->get_coordinates().first >= x && it1->get_coordinates().first <= x + size) ||
                (x >= it1->get_coordinates().first && x <= it1->get_coordinates().first + it1->get_size())) {
                return false;//пересекаются
            }
        }
        return true;
    }

    bool Game::check_for_conflict(int x1, int y1, int size1, int x2, int y2, int size2) const {
        if ((x1 > x2 + size2 || x2 > x1 + size1) || (y1 > y2 + size2 || y2 > y1 + size1)) {
            return true;
        }
        return false;//пересекаются
    }

    bool Game::destroy_objects_by_shots(int x1, int y1, int size1) {
        auto it1 = asteroids_in_the_field.begin();
        while (it1 != asteroids_in_the_field.end()) {
            if (!check_for_conflict(x1, y1, size1, it1->get_coordinates().first, it1->get_coordinates().second, it1->get_size())) {//ударил астероид
                Asteroid temp_asteroid = *it1;
                asteroids_in_the_field.erase(it1);
                temp_asteroid.destroy();
                if (temp_asteroid.get_state() == kDead) {
                    changes.emplace_back(Changes{Delete_object, temp_asteroid.get_id()});
                } else {
                    changes.emplace_back(Changes{Break_asteroid, temp_asteroid.get_id(), temp_asteroid.get_coordinates(), temp_asteroid.get_size()});
                    asteroids_in_the_field.insert(temp_asteroid);
                }
                return false;
            }
            it1++;
        }
        auto it2 = bonus_in_the_field.begin();
        while (it2 != bonus_in_the_field.end()) {
            if (!check_for_conflict(x1, y1, size1, it2->get_coordinates().first, it2->get_coordinates().second, bonus_size)) {//ударил астероид
                changes.emplace_back(Changes{Delete_object, it2->get_id()});
                if (it2->get_type() == "coin") {
                    coins++;
                    changes.emplace_back(Changes{Add_coin});
                } else {
                    lives = std::min(lives + 1, 3);
                    changes.emplace_back(Changes{Add_heart});
                }
                bonus_in_the_field.erase(it2);
                return false;
            }
            it2++;
        }
        return true;
    }

    void Game::generate_asteroid() {
        if (random_number(0, 70) == 5 && asteroids_in_the_field.size() < 3) {
            int size = random_number(70, 120);
            int x = random_number(0, kWidth - size);
            while (!check_for_nothing(x, size)) {//проверка на то что пусто
                x = random_number(0, kWidth - size);
            }
            Asteroid new_asteroid(x, size, new_uuid());
            changes.emplace_back(Changes{Create_asteroid,
                                         new_asteroid.get_id(),
                                         {new_asteroid.get_coordinates().first,
                                          new_asteroid.get_coordinates().second},
                                         new_asteroid.get_size()});
            asteroids_in_the_field.insert(std::move(new_asteroid));
        }
    }

    void Game::generate_bonus() {
        if (random_number(0, 200) == 5) {
            int x = random_number(0, kWidth - bonus_size);
            if (check_for_nothing(x, bonus_size)) {
                if (random_number(0, 1) == 1) {
                    Bonus new_coin(x, new_uuid(), "coin");
                    changes.emplace_back(Changes{Create_coin, new_coin.get_id(), new_coin.get_coordinates(), bonus_size});
                    bonus_in_the_field.insert(std::move(new_coin));
                } else {
                    Bonus new_heart(x, new_uuid(), "heart");
                    changes.emplace_back(Changes{Create_heart, new_heart.get_id(), new_heart.get_coordinates(), bonus_size});
                    bonus_in_the_field.insert(std::move(new_heart));
                }
            }
        }
    }

    void Game::moving_shots() {
        auto it = shots_in_the_field.begin();
        std::set<Shot> after_changes;
        while (it != shots_in_the_field.end()) {
            if (!destroy_objects_by_shots(it->get_coordinates().first, it->get_coordinates().second, it->get_size())) {//столкнулись
                changes.emplace_back(Changes{Delete_object, it->get_id()});
            } else {
                Shot temp_shot = *it;
                temp_shot.move();
                if (!check_for_borders(temp_shot.get_coordinates().second, temp_shot.get_size()) ||
                    !destroy_objects_by_shots(temp_shot.get_coordinates().first, temp_shot.get_coordinates().second, temp_shot.get_size())) {//столкнулись
                    changes.emplace_back(Changes{Delete_object, temp_shot.get_id()});
                } else {
                    after_changes.insert(temp_shot);
                    changes.emplace_back(Changes{Move_object, temp_shot.get_id(), temp_shot.get_coordinates()});
                }
            }
            it++;
        }
        shots_in_the_field = after_changes;
    }

    void Game::moving_asteroids() {
        auto it = asteroids_in_the_field.begin();
        std::set<Asteroid> after_changes;
        while (it != asteroids_in_the_field.end()) {
            Asteroid cur_asteroid = *it;
            cur_asteroid.move(game_speed);
            if (!check_for_borders(cur_asteroid.get_coordinates().second, cur_asteroid.get_size()) ||
                !check_for_conflict_with_ship(cur_asteroid.get_coordinates().first, cur_asteroid.get_coordinates().second, cur_asteroid.get_size())) {//врезались в границу
                changes.emplace_back(Changes{Delete_object,
                                             cur_asteroid.get_id()});
                check_for_living();
            } else {//можем двигать
                changes.emplace_back(Changes{Move_object,
                                             cur_asteroid.get_id(),
                                             cur_asteroid.get_coordinates()});
                after_changes.insert(cur_asteroid);
            }
            it++;
        }
        asteroids_in_the_field = after_changes;
    }

    void Game::moving_bonus() {
        auto it = bonus_in_the_field.begin();
        std::set<Bonus> after_changes;
        while (it != bonus_in_the_field.end()) {
            Bonus temp_bonus = *it;
            temp_bonus.move(game_speed);
            if (!check_for_borders(temp_bonus.get_coordinates().second, bonus_size)) {
                changes.emplace_back(Changes{Delete_object, temp_bonus.get_id()});
                it++;
                continue;
            }
            if (!check_for_conflict_with_ship(temp_bonus.get_coordinates().first, temp_bonus.get_coordinates().second, bonus_size)) {
                if (temp_bonus.get_type() == "coin") {
                    coins++;
                    changes.emplace_back(Changes{Add_coin});
                } else {
                    if (lives != 3) {
                        lives = std::min(lives + 1, 3);
                        changes.emplace_back(Changes{Add_heart});
                    }
                }
                changes.emplace_back(Changes{Delete_object, temp_bonus.get_id()});
                it++;
                continue;
            }
            changes.emplace_back(Changes{Move_object, temp_bonus.get_id(), temp_bonus.get_coordinates()});
            after_changes.insert(temp_bonus);
            it++;
        }
        bonus_in_the_field = after_changes;
    }

    void Game::moving_ship(MoveDirection direction) {
        ship.move(direction);
        changes.emplace_back(
                Changes{Move_object,
                        ship.get_id(),
                        ship.get_coordinates(),
                        ship.get_size()});
    }

    void Game::make_move(MoveDirection direction) {
        moving_ship(direction);
        moving_asteroids();
        moving_bonus();
        moving_shots();
        generate_asteroid();
        generate_bonus();
    }

    void Game::clear_field() {
        for (auto &i : asteroids_in_the_field) {
            changes.emplace_back(Changes{Delete_object, i.get_id()});
        }
        asteroids_in_the_field.clear();
        for (auto &i : shots_in_the_field) {
            changes.emplace_back(Changes{Delete_object, i.get_id()});
        }
        shots_in_the_field.clear();
        for (auto &i : bonus_in_the_field) {
            changes.emplace_back(Changes{Delete_object, i.get_id()});
        }
        bonus_in_the_field.clear();
    }

    std::pair<int, int> get_field_size() {
        return {kWidth, kHeight};
    }

}// namespace eclipse
