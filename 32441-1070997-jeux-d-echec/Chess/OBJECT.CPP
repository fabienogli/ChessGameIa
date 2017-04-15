#include "GameH.h"
#include <graphics.h>
//***********************************************************************//
ChessButton::ChessButton()
{
 X=0; Y=0;
 Width=0; Height=0;
 Color=0; BkColor=0;
 Caption[0]=0;
}
ChessButton::ChessButton(int x,int y,int width,int height,int color,int bkcolor,char *caption)
{
 Caption[0]=0;
 X=x; Y=y;
 Width=width; Height=height;
 Color=color; BkColor=bkcolor;
 strcpy(Caption,caption);
 Draw();
}
ChessButton::~ChessButton()
{

}
int ChessButton::Click()
{
 int x,y,btn;
 Mouse M;
 M.getInformation(x,y,btn);
 if((btn==1)&&(x>=X)&&(x<X+Width)&&(y>=Y)&&(y<Y+Height))
  {
    BkColor=15-BkColor;
    Draw();
    while(btn==1)
     {
       M.getInformation(x,y,btn);
     }
    BkColor=15-BkColor;
    Draw();
    return OK;
  }
 return NO;
}
void ChessButton::Draw()
{
  int c;
  Mouse M;
  M.Hide();
  c=getcolor();
  setfillstyle(1,15-BkColor);
  bar(X,Y,X+Width,Y+Height);
  setfillstyle(1,BkColor);
  bar(X,Y,X+Width-2,Y+Height-2);
  setcolor(Color);
  outtextxy(X+4,Y+8,Caption);
  setcolor(c);
  M.Show();
}
void ChessButton::Validate()
{
  Draw();
}

void ChessButton::SetCaption(char *caption)
{
	Caption[0]=0; 
	strcpy(Caption,caption); 
	Draw();
}
//***********************************************************************//
ChessEdit::ChessEdit()
{
 X=0; Y=0;
 Width=0; Height=0;
 Color=0; BkColor=0;
 Text[0]=0;
}
ChessEdit::ChessEdit(int x,int y,int width,int height,int color,int bkcolor,char *text)
{
 Text[0]=0;
 strcpy(Text,text);
 X=x; Y=y;
 Width=width; Height=height;
 Color=color; BkColor=bkcolor;
 Draw();
}
ChessEdit::~ChessEdit()
{
}
void ChessEdit::setText()
{
 int ind;
 char car;

 Text[0]='-';
 Text[1]=0;
 car='-';  ind=0;
 while(1)
  {
    Draw();
    car=getch();
    if((car==13)||(car==27))break;
    if(car==8)
     {
       if(ind>0)
	{
	  Text[ind]=0;
	  ind--; Text[ind]='-';
	}
     }
    if(ind<(Width-2-4)/8)
     {
       if((car>='a')&&(car<='z')||(car>='A')&&(car<='Z')||(car==' ')||((car>32)&&(car<58)))
	{
	  Text[ind]=car; ind++;
	  Text[ind]='-'; Text[ind+1]=0;
	}
     }
     if(car==0)car=getch(); car=0;
  }
  Text[ind]=0;
  Draw();
}
void ChessEdit::getText(char *text)
{
  text[0]=0;
  strcpy(text,Text);
}

void ChessEdit::Draw()
{
  int c;
  Mouse M;
  M.Hide();
  c=getcolor();
  setfillstyle(1,15-BkColor);
  bar(X,Y,X+Width,Y+Height);
  setfillstyle(1,BkColor);
  bar(X+2,Y+2,X+Width-2,Y+Height-2);
  setcolor(Color);
  outtextxy(X+4,Y+8,Text);
  setcolor(c);
  M.Show();
}

int ChessEdit::Click()
{
 int x,y,btn;
 Mouse M;
 M.getInformation(x,y,btn);
 return((btn==1)&&(x>=X)&&(x<X+Width)&&(y>=Y)&&(y<Y+Height));
}

void ChessEdit::Validate()
{
  Draw();
}