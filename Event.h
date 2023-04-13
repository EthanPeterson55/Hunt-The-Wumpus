#pragma once
using namespace std;
#include <iostream>
#include <stdlib.h>
#include <vector>

class Event {
    protected:

    public:
        Event();
        virtual void percept() = 0;
        virtual void encounter() = 0;
    
};