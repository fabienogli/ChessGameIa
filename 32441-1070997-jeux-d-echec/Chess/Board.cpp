// hessboard.cpp: implementation of the Chessboard class.
//
//////////////////////////////////////////////////////////////////////

#include "GameH.h"

#include <graphics.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------//

//char Board::Default_Board_Image[CHESSBOARD_WIDTH*10/2][CHESSBOARD_HEIGHT*10];
//------------------------------------------------------------------//

Board::Board()
{
  Height=0;
  the_game=NULL; // there is no game !!!
  Width =0;
  X=0; Y=0;
  Init_Image();
  Init_the_board();
  Draw();
}

Board::~Board()
{
  Destroy_Image();
  if(the_game)the_game->Chessboard_destroy();
}

Board::Board(const int x, const int y, const int width, const int height, Game * const game)
{
  Height=height;
  the_game=game;
  Width =width;
  X=x; Y=y;
  Init_Image();
  Init_the_board();
  Draw();
}

void Board::Draw()
{
  int colom,line;
  Screen s;
  Mouse M;	

  M.Hide();	
  s.Clear(9);
  s.Fill(X-Width/4,Y-Height/4,8*Width+Width/2,8*Height+Height/2,1);
  for(colom=0;colom<8;colom++)
   for(line=0;line<4;line++)
    {
      if(colom%2==0)
       {
	 s.getImage(X+(colom*Width),Y+(2*line*Height),Width,Height,Black_Image);
	 s.getImage(X+(colom*Width),Y+((2*line+1)*Height),Width,Height,White_Image);
       }
      else
       {
	 s.getImage(X+(colom*Width),Y+(2*line*Height),Width,Height,White_Image);
	 s.getImage(X+(colom*Width),Y+((2*line+1)*Height),Width,Height,Black_Image);
       }
    }
    //s.getImage(X-Width,Y-Height,10*Width,10*Height,Board_Image);
    settextstyle(0,0,1);
    outtextxy(X,Y-8,"  1    2    3    4    5    6    7    8");
    settextstyle(0,1,1);
    outtextxy(X,Y+8,"  A    B    C    D    E    F    G    H");
    settextstyle(0,0,1);
  M.Show();	
}

void Board::Init_Image()
{
   White_Image=(BitMap *)malloc(sizeof(BitMap));
   White_Image->Image=(char far *)Game::Default_White_Image;
   White_Image->X=X; White_Image->Y=Y;

   Black_Image=(BitMap *)malloc(sizeof(BitMap));
   Black_Image->Image=(char far *)Game::Default_Black_Image;
   Black_Image->X=X; Black_Image->Y=Y;
}

void Board::Destroy_Image()
{
  free(White_Image); farfree(Black_Image);
  //free(Board_Image);
}

void Board::Change_Piece(const int from_x,const int from_y,const int to_x,const int to_y)
{
 the_board[to_x][to_y]=the_board[from_x][from_y];
 if((to_x!=from_x)||(to_y!=from_y)) the_board[from_x][from_y]=0;
}
void Board::Put_Piece(const int x,const int y,const unsigned char the_player)
{
  the_board[x][y]=the_player;
}

void Board::Init_the_board()
{
  for(int i=0;i<8;i++)
   for(int j=0;j<8;j++)
    the_board[i][j]=0;
}

int Board::is_Adversery_in(const int x,const int y,unsigned char the_player)
{
  return ((the_board[x][y]!=the_player)&&(the_board[x][y]));
}
int Board::is_Mine_in(const int x,const int y,unsigned char the_player)
{
  return (the_board[x][y]==the_player);
}

int Board::is_Empty_in(const int x,const int y)
{
  return (!the_board[x][y]);
}
