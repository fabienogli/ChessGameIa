// Game.cpp: implementation of the Game class.
//
//////////////////////////////////////////////////////////////////////

#include "GameH.h"

#include <dir.h>
#include <graphics.h>


//******************************************************************//
//******************************************************************//
unsigned char Game::Default_White_Image[CHESSBOARD_WIDTH/2][CHESSBOARD_HEIGHT];
unsigned char Game::Default_Black_Image[CHESSBOARD_WIDTH/2][CHESSBOARD_HEIGHT];


unsigned char Game::Default_Player1_Image[CHESSBOARD_WIDTH/2][CHESSBOARD_HEIGHT];
unsigned char Game::Default_Player2_Image[CHESSBOARD_WIDTH/2][CHESSBOARD_HEIGHT];

unsigned char Game::Default_Piece_Image[CHESSBOARD_WIDTH/2][CHESSBOARD_HEIGHT];

unsigned char Game::Default_Pawn_Image2[CHESSBOARD_WIDTH/2][CHESSBOARD_HEIGHT];
unsigned char Game::Default_Tower_Image2[CHESSBOARD_WIDTH/2][CHESSBOARD_HEIGHT];
unsigned char Game::Default_Rider_Image2[CHESSBOARD_WIDTH/2][CHESSBOARD_HEIGHT];
unsigned char Game::Default_Mad_Image2[CHESSBOARD_WIDTH/2][CHESSBOARD_HEIGHT];
unsigned char Game::Default_King_Image2[CHESSBOARD_WIDTH/2][CHESSBOARD_HEIGHT];
unsigned char Game::Default_Queen_Image2[CHESSBOARD_WIDTH/2][CHESSBOARD_HEIGHT];

unsigned char Game::Default_Pawn_Image1[CHESSBOARD_WIDTH/2][CHESSBOARD_HEIGHT];
unsigned char Game::Default_Tower_Image1[CHESSBOARD_WIDTH/2][CHESSBOARD_HEIGHT];
unsigned char Game::Default_Rider_Image1[CHESSBOARD_WIDTH/2][CHESSBOARD_HEIGHT];
unsigned char Game::Default_Mad_Image1[CHESSBOARD_WIDTH/2][CHESSBOARD_HEIGHT];
unsigned char Game::Default_King_Image1[CHESSBOARD_WIDTH/2][CHESSBOARD_HEIGHT];
unsigned char Game::Default_Queen_Image1[CHESSBOARD_WIDTH/2][CHESSBOARD_HEIGHT];
//******************************************************************//
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Game::Game()
{
  Load_Ressource("./1/");
  chessboard = new Board(CHESSBOARD_LEFT,CHESSBOARD_TOP,CHESSBOARD_WIDTH,CHESSBOARD_HEIGHT,this);
  player1 = new Player(PLAYER1," PLAYER1",this,CHESSBOARD_LEFT-3*CHESSBOARD_WIDTH,CHESSBOARD_TOP+40);
  player2 = new Player(PLAYER2,"PLAYER2",this,CHESSBOARD_LEFT+9*CHESSBOARD_WIDTH,CHESSBOARD_TOP+40);
  my_stack=new Stack;
  setcolor(15);
  setfillstyle(1,0);
  bar(2,2,getmaxx()-2,18);
  setfillstyle(1,8);
  bar(4,4,getmaxx()-4,16);
  outtextxy(10,8,"       CHESS V 1.0                < E.O.A: HABBOUCHI Ahmed !>");
  setfillstyle(1,0);
  bar(2,450,getmaxx()-2,450+18);
  setfillstyle(1,8);
  bar(4,450+2,getmaxx()-4,450+16);
  outtextxy(6,450+2+6," ESC: Quit         R: Replay         N: Name        D: Design");
}

Game::~Game()
{
 if(player1) delete player1;
 if(player2) delete player2;
 if(chessboard) delete chessboard;
 delete my_stack;
}

void Game::Chessboard_destroy()
{
 chessboard=NULL;
}

void Game::Player_destroy(const int ident)
{
	if(ident==PLAYER1){player1=NULL;}
	if(ident==PLAYER2){player2=NULL;}
}

