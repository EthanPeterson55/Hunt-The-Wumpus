#include "Room.h"

/*********************************************************************
** Function: Room()
** Description: constructs a room class object.
** Parameters: N/A
** Pre-Conditions: N/A
** Post-Conditions: Room class object created.
*********************************************************************/ 

Room::Room(){
    this->row = 0;
    this->col = 0;
    this->e = NULL; // sets rooms event to NULL by default.
    this->event = false;
    this->isPlayer = false;
    this->eventNum = 0;
}

/*********************************************************************
** Function: Room(int, int)
** Description: constructs a room class object with setting the Room row and col.
** Parameters: int r, int c
** Pre-Conditions: row and col chosen.
** Post-Conditions: room class object created.
*********************************************************************/ 

Room::Room(int r, int c){
    this->row = r;
    this->col = c;
}

/*********************************************************************
** Function: printRooom()
** Description: prints the event stored in the room.
** Parameters: N/A
** Pre-Conditions: event stored in room.
** Post-Conditions: event stored in room printed.
*********************************************************************/ 

void Room::printRoom(){
    cout << this->e << endl; // prints event.
}

/*********************************************************************
** Function: checkEvent()
** Description: checks if there is an event in the room.
** Parameters: N/A
** Pre-Conditions: N/A
** Post-Conditions: event bool returned.
*********************************************************************/ 

bool Room::checkEvent(){
    return this->event;
}

/*********************************************************************
** Function: setEvent(Event*)
** Description: sets the event in the room to the event pointer in paramter.
** Parameters: Event* E.
** Pre-Conditions: Event pointer stated.
** Post-Conditions: sets event in room to event provided.
*********************************************************************/ 

void Room::setEvent(Event* E){
    this->e = E;
    event = true;
}

/*********************************************************************
** Function: geteventNum()
** Description: returns the event number in the room.
** Parameters: N/A
** Pre-Conditions: event num set.
** Post-Conditions: event num for room returned.
*********************************************************************/ 

int Room::geteventNum(){
    return this->eventNum;
}

/*********************************************************************
** Function: setEventNum(int)
** Description: sets event num to number provided
** Parameters: int num
** Pre-Conditions: number you want to set to provided.
** Post-Conditions: rooms event number is set to parameter int.
*********************************************************************/ 

void Room::setEventNum(int num){
    this->eventNum = num; // sets event num
}

/*********************************************************************
** Function: getEvent()
** Description: returns the event in the room.
** Parameters: N/A
** Pre-Conditions: event set for the room.
** Post-Conditions: event pointer in room returned.
*********************************************************************/ 

Event* Room::getEvent(){
    return e;
}



