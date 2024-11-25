#include <iostream>
#include "MacUILib.h"
#include "objPos.h"

using namespace std;

#define DELAY_CONST 100000

bool exitFlag;
int i,j,p;
char input=0;


void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(exitFlag == false)  
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

    exitFlag = false;
}

void GetInput(void)
{
    if (MacUILib_hasChar()){
        input=MacUILib_getChar();
    }
    
   
}

void RunLogic(void)
{
   if (input==' '){
        exitFlag=true;
    } 
    
}

void DrawScreen(void)
{
    MacUILib_clearScreen();
    objPos part(10,5,'@');


    for (i=0; i<10; i++){
        for (j=0; j<20; j++){
            
            if (i==0|| i==9|| j==0|| j==19){
                cout<<"#";
            }

            else if (i== part.pos->y  && j== part.pos->x){
    
                cout<<part.symbol;

            }
            else{
                cout<<" ";
            }

            
        }
        MacUILib_printf("\n");
    }   
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    

    MacUILib_uninit();
}
