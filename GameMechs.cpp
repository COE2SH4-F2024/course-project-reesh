#include "GameMechs.h"
#include "MacUILib.h"


GameMechs::GameMechs()
{
    //Initialize game control variables
    input=0;
    exitFlag=false;
    loseFlag=false;
    score=0;

    game_speed = NORMAL;

    boardSizeX=20;
    boardSizeY=10;
    
}

GameMechs::GameMechs(int boardX, int boardY)
{
    input=0;
    exitFlag=false;
    loseFlag=false;
    score=0;

    game_speed = NORMAL;

    boardSizeX=boardX;
    boardSizeY=boardY;
    
    
}

//removed ~Game destructor, no heap allocations in this class

bool GameMechs::getExitFlagStatus() const
{
    return exitFlag;
}

bool GameMechs::getLoseFlagStatus() const
{
    return loseFlag;
}
    

char GameMechs::getInput() const
{

    return input;
}

int GameMechs::getScore() const
{
    return score;

}


void GameMechs::setScore(int newScore)
{
    score = newScore;
}

void GameMechs::incrementScore()
{
    score++;
}


int GameMechs::getBoardSizeX() const
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY() const
{
    return boardSizeY;
}


GameMechs::SPEEDState GameMechs::getGameSpeed() const {
    
    return game_speed;

}

void GameMechs::setGameSpeed(SPEEDState speed){
    
    game_speed = speed;

}


void GameMechs::increaseGameSpeed(){
    if (game_speed < VERY_FAST){
        game_speed = (SPEEDState)(game_speed + 1);;
    }
    else {
        game_speed = VERY_SLOW; 
    }
} 

void GameMechs::decreaseGameSpeed(){
    if (game_speed>VERY_SLOW){
        game_speed = (SPEEDState)(game_speed - 1);
    }
    else{
        game_speed = VERY_FAST;
    }
}

int GameMechs::getDelay() const {
    switch (game_speed) {
        case VERY_SLOW:
            return 1000000;
        case SLOW:
            return 500000; 
        case NORMAL:
            return 300000;
        case FAST:
            return 100000;  
        case VERY_FAST:
            return 70000; 
        default:
            return 300000;   
    }
}


void GameMechs::setExitTrue()
{
    exitFlag= true;
}

void GameMechs::setLoseFlag()
{
    loseFlag=true;
}

void GameMechs::setInput(char this_input)
{
    input=this_input;
}

void GameMechs::clearInput()
{
    input=0;
}

void GameMechs::SpecialFoodScore()
{
    score += 10;
}

