#include "Player.h"


Player::Player(GameMechs* thisGMRef, Food* thisFoodRef)
{
    mainGameMechsRef = thisGMRef;
    mainFoodRef = thisFoodRef;
    myDir = STOP;

    playerPosList = new objPosArrayList();
   
   //HPos will begin the game with '@' in middle of game board and insert it as the "head" of the snake/playerPosList
    objPos HPos(mainGameMechsRef->getBoardSizeX()/2, mainGameMechsRef->getBoardSizeY()/2, '@'); 
    playerPosList->insertHead(HPos);


}


Player::~Player()
{
    // delete heap members here

    delete playerPosList;
}

objPosArrayList* Player::getPlayerPos() const
{
    // return the reference to the playerPos arrray list
    return playerPosList;
}

void Player::updatePlayerDir()
{
    char input = mainGameMechsRef->getInput();
        // wasd input processing logic for updating direction
        switch(input)
        {            
            case 'w':
                if (myDir ==STOP || myDir== LEFT|| myDir==RIGHT){
                    myDir=UP;
                    }
                break;
            case 'a':
               if (myDir ==STOP ||myDir== UP|| myDir==DOWN){
                    myDir=LEFT;
                    
                }
                break;
            case 's':
                if (myDir ==STOP||myDir== LEFT|| myDir==RIGHT){
                    myDir=DOWN;   
                }
                break;
            case 'd':
                if (myDir==STOP||myDir== UP|| myDir==DOWN){
                    myDir=RIGHT;
                    
                }
                break;

        
            default:
                
                break;
        }         
}

void Player::updatePlayerSpeed() 
{
    char input = mainGameMechsRef->getInput();
    switch (input) {
        case '+': 
            mainGameMechsRef->increaseGameSpeed();
            break;
        case '-': 
            mainGameMechsRef->decreaseGameSpeed();
            break;
        default:
            break;
    }
}


objPos Player::newHeadpos()
{
    //tracks head element 
    objPos playerPos= playerPosList->getHeadElement();

    //x-y coors for head
    int Hx= playerPos.pos->x;
    int Hy= playerPos.pos->y;
    // Finite State Machine and wrap around logic
    updatePlayerDir();
    switch (myDir)
    {
        case UP:
            Hy--;
            if (Hy <=0){
                Hy= mainGameMechsRef->getBoardSizeY()-2;
            }
        break;
        
        case DOWN:
             Hy++;
             if (Hy >= mainGameMechsRef->getBoardSizeY()-1){
                Hy= 1;
             }
        break; 

        case LEFT:
            Hx--;
            if (Hx <=0){
                Hx= mainGameMechsRef->getBoardSizeX()-2;
            }
        break;

        case RIGHT:
            Hx++;
            if(Hx >=mainGameMechsRef->getBoardSizeX()-1){
                Hx=1;
            }
        break;

        default:
            // When an invalid input is entered
            myDir = STOP; //Set direction to STOP (0)
            break;


    }
    //Updates head position
    return objPos(Hx,Hy,'@');
}



bool Player::checkfoodCollision(const objPos& newHead) 
{
    //Impliments score actions for specific food collisions and generates new food after every collision 
    objPosArrayList* foodList = mainFoodRef->getFoodPos();
    bool ateFood = false;  

    for (int i = 0; i < foodList->getSize(); i++) {
        objPos food = foodList->getElement(i);
        if (newHead.pos->x == food.pos->x && newHead.pos->y == food.pos->y) {
            ateFood = true;
            if (food.symbol == '$') {
                mainGameMechsRef->SpecialFoodScore();
            } 
            else if (food.symbol == 'O') {
                mainGameMechsRef->incrementScore();
            }
            mainFoodRef->generateFood(playerPosList); 
            break;  
        }
    }
    return ateFood;
}

bool Player::checkSelfCollision() {

    objPos headPos = playerPosList->getHeadElement();
    int Hx = headPos.pos->x;
    int Hy = headPos.pos->y;

//Iterate through snake size
    for (int i = 1; i < playerPosList->getSize(); i++) {
        objPos body = playerPosList->getElement(i);
        int Bx = body.pos->x;
        int By = body.pos->y;

        // If the head collides with any part of the body, end the game
        if (Hx == Bx && Hy == By) {
            mainGameMechsRef->setExitTrue();
            mainGameMechsRef->setLoseFlag();
            return true;  
        }
    }
    return false;  
}


void Player::afterEating(const objPos& newHead, bool ateFood) 
{
    //impliments body growth and score updates
    if (ateFood) {
        playerPosList->insertHead(newHead); 
        mainFoodRef->generateFood(playerPosList); 
    } 
    else {
        playerPosList->insertHead(newHead);  
        playerPosList->removeTail();  
    }

    int snakeSize = playerPosList->getSize();
    if (snakeSize > 0){
        mainGameMechsRef->setScore(mainGameMechsRef->getScore());
        }
    else{
        mainGameMechsRef->setScore(0);
        }
}




void Player::movePlayer() 
{
    //Implements game player methods to move player accordingly
    updatePlayerDir();
    objPos newHead = newHeadpos();
    bool ateFood = checkfoodCollision(newHead); 
    afterEating(newHead, ateFood);
    if (checkSelfCollision()) {
        return;
    }
}

    