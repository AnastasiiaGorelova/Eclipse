#ifndef MAIN_GAME_SHOTS_H
#define MAIN_GAME_SHOTS_H

#include "game_fwd.h"
#include "space_ship.h"
#include <string>
#include <utility>

namespace eclipse {
    struct Shot {
    private:
        int size = 35;
        int x;
        int y;
        int speed = 3;
        std::string id;

    public:
        Shot(int x, int y, std::string id) : x(x), y(y), id(std::move(id)) {
        }
        [[nodiscard]] int get_size() const;
        [[nodiscard]] std::pair<int, int> get_coordinates() const;
        [[nodiscard]] std::string get_id() const;
        void move();
        void move_for_alien();

        friend bool operator<(const Shot &first, const Shot &second);
    };
}// namespace eclipse

#endif// MAIN_GAME_SHOTS_H
