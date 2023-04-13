#include "Wumpus.h"

/*********************************************************************
** Function: Wumpus()
** Description: creates a wumpus class object
** Parameters: N/A
** Pre-Conditions: N/A
** Post-Conditions: Wumpus class object created.
*********************************************************************/ 

Wumpus::Wumpus(){
    this->dead = false; // sets dead bool to true.
}

/*********************************************************************
** Function: percept()
** Description: print wumpus percept message
** Parameters: N/A
** Pre-Conditions: wumpus class object created.
** Post-Conditions: percept message printed
*********************************************************************/ 

void Wumpus::percept(){
    cout << "You smell a terrible stench." << endl;
}

/*********************************************************************
** Function: encounter()
** Description: prints wumpus encounter message
** Parameters: N/A
** Pre-Conditions: wumpus class object created.
** Post-Conditions: encounter message printed.
*********************************************************************/ 

void Wumpus::encounter(){
    cout << "The mighty Wumpus grabs you and tears you to shreds!" << endl;
}

/*********************************************************************
** Function: isDead()
** Description: returns the state of the dead bool variable.
** Parameters: N/A
** Pre-Conditions: wumpus class object created.
** Post-Conditions: dead bool variable returned.
*********************************************************************/ 

bool Wumpus::isDead(){
    return this->dead;
}



