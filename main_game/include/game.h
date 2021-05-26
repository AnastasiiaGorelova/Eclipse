#ifndef MAIN_GAME_GAME_H
#define MAIN_GAME_GAME_H

#include "asteroids.h"
#include "bonus.h"
#include "changes.h"
#include "game_fwd.h"
#include "monster.h"
#include "shots.h"
#include "space_ship.h"
#include "util.h"
#include <random>
#include <set>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace eclipse {

    struct Game {
    private:
        spaceship ship = spaceship(kWidth, kHeight, new_uuid());
        monster alien = monster(kWidth, new_uuid());
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
        void moving_alien_shots();
        void moving_bonus();
        void moving_asteroids();
        void moving_ship(MoveDirection direction);
        void shoot_by_alien();

        bool check_for_borders(int y, int size) const;
        bool check_for_nothing(int x, int size) const;
        bool check_for_conflict_with_ship(int x, int y, int size) const;
        bool check_for_conflict(int x1, int y1, int size1, int x2, int y2, int size2) const;
        bool destroy_objects_by_shots(int x1, int y1, int size1);

    public:
        int coins = 0;
        int lives = 3;
        //int coins_to_buy_live = 5;
        int coins_to_buy_live = 5;
        GameState game_state = kOngoing;
        Game() {}

        std::vector<Changes> changes = {Changes{Create_ship,
                                                ship.get_id(),
                                                ship.get_coordinates(), ship.get_size()}};

        bool get_game_state() const;

        void make_move(MoveDirection direction = kNoMove);
        void make_move_with_alien(MoveDirection direction = kNoMove);
        void shoot();
        void clear_field();
        std::string get_ship_id() const;
        void attack_by_alien();
        void set_alien();
    };

}// namespace eclipse

#endif// MAIN_GAME_GAME_H