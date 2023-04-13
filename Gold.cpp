#include "Gold.h"

/*********************************************************************
** Function: Gold()
** Description: constructs a gold class object
** Parameters: N/A
** Pre-Conditions: N/A
** Post-Conditions: Gold class object created.
*********************************************************************/ 

Gold::Gold(){
    
}

/*********************************************************************
** Function: percept()
** Description: print Gold percept message
** Parameters: N/A
** Pre-Conditions: Gold class object created.
** Post-Conditions: percept message printed
*********************************************************************/ 

void Gold::percept(){
    cout << "You see a glimmer nearby." << endl;
}

/*********************************************************************
** Function: encounter()
** Description: prints Gold encounter message
** Parameters: N/A
** Pre-Conditions: Gold class object created.
** Post-Conditions: encounter message printed.
*********************************************************************/ 

void Gold::encounter(){
    cout << "You grab the gold and add it to your bag!" << endl;
    this->found = true; // sets found bool to true.
}