#ifndef MAIN_GAME_SHOTS_H
#define MAIN_GAME_SHOTS_H

#include <string>
#include <utility>
#include "game_fwd.h"
#include "space_ship.h"

namespace eclipse {
struct Shot {
private:
    int size = 20;
    int x;
    int y;
    int speed = 50;
    std::string id;

public:
    Shot(int x, int y, std::string id) : x(x), y(y), id(std::move(id)) {
    }
    int get_size() const;
    std::pair<int, int> get_coordinates() const;
    std::string get_id() const;
    void move();
};
}  // namespace eclipse

#endif  // MAIN_GAME_SHOTS_H
