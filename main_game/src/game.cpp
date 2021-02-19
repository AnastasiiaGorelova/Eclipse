
#include "../include/game.h"
#include "../include/game_fwd.h"
#include <cmath>
#include <vector>

namespace eclipse {
    namespace {
        bool checker_for_nothing(const int &x_start, const int &x_finish,
                                 const int &y_start, const int &y_finish, const Game &g) {
            for (int i = x_start; i < x_finish; i++) {
                for (int j = y_start; j < y_finish; j++) {
                    if (j == HEIGHT) {
                        return false;
                    }
                    if (g.get_field_state(i, j) != NOTHING) {
                        return false;
                    }
                }
            }
            return true;
        }

        template<typename T>
        void swap(std::vector<T> &vec, int first_id, int second_id) {
            T temp = vec[first_id];
            vec[first_id] = vec[second_id];
            vec[second_id] = temp;
        }

    }// namespace

    Game_state Game::get_game_state() const { return game_state; }

    Field_state Game::get_field_state(int x, int y) const { return field[x][y]; }

    int Game::get_time() const { return static_cast<int>(ceil(Game::time)); }

    void Game::change_field(int x_start, int x_finish, int y_start, int y_finish, Field_state value) {
        for (int i = x_start; i < x_finish; i++) {//проверить знак < или <=??
            for (int j = y_start; j < y_finish; j++) {
                field[i][j] = value;
            }
        }
    }

    void Game::shoot() {
        int x = my_ship.where_is_ship().first;
        int y = my_ship.where_is_ship().second + 1;
        Shot my_shot(x, y);
        shots_in_the_field.push_back(my_shot);
        field[x][y] = SHOT;
    }

    void Game::generate_asteroid() {
        int size = rand() % 5 + 1;
        int x = rand() % WIDTH;
        while (!checker_for_nothing(x, x + size, 0, size, *this)) {
            x = rand() % WIDTH;
        }
        Asteroid my_asteroid(x, size);
        asteroids_in_the_field.push_back(my_asteroid);
        change_field(x, x + size, 0, size, ASTEROID);
    }

    void Game::moving_shots() {
        int id = 0;
        while (id < shots_in_the_field.size()) {
            field[shots_in_the_field[id].where_is_shot().first][shots_in_the_field[id].where_is_shot().second] = NOTHING;
            shots_in_the_field[id].move();
            int new_x = shots_in_the_field[id].where_is_shot().first;
            int new_y = shots_in_the_field[id].where_is_shot().second;
            field[new_x][new_y] = SHOT;
            if (field[new_x][new_y + asteroids_speed] == ASTEROID) {//если сейчас столкнется с астероидом --> удаляем
                swap(shots_in_the_field, id, static_cast<int>(shots_in_the_field.size()) - 1);
                shots_in_the_field.pop_back();
            } else {
                id++;
            }
        }
    }

    bool Game::check_for_living() {
        lives--;
        if (lives <= 0) {//dead
            game_state = FINISHED;
            return false;
        }
        return true;
    }

    void Game::moving_asteroids() {
        int id = 0;
        while (id < asteroids_in_the_field.size()) {
            int x = asteroids_in_the_field[id].where_is_asteroid().first;
            int old_y = asteroids_in_the_field[id].where_is_asteroid().second;
            int size = asteroids_in_the_field[id].get_size();
            if (!checker_for_nothing(x, x + size, old_y + size, old_y + size + asteroids_speed, *this)) {
                //не можем спокойно подвинуть астероид
                asteroids_in_the_field[id].killer();
                if (old_y + size + asteroids_speed >= HEIGHT || asteroids_in_the_field[id].get_state() == DEAD) {//врезались в землю
                    id++;
                    if (!check_for_living())
                        break;
                    change_field(x, x + size, old_y, old_y + size, NOTHING);
                    swap(asteroids_in_the_field, id, static_cast<int>(asteroids_in_the_field.size()) - 1);
                    asteroids_in_the_field.pop_back();
                    continue;
                    //?????
                }
            } else {
                //пусто, можно двигать
                change_field(x, x + size, old_y, old_y + asteroids_speed, NOTHING);
                asteroids_in_the_field[id].move(asteroids_speed);
                int new_y = asteroids_in_the_field[id].where_is_asteroid().second;
                change_field(x, x + size, new_y, new_y + size, ASTEROID);
                id++;
            }
        }
    }

    void Game::make_move() {
        //TODO
    }

    void Game::run_game() {
        //TODO
    }

    std::pair<int, int> get_field_size() {
        return std::make_pair(WIDTH, HEIGHT);
    }

}// namespace eclipse