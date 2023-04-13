#pragma once
#include "Event.h"

class Wumpus : public Event {
    private:
    bool dead = false;
    public:
        Wumpus();
        void percept();
        void encounter();
        bool isDead();
};
