#include "Room.h"
#include "Game.h"


/*********************************************************************
** Function: Game()
** Description: Constructs a game class object.
** Parameters: N/A
** Pre-Conditions: hand class.
** Post-Conditions: Game class object created.
*********************************************************************/ 

Game::Game(){
    this->size = 0;
    this->n_arrows = 3; // sets number of arrows to 3.
}

/*********************************************************************
** Function: ~Game()
** Description: deletes dynamic memory in the cave vector and then clears the vector.
** Parameters: N/A
** Pre-Conditions: game class object created.
** Post-Conditions: Dynamic memory deleted.
*********************************************************************/ 

Game::~Game(){
    for (int i = 0; i < this->size; i++)
    {
        for (int j = 0; j < this->size; j++)
        {
            delete cave[i][j].getEvent(); // deletes all dynamic memory in cave
        }
    }
    cave.clear();
}

/*********************************************************************
** Function: GameFlow()
** Description: runs one iteration of a game of hunt the wumpus.
** Parameters: N/A
** Pre-Conditions: game class objecg created.
** Post-Conditions:one game is played.
*********************************************************************/ 

void Game::GameFlow(){
    cheatmodeornot();
    createGame();
    randRooms();
    while(this->gameOver == false){
        check_encounter();
        printcheatmodeornot();
        printNarrows();
        check_percept();
        player_turn();
        check_encounter();
        check_win();
        if(this->gameOver == true){
          GAMEOVER();
        }
        if(this->win == true){
          WIN();
          break;
        }
    }
}

/*********************************************************************
** Function: printNarrows()
** Description: prints the number of arrows the player has
** Parameters: N/A
** Pre-Conditions: number of arrows set.
** Post-Conditions:one  num of arrows printed.
*********************************************************************/ 

void Game::printNarrows(){
  cout << "Number of Arrows: " << this->n_arrows << endl;
}


/*********************************************************************
** Function: printGameCheat()
** Description: prints the cave grid with each event, the escape rope and the adventurer.
** Parameters: N/A
** Pre-Conditions: cave vector created.
** Post-Conditions: One iteration of cavre grid is priunted with cheats.
*********************************************************************/ 

void Game::printGameCheat(){
    for(int i = 0; i < this->size; i++){
        for(int j = 0; j < this->size; j++){
        {
            cout << "[";
            if(advLocation[i][j]){ // prints adventurers location with astrics.
                cout << "*";
            }else if(cave.at(i).at(j).geteventNum() == 1){
                cout << "W";
            }else if(cave.at(i).at(j).geteventNum() == 2){
                cout << "B";
            }else if(cave.at(i).at(j).geteventNum() == 3){
                cout << "P";
            }else if(cave.at(i).at(j).geteventNum() == 4){
                cout << "G";
            }else if(ropeLocation[i][j]){
                cout << "R";
            }else{
                cout << " ";
            }
                cout << "]\t";
        }
        }
        cout << endl;
    }
}

/*********************************************************************
** Function: createGame()
** Description: creates 3 2d vectors, one for cave grid, adventurers location, and escape rope location.
** Parameters: N/A
** Pre-Conditions: N/A
** Post-Conditions: Game setup created.
*********************************************************************/ 

void Game::createGame(){
  createCave();
  create_advlocation();
  create_ropeLocation();
}

/*********************************************************************
** Function: createCave()
** Description: creates a 2d vector for the cave grid.
** Parameters: N/A
** Pre-Conditions: N/A
** Post-Conditions: cave vector created.
*********************************************************************/ 

void Game::createCave(){
    setSize();

    for (int i = 0; i < this->size; i++)
  {
    vector<Room> row_vec;
    for (int j = 0; j < this->size; j++)
    {
      Room r;
      row_vec.push_back(r); // allocating space for the cave grid with rooms.
    }
    this->cave.push_back(row_vec);
  }
}

