
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

//TODO: подключить таймер, функции запуска игры, почистить и потестить код, сделать список Shot??

namespace eclipse {
    struct Game {
    private:
        GameState game_state = kOngoing;
        std::vector<std::vector<FieldState>> field;
        int lives = 3;
        int asteroids_speed = 2;
        SpaceShip ship;
        std::vector<Asteroid> asteroids_in_the_field;
        std::vector<Shot> shots_in_the_field;

        void change_field(int x_start, int x_finish, int y_start, int y_finish, FieldState value);
        void check_for_living();
        void shoot();
        void generate_asteroid();
        void moving_shots();
        void moving_asteroids();
        void moving_ship(MoveDirection direction);


    public:
        Game() {
            field.resize(kWidth, std::vector<FieldState>(kHeight, kNothing));
            for (int i = ship.find_ship().first; i < ship.find_ship().first + ship.get_size(); i++) {
                for (int j = ship.find_ship().second; j < kHeight; j++) {
                    field[i][j] = kSpaceShip;
                }
            }
        }

        GameState get_game_state() const;

        FieldState get_field_state(int x, int y) const;

        void make_move(MoveDirection direction = kNoMove);//TODO: add the interaction with the keyboard
    };

}// namespace eclipse

#endif//MAIN_GAME_GAME_H
