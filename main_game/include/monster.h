#ifndef MAIN_GAME_MONSTER_H
#define MAIN_GAME_MONSTER_H

#include "game_fwd.h"
#include "shots.h"
#include "util.h"
#include <set>
#include <string>

namespace eclipse {

    struct alien_heart {
        int x;
        int y;
        int size;
        std::string id;
    };

    struct monster {
    private:
        const int size = 130;
        int x;
        int y = 0;
        std::string id;
        int speed = 3;
        MonsterState state = Not_on_the_field;
        int lives = 5;
        int steps_to_one_side = 0;
        MoveDirection direction = kRight;
        void set_hearts();

    public:
        monster(int width, std::string id) : x(width / 2 - size / 2), id(std::move(id)) {
        }
        std::set<Shot> alien_shots_in_the_field;
        std::vector<alien_heart> heart_coordinates;
        std::pair<int, int> get_coordinates() const;
        std::string get_id() const;
        int get_size() const;
        void move(MoveDirection direction);
        MonsterState get_state() const;
        void change_state(MonsterState new_state);
        void decrease_lives();
    };
}// namespace eclipse


#endif//MAIN_GAME_MONSTER_H
