#include "GameH.h"
#include <graphics.h>

ChessDialog::ChessDialog(int x,int y,int width,int height,char *title,char * caption)
{
    X=x; Y=y;
    Width=width; Height=height;
    Title[0]=0; Caption[0]=0;
    strcpy(Title,title);
    strcpy(Caption,caption);
    BkImage=farmalloc(4+Width*Height);
    Mouse *M=new Mouse;
    M->Hide();
    getimage(X,Y,X+Width,Y+Height,BkImage);
    M->Show();
    Draw();
}

ChessDialog::~ChessDialog()
{
  Mouse *M=new Mouse;
  M->Hide();
  putimage(X,Y,BkImage,0);
  M->Show();
  farfree(BkImage);
}

void ChessDialog::Draw()
{
   int col,bkcol;
   Mouse *M=new Mouse;
   M->Hide();
   col=getcolor(); bkcol=getbkcolor();
   setcolor(1);
   setfillstyle(1,0);
   bar(X,Y,X+Width,Y+Height);
   setfillstyle(1,8);
   bar(X+1,Y+1,X+Width-1,Y+Height-1);
   setfillstyle(1,7);
   bar(X+2,Y+2,X+Width-2,Y+Height-2);
   setfillstyle(1,8);
   bar(X+2,Y+2,X+Width-2,Y+16);
   outtextxy(X+4,Y+8,Title);
   outtextxy(X+4,Y+8+16,Caption);
   setcolor(col); setfillstyle(1,bkcol);
   M->Show();
   delete M;
}

int ChessDialog::DoModel()
{
 return NO;
}
//***************************//
DialogPiece::DialogPiece(int x,int y,int width,int height,char *title,char * caption):
ChessDialog(x,y,width,height,title,caption)
{
    BQ=new ChessButton(X+4,Y+36+2,7*8,20,1,8," Queen");
    BT=new ChessButton(X+4,Y+36+2+22,7*8,20,1,8," Tower");
    BR=new ChessButton(X+4,Y+36+2+22+22,7*8,20,1,8," Rider");
    BM=new ChessButton(X+4,Y+36+2+22+22+22,7*8,20,1,8," Mad");
}

DialogPiece::~DialogPiece()
{
  if(BQ)delete BQ;
  if(BT)delete BT;
  if(BR)delete BR;
  if(BM)delete BM;
}

int DialogPiece::DoModel()
{
   while(1)
    {
      if(BQ->Click())return QUEEN;
      if(BT->Click())return TOWER;
      if(BR->Click())return RIDER;
      if(BM->Click())return MAD;
    }
}
//***************************//

DialogQuestion::DialogQuestion(int x,int y,int width,int height,char *title,char * caption)
:ChessDialog(x,y,width,height,title,caption)
{
    BYes=new ChessButton(X+4,Y+36+2,5*8,20,1,8," YES");
    BNo=new ChessButton(X+4+6*8,Y+36+2,5*8,20,1,8," NO");
}

DialogQuestion::~DialogQuestion()
{
  if(BYes)delete BYes;
  if(BNo)delete BNo;
}

int DialogQuestion::DoModel()
{
   while(1)
    {
      if(BYes->Click())return OK;
      if(BNo->Click())return NO;
    }
}
//***************************//
DialogDesign::DialogDesign(int x,int y,int width,int height,char *title,char * caption):
ChessDialog(x,y,width,height,title,caption)
{
    BStandard=new ChessButton(X+4,Y+36+2,12*8,20,1,8," Standard");
    BNew=new ChessButton(X+4,Y+36+2+22,12*8,20,1,8," New");
}

DialogDesign::~DialogDesign()
{
  if(BStandard)delete BStandard;
  if(BNew)delete BNew;
}

int DialogDesign::DoModel()
{
   while(1)
    {
      if(BStandard->Click())return 1;
      if(BNew->Click())return 2;
    }
}
//********************************//
DialogPlayer::DialogPlayer(int x,int y,int width,int height,char *title,char * caption)
:ChessDialog(x,y,width,height,title,caption)
{
    P1=HUMAIN; P2=HUMAIN;

    Name1=new ChessEdit(X+4,Y+36+2,12*8,20,1,8,"Player1");
	HO1=new ChessButton(X+4+12*8,Y+36+2,12*8,20,1,8,"Humain");

	Name2=new ChessEdit(X+4,Y+36+2+22,12*8,20,1,8,"Player2");
	HO2=new ChessButton(X+4+12*8,Y+36+2+22,12*8,20,1,8,"Humain");

	BOK=new ChessButton(X+4,Y+36+2+22+22,12*8,20,1,8," OK");
}
DialogPlayer::~DialogPlayer()
{
  if(BOK)delete BOK;
  if(HO1)delete HO1;
  if(HO2)delete HO2;
  if(Name1)delete Name1;
  if(Name2)delete Name2;
}

int DialogPlayer::DoModel()
{
  while(1)
  {
  if(Name1->Click())Name1->setText();
  if(Name2->Click())Name2->setText();
  if(HO1->Click())
  {
	if(P1==HUMAIN)
		{
		  P1=COMPUTER;
		  HO1->SetCaption("Computer");
		}
	else
	{
	  P1=HUMAIN;
	  HO1->SetCaption("Humain");
	}
  }
 if(HO2->Click())
  {
	if(P2==HUMAIN)
		{
		  P2=COMPUTER;
	  HO2->SetCaption("Computer");
		}
	else
	{
	  P2=HUMAIN;
	  HO2->SetCaption("Humain");
	}
  }
  if(BOK->Click())return OK;
  }
}