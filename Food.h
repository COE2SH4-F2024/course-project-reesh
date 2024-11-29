#ifndef FOOD_H
#define FOOD_H

#include <stdlib.h>
#include <time.h>

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"


using namespace std;
class GameMechs;
class Food
{
    private:
        objPos foodPos;
        GameMechs* mainGameMechsRef;

    public:
        
        Food(GameMechs* thisGMRef);
        ~Food(); 
        void generateFood(objPos blockOff);
        objPos getFoodPos() const;
        
        
};

#endif