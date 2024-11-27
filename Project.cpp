#include <iostream>
#include "MacUILib.h"
#include "objPos.h"

#include "Player.h"
#include"GameMechs.h"

using namespace std;



int i,j,p;
char input;
Player *myPlayer;//pointer to a Player object
GameMechs *myGM;




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

    myGM = new GameMechs();//defualt one so always created as 20X10
    myPlayer = new Player(myGM);
    

    
}

void GetInput(void)
{
//do we need now...
    if (MacUILib_hasChar()) { 
        myGM->setInput(MacUILib_getChar());  
    }
   
   else
   {
        myGM->clearInput();
   }
}

void RunLogic(void)
{
    input = myGM->getInput();

    if (input == '+' || input == '-') {
        myPlayer->updatePlayerSpeed();
    } 
    if (input == ' ') {
        myGM->setExitTrue();
    } 
    
    if (input=='$'){
        myGM->incrementScore();

    }
    if (input == 'l') { 
        myGM->setLoseFlag();
    }

        myPlayer->updatePlayerDir();  
        myPlayer->movePlayer(); 

      
        myGM->clearInput();
    }

   

void DrawScreen(void)
{
    MacUILib_clearScreen();
    MacUILib_printf("Use WASD to move & spacebar to exit\n\n");
    

    objPos playerPos = myPlayer->getPlayerPos();


    for (i=0; i<10; i++){
        for (j=0; j<20; j++){
            
            if (i==0|| i==9|| j==0|| j==19){
                MacUILib_printf("#");
            }

            else if (i== playerPos.pos->y  && j== playerPos.pos->x){
                MacUILib_printf("%c",playerPos.symbol);
            }
            else{
                MacUILib_printf(" ");
            }

            
        }
        MacUILib_printf("\n");
    
    }   
    
    MacUILib_printf("\nCurrent score: %d\n", myGM->getScore());

           
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

    if (myGM->getLoseFlagStatus()) {
        MacUILib_printf("\nLose flag is TRUE");
    }
            

    if (myGM->getLoseFlagStatus()==true && myGM->getExitFlagStatus() == true) {
        MacUILib_printf("\nYou lost the game :( ");
    }  

    
    else if(myGM->getLoseFlagStatus() == false && myGM->getExitFlagStatus() == true)
    {
        MacUILib_printf("\nYay, you won! :)");
    }

    
}

void LoopDelay(void)
{
    MacUILib_Delay(myGM->getDelay());
    
}


void CleanUp(void)
{
    MacUILib_clearScreen();    

    delete myPlayer;
    myPlayer = nullptr;

    delete myGM;
    myGM = nullptr;

    MacUILib_uninit();
}
