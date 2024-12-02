#ifndef PLAYER_H
#define PLAYER_H


#include "GameMechs.h"
#include "Food.h"
#include "objPos.h"
#include "objPosArrayList.h"

class GameMechs;
class Food;

class Player
{
    //Player Class to deal with player behaviour
    public:
        enum Dir {UP, DOWN, LEFT, RIGHT, STOP};  // This is the direction state

        Player(GameMechs* thisGMRef, Food* thisFoodRef);
        ~Player();

        objPosArrayList* getPlayerPos() const; //for snake body list control     
        void updatePlayerDir();
        void movePlayer();

        // More methods added here
        void updatePlayerSpeed();
        objPos newHeadpos();
        bool checkSelfCollision();
        bool checkfoodCollision(const objPos& newHead);

        void afterEating(const objPos& newHead, bool ateFood);




    private:
        objPosArrayList* playerPosList; //for snake body list control    
        enum Dir myDir;

        //a reference to the Main Game Mechanisms
        GameMechs* mainGameMechsRef;
        Food* mainFoodRef;
};

#endif