Game::Game(char * Dir_Name)
{
  int P1,P2;
  char name_player1[20],name_player2[20];

  Load_Ressource(Dir_Name);
  chessboard = new Board(CHESSBOARD_LEFT,CHESSBOARD_TOP,CHESSBOARD_WIDTH,CHESSBOARD_HEIGHT,this);

  DialogPlayer * DP = new DialogPlayer(50,200,260,110,"PLAYERS","Name && Kind");
	DP->DoModel();
    DP->Name1->getText(name_player1);
	DP->Name2->getText(name_player2);
	P1 = DP->P1; P2= DP->P2;
  delete DP;

  if((P1==HUMAIN)||(P2==HUMAIN))Save=OK;
  else Save=NO;

  if(P1==COMPUTER)
	  player1 = new OPlayer(PLAYER1,name_player1,this,CHESSBOARD_LEFT-3*CHESSBOARD_WIDTH,CHESSBOARD_TOP+40);
  else
	  player1 = new HPlayer(PLAYER1,name_player1,this,CHESSBOARD_LEFT-3*CHESSBOARD_WIDTH,CHESSBOARD_TOP+40);
  if(P2==COMPUTER)
	player2 = new OPlayer(PLAYER2,name_player2,this,CHESSBOARD_LEFT+9*CHESSBOARD_WIDTH,CHESSBOARD_TOP+40);
  else
    player2 = new HPlayer(PLAYER2,name_player2,this,CHESSBOARD_LEFT+9*CHESSBOARD_WIDTH,CHESSBOARD_TOP+40);

  my_stack=new Stack;
  setcolor(15);
  setfillstyle(1,0);
  bar(2,2,getmaxx()-2,18);
  setfillstyle(1,8);
  bar(4,4,getmaxx()-4,16);
  outtextxy(10,8,"       CHESS V 1.0                < E.O.A: HABBOUCHI Ahmed !>");
  setfillstyle(1,0);
  bar(2,450,getmaxx()-2,450+18);
  setfillstyle(1,8);
  bar(4,450+2,getmaxx()-4,450+16);
  outtextxy(6,450+2+6," ESC: Quit         R: Replay         N: Name        D: Design");
}

int Game::Start()
{
   int Game_State;
   char message[20]={0};
   int Chose;

  // the game begining
  Game_State = GAME_FINE; // we are just in the begin'n !!!
  while(Game_State == GAME_FINE)
   {

     if((!player1)||(!player2)||(!chessboard))
      {
	 // ERROR !!!
	 Game_State = GAME_ERROR;
	 break;
      }
       Game_State=player1->Play();
      if(Game_State == GAME_FINE)
       {
	 Game_State=player2->Play();
       }
   }
   switch(Game_State)
    {
      case GAME_ERROR:
	    // there is an error !!!
	    strcpy(message,"ERROR !!!");
	    break;
      case PLAYER1_ABORT_GAME:
	   // PLAYER1 gave-up !!!
	    strcpy(message,"PLAYER1 ABORT GAME");
	    break;
      case PLAYER2_ABORT_GAME:
	   // PLAYER2 gave-up !!!
	    strcpy(message,"PLAYER2 ABORT GAME");
	    break;
      case PLAYER1_WON:
	   // PLAYER1 won !!!
	    strcpy(message,"PLAYER1 WON");
	    break;
      case PLAYER2_WON:
	   // PLAYER2 won !!!
	    strcpy(message,"PLAYER2 WON");
	    break;
    }
    DialogQuestion *D = new DialogQuestion(10,200,150,80,message,"Play again ?");
     Chose = D->DoModel();
    delete D;
    return Chose;
}

void Game::Change_Piece(const int form_x,const int form_y,const int to_x,const int to_y)
{
  chessboard->Change_Piece(form_x,form_y,to_x,to_y);
}

void Game::Put_Piece(const int x,const int y,const unsigned char the_player)
{
   chessboard->Put_Piece(x,y,the_player);
}

int Game::is_Adversery_in(const int x,const int y,unsigned char the_player)
{
  return chessboard->is_Adversery_in(x,y,the_player);
}
int Game::is_Mine_in(const int x,const int y,unsigned char the_player)
{
  return chessboard->is_Mine_in(x,y,the_player);
}
int Game::is_Empty_in(const int x,const int y)
{
  return chessboard->is_Empty_in(x,y);
}

int Game::Player_Take_XY(const int x,const int y,const int ident)
{
  int Aux;
  switch(ident)
   {
     case PLAYER1:
		   Aux=player2->Out_Side_Piece(x,y);
		  break;
     case PLAYER2:
		   Aux=player1->Out_Side_Piece(x,y);
		  break;
   }
   Put_Piece(x,y,ident);
   return Aux;
}

int Game::is_King_in(const int x,const int y,const int iden)
{
  if(iden==PLAYER1)return player1->is_my_King_in(x,y);
  return player2->is_my_King_in(x,y);
}

int Game::Echec(int iden)
{
  if(iden==PLAYER1)return player2->Echec();
  return player1->Echec();
}

int Game::Out_Side_Piece(const int x,const int y,const int iden)
{
  if(iden==PLAYER1)return player2->Out_Side_Piece(x,y);
  return player1->Out_Side_Piece(x,y);
}
int Game::In_Side_Piece(const int x,const int y,const int iden)
{
  if(iden==PLAYER1)return player2->In_Side_Piece(x,y);
  return player1->In_Side_Piece(x,y);
}

int Game::In_Side_Piece(const int x,const int y,const int kind,const int iden)
{
  if(iden==PLAYER1)return player2->In_Side_Piece(x,y,kind);
  return player1->In_Side_Piece(x,y,kind);
}

int Game::Out_Side_Piece_Temp(const int x,const int y,const int iden)
{
  if(iden==PLAYER1)return player2->Out_Side_Piece_Temp(x,y);
  return player1->Out_Side_Piece_Temp(x,y);
}
int Game::In_Side_Piece_Temp(const int x,const int y,const int iden)
{
  if(iden==PLAYER1)return player2->In_Side_Piece_Temp(x,y);
  return player1->In_Side_Piece_Temp(x,y);
}

