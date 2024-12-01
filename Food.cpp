#include "Food.h"
#include "GameMechs.h"
#include "objPos.h"


Food::Food(GameMechs* thisGMRef)
{
   mainGameMechsRef = thisGMRef;
   foodBucket = new objPosArrayList();
    
}

Food::~Food()
{
    delete foodBucket;
    foodBucket = nullptr;
}


Food& Food::operator=(const Food& copy) {
    if (this != &copy) { 
        delete foodBucket;  

        mainGameMechsRef = copy.mainGameMechsRef;
        foodBucket = new objPosArrayList();
        for (int i = 0; i < copy.foodBucket->getSize(); i++) {
            foodBucket->insertTail(copy.foodBucket->getElement(i));  // Copy each element
        }
    }
    return *this;
}

Food::Food(const Food& copy)
{
    mainGameMechsRef = copy.mainGameMechsRef;
    foodBucket = new objPosArrayList(); 
    for (int i = 0; i < copy.foodBucket->getSize(); i++) {
        objPos copyFoodPos = copy.foodBucket->getElement(i);
        foodBucket->insertTail(copyFoodPos);
    } 
}

void Food::generateFood(objPosArrayList* blockOff)
{
    int randX, randY;
    int genCount = 0;  
    int checkIndex = 0;
    int xRange = mainGameMechsRef->getBoardSizeX() - 2;
    int yRange = mainGameMechsRef->getBoardSizeY() - 2;

    int spFoodcount = rand() % 2 + 1;  // Randomly choose 1 or 2 items to be '$'
    
    for (checkIndex = foodBucket->getSize(); checkIndex > 0; checkIndex--)
        foodBucket->removeTail(); 
    
    while (genCount < 5){
        bool isValid=false;
        while (!isValid) {
            randX = rand() % xRange + 1;
            randY = rand() % yRange + 1;
            isValid = true;

            // Check against the snake's body
            for (int checkI = 0; checkI < blockOff->getSize(); checkI++) {
                objPos bodyPart = blockOff->getElement(checkI);
                if (bodyPart.pos->x == randX && bodyPart.pos->y == randY) {
                    isValid = false;
                    break;
                }
            }

            for (int checkI = 0; checkI < foodBucket->getSize(); checkI++) {
                objPos genFoodPos = foodBucket->getElement(checkI);
                if (genFoodPos.pos->x == randX && genFoodPos.pos->y == randY) {
                    isValid = false;
                    break;
                }
            }
        }

        
        if (spFoodcount > 0) {
            foodBucket->insertTail(objPos(randX, randY, '$')); 
            spFoodcount--;  // Decrement the count of $ so only places 1 or 2 $
        } else {
            foodBucket->insertTail(objPos(randX, randY, 'O')); 
        }

        genCount++;  
    }

}

objPosArrayList* Food::getFoodPos() const
{
    return foodBucket;
}

