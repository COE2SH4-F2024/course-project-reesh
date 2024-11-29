#include "Player.h"


Player::Player(GameMechs* thisGMRef, Food* thisFoodRef)
{
    mainGameMechsRef = thisGMRef;
    mainFoodRef = thisFoodRef;
    myDir = STOP;

    // more actions to be included
    playerPos.pos->x = mainGameMechsRef->getBoardSizeX()/2;
    playerPos.pos->y= mainGameMechsRef->getBoardSizeY()/2;
    playerPos.symbol= '@';


}


Player::~Player()
{
    // delete any heap members here
    //didnt say new anywhere for now 
}

objPos Player::getPlayerPos() const
{
    // return the reference to the playerPos arrray list
    return playerPos;
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
    // PPA3 Finite State Machine logic
    updatePlayerDir();
    switch (myDir)
    {
        case UP:
            playerPos.pos->y--;
            if (playerPos.pos->y <=0){
                playerPos.pos->y= mainGameMechsRef->getBoardSizeY()-2;
            }
        break;
        
        case DOWN:
             playerPos.pos->y++;
             if (playerPos.pos->y >= mainGameMechsRef->getBoardSizeY()-1){
                playerPos.pos->y= 1;
             }
        break; 

        case LEFT:
            playerPos.pos->x--;
            if (playerPos.pos->x <=0){
                playerPos.pos->x= mainGameMechsRef->getBoardSizeX()-2;
            }
        break;

        case RIGHT:
            playerPos.pos->x++;
            if(playerPos.pos->x >=mainGameMechsRef->getBoardSizeX()-1){
                playerPos.pos->x=1;
            }
        break;

        default:
            // When an invalid input is entered
            myDir = STOP; // Set direction to STOP
            playerPos.pos->x = 11; // Reset player position to (11, 5)
            playerPos.pos->y = 5;
            break;


    }
}

// More methods to be added