/*********************************************************************
** Function: create_advlocation()
** Description: creates a 2d vector for the adv location grid.
** Parameters: N/A
** Pre-Conditions: N/A
** Post-Conditions: adv location vector created
*********************************************************************/ 

void Game::create_advlocation(){
  for (int i = 0; i < this->size; i++)
  {
    vector<bool> row_vec; 
    for (int j = 0; j < this->size; j++)
    {
      bool f = false;
      row_vec.push_back(f); // allocating space for the advlocation room with bools
    }
    this->advLocation.push_back(row_vec);
  }
}

/*********************************************************************
** Function: create_ropelocation()
** Description: creates a 2d vector for the adv location grid.
** Parameters: N/A
** Pre-Conditions: N/A
** Post-Conditions: rope location vector created
*********************************************************************/ 

void Game::create_ropeLocation(){
  for (int i = 0; i < this->size; i++)
  {
    vector<bool> row_vec;
    for (int j = 0; j < this->size; j++)
    {
      bool f = false;
      row_vec.push_back(f); // allocating space for the advlocation room with bools
    }
    this->ropeLocation.push_back(row_vec);
  }
}

/*********************************************************************
** Function: randRooms()
** Description: fills a random room with each event in the cave vector and puts adventurer in a random room.
** Parameters: N/A
** Pre-Conditions: cave and advlocation vectors created.
** Post-Conditions: events and adventurer put in random rooms.
*********************************************************************/ 

void Game::randRooms(){ // modularize
    srand(time(NULL));
    int randRow = RandI();
    int randCol = RandI();
  Event* wump = new Wumpus();
  this->cave.at(randRow).at(randCol).setEvent(wump); // fills rand room with a wumpus event pointer.
  this->cave.at(randRow).at(randCol).setEventNum(1);
  while(this->cave.at(randRow).at(randCol).checkEvent()){
    randRow = RandI();
    randCol = RandI();
  }
  Event* bat1 = new Bats();
  cave.at(randRow).at(randCol).setEvent(bat1); // fills rand room with a Bat event pointer.
  cave.at(randRow).at(randCol).setEventNum(2);
  while(cave.at(randRow).at(randCol).checkEvent()){
    randRow = RandI();
    randCol = RandI();
  }
  Event* bat2 = new Bats();
  cave[randRow][randCol].setEvent(bat2); // fills rand room with a Bat event pointer.
  cave.at(randRow).at(randCol).setEventNum(2);
  while(cave.at(randRow).at(randCol).checkEvent()){
    randRow = RandI();
    randCol = RandI();
  }
  Event* gold = new Gold();
  cave.at(randRow).at(randCol).setEvent(gold); // fills rand room with a gold event pointer.
  cave.at(randRow).at(randCol).setEventNum(4);
  while(cave.at(randRow).at(randCol).checkEvent()){
    randRow = RandI();
    randCol = RandI();
  }
  Event* pit1 = new Pit();
  cave.at(randRow).at(randCol).setEvent(pit1); // fills rand room with a pit event pointer.
  cave.at(randRow).at(randCol).setEventNum(3);
  while(cave.at(randRow).at(randCol).checkEvent()){
    randRow = RandI();
    randCol = RandI();
  }
  Event* pit2 = new Pit();
  cave.at(randRow).at(randCol).setEvent(pit2); // fills rand room with a pit event pointer.
  cave.at(randRow).at(randCol).setEventNum(3);
  while(cave.at(randRow).at(randCol).checkEvent()){
    randRow = RandI();
    randCol = RandI();
  }
  this->escapeRow = randRow;
  this->escapeCol = randCol;
  this->advRow = randRow;
  this->advCol = randCol;
  ropeLocation.at(this->escapeRow).at(this->escapeCol) = true; // sets adventurer to random room
  advLocation.at(this->advRow).at(this->advCol) = true; // keeps track of escape rope.
}

/*********************************************************************
** Function: RandI()
** Description: returns a random number from the size of dimensions of the cave vector.
** Parameters: N/A
** Pre-Conditions: size determined.
** Post-Conditions: rand int returned.
*********************************************************************/ 

