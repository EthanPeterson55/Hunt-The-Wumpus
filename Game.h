#pragma once
#include "Event.h"
#include "Bats.h"
#include "Gold.h"
#include "Pit.h"
#include "Wumpus.h"
#include "Room.h"
#include <ctime>
#include <vector>
#include <curses.h>

class Game{
    private:
        bool cheat;
        bool gold = false;
        bool wump = false;
        bool win = false;
        int n_arrows;
        int size;
        vector<vector<Room> > cave;
        vector<vector<bool> > advLocation;
        vector<vector<bool> > ropeLocation;
        int advRow;
        int advCol;
        bool gameOver = false;
        int escapeRow;
        int escapeCol;
    public:
        Game();
        ~Game();
        void printGameCheat();
        void GameFlow();
        void createCave();
        void randRooms();
        int RandI();
        void setSize();
        void character_move(string);
        string move_error(string);
        void clear_screen();
        void check_percept();
        string print_percept(int);
        void check_encounter();
        void randRoom();
        void GAMEOVER();
        void shoot_arrow(string);
        void player_turn();
        void wumpus_rand();
        void WIN();
        void check_win();
        void create_advlocation();
        void create_ropeLocation();
        void createGame();
        int getarrowfiringup();
        int getarrowfiringdown();
        string arrow_error(string);
        void cheatmodeornot();
        void printGame();
        void printcheatmodeornot();
        void hitWump(int, char);
        void printNarrows();
};