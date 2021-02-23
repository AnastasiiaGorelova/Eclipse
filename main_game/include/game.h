
#ifndef MAIN_GAME_GAME_H
#define MAIN_GAME_GAME_H
#include "asteroids.h"
#include "game_fwd.h"
#include "shots.h"
#include "space_ship.h"
#include <ctime>
#include <random>
#include <string>
#include <vector>

//TODO: подключить таймер, функции запуска игры, почистить и потестить код, убрать rand()

namespace eclipse {
    struct Game {
    private:
        double time = std::clock();
        Game_state game_state = ONGOING;
        std::vector<std::vector<Field_state>> field;
        int lives = 3;
        int asteroids_speed = 2;
        Space_ship my_ship;
        std::vector<Asteroid> asteroids_in_the_field;
        std::vector<Shot> shots_in_the_field;

        static std::string new_uuid();
        void change_field(int x_start, int x_finish, int y_start, int y_finish, Field_state value);
        bool check_for_living();
        void shoot();
        void generate_asteroid();
        void moving_shots();
        void moving_asteroids();
        void moving_ship(Go direction);

        friend class Space_ship;


    public:
        Game() {
            field.resize(WIDTH, std::vector<Field_state>(HEIGHT, NOTHING));
            for (int i = my_ship.where_is_ship().first; i < my_ship.where_is_ship().first + my_ship.get_size(); i++) {
                for (int j = my_ship.where_is_ship().second; j < HEIGHT; j++) {
                    field[i][j] = SPACE_SHIP;
                }
            }
            time = static_cast<double>(clock()) / static_cast<double>(CLOCKS_PER_SEC);
        }

        Game_state get_game_state() const;

        Field_state get_field_state(int x, int y) const;

        int get_time() const;

        void make_move(Go direction = NO_MOVE);       //TODO: add the interaction with the keyboard

    };

}// namespace eclipse

#endif//MAIN_GAME_GAME_H