int Game::RandI(){
    int num = rand() % this->size; // gets a random num from the size of grid.
    return num;
}

/*********************************************************************
** Function: setSize()
** Description: Asks user what size they want the cave to be and sets the size to that value.
** Parameters: N/A
** Pre-Conditions: N/A
** Post-Conditions: adv location vector created
*********************************************************************/ 

void Game::setSize(){
  int siz;
  cout << "How big do you want the game to be?" << endl;
  cin >> siz;
  this->size = siz;
}

/*********************************************************************
** Function: character_move()
** Description: takes an input for move then moves the player one room in that direction.
** Parameters: string move
** Pre-Conditions: move diredtion determined and adv location vector created.
** Post-Conditions: adventurer moved one room.
*********************************************************************/

void Game::character_move(string move){

  if(move == "w"){
      this->advLocation[this->advRow][this->advCol] = false;
      this->advLocation[this->advRow - 1][this->advCol] = true;
      this->advRow--;
  }
  if(move == "a"){
      this->advLocation[this->advRow][this->advCol] = false;
      this->advLocation[this->advRow][this->advCol - 1] = true;
      this->advCol--;
  }
  if(move == "s"){
      this->advLocation[this->advRow][this->advCol] = false;
      this->advLocation[this->advRow + 1][this->advCol] = true;
      this->advRow++;
  }
  if(move == "d"){
      this->advLocation[this->advRow][this->advCol] = false;
      this->advLocation[this->advRow][this->advCol + 1] = true;
      this->advCol++;
  }
}

/*********************************************************************
** Function: move_error()
** Description: error checks the move adventurer input
** Parameters: string move
** Pre-Conditions: which direction you want to move in.
** Post-Conditions: input error handled.
*********************************************************************/ 

string Game::move_error(string move){ // modularize
    bool error = true;
    while(error){
    if(move == "w" && advLocation[0][this->advCol]){ // makes sure adv isnt trying to move out of map(seg fault)
        cout << "You cant move out of the map, Try Again!" << endl;
    }else if (move == "a" && advLocation[this->advRow][0]){ // makes sure adv isnt trying to move out of map(seg fault)
        cout << "You cant move out of the map, Try Again!" << endl;
    }else if (move == "s" && advLocation[this->size - 1][this->advCol]){ // makes sure adv isnt trying to move out of map(seg fault)
        cout << "You cant move out of the map, Try Again!" << endl;
    }else if (move == "d" && advLocation[this->advRow][this->size - 1]){ // makes sure adv isnt trying to move out of map(seg fault)
        cout << "You cant move out of the map, Try Again!" << endl;
    }else{
      break;
    }
    if(error)
      getline(cin, move);
    }
    return move;
}

/*********************************************************************
** Function: arrow_error()
** Description: error checks the fire arrow input
** Parameters: string move
** Pre-Conditions: which direction you want to fire arrow in.
** Post-Conditions: input error handled.
*********************************************************************/ 

string Game::arrow_error(string move){
    bool error = true;
    while(error){
    if(move == " w" && advLocation[0][this->advCol]){ // makes sure user cant shoot arrow out of map
        cout << "You cant shoot arrows out of the map, Try Again!" << endl;
    }else if (move == " a" && advLocation[this->advRow][0]){
        cout << "You cant shoot arrows out of the map, Try Again!" << endl;
    }else if (move == " s" && advLocation[this->size - 1][this->advCol]){
        cout << "You cant shoot arrows out of the map, Try Again!" << endl;
    }else if (move == " d" && advLocation[this->advRow][this->size - 1]){
        cout << "You cant shoot arrows out of the map, Try Again!" << endl;
    }else{
      break;
    }
    if(error){
      getline(cin, move);
    }
    }
    return move;
}

/*********************************************************************
** Function: clear_screen()
** Description: cleares screen by couting endls.
** Parameters: N/A
** Pre-Conditions: N/A
** Post-Conditions: screen cleared.
*********************************************************************/ 

