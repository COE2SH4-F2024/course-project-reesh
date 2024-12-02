#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include <time.h>

#include "Player.h"
#include"GameMechs.h"
#include "Food.h"

using namespace std;


const int LOOP_DELAY = 3000000; 
int i,j,p;
char input;

//Pointers to Class objects
Player *myPlayer;
GameMechs *myGM;
Food *food;


void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(myGM->getExitFlagStatus()==false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    //Allocating objects on the heap
    myGM = new GameMechs();
    food = new Food(myGM);
    myPlayer = new Player(myGM,food);
    

    srand(time(NULL)); 

    food->generateFood(myPlayer->getPlayerPos());
}

void GetInput(void)
{

    if (MacUILib_hasChar()) { 
        myGM->setInput(MacUILib_getChar());  
    }
   
   else {
        myGM->clearInput();
    }

}


void RunLogic(void)
{
    
    input = myGM->getInput();

    //switch case to control player speed and exit based on input
    switch (input) {
        case '+':
        case '-':
            myPlayer->updatePlayerSpeed();
            break;
        
        case ' ':
            myGM->setExitTrue();
            break;

        default:
            break;  // Default case if no match is found (optional)
    }

    //accesses methods in Player class to process inputs for direction and moves player accordingly
        myPlayer->updatePlayerDir();  
        myPlayer->movePlayer(); 
    
      
        myGM->clearInput();
        
}

   

void DrawScreen(void)
{
    MacUILib_clearScreen();
    MacUILib_printf("Use WASD to move & spacebar to exit!\nCollect the snake food. Grab the special food, $, for 10 BONUS points!\n\n");
    
    int boardX=myGM-> getBoardSizeX();
    int boardY=myGM-> getBoardSizeY();
    
    //assigning pointers to getter methods for Player and Food class, and getting their size
    objPosArrayList* snake = myPlayer->getPlayerPos();
    int snakesize = snake->getSize();

    objPosArrayList* foodPosList = food->getFoodPos();
    int foodListSize = foodPosList->getSize();

    
    for (i=0; i<boardY; i++){
        for (j=0; j<boardX; j++){
             int isSnake=0; //flag to check if the position on board is a snake body symbol 

//forloopfor snake/playerPosList printing
            for(int k=0; k<snakesize; k++){
                objPos Bodypart = snake->getElement(k);

                if (i== Bodypart.pos->y  && j== Bodypart.pos->x)
                {
                    MacUILib_printf("%c",Bodypart.symbol);
                    isSnake=1;
                    break;
                }
            }
//back to normal printing boarder, blank spaces, and food where its not a snake part
            if (!isSnake)
            {
                if (i==0|| i==boardY-1|| j==0|| j==boardX-1){
                    MacUILib_printf("#");
                }
                else{
                    bool foodFound = false;
                    for (int foodI=0;foodI<foodListSize;foodI++){
                        objPos foodPos = foodPosList->getElement(foodI);
                        if (i == foodPos.pos->y && j == foodPos.pos->x){
                            MacUILib_printf("%c", foodPos.symbol);
                            foodFound = true;
                            break;
                        }
                    }
                    if (!foodFound){
                        MacUILib_printf("%c",' ');
                    }
                }

            }
            
            
        }
        MacUILib_printf("\n");
    
    }   
    
    MacUILib_printf("\nCurrent score: %d\n", myGM->getScore());

    //print speed player-directions     
    switch (myGM->getGameSpeed()) {
        case GameMechs::VERY_SLOW:
            MacUILib_printf("Speed Level: Very Slow (enter '+' to increase, '-' to decrease)\n");
            break;
        case GameMechs::SLOW:
            MacUILib_printf("Speed Level: Slow (enter '+' to increase, '-' to decrease)\n");
            break;
        case GameMechs::NORMAL:
            MacUILib_printf("Speed Level: Normal (enter '+' to increase, '-' to decrease)\n");
            break;
        case GameMechs::FAST:
            MacUILib_printf("Speed Level: Fast (enter '+' to increase, '-' to decrease)\n");
            break;
        case GameMechs::VERY_FAST:
            MacUILib_printf("Speed Level: Very Fast (enter '+' to increase, '-' to decrease)\n");
            break;
        default:
            break;
    }

            
    //print situational exit messages (forced or lost)
    if (myGM->getLoseFlagStatus()==true && myGM->getExitFlagStatus() == true) {
        MacUILib_printf("\nOops, you lost the game! :( \nTry again, you can do it! :)");
        MacUILib_Delay(LOOP_DELAY); 
    }  

    
    else if(myGM->getLoseFlagStatus() == false && myGM->getExitFlagStatus() == true)
    {

        MacUILib_printf("\nGame ended by player!");
        MacUILib_Delay(LOOP_DELAY); 
    }

    
}



void LoopDelay(void)
{
    MacUILib_Delay(myGM->getDelay());
    
}

void CleanUp(void)
{
    MacUILib_clearScreen();    

    //deleting memory on the heap
    delete myPlayer;
    myPlayer = nullptr;

    delete food;
    food = nullptr;

    delete myGM;
    myGM = nullptr;

    MacUILib_uninit();
}