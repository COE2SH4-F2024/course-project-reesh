#include "Food.h"
#include "GameMechs.h"
#include "objPos.h"


Food::Food(GameMechs* thisGMRef)
{
   mainGameMechsRef = thisGMRef;
   foodPos.setObjPos(5,5,'F');
    
}

Food::~Food()
{
    //not rn
}



void Food::generateFood(objPos blockOff)
{
    int randX;
    int randY;
    int isValid = 0;
    int xRange = mainGameMechsRef->getBoardSizeX()-2;
    int yRange = mainGameMechsRef->getBoardSizeY()-2;
    while (!isValid){
        randX = rand() % xRange + 1;
        randY = rand() % yRange + 1;
        if (randX != blockOff.pos->x && randY != blockOff.pos->y) {
            isValid = 1;
        }
    }

    foodPos.pos->x = randX;
    foodPos.pos->y= randY;
    foodPos.symbol = 'F';
        
    
}

objPos Food::getFoodPos() const
{
    return foodPos;
}