void Game::clear_screen(){
    for (int i = 0; i < 2000; i++)
    {
        cout << endl;
    }
}

/*********************************************************************
** Function: check_percept()
** Description: checks if an event is within one room from the adventurer and calls that events percept.
** Parameters: N/A
** Pre-Conditions: cave vector created.
** Post-Conditions: percept checked.
*********************************************************************/ 

void Game::check_percept(){
    if(this->advRow != size - 1){
      if(this->cave[this->advRow + 1][this->advCol].geteventNum() != 0){
            cave[this->advRow + 1][this->advCol].getEvent()->percept();
        }
    }
    if(this->advRow != 0){
        if(this->cave[this->advRow - 1][this->advCol].geteventNum() != 0){
              cave[this->advRow - 1][this->advCol].getEvent()->percept();
        }
    }
    if(this->advCol != size - 1){
        if(this->cave[this->advRow][this->advCol + 1].geteventNum() != 0){
              cave[this->advRow][this->advCol + 1].getEvent()->percept();
        }
    }
    if(this->advCol != 0){
        if(this->cave[this->advRow][this->advCol - 1].geteventNum() != 0){
              cave[this->advRow][this->advCol - 1].getEvent()->percept();
        }
    }
}

/*********************************************************************
** Function: create_encounter()
** Description: checks if adventurer is in the same room as an event and does something accordingly.
** Parameters: N/A
** Pre-Conditions: cave vector created.
** Post-Conditions: encounter checked and done accordingly.
*********************************************************************/ 

void Game::check_encounter(){
  for (int i = 0; i < 3; i++)
  {
    if(this->cave[this->advRow][this->advCol].geteventNum() == 1){
    cave[this->advRow][this->advCol].getEvent()->encounter();
    this->gameOver = true;
  }
  if(this->cave[this->advRow][this->advCol].geteventNum() == 2){
    advLocation[this->advRow][this->advCol] = false;
    cave[this->advRow][this->advCol].getEvent()->encounter();
    randRoom();
    advLocation[this->advRow][this->advCol] = true;
  }
  if(this->cave[this->advRow][this->advCol].geteventNum() == 3){
    cave[this->advRow][this->advCol].getEvent()->encounter();
    this->gameOver = true;
  }
  if(this->cave[this->advRow][this->advCol].geteventNum() == 4){
    cave[this->advRow][this->advCol].getEvent()->encounter();
    cave[this->advRow][this->advCol].setEventNum(0);
    this->gold = true;
  }
  }
}

/*********************************************************************
** Function: randRoom()
** Description: takes a random row and col and set sthem to advRow and advCol
** Parameters: N/A
** Pre-Conditions: RandI() created
** Post-Conditions: rand row and col generated.
*********************************************************************/ 

void Game::randRoom(){
  srand(time(NULL));
  int row = RandI();
  int col = RandI();

  this->advRow = row;
  this->advCol = col;
}

/*********************************************************************
** Function: GAMEOVER()
** Description: cleares screen, checks encounter, then prints game over screen
** Parameters: N/A
** Pre-Conditions: N/A
** Post-Conditions: game over screen printed.
*********************************************************************/ 

void Game::GAMEOVER(){
    clear_screen();
    check_encounter();
    cout << "~~~~~~~~~~~~~~GAME OVER~~~~~~~~~~~~~~~~~" << endl;
    for (int i = 0; i < 8; i++)
    {
      cout << " " << endl;
    }
}

/*********************************************************************
** Function: shoot_arrow(string)
** Description: shoots arrow in direction inputed by user.
** Parameters: string dir
** Pre-Conditions: cave vector create, direction given.
** Post-Conditions: arrows fired in direction.
*********************************************************************/ 

