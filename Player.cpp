#include "Player.h"


Player::Player(GameMechs* thisGMRef, Food* thisFoodRef)
{
    mainGameMechsRef = thisGMRef;
    mainFoodRef = thisFoodRef;
    myDir = STOP;

    playerPosList = new objPosArrayList();
    // more actions to be included
    objPos HPos(mainGameMechsRef->getBoardSizeX()/2, mainGameMechsRef->getBoardSizeY()/2, '@'); 
    // // playerPos.pos->y= mainGameMechsRef->getBoardSizeY()/2;
    // // playerPos.symbol= '@';
    playerPosList->insertHead(HPos);//MAKE SURE THIS LINE IS RIGHT


}


Player::~Player()
{
    // delete any heap members here
    //didnt say new anywhere for now 
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
        // PPA3 input processing logic 
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
    //x-y coors for head
   
    //char Hsym= playerPosList->getHeadElement().getSymbol();

    objPos playerPos= playerPosList->getHeadElement();
    //x-y coors for head
    int Hx= playerPos.pos->x;
    int Hy= playerPos.pos->y;
    // PPA3 Finite State Machine logic
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
            myDir = STOP; // Set direction to STOP
           // playerPos.pos->x = 11; // Reset player position to (11, 5)
            //playerPos.pos->y = 5;
            break;


    }
    return objPos(Hx,Hy,'@');
}



bool Player::checkfoodCollision(const objPos& newHead) 
{
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

    //3C

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
    if (ateFood) {
        playerPosList->insertHead(newHead); 
        mainFoodRef->generateFood(playerPosList); 
    } else {
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
    updatePlayerDir();
    objPos newHead = newHeadpos();
    bool ateFood = checkfoodCollision(newHead); 
    afterEating(newHead, ateFood);
    if (checkSelfCollision()) {
        return;
    }
}

    