#include "Pit.h"

/*********************************************************************
** Function: Pit()
** Description: constructs a Pit class object
** Parameters: N/A
** Pre-Conditions: N/A
** Post-Conditions: Pit class object created.
*********************************************************************/ 

Pit::Pit(){
    
}

/*********************************************************************
** Function: percept()
** Description: print Pit percept message
** Parameters: N/A
** Pre-Conditions: Pit class object created.
** Post-Conditions: percept message printed
*********************************************************************/ 

void Pit::percept(){
    cout << "You feel a breeze." << endl;
}

/*********************************************************************
** Function: encounter()
** Description: prints pit encounter message
** Parameters: N/A
** Pre-Conditions: pit class object created.
** Post-Conditions: encounter message printed.
*********************************************************************/ 

void Pit::encounter(){
    cout << "You fall into a bottomless pit and DIE!" << endl;
}