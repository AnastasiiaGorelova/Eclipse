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

    void Game::shoot() {
        //        int x = ship.get_coordinates().first + ship.get_size() / 2 - shot_size / 2;
        //        int y = ship.get_coordinates().second - 1;
        //        Shot new_shot(x, y, new_uuid());
        //        changes.emplace_back(Changes{Create_shot,
        //                                     new_shot.get_id(),
        //                                     {new_shot.get_coordinates().first, new_shot.get_coordinates().second},
        //                                     new_shot.get_size()});
        //        shots_in_the_field.insert(std::move(new_shot));
    }

    bool Game::check_for_nothing(int x, int size) const {
        //        auto it1 = asteroids_in_the_field.lower_bound(Asteroid(x, -1, default_id));
        //        if (it1 != asteroids_in_the_field.end() && it1->get_coordinates().first <= x + size) {  //кто-то есть
        //            return false;
        //        }
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

    void Game::generate_asteroid() {
        if (random_number(0, 70) == 5 && asteroids_in_the_field.size() < 2) {
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

    //    void Game::moving_shots() {
    //        std::size_t id = 0;
    //        while (id < shots_in_the_field.size()) {
    //            int old_x = shots_in_the_field[id].get_coordinates().first;
    //            int old_y = shots_in_the_field[id].get_coordinates().second;
    //            change_field(old_x, old_x + shots_in_the_field[id].get_size(), old_y,
    //                         old_y + shots_in_the_field[id].get_size(), default_id);
    //            shots_in_the_field[id].move();
    //            int new_y = shots_in_the_field[id].get_coordinates().second;
    //            std::string checker1 = checker_for_nothing(old_x, old_x + shots_in_the_field[id].get_size(), new_y,
    //                                                       new_y + shots_in_the_field[id].get_size());
    //            std::string checker2 = checker_for_nothing(old_x, old_x + shots_in_the_field[id].get_size(),
    //                                                       new_y - game_speed, new_y - game_speed + shots_in_the_field[id].get_size());
    //            //сейчас врежется астероид
    //            if (checker1 != default_id || checker2 != default_id) {//если сейчас столкнется с астероидом --> удаляем
    //                changes.emplace_back(
    //                        Changes{Delete_object,
    //                                shots_in_the_field[id].get_id()});
    //                if (checker1 != default_id) {
    //                    map.insert({checker1, "asteroid"});
    //                } else {
    //                    map.insert({checker2, "asteroid"});
    //                }
    //                shots_in_the_field.erase(shots_in_the_field.begin() + id);
    //            } else {
    //                change_field(old_x, old_x + shots_in_the_field[id].get_size(), new_y,
    //                             new_y + shots_in_the_field[id].get_size(), shots_in_the_field[id].get_id());
    //                changes.emplace_back(Changes{Move_object,
    //                                             shots_in_the_field[id].get_id(),
    //                                             {old_x, new_y}});
    //                id++;
    //            }
    //        }
    //    }

    void Game::moving_shots() {
        //        auto it = shots_in_the_field.begin();
        //        while (it != shots_in_the_field.end()) {
        //            int old_x = it->get_coordinates().first;
        //            int old_y = it->get_coordinates().second;
        //            Shot temp_shot = *it;
        //            shots_in_the_field.erase(it);
        //            temp_shot.move();
        //            int new_y = temp_shot.get_coordinates().second;
        ////            std::string checker1 = checker_for_nothing(old_x, old_x + shots_in_the_field[id].get_size(), new_y,
        ////                                                       new_y + shots_in_the_field[id].get_size());
        ////            std::string checker2 = checker_for_nothing(old_x, old_x + shots_in_the_field[id].get_size(),
        ////                                                       new_y - game_speed, new_y - game_speed + shots_in_the_field[id].get_size());
        //
        //            //сейчас врежется астероид
        //            if (checker1 != default_id || checker2 != default_id) {//если сейчас столкнется с астероидом --> удаляем
        //                changes.emplace_back(
        //                        Changes{Delete_object,
        //                                shots_in_the_field[id].get_id()});
        //                if (checker1 != default_id) {
        //                    map.insert({checker1, "asteroid"});
        //                } else {
        //                    map.insert({checker2, "asteroid"});
        //                }
        //                shots_in_the_field.erase(shots_in_the_field.begin() + id);
        //            } else {
        //                change_field(old_x, old_x + shots_in_the_field[id].get_size(), new_y,
        //                             new_y + shots_in_the_field[id].get_size(), shots_in_the_field[id].get_id());
        //                changes.emplace_back(Changes{Move_object,
        //                                             shots_in_the_field[id].get_id(),
        //                                             {old_x, new_y}});
        //                id++;
        //            }
        //        }
    }

    void Game::moving_asteroids() {
        //std::cerr << "a " <<'\n';
        auto it = asteroids_in_the_field.begin();
        std::set<Asteroid> after_changes;
        while (it != asteroids_in_the_field.end()) {
            Asteroid cur_asteroid = *it;
            cur_asteroid.move(game_speed);
            if (!check_for_conflict_with_ship(cur_asteroid.get_coordinates().first, cur_asteroid.get_coordinates().second, cur_asteroid.get_size())) {
                cur_asteroid.destroy();
            }
            if (!check_for_borders(cur_asteroid.get_coordinates().second, cur_asteroid.get_size()) || cur_asteroid.get_state() == kDead) {//врезались в границу
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
        //std::cerr << "b " <<'\n';
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
                    lives = std::min(lives + 1, 3);
                    changes.emplace_back(Changes{Add_heart});
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
        int y = ship.get_coordinates().second;
        int old_x = ship.get_coordinates().first;
        ship.move(direction);
        int new_x = ship.get_coordinates().first;
        changes.emplace_back(
                Changes{Move_object,
                        ship.get_id(),
                        {new_x, y},
                        ship.get_size()});
    }


    void Game::make_move(MoveDirection direction) {
        moving_ship(direction);
        moving_bonus();
        moving_asteroids();
        //moving_shots();
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
        //        map.clear();
        //        field.clear();
        //        field.resize(kWidth, std::vector<std::string>(kHeight, default_id));
        //        for (int i = ship.get_coordinates().first;
        //             i < ship.get_coordinates().first + ship.get_size(); i++) {
        //            for (int j = ship.get_coordinates().second; j < kHeight; j++) {
        //                field[i][j] = "abcd";
        //            }
        //        }
    }

    std::pair<int, int> get_field_size() {
        return {kWidth, kHeight};
    }

}// namespace eclipse
