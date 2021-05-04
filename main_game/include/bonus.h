#ifndef MAIN_GAME_BONUS_H
#define MAIN_GAME_BONUS_H

#include <string>

namespace eclipse {
    struct Coin {
    private:
        int x;
        int y = 0;
        std::string id;

    public:
        Coin(int x, std::string id) : x(x), id(std::move(id)) {}

        void move(int speed);
        std::pair<int, int> get_coordinates() const;  // x,y coordinates
        std::string get_id() const;
    };

    struct Heart {
    private:
        int x;
        int y = 0;
        std::string id;

    public:
        Heart(int x, std::string id) : x(x), id(std::move(id)) {}

        void move(int speed);
        std::pair<int, int> get_coordinates() const;  // x,y coordinates
        std::string get_id() const;
    };
}// namespace eclipse

#endif//MAIN_GAME_BONUS_H
