#ifndef GAMEMECHS_H
#define GAMEMECHS_H

#include <cstdlib>
#include <time.h>

#include "objPos.h"
#include "objPosArrayList.h"
#include "Food.h"
#include "Player.h"

using namespace std;

class GameMechs
{
    private:
        char input;
        bool exitFlag;
        bool loseFlag;
        int score;

        int boardSizeX;
        int boardSizeY;

        objPos food;

    public:
        enum SPEEDState { VERY_SLOW = 0, SLOW = 1, NORMAL = 2, FAST = 3, VERY_FAST = 4 };  // Speed states
        SPEEDState game_speed;
        
        GameMechs();
        GameMechs(int boardX, int boardY);
        ~GameMechs(); // is this one needed at all? Why or why not?
        
        bool getExitFlagStatus() const; 
        void setExitTrue();
        bool getLoseFlagStatus() const;
        void setLoseFlag();

        char getInput() const;
        void setInput(char this_input);
        void clearInput();

        int getBoardSizeX() const;
        int getBoardSizeY() const;

        SPEEDState getGameSpeed() const;
        void setGameSpeed(SPEEDState speed);
        void increaseGameSpeed(); 
        void decreaseGameSpeed();
        int getDelay() const;

        
        int getScore() const;
        void setScore(int newScore);
        void incrementScore();
        void SpecialFoodScore();
        

        
        // More methods should be added here
};

#endif