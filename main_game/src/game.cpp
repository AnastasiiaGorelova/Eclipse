#include "game.h"
#include "game_fwd.h"
#include "util.h"
#include <vector>

#include "God.h"
extern ::God damn;


namespace eclipse {
    namespace {
        bool checker_for_nothing(int x_start,
                                 int x_finish,
                                 int y_start,
                                 int y_finish,
                                 const Game &g) {
            for (int i = x_start; i < x_finish; i++) {
                for (int j = y_start; j < y_finish; j++) {
                    if (j >= kHeight || j < 0) {
                        return false;
                    }
                    if (g.get_field_state(i, j) != kNothing) {
                        return false;
                    }
                }
            }
            return true;
        }

        int random_number(int l, int r) {
            std::mt19937 gen{std::random_device{}()};
            std::uniform_int_distribution<> dist(l, r);
            return dist(gen);
        }

    }// namespace

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

    FieldState Game::get_field_state(int x, int y) const {
        return field[x][y];
    }

    void Game::change_field(int x_start,
                            int x_finish,
                            int y_start,
                            int y_finish,
                            FieldState value) {
        for (int i = x_start; i < x_finish; i++) {
            for (int j = y_start; j < y_finish; j++) {
                field[i][j] = value;
            }
        }
    }

    void Game::shoot() {
        int x = ship.get_coordinates().first + ship.get_size() / 2;
        int y = ship.get_coordinates().second - 1;
        Shot new_shot(x, y, new_uuid());
        changes.emplace_back(Changes{Create_shot,
                                     new_shot.get_id(),
                                     {new_shot.get_coordinates().first, new_shot.get_coordinates().second},
                                     new_shot.get_size()});
        change_field(x, x + new_shot.get_size(), y, y + new_shot.get_size(), kShot);
        shots_in_the_field.push_back(std::move(new_shot));
    }

    void Game::generate_asteroid() {
        if (random_number(0, 90) == 5) {
            //if (true) {
            int size = random_number(70, 120);
            int x = random_number(0, kWidth - size);
            while (!checker_for_nothing(x, x + size, 0, size, *this)) {
                x = random_number(0, kWidth - size);
            }
            Asteroid new_asteroid(x, size, new_uuid());
            changes.emplace_back(Changes{Create_asteroid,
                                         new_asteroid.get_id(),
                                         {new_asteroid.get_coordinates().first,
                                          new_asteroid.get_coordinates().second},
                                         new_asteroid.get_size()});
            asteroids_in_the_field.push_back(std::move(new_asteroid));
            change_field(x, x + size, 0, size, kAsteroid);
        }
    }

    void Game::moving_shots() {
        std::size_t id = 0;
        while (id < shots_in_the_field.size()) {
            int old_x = shots_in_the_field[id].get_coordinates().first;
            int old_y = shots_in_the_field[id].get_coordinates().second;
            change_field(old_x, old_x + shots_in_the_field[id].get_size(), old_y,
                         old_y + shots_in_the_field[id].get_size(), kNothing);
            shots_in_the_field[id].move();
            int new_y = shots_in_the_field[id].get_coordinates().second;
            if (!checker_for_nothing(old_x, old_x + shots_in_the_field[id].get_size(), new_y,
                                     new_y + shots_in_the_field[id].get_size(), *this) ||
                shots_in_the_field[id].get_coordinates().second <=
                        0) {//если сейчас столкнется с астероидом --> удаляем
                changes.emplace_back(
                        Changes{Delete_object,
                                shots_in_the_field[id].get_id()});
                shots_in_the_field.erase(shots_in_the_field.begin() + id);
            } else {
                change_field(old_x, old_x + shots_in_the_field[id].get_size(), new_y,
                             new_y + shots_in_the_field[id].get_size(), kShot);
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
                         kNothing);
            asteroids_in_the_field[id].move(asteroids_speed);
            int new_y = asteroids_in_the_field[id].get_coordinates().second;
            if (!checker_for_nothing(old_x, old_x + size, new_y,
                                     new_y + size, *this)) {
                //не можем спокойно подвинуть астероид
                asteroids_in_the_field[id].destroy();
                if (new_y + size >= kHeight ||
                    asteroids_in_the_field[id].get_state() ==
                            kDead) {//врезались в землю
                    if (new_y + size >= kHeight) {
                        check_for_living();
                    }
                    change_field(ship.get_coordinates().first,
                                 ship.get_coordinates().first + ship.get_size(),
                                 ship.get_coordinates().second,
                                 ship.get_coordinates().second + ship.get_size(),
                                 kSpaceShip);
                    // если в корабль врезался астероид, восстанавливаем  корабль
                    changes.emplace_back(Changes{Delete_object,
                                                 asteroids_in_the_field[id].get_id()});
                    asteroids_in_the_field.erase(asteroids_in_the_field.begin() + id);
                    continue;
                }
            } else {
                //пусто, можно двигать
                change_field(old_x, old_x + size, new_y, new_y + size, kAsteroid);
                changes.emplace_back(Changes{Move_object,
                                             asteroids_in_the_field[id].get_id(),
                                             {old_x, new_y},
                                             size});
                id++;
            }
        }
    }

    void Game::moving_ship(MoveDirection direction) {
        int y = ship.get_coordinates().second;
        int old_x = ship.get_coordinates().first;
        change_field(old_x, old_x + ship.get_size(), y, y + ship.get_size(),
                     kNothing);
        ship.move(direction);
        int new_x = ship.get_coordinates().first;
        change_field(new_x, new_x + ship.get_size(), y, y + ship.get_size(),
                     kSpaceShip);
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
        //shoot();
        generate_asteroid();
    }

    std::pair<int, int> get_field_size() {
        return {kWidth, kHeight};
    }

}// namespace eclipse
