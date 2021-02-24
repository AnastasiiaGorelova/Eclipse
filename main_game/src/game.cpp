
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

        int random_number(int l, int r) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dist(l, r);
            return dist(gen);
        }

    }// namespace

    std::string Game::new_uuid() {
        static auto &chrs = "0123456789"
                            "abcdefghijklmnopqrstuvwxyz"
                            "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        thread_local static std::mt19937 gen{std::random_device{}()};
        thread_local static std::uniform_int_distribution<std::string::size_type> dis(0, sizeof(chrs) - 2);//-1???
        std::string str;
        int length = 10;
        str.reserve(length);
        while (length--)
            str += chrs[dis(gen)];

        return str;
    }

    void Game::check_for_living() {
        --lives;
        if (lives <= 0) {//dead
            game_state = FINISHED;
        }
    }

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
        int x = my_ship.x + my_ship.size / 2;
        int y = my_ship.y - 1;
        Shot my_shot(x, y, new_uuid());
        shots_in_the_field.push_back(my_shot);
        field[x][y] = SHOT;
    }

    void Game::generate_asteroid() {
        int size = random_number(2, 3);
        int x = random_number(0, WIDTH - size);
        while (!checker_for_nothing(x, x + size, 0, size, *this)) {
            x = random_number(0, WIDTH - size);
        }
        Asteroid my_asteroid(x, size, new_uuid());
        asteroids_in_the_field.push_back(my_asteroid);
        change_field(x, x + size, 0, size, ASTEROID);
    }

    void Game::moving_shots() {
        int id = 0;
        while (id < shots_in_the_field.size()) {
            field[shots_in_the_field[id].x][shots_in_the_field[id].y] = NOTHING;
            if (shots_in_the_field[id].y != 0) {
                shots_in_the_field[id].move();
            }
            int new_y = shots_in_the_field[id].y;
            if (field[shots_in_the_field[id].x][new_y] == ASTEROID ||
                field[shots_in_the_field[id].x][new_y - asteroids_speed] == ASTEROID ||
                shots_in_the_field[id].y == 0) {//если сейчас столкнется с астероидом --> удаляем
                swap(shots_in_the_field, id, static_cast<int>(shots_in_the_field.size()) - 1);
                shots_in_the_field.pop_back();
                continue;
            }
            field[shots_in_the_field[id].x][new_y] = SHOT;
            id++;
        }
    }

    void Game::moving_asteroids() {
        int id = 0;
        while (id < asteroids_in_the_field.size()) {
            int x = asteroids_in_the_field[id].x;
            int old_y = asteroids_in_the_field[id].y;
            int size = asteroids_in_the_field[id].size;
            if (!checker_for_nothing(x, x + size, old_y + size, old_y + size + asteroids_speed, *this)) {
                //не можем спокойно подвинуть астероид
                asteroids_in_the_field[id].killer();
                if (old_y + size + asteroids_speed >= HEIGHT || asteroids_in_the_field[id].get_state() == DEAD) {//врезались в землю
                    change_field(x, x + size, old_y, old_y + size, NOTHING);
                    change_field(my_ship.x, my_ship.x + my_ship.size, my_ship.y, my_ship.y + my_ship.size, SPACE_SHIP);
                    // если в корабль врезался астероид, восстанавливаем  корабль
                    swap(asteroids_in_the_field, id, static_cast<int>(asteroids_in_the_field.size()) - 1);
                    asteroids_in_the_field.pop_back();
                    check_for_living();
                    continue;
                }
            } else {
                //пусто, можно двигать
                change_field(x, x + size, old_y, old_y + asteroids_speed, NOTHING);
                asteroids_in_the_field[id].move(asteroids_speed);
                int new_y = asteroids_in_the_field[id].y;
                change_field(x, x + size, new_y, new_y + size, ASTEROID);
                id++;
            }
        }
    }

    void Game::moving_ship(Go direction) {
        int y = my_ship.y;
        int old_x = my_ship.x;
        change_field(old_x, old_x + my_ship.size, y, y + my_ship.size, NOTHING);
        my_ship.move(direction);
        int new_x = my_ship.x;
        change_field(new_x, new_x + my_ship.size, y, y + my_ship.size, SPACE_SHIP);
    }

    void Game::make_move(Go direction) {//лазеры летят по времени?
        moving_ship(direction);
        moving_shots();
        moving_asteroids();
        shoot();
        generate_asteroid();
    }

    std::pair<int, int> get_field_size() {
        return std::make_pair(WIDTH, HEIGHT);
    }

}// namespace eclipse