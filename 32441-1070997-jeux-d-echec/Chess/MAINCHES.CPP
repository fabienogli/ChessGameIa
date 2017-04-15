#include "GameH.h"


void main()
{
   Mouse *M=new Mouse;
    M->Init();
    M->Hande();
   delete M;

   Screen *S=new Screen;
    S->Mode(0);
   delete S;

   Game *g;
   while(1)
   {
     g=new Game("./1");
     if(!g->Start())break;
     delete g;
   }
   delete g;
}