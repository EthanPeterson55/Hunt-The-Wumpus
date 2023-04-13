#pragma once
#include "Event.h"

class Gold : public Event {
    private:
        bool found = false;
    public:
        Gold();
        void encounter();
        void percept();
};