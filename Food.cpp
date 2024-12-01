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



void Food::generateFood(objPosArrayList& blockOff)
{
    int randX; 
    int randY;
    bool isValid = false;
    int xRange = mainGameMechsRef->getBoardSizeX() - 2;
    int yRange = mainGameMechsRef->getBoardSizeY() - 2;

    while (!isValid) {
        randX = rand() % xRange + 1;
        randY = rand() % yRange + 1;

        isValid = true; 

        for (int blockOffpos = 0; blockOffpos < blockOff.getSize(); blockOffpos++) {
            objPos currentPos = blockOff.getElement(blockOffpos); 
            if (randX == currentPos.pos->x && randY == currentPos.pos->y) {
                isValid = false; 
                break;
            }
        }
    }

    foodPos.pos->x = randX;
    foodPos.pos->y = randY;
    foodPos.symbol = 'F';
}

objPos Food::getFoodPos() const
{
    return foodPos;
}