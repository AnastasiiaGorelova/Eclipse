#ifndef MAIN_GAME_BONUS_H
#define MAIN_GAME_BONUS_H

#include <string>

namespace eclipse {
    struct Bonus {
    private:
        int x;
        int y = 0;
        std::string id;
        std::string type;

    public:
        Bonus(int x, std::string id, std::string type) : x(x), id(std::move(id)), type(std::move(type)) {}

        void move(int speed);
        std::pair<int, int> get_coordinates() const;// x,y coordinates
        std::string get_id() const;
        std::string get_type() const;
    };
}// namespace eclipse

#endif//MAIN_GAME_BONUS_H