void Game::shoot_arrow(string dir){
  srand(time(NULL));
  bool miss = true;
  for (int i = 0; i <= getarrowfiringup(); i++)
    {
      for (int j = 0; j <= getarrowfiringup(); j++)
      {
  if(dir == " w"){
        if(cave[advRow - i][advCol].geteventNum() == 1){
          hitWump(i, 'w');
          miss = false;
        }
  }else if(dir == " a"){
        if(cave[advRow][advCol - i].geteventNum() == 1){
          hitWump(i, 'a');
          miss = false;
        }
  }else if(dir == " d"){
        if(cave[advRow][advCol + i].geteventNum() == 1){
          hitWump(i, 'd');
          miss = false;
        }
      }
    }
  }
  if(dir == " s"){
    for (int i = 0; i <= getarrowfiringdown(); i++)
    {
      for (int j = 0; j <= getarrowfiringdown(); j++)
      {
        if(cave[advRow + i][advCol].geteventNum() == 1){
          hitWump(i, 's');
          miss = false;
        }
      }
    }
  }
  if(miss && wump == false){
    wumpus_rand();
  }
}

/*********************************************************************
** Function: hitWump(int, char)
** Description: prints wumpus kill message and sets event num to 0.
** Parameters: int i, char dir.
** Pre-Conditions: cave vector created.
** Post-Conditions: wumpus kill messaged if wumpus is hit.
*********************************************************************/ 

void Game::hitWump(int i, char dir){
  if(dir == 'w'){
    cout << "The mighty Wumpus' heart is peirced! He falls to the ground and dies!" << endl;
    this->wump = true;
    cave[this->advRow - i][this->advCol].setEventNum(0); // sets the old wumpus room to 0
  }else if(dir == 'a'){
    cout << "The mighty Wumpus' heart is peirced! He falls to the ground and dies!" << endl;
     this->wump = true;
    cave[advRow][advCol - i].setEventNum(0); // sets the old wumpus room to 0
  }else if(dir == 's'){
    cout << "The mighty Wumpus' heart is peirced! He falls to the ground and dies!" << endl;
    this->wump = true;
    cave[advRow + i][advCol].setEventNum(0); // sets the old wumpus room to 0
  }else if(dir == 'd'){
    cout << "The mighty Wumpus' heart is peirced! He falls to the ground and dies!" << endl;
    this->wump = true;
    cave[advRow][advCol + i].setEventNum(0); // sets the old wumpus room to 0
  }
}

/*********************************************************************
** Function: player_turn()
** Description: takes input for move or fire arrow and does that accordingly.
** Parameters: N/A
** Pre-Conditions: move_error() created, other function created.
** Post-Conditions: 
*********************************************************************/ 

void Game::player_turn(){
  string choice;
  cout << "Enter a direction to move in Up(W), Left(A), Down(S), Right(D) or fire and arrow in a direction with a space before the direciton!" << endl;
  getline(cin, choice);
  if(choice == "w" || choice == "a" || choice == "s" || choice == "d"){
    choice = move_error(choice);
    character_move(choice);
  }else if(choice == " w" || choice == " a" || choice == " s" || choice == " d"){
    choice = arrow_error(choice);
    if(this->n_arrows > 0){
      this->n_arrows--; // minus one from number of arrows
      shoot_arrow(choice);
    }else{
      cout << "You are out of arrows!!" << endl;
    } 
  }
}

/*********************************************************************
** Function: wumpus_rand()
** Description: 75% chance for the wumpus to move to a random location on the cave grid vector.
** Parameters: N/A
** Pre-Conditions: cave vector created.
** Post-Conditions: rope location vector created
*********************************************************************/ 

void Game::wumpus_rand(){
  srand(time(NULL));
  Event* wump = new Wumpus();
  bool TrueFalse = (rand() % 100) < 75; // 75% chance to happen.
  if(TrueFalse){
  int row = RandI();
  int col = RandI();
  while(cave.at(row).at(col).geteventNum() != 0){ // makes sure wumpus isnt spawned in same room as another event
    row = RandI();
    col = RandI();
  }
  for (int i = 0; i < this->size; i++) // modularize
  {
    for (int j = 0; j < this->size; j++)
    {
      if(cave[i][j].geteventNum() == 1){
        cave[i][j].setEventNum(0);
      }
    }
  }
  cave[row][col].setEvent(wump);
  cave[row][col].setEventNum(1);
  cout << "You have missed and awoken the wumpus, He runs to another room!" << endl;
  }
}