int Game::Replay(const int iden)
{
  if(iden==PLAYER1)return player2->Replay();
  return player1->Replay();
}

int Game::getKind(int iden,int x,int y)
{
  if(iden==PLAYER1)return player2->getKind(x,y);
  return player1->getKind(x,y);
}

int Game::getLast_Movment(int &from_x,int &from_y,int &to_x,int &to_y,int &kind,int &kind_c)
{
  return my_stack->Pop(from_x,from_y,to_x,to_y,kind,kind_c);
}

void Game::Add_Movment(int X_From,int Y_From,int X_To,int Y_To,int kind,int kind_c)
{
  my_stack->Push(X_From,Y_From,X_To,Y_To,kind,kind_c);
}

void Game::Load_Ressource(char *Dir)
{
   char far * Ptr_Image;
   char * Ldir=new char[256];
      getcwd(Ldir,255);
      chdir(Dir);

      Screen *S=new Screen;

      Ptr_Image=(char far *)Default_White_Image;
      S->LoadBmpToRC(Ptr_Image,"White.bmp");
      Ptr_Image=(char far *)Game::Default_Black_Image;
      S->LoadBmpToRC(Ptr_Image,"Black.bmp");

      Ptr_Image=(char far *)Game::Default_Pawn_Image1;
      S->LoadBmpToRC(Ptr_Image,"Pawn1.bmp");
      Ptr_Image=(char far *)Game::Default_Tower_Image1;
      S->LoadBmpToRC(Ptr_Image,"Tower1.bmp");
      Ptr_Image=(char far *)Game::Default_Rider_Image1;
      S->LoadBmpToRC(Ptr_Image,"Rider1.bmp");
      Ptr_Image=(char far *)Game::Default_Mad_Image1;
      S->LoadBmpToRC(Ptr_Image,"Mad1.bmp");
      Ptr_Image=(char far *)Game::Default_King_Image1;
      S->LoadBmpToRC(Ptr_Image,"King1.bmp");
      Ptr_Image=(char far *)Game::Default_Queen_Image1;
      S->LoadBmpToRC(Ptr_Image,"Queen1.bmp");

      Ptr_Image=(char far *)Game::Default_Pawn_Image2;
      S->LoadBmpToRC(Ptr_Image,"Pawn2.bmp");
      Ptr_Image=(char far *)Game::Default_Tower_Image2;
      S->LoadBmpToRC(Ptr_Image,"Tower2.bmp");
      Ptr_Image=(char far *)Game::Default_Rider_Image2;
      S->LoadBmpToRC(Ptr_Image,"Rider2.bmp");
      Ptr_Image=(char far *)Game::Default_Mad_Image2;
      S->LoadBmpToRC(Ptr_Image,"Mad2.bmp");
      Ptr_Image=(char far *)Game::Default_King_Image2;
      S->LoadBmpToRC(Ptr_Image,"King2.bmp");
      Ptr_Image=(char far *)Game::Default_Queen_Image2;
      S->LoadBmpToRC(Ptr_Image,"Queen2.bmp");

      Ptr_Image=(char *)Game::Default_Player1_Image;
      S->LoadBmpToRC(Ptr_Image,"Player1.bmp");
      Ptr_Image=(char *)Game::Default_Player2_Image;
      S->LoadBmpToRC(Ptr_Image,"Player2.bmp");

    chdir(Ldir);
    if (Ldir)delete[] Ldir;
    delete S;
}

void Game::Validate()
{
    Mouse *M=new Mouse;
    M->Hide();
    chessboard->Draw();
    player1->Validate();
    player2->Validate();
    setcolor(15);
    setfillstyle(1,0);
    bar(2,2,getmaxx()-2,18);
    setfillstyle(1,8);
    bar(4,4,getmaxx()-4,16);
    outtextxy(10,8,"       CHESS V 1.0                < E.O.A: HABBOUCHI Ahmed !>");
    setfillstyle(1,0);
    bar(2,450,getmaxx()-2,450+18);
    setfillstyle(1,8);
    bar(4,450+2,getmaxx()-4,450+16);
    outtextxy(6,450+2+6," ESC: Quit         R: Replay         N: Name         D: Design");
    M->Show();
    delete M;
}

void Game::Change_Ressource()
{
  char Dir[6]="./";
  int Chose;

    DialogDesign *D = new DialogDesign(200,200,150,100,"Design","Witch One?");
     Chose = D->DoModel();
    delete D;
  Dir[2]=(char)Chose+'0';
  Dir[3]=0;
  Load_Ressource(Dir);
  Validate();
}

int Game::Echec_And_Mate(int iden)
{
  if(iden==PLAYER1)return player2->Echec_And_Mate_To_Me();
  return player1->Echec_And_Mate_To_Me();
}

int Game::getMax(int iden)
{
  if(iden==PLAYER1)return player2->getMax();
  return player1->getMax();
}