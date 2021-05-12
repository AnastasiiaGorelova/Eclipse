#ifndef MAIN_GAME_GAME_H
#define MAIN_GAME_GAME_H

#include "asteroids.h"
#include "bonus.h"
#include "changes.h"
#include "game_fwd.h"
#include "shots.h"
#include "space_ship.h"
#include <random>
#include <set>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace eclipse {

    struct Game {
    private:
        GameState game_state = kOngoing;
        //        std::vector<std::vector<std::string>> field;
        //        std::unordered_map<std::string, std::string> map;//for asteroids to delete
        spaceship ship = spaceship(kWidth, kHeight);
        int game_speed = 1;//asteroids
        int shot_size = 40;
        int bonus_size = 60;
        std::set<Asteroid> asteroids_in_the_field;
        std::set<Bonus> bonus_in_the_field;
        std::set<Shot> shots_in_the_field;

        void check_for_living();
        void generate_asteroid();
        void generate_bonus();
        void moving_shots();
        void moving_bonus();
        void moving_asteroids();
        void moving_ship(MoveDirection direction);

        bool check_for_borders(int y, int size) const;
        bool check_for_nothing(int x, int size) const;
        bool check_for_conflict_with_ship(int x, int y, int size) const;
        bool check_for_conflict(int x1, int y1, int size1, int x2, int y2, int size2) const;
        bool destroy_objects_by_shots(int x1, int y1, int size1);

    public:
        int coins = 0;
        int lives = 3;
        int coins_to_buy_live = 5;
        Game() {
            //            field.resize(kWidth, std::vector<std::string>(kHeight, default_id));
            //            for (int i = ship.get_coordinates().first;
            //                 i < ship.get_coordinates().first + ship.get_size(); i++) {
            //                for (int j = ship.get_coordinates().second; j < kHeight; j++) {
            //                    field[i][j] = "abcd";
            //                }
            //            }
        }

        std::vector<Changes> changes = {Changes{Create_ship,
                                                ship.get_id(),
                                                ship.get_coordinates(), ship.get_size()}};

        GameState get_game_state() const;

        std::string get_field_state(int x, int y) const;

        void make_move(MoveDirection direction = kNoMove);
        void shoot();
        void clear_field();
    };

}// namespace eclipse

#endif// MAIN_GAME_GAME_H
