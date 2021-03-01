#include "include/game.h"
#include "include/game_fwd.h"
#include "include/util.h"
#include <vector>

namespace eclipse {
    namespace {
        bool checker_for_nothing(int x_start, int x_finish,
                                 int y_start, int y_finish, const Game &g) {
            for (int i = x_start; i < x_finish; i++) {
                for (int j = y_start; j < y_finish; j++) {
                    if (j == kHeight) {
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
        if (lives <= 0) {//dead
            game_state = kFinished;
        }
    }

    GameState Game::get_game_state() const { return game_state; }

    FieldState Game::get_field_state(int x, int y) const { return field[x][y]; }

    void Game::change_field(int x_start, int x_finish, int y_start, int y_finish, FieldState value) {
        for (int i = x_start; i < x_finish; i++) {//проверить знак < или <=??
            for (int j = y_start; j < y_finish; j++) {
                field[i][j] = value;
            }
        }
    }

    void Game::shoot() {
        int x = ship.get_coordinates().first + ship.get_size() / 2;
        int y = ship.get_coordinates().second - 1;
        shots_in_the_field.emplace_back(Shot(x, y, new_uuid()));
        field[x][y] = kShot;
    }

    void Game::generate_asteroid() {
        int size = random_number(2, 3);
        int x = random_number(0, kWidth - size);
        while (!checker_for_nothing(x, x + size, 0, size, *this)) {
            x = random_number(0, kWidth - size);
        }
        asteroids_in_the_field.emplace_back(Asteroid(x, size, new_uuid()));
        change_field(x, x + size, 0, size, kAsteroid);
    }

    void Game::moving_shots() {
        std::size_t id = 0;
        while (id < shots_in_the_field.size()) {
            field[shots_in_the_field[id].get_coordinates().first][shots_in_the_field[id].get_coordinates().second] = kNothing;
            if (shots_in_the_field[id].get_coordinates().second != 0) {
                shots_in_the_field[id].move();
            }
            int new_y = shots_in_the_field[id].get_coordinates().second;
            if (field[shots_in_the_field[id].get_coordinates().first][new_y] == kAsteroid ||
                //field[shots_in_the_field[id].x][new_y - asteroids_speed] == ASTEROID ||          //утечка памяти??
                shots_in_the_field[id].get_coordinates().second == 0) {//если сейчас столкнется с астероидом --> удаляем
                std::swap(shots_in_the_field[id], shots_in_the_field[shots_in_the_field.size() - 1]);
                shots_in_the_field.pop_back();
            } else {
                field[shots_in_the_field[id].get_coordinates().first][new_y] = kShot;
                id++;
            }
        }
    }

    void Game::moving_asteroids() {
        std::size_t id = 0;
        while (id < asteroids_in_the_field.size()) {
            int x = asteroids_in_the_field[id].get_coordinates().first;
            int old_y = asteroids_in_the_field[id].get_coordinates().second;
            int size = asteroids_in_the_field[id].get_size();
            if (!checker_for_nothing(x, x + size, old_y + size, old_y + size + asteroids_speed, *this)) {
                //не можем спокойно подвинуть астероид
                asteroids_in_the_field[id].destroy();
                if (old_y + size + asteroids_speed >= kHeight || asteroids_in_the_field[id].get_state() == kDead) {//врезались в землю
                    change_field(x, x + size, old_y, old_y + size, kNothing);
                    change_field(ship.get_coordinates().first, ship.get_coordinates().first + ship.get_size(), ship.get_coordinates().second,
                                 ship.get_coordinates().second + ship.get_size(), kSpaceShip);
                    // если в корабль врезался астероид, восстанавливаем  корабль
                    std::swap(asteroids_in_the_field[id], asteroids_in_the_field[asteroids_in_the_field.size() - 1]);
                    asteroids_in_the_field.pop_back();
                    check_for_living();
                    continue;
                }
            } else {
                //пусто, можно двигать
                change_field(x, x + size, old_y, old_y + asteroids_speed, kNothing);
                asteroids_in_the_field[id].move(asteroids_speed);
                int new_y = asteroids_in_the_field[id].get_coordinates().second;
                change_field(x, x + size, new_y, new_y + size, kAsteroid);
                id++;
            }
        }
    }

    void Game::moving_ship(MoveDirection direction) {
        int y = ship.get_coordinates().second;
        int old_x = ship.get_coordinates().first;
        change_field(old_x, old_x + ship.get_size(), y, y + ship.get_size(), kNothing);
        ship.move(direction);
        int new_x = ship.get_coordinates().first;
        change_field(new_x, new_x + ship.get_size(), y, y + ship.get_size(), kSpaceShip);
    }

    void Game::make_move(MoveDirection direction) {//лазеры летят по времени?
        moving_ship(direction);
        moving_shots();
        moving_asteroids();
        shoot();
        generate_asteroid();
    }

    std::pair<int, int> get_field_size() {
        return {kWidth, kHeight};
    }

}// namespace eclipse