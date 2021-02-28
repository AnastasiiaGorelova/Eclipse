#ifndef MAIN_GAME_GOD_H
#define MAIN_GAME_GOD_H

#include "game_window.h"
#include "main_window.h"

class God {
public:

//for qt
static void show_menu();
static void close_menu();
static void show_game_field();
static void set_object(int x, int y, int size, const std::string& hash, const std::string& object_name);
static void move_object(int x, int y, const std::string& hash);
static void delete_object(const std::string& hash);

//for logic
static void clicked_on_start();
static void clicked_on_exit();
static void pushed_button_left();
static void pushed_button_right();

//both




};

#endif //MAIN_GAME_GOD_H
