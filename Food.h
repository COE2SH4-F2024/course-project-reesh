#ifndef FOOD_H
#define FOOD_H

#include <stdlib.h>
#include <time.h>

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"


class GameMechs;
class Food
{
    private:
        objPosArrayList* foodBucket;
        GameMechs* mainGameMechsRef;

    public:
        
        Food(GameMechs* thisGMRef);
        ~Food(); 

        Food &operator=(const Food &copy);
        Food(const Food &copy);

        void generateFood(objPosArrayList* blockOff);
		objPosArrayList* getFoodPos() const;


        
        
};

#endif