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

void Player::updatePlayerSpeed() {
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


void Player::movePlayer()
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
    objPos Hnew(Hx,Hy,'@');
    
    //3C
    for (int i=1; i < playerPosList->getSize(); i++){
        objPos body = playerPosList->getElement(i);
        int Bx= body.pos->x;
        int By= body.pos->y;

        if (Hx==Bx && Hy==By){
            mainGameMechsRef->setExitTrue();
            mainGameMechsRef->setLoseFlag();
        }

    }
    //3C
    if (Hnew.pos->x == mainFoodRef->getFoodPos().pos->x &&
        Hnew.pos->y == mainFoodRef->getFoodPos().pos->y){
            playerPosList->insertHead(Hnew);
            mainFoodRef->generateFood(*playerPosList);
        
    }
    else {
        playerPosList->insertHead(Hnew);
        playerPosList->removeTail();
    }

    int snakeSize = playerPosList->getSize();

        if (snakeSize > 0){
            mainGameMechsRef->setScore(snakeSize - 1);
        }
        else{
            mainGameMechsRef->setScore(0);
        }
}

// More methods to be added