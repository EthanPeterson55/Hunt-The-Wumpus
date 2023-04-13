#include "Game.h"

/*********************************************************************
** Program Filename: Hunt.zip
** Author: Ethan Peterson
** Date: 11/20/22
** Description: Creates a user friendly Hunt the Wumpus game
** Input: Debug mode or not, what direction you want to move or fire arrow in, play again?, play with same config?.
** Output: Game of Hunt the Wumpus to terminal
*********************************************************************/

/*********************************************************************
** Function: playAgain()
** Description: takes input for if user wants to play game again and return choice.
** Parameters: N/A
** Pre-Conditions: N/A
** Post-Conditions: choice returned.
*********************************************************************/ 

bool playAgain(){
  char choice;
  cout << "Would you like to play again? (Y or N)" << endl;
  cin >> choice;
  if(choice == 'y' || choice == 'Y'){
    return true;
  }else{
    return false;
  }
}

int main(){
  bool again = true;
  while(again){
  Game g;
  g.clear_screen(); // clears screen
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~HUNT THE WUMPUS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  g.GameFlow(); // one iteration of a game.
  again = playAgain();
  }

  return 0;
}