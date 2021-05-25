#ifndef MAIN_GAME_SHOTS_H
#define MAIN_GAME_SHOTS_H

#include "game_fwd.h"
#include "space_ship.h"
#include <string>
#include <utility>

namespace eclipse {
    struct Shot {
    private:
        int size = 40;//fixed
        int x;
        int y;
        //int speed = 2;//влияет на расстояние между выстрелами
        int speed = 3;//влияет на расстояние между выстрелами
        std::string id;

    public:
        Shot(int x, int y, std::string id) : x(x), y(y), id(std::move(id)) {
        }
        int get_size() const;
        std::pair<int, int> get_coordinates() const;
        std::string get_id() const;
        void move();

        friend bool operator<(const Shot& first, const Shot& second);
    };
}// namespace eclipse

#endif// MAIN_GAME_SHOTS_H
