
#ifndef MAIN_GAME_GAME_H
#define MAIN_GAME_GAME_H

#include "asteroids.h"
#include "game_fwd.h"
#include "shots.h"
#include "space_ship.h"
#include <ctime>
#include <vector>
#include <QGraphicsView>
#include <QGraphicsScene>

namespace eclipse {
    struct Game : public QGraphicsView {
        //for qt
        void makeGame(int const width, int const height);
        QGraphicsScene *scene;
    private:
        Q_OBJECT
        Space_ship *ship;
        //end for qt

        double time;
        Game_state game_state = ONGOING;
        std::vector<std::vector<Field_state>> field;
        int lives = 3;
        Space_ship my_ship;
        std::vector<Asteroid> asteroids_in_the_field;
        std::vector<Shot> shots_in_the_field;

        void moving_shots();
        void moving_asteroids();//TODO: to run both vectors
        void make_move();       //TODO: add the interaction with the keyboard

    public:

        Game();
        Game_state get_game_state() const;
        Field_state get_field_state(int x, int y) const;
        int get_time() const;
        void run_game();
    };
}// namespace eclipse

#endif//MAIN_GAME_GAME_H
