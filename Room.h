#pragma once
#include "Event.h"

class Room{
    protected:
       int row;
       int col;
       Event* e;
       bool event;
       bool isPlayer;
       int eventNum;
    public:
        Room();
        Room(int, int);
        void printRoom();
        bool checkEvent();
        void setEvent(Event*);
        int geteventNum();
        void setEventNum(int);
        Event* getEvent();
        

};