/*********************************************************************
** Function: WIN()
** Description: prints YOU WIN screen.
** Parameters: N/A
** Pre-Conditions: N/A
** Post-Conditions: You win screen printed.
*********************************************************************/ 

void Game::WIN(){
    clear_screen();
    cout << "~~~~~~~~~~~~~~YOU WIN~~~~~~~~~~~~~~~~~" << endl;
    for (int i = 0; i < 8; i++)
    {
      cout << " " << endl;
    }
}

/*********************************************************************
** Function: check_win()
** Description: checks if wumpus is slain, gold is collected, and adventurer is in the same room as the escape rope returns true if true
** Parameters: N/A
** Pre-Conditions: advLocation created.
** Post-Conditions: win conditions checked.
*********************************************************************/ 

void Game::check_win(){
  if(this->advLocation[escapeRow][escapeCol] == true && this->wump == true && this->gold == true){ // checks to see if all win conditions are met.
    this->win = true;
  }
}

/*********************************************************************
** Function: getarrowfiringup()
** Description: error handles firing arrows upwards to make sure not checking rooms that dont exist(seg fault)
** Parameters: N/A
** Pre-Conditions: advLocation vector created.
** Post-Conditions: error handling checked.
*********************************************************************/ 

int Game::getarrowfiringup(){
  int num;
  int num1;
  if(advLocation[1][advCol]){ // makes sure no seg faults
    return 1;
  }else if(advLocation[2][advCol]){ // makes sure no seg faults
    return 2;
  }else{
    return 3;
  }
}

/*********************************************************************
** Function: getarrowfiringdown()
** Description: error handles firing arrows downwards to make sure not checking rooms that dont exist(seg fault)
** Parameters: N/A
** Pre-Conditions: adv vector created
** Post-Conditions: error handling checked.
*********************************************************************/ 

int Game::getarrowfiringdown(){
  if(advLocation[this->size - 2][advCol]){ // makes sure no seg faults
    return 1;
  }else if(advLocation[this->size - 3][advCol]){ // makes sure no seg faults
    return 2;
  }else{
    return 3;
  }
}

/*********************************************************************
** Function: cheatmodeornot()
** Description: asks user if they want to play in debug mode or not and changes the class variable accordingly.
** Parameters: N/A
** Pre-Conditions: game created
** Post-Conditions: debug mode or not found.
*********************************************************************/ 

void Game::cheatmodeornot(){
  char cheat;
  cout << "Would you like to play in debug mode or not? (Y or N)" << endl;
  cin >> cheat;

  if(cheat == 'Y' || cheat == 'y'){
    this->cheat = true;
  }else if(cheat == 'N' || cheat == 'n'){
    this->cheat = false;
  }
}

/*********************************************************************
** Function: printGame()
** Description: prints one iteration of the game grid without debug mode.
** Parameters: N/A
** Pre-Conditions: advLocation vector created.
** Post-Conditions: one iteration of game printed.
*********************************************************************/ 

void Game::printGame(){
  for(int i = 0; i < this->size; i++){
        for(int j = 0; j < this->size; j++){
        {
            cout << "[";
            if(advLocation[i][j]){
                cout << "*";
            }else{
                cout << " ";
            }
                cout << "]\t";
        }
        }
        cout << endl;
    }
}

/*********************************************************************
** Function: printcheatmodeornot()
** Description: checks the class variable cheat and calls the print function that coresponds with the choice.
** Parameters: N/A
** Pre-Conditions: N/A
** Post-Conditions: correct print function called.
*********************************************************************/ 

void Game::printcheatmodeornot(){
  if(this->cheat == true){
    printGameCheat();
  }else if(this->cheat == false){
    printGame();
  }
}
