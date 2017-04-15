// Piece.cpp: implementation of the Piece class.
//
//////////////////////////////////////////////////////////////////////

#include "GameH.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


Piece::Piece()
{
	identifier_for_my_owner=0;
	my_owner=NULL;
	Name[0]=0; // my name is "" !!!
	X=0; Y=0;
	Piece_Image;
	Back_Ground;
	Kind=NO_PIECE;
	Out=OK;
	Moved=0;
	my_owner->Piece_In();
	XS=CHESSBOARD_LEFT+(CHESSBOARD_WIDTH*X );
	YS=CHESSBOARD_TOP +(CHESSBOARD_HEIGHT*Y);

	Piece_Image=(BitMap *)malloc(sizeof(BitMap));
	Piece_Image->Image=(char far *)Game::Default_Piece_Image;
	Piece_Image->X=CHESSBOARD_WIDTH; Piece_Image->Y=CHESSBOARD_HEIGHT;

	Back_Ground=(BitMap *)malloc(sizeof(BitMap));
	Back_Ground->Image=(unsigned char far *)farmalloc(CHESSBOARD_WIDTH*CHESSBOARD_HEIGHT);
	Back_Ground->X=CHESSBOARD_WIDTH; Back_Ground->Y=CHESSBOARD_HEIGHT;

	Draw();
}


Piece::~Piece()
{
	free(Piece_Image); free(Back_Ground);
	if(my_owner) my_owner->Piece_Die(identifier_for_my_owner);
}

Piece::Piece(const int ident,  Player *owner, const char *name,const int kind,const int x, const int y)
{
	identifier_for_my_owner=ident;
	my_owner=owner;
	strcpy(Name,name); // my name is "" !!!
	X=x; Y=y;
	XS=CHESSBOARD_LEFT+(CHESSBOARD_WIDTH*X );
	YS=CHESSBOARD_TOP +(CHESSBOARD_HEIGHT*Y);
	Kind=kind;
	my_owner->Put_Piece(X,Y);
	Out=NO;
	Out_T=NO;
	Moved=0;
	my_owner->Piece_In();
	Piece_Image=(BitMap *)malloc(sizeof(BitMap));
	if(my_owner->getIdentifier()==PLAYER1)
	 {
	switch(Kind)
	 {
	   case PAWN :
		  //change the image !!!
		  Piece_Image->Image=(char far *)Game::Default_Pawn_Image1;
		  break;
	   case TOWER:
		  //change the image !!!
		  Piece_Image->Image=(char far *)Game::Default_Tower_Image1;
		  break;
	   case RIDER:
		  //change the image !!!
		  Piece_Image->Image=(char far *)Game::Default_Rider_Image1;
		 break;
	   case MAD  :
		  //change the image !!!
		  Piece_Image->Image=(char far *)Game::Default_Mad_Image1;
		 break;
	   case KING :
		  //change the image !!!
		  Piece_Image->Image=(char far *)Game::Default_King_Image1;
		 break;
	   case QUEEN:
		  //change the image !!!
		  Piece_Image->Image=(char far *)Game::Default_Queen_Image1;
		 break;
	   default:
		  //change the image !!!
		  Piece_Image->Image=(char far *)Game::Default_Piece_Image;
	 }
	 }
	 else
	 {
	switch(Kind)
	 {
	   case PAWN :
		  //change the image !!!
		  Piece_Image->Image=(char far *)Game::Default_Pawn_Image2;
		 break;
	   case TOWER:
		  //change the image !!!
		  Piece_Image->Image=(char far *)Game::Default_Tower_Image2;
		 break;
	   case RIDER:
		  //change the image !!!
		  Piece_Image->Image=(char far *)Game::Default_Rider_Image2;
		 break;
	   case MAD  :
		  //change the image !!!
		  Piece_Image->Image=(char far *)Game::Default_Mad_Image2;
		 break;
	   case KING :
		  //change the image !!!
		  Piece_Image->Image=(char far *)Game::Default_King_Image2;
		 break;
	   case QUEEN:
		  //change the image !!!
		  Piece_Image->Image=(char far *)Game::Default_Queen_Image2;
		 break;
	   default:
		  //change the image !!!
		  Piece_Image->Image=(char far *)Game::Default_Piece_Image;
	 }

	 }

	Piece_Image->X=CHESSBOARD_WIDTH; Piece_Image->Y=CHESSBOARD_HEIGHT;

	Back_Ground=(BitMap *)malloc(sizeof(BitMap));
	Back_Ground->Image=(unsigned char far *)farmalloc(CHESSBOARD_WIDTH*CHESSBOARD_HEIGHT);
	Back_Ground->X=CHESSBOARD_WIDTH; Back_Ground->Y=CHESSBOARD_HEIGHT;

	Draw();
}

char * Piece::getName()
{
	return Name;
}

int Piece::is_Me(const int x,const int y)
{
  int xs,ys;
  if((Out)||(Out_T))return NO;
  xs=(x-CHESSBOARD_LEFT)/CHESSBOARD_WIDTH;
  ys=(y-CHESSBOARD_TOP )/CHESSBOARD_HEIGHT;
  return((xs==X)&&(ys==Y));
}

int Piece::is_King()
{
  if((Out)||(Out_T))return NO;
  return(Kind==KING);
}

int Piece::is_King(const int x,const int y)
{
  if((Out)||(Out_T))return NO;
  return((X==x)&&(Y==y)&&(Kind==KING));
}

void Piece::setXY(const int x,const int y)
{
   if((Out)||(Out_T))return;	
  X=x; Y=y;
}
void Piece::getXY(int &x,int &y)
{
  x=X; y=Y;
}

void Piece::setXSYS(const int x,const int y)
{
   if((Out)||(Out_T))return;
	XS=x; YS=y;
}
void Piece::getXSYS(int &x,int &y)
{
  x=XS; y=YS;
}

int Piece::setScreen_Position(const int x,const int y)
{
  if((Out)||(Out_T))return OK;
  if((XS!=x)||(YS!=y))
  {
  //--------------------//
   Redraw();
  //-------------------//
   XS=x; YS=y;
  //-------------------//
    Draw();
  //-------------------//
  return NO;
  }
 return OK;
}

int Piece::Assert_Position()
{
  int x_aux,y_aux,xs_aux,ys_aux;
  x_aux=CHESSBOARD_LEFT+(CHESSBOARD_WIDTH*X);
  y_aux=CHESSBOARD_TOP +(CHESSBOARD_HEIGHT*Y);
  xs_aux=XS; ys_aux=YS;
  setScreen_Position(x_aux,y_aux);
  return((x_aux==xs_aux)&&(y_aux==ys_aux));
}

int Piece::is_Ok_to_take_XSYS()
{
  int x,y;
  if(!my_owner)return NO;
  if((Out)||(Out_T))return NO;
  if((XS<CHESSBOARD_LEFT)||(YS<CHESSBOARD_TOP))return NO;
  //X=(XS-CHESSBOARD_LEFT)/CHESSBOARD_WIDTH;
  //Y=(YS-CHESSBOARD_TOP )/CHESSBOARD_HEIGHT;
  x=(XS-CHESSBOARD_LEFT)/CHESSBOARD_WIDTH;
  y=(YS-CHESSBOARD_TOP )/CHESSBOARD_HEIGHT;

  if((x>7)||(y>7))return NO;
  return OK; //Assert_Position();
}

void Piece::Draw()
{
	Screen *s=new Screen;
	Mouse  *m=new Mouse;
	m->Hide();
	s->setImage(XS,YS,CHESSBOARD_WIDTH,CHESSBOARD_HEIGHT,Back_Ground);
	s->getImage_Transparent(XS,YS,CHESSBOARD_WIDTH,CHESSBOARD_HEIGHT,Piece_Image);
	m->Show();
	delete m;
	delete s;
}

void Piece::Redraw()
{
	Screen *s=new Screen;
	Mouse  *m=new Mouse;
	m->Hide();
	s->getImage(XS,YS,CHESSBOARD_WIDTH,CHESSBOARD_HEIGHT,Back_Ground);
	m->Show();
	delete m;
	delete s;
}

void Piece::Go_out()
{
  if(!Out)
   {
     Redraw();
     Out=OK;
     my_owner->Piece_Out();
   }
}

void Piece::Go_out_Temp()
{
  if(!Out)
  Out_T=OK;
}

int Piece::Go_in()
{
  if(Out)
   {
     Out=NO;
     Out_T=NO;
     my_owner->Put_Piece(X,Y);
     Draw();
     my_owner->Piece_In();
     return OK;
   }
  return NO;
}

int Piece::Go_in(const int x,const int y)
{
if((Out)||(X==x)&&(Y==y))
 {
   Out=NO;
   Out_T=NO;
   my_owner->Put_Piece(X,Y);
   Draw();
   my_owner->Piece_In();
   return OK;
 }
 return NO;
}

int Piece::Go_in(const int x,const int y,const int kind)
{
if((Out)&&(X==x)&&(Y==y)&&(Kind==kind))
 {
   Out=NO;
   Out_T=NO;
   my_owner->Put_Piece(X,Y);
   Draw();
   my_owner->Piece_In();
   return OK;
 }
 return NO;
}

int Piece::Go_in_Temp(const int x,const int y)
{
 if((!Out)&&(Out_T)&&(X==x)&&(Y==y))
  {
    Out_T=NO;
    my_owner->Put_Piece(X,Y);
    return OK;
  }
  return NO;
}

void Piece::Take(const int x,const int y)
{
  my_owner->Change_Piece(X,Y,x,y);
  X=x; Y=y;
  Assert_Position();
}

int Piece::NO_Echec(int x_test,int y_test)
{
  int X_T,Y_T,if_in;

  if((Out)||(Out_T))return NO;
  X_T=X; Y_T=Y;
  if_in=my_owner->Out_Side_Adversery_Piece_Temp(x_test,y_test);
  my_owner->Change_Piece(X,Y,x_test,y_test);
  X=x_test; Y=y_test;
   if(my_owner->Echec_To_Me())
    {
	X=X_T; Y=Y_T;
	my_owner->Change_Piece(x_test,y_test,X,Y);
	if(if_in)my_owner->In_Side_Adversery_Piece_Temp(x_test,y_test);
	return NO;
    }
  X=X_T; Y=Y_T;
  my_owner->Change_Piece(x_test,y_test,X,Y);
  if(if_in)my_owner->In_Side_Adversery_Piece_Temp(x_test,y_test);

  return OK;
}

int Piece::getKind()
{
 return Kind;
}

void Piece::Validate()
{
 if(!Out)Draw();
}

int Piece::Tower_Not_Moved()
{
  return NO;
} //just for the tower !!!

int Piece::Can_Play()
{
  int x,y;
  return(getMax(x,y)!=-1000);
}

int Piece::getMax(int &x,int &y)
{
 return -1000;
}
int Piece::TakeOn(int &X_T,int &Y_T,int x_test, int y_test)
{
  int if_in;

  X_T=X; Y_T=Y;
  if_in=my_owner->Out_Side_Adversery_Piece_Temp(x_test,y_test);
  my_owner->Change_Piece(X,Y,x_test,y_test);
  X=x_test; Y=y_test;
return if_in;
}

void Piece::TakeOff(int X_T,int Y_T,int x_test, int y_test,int if_in)
{
	X=X_T; Y=Y_T;
	my_owner->Change_Piece(x_test,y_test,X,Y);
	if(if_in)my_owner->In_Side_Adversery_Piece_Temp(x_test,y_test);
}

//---------------------------------------------------------------------//
//                          the real pieces                            //
//---------------------------------------------------------------------//

Pawn::Pawn(const int ident,Player * owner, const char *name,const int x,int const y):
Piece(ident,owner,name,PAWN,x,y)
{
}
Pawn::~Pawn()
{

}

int Pawn::is_Ok_to_take_XSYS()
{
  int x_test,y_test,X_T,Y_T;


  if(!(Piece::is_Ok_to_take_XSYS())){Assert_Position();return NO;}
  x_test=(XS-CHESSBOARD_LEFT)/CHESSBOARD_WIDTH;
  y_test=(YS-CHESSBOARD_TOP )/CHESSBOARD_HEIGHT;

	if(Advance(x_test,y_test)||(First_Advance(x_test,y_test))||(Eat(x_test,y_test)))
	 { //if fine !
		if(!(Piece::NO_Echec(x_test,y_test)))return Assert_Position();
		X_T=X; Y_T=Y;
		X=x_test;
		Y=y_test;
		Assert_Position();
		if(my_owner->I_Take_XY(X,Y))Draw();
		my_owner->Change_Piece(X_T,Y_T,x_test,y_test);
		if((X==0)||(X==7))my_owner->Change_Pawn(identifier_for_my_owner,X,Y);
		Moved++;
		return OK;
	 }
	return Assert_Position();
}
int Pawn::Advance(const int x,const int y)
{
  int direction;
  direction=-1;//the second player !!!
  if(my_owner->getIdentifier()==PLAYER1)direction=1;

  return ((x==X+direction)&&(y==Y)&&(my_owner->is_Empty_in(x,y)));
}

int Pawn::First_Advance(const int x,const int y)
{
  int direction;
  int exception_X;
  direction=-1; exception_X=6;//the second player !!!
  if(my_owner->getIdentifier()==PLAYER1){ direction=1; exception_X=1;}
  return((x==X+2*direction)&&(X==exception_X)&&(y==Y)&&(my_owner->is_Empty_in(x,y))&&(my_owner->is_Empty_in(x-direction,y)));
}
int Pawn::Eat(const int x,const int y)
{
  int direction;
  direction=-1;//the second player !!!
  if(my_owner->getIdentifier()==PLAYER1)direction=1;
  return((x==X+direction)&&((y==Y+1)||(y==Y-1))&&(my_owner->is_Adversery_in(x,y)));
}

int Pawn::getMax(int &x,int &y)
{
	 int MAX,max_t;
	int direction;

  if((Out)||(Out_T))return -1000;
  MAX=max_t=-1000;
  direction=-1;//the second player !!!
  if(my_owner->getIdentifier()==PLAYER1)direction=1;
  if(Advance(X+direction,Y))if(NO_Echec(X+direction,Y)){x=X+direction;y=Y;MAX=0; max_t=0;}
  if((X==1)||(X==6))
  {
	if(First_Advance(X+2*direction,Y))if(NO_Echec(X+2*direction,Y)){x=X+2*direction;y=Y;MAX=0;max_t=0;}
  }
  if(Y<7)
  {
	if(Eat(X+direction,Y+1))if(NO_Echec(X+direction,Y+1)){x=X+direction;y=Y+1;MAX=my_owner->getPiece_Value(X+direction,Y+1); max_t=MAX;}
  }
  if(Y>0)
  {
	if(Eat(X+direction,Y-1))if(NO_Echec(X+direction,Y-1)){max_t=my_owner->getPiece_Value(X+direction,Y-1);
		if(MAX<max_t){x=X+direction;y=Y-1; MAX=max_t;}}
  }
  return MAX;
}


int Pawn::getMaxAbs(int &x,int &y)
{
	 int Max,max_t,max_t2;
	int direction;
	int temp_x,temp_y;
	int if_in,X_T,Y_T;

  if((Out)||(Out_T))return -1000;
  Max=max_t=max_t2=-1000;
  direction=-1;//the second player !!!
  if(my_owner->getIdentifier()==PLAYER1)direction=1;

  if(Advance(X+direction,Y))if(NO_Echec(X+direction,Y))
	 {
		  temp_x=X+direction; temp_y=Y;
		  if_in=TakeOn(X_T,Y_T,temp_x,temp_y);
		  max_t=0; max_t2=my_owner->getMaxAdv();
		  if(Max<=max_t-max_t2)
		  {x=X;y=Y;Max=max_t-max_t2;}
		  TakeOff(X_T,Y_T,temp_x,temp_y,if_in);
	 }
  if((X==1)||(X==6))
  {
	if(First_Advance(X+2*direction,Y))if(NO_Echec(X+2*direction,Y))
	 {
		//x=X+2*direction;y=Y;MAX=0;max_t=0;
		  temp_x=X+2*direction; temp_y=Y;
		  if_in=TakeOn(X_T,Y_T,temp_x,temp_y);
		  max_t=0; max_t2=my_owner->getMaxAdv();
		  if(Max<=max_t-max_t2)
		  {x=X;y=Y;Max=max_t-max_t2;}
		  TakeOff(X_T,Y_T,temp_x,temp_y,if_in);
	 }
  }
  if(Y<7)
  {
	if(Eat(X+direction,Y+1))if(NO_Echec(X+direction,Y+1))
	 {
		//x=X+direction;y=Y+1;
		  max_t=my_owner->getPiece_Value(X+direction,Y+1);
		  temp_x=X+direction; temp_y=Y+1;
		  if_in=TakeOn(X_T,Y_T,temp_x,temp_y);
		  max_t2=my_owner->getMaxAdv();
		  if(Max<=max_t-max_t2)
		  {x=X;y=Y;Max=max_t-max_t2;}
		  TakeOff(X_T,Y_T,temp_x,temp_y,if_in);
	 }
  }
  if(Y>0)
  {
	if(Eat(X+direction,Y-1))if(NO_Echec(X+direction,Y-1))
	{
		  max_t=my_owner->getPiece_Value(X+direction,Y-1);
		  temp_x=X+direction; temp_y=Y-1;
		  if_in=TakeOn(X_T,Y_T,temp_x,temp_y);
		  max_t2=my_owner->getMaxAdv();
		  if(Max<=max_t-max_t2)
		  {x=X;y=Y;Max=max_t-max_t2;}
		  TakeOff(X_T,Y_T,temp_x,temp_y,if_in);
	 }
  }
  return Max;
}

int Pawn::Echec()
{
  int direction;

  if((Out)||(Out_T))return NO;
  direction=-1;//the second player !!!
  if(my_owner->getIdentifier()==PLAYER1)direction=1;
  return((my_owner->is_Adversery_King_in(X+direction,Y+1))||(my_owner->is_Adversery_King_in(X+direction,Y-1)));
}

Tower::Tower(const int ident,Player * owner, const char *name,const int x,int const y):
Piece(ident,owner,name,TOWER,x,y)
{
}

Tower::~Tower()
{

}

int Tower::is_Ok_to_take_XSYS()
{
  int x_test,y_test;
  int X_T,Y_T;

  if(!(Piece::is_Ok_to_take_XSYS())){Assert_Position();return NO;}

  x_test=(XS-CHESSBOARD_LEFT)/CHESSBOARD_WIDTH;
  y_test=(YS-CHESSBOARD_TOP )/CHESSBOARD_HEIGHT;
  if(my_owner->is_Mine_in(x_test,y_test))return Assert_Position();

  if(Move()==NO){Assert_Position();return NO;}
  //if fine !

  X_T=X; Y_T=Y;
  X=x_test;
  Y=y_test;
  Assert_Position();
  if(my_owner->I_Take_XY(X,Y))Draw();
  my_owner->Change_Piece(X_T,Y_T,x_test,y_test);
  Moved++;
  return OK;
}
int Tower::Move()
{
  int x_test,y_test,direction;
  int index;

  x_test=(XS-CHESSBOARD_LEFT)/CHESSBOARD_WIDTH;
  y_test=(YS-CHESSBOARD_TOP )/CHESSBOARD_HEIGHT;
  if((X!=x_test)&&(Y!=y_test))return NO;
  direction=1;
  if(X==x_test)
	{
	  index=Y;
	  if(Y>y_test)direction=-1;
	  index=index+direction;
	  while(direction*index<direction*y_test)
		{
	 if(!my_owner->is_Empty_in(x_test,index))break;
	 index=direction+index;
		}
		if(index!=y_test) return NO;
	}
  else
	{
	  index=X;
	  if(X>x_test)direction=-1;
	  index=index+direction;
	  while(direction*index<direction*x_test)
		{
	 if(!my_owner->is_Empty_in(index,y_test))break;
	 index=index+direction;
		}
		if(index!=x_test) return NO;
	}
  if(!Piece::NO_Echec(x_test,y_test))return NO;
  return OK;
}

int Tower::getMax(int &x,int &y)
{
	 int MAX,max_t;
	int temp;

if((Out)||(Out_T))return -1000;
  MAX=-1000;
  max_t=-1000;
  temp=X-1;
  while(temp>=0)
  {
	if(!my_owner->is_Mine_in(temp,Y))if(NO_Echec(temp,Y)){max_t=my_owner->getPiece_Value(temp,Y);if(MAX<max_t){x=temp; y=Y; MAX=max_t;}}
	if(!my_owner->is_Empty_in(temp,Y))break;
	temp--;
  }

 temp=X+1;
  while(temp<8)
  {
	if(!my_owner->is_Mine_in(temp,Y))if(NO_Echec(temp,Y)){max_t=my_owner->getPiece_Value(temp,Y);if(MAX<max_t){x=temp; y=Y; MAX=max_t;}}
	if(!my_owner->is_Empty_in(temp,Y))break;
	temp++;
  }

  temp=Y-1;
  while(temp>=0)
  {
	if(!my_owner->is_Mine_in(X,temp))if(NO_Echec(X,temp)){max_t=my_owner->getPiece_Value(X,temp);if(MAX<max_t){x= X; y=temp; MAX=max_t;}}
	if(!my_owner->is_Empty_in(X,temp))break;
	temp--;
  }

 temp=Y+1;
  while(temp<8)
  {
	if(!my_owner->is_Mine_in(X,temp))if(NO_Echec(X,temp)){max_t=my_owner->getPiece_Value(X,temp);if(MAX<max_t){x= X; y=temp; MAX=max_t;}}
	if(!my_owner->is_Empty_in(X,temp))break;
	temp++;
  }
  return MAX;
}

int Tower::getMaxAbs(int &x,int &y)
{
	 int Max,max_t,max_t2;
	 int temp;
	 int temp_x,temp_y,if_in,X_T,Y_T;

if((Out)||(Out_T))return -1000;
  Max=-1000;
  max_t=-1000;
  temp=X-1;
  while(temp>=0)
  {
	if(!my_owner->is_Mine_in(temp,Y))if(NO_Echec(temp,Y))
	 {
	  max_t=my_owner->getPiece_Value(temp,Y);
	  if_in=TakeOn(X_T,Y_T,temp,Y);
	  max_t2=my_owner->getMaxAdv();
	  if(Max<=max_t-max_t2)
		{x=X;y=Y;Max=max_t-max_t2;}
	  TakeOff(X_T,Y_T,temp,Y,if_in);
	 }
	if(!my_owner->is_Empty_in(temp,Y))break;
	temp--;
  }

 temp=X+1;
  while(temp<8)
  {
	if(!my_owner->is_Mine_in(temp,Y))if(NO_Echec(temp,Y))
	 {
	  max_t=my_owner->getPiece_Value(temp,Y);
	  if_in=TakeOn(X_T,Y_T,temp,Y);
	  max_t2=my_owner->getMaxAdv();
	  if(Max<=max_t-max_t2)
		{x=X;y=Y;Max=max_t-max_t2;}
	  TakeOff(X_T,Y_T,temp,Y,if_in);
	 }
	if(!my_owner->is_Empty_in(temp,Y))break;
	temp++;
  }

  temp=Y-1;
  while(temp>=0)
  {
	if(!my_owner->is_Mine_in(X,temp))if(NO_Echec(X,temp))
	 {
	  max_t=my_owner->getPiece_Value(X,temp);
	  if_in=TakeOn(X_T,Y_T,X,temp);
	  max_t2=my_owner->getMaxAdv();
	  if(Max<=max_t-max_t2)
		{x=X;y=Y;Max=max_t-max_t2;}
	  TakeOff(X_T,Y_T,X,temp,if_in);
	 }
	if(!my_owner->is_Empty_in(X,temp))break;
	temp--;
  }

 temp=Y+1;
  while(temp<8)
  {
	if(!my_owner->is_Mine_in(X,temp))if(NO_Echec(X,temp))
	 {
	  max_t=my_owner->getPiece_Value(X,temp);
	  if_in=TakeOn(X_T,Y_T,X,temp);
	  max_t2=my_owner->getMaxAdv();
	  if(Max<=max_t-max_t2)
		{x=X;y=Y;Max=max_t-max_t2;}
	  TakeOff(X_T,Y_T,X,temp,if_in);
	 }
	if(!my_owner->is_Empty_in(X,temp))break;
	temp++;
  }
  return Max;
}

int Tower::Tower_Not_Moved()
{
  return((!Moved)&&(!Out));
}
int Tower::Echec()
{
 return echec();
}

int Tower::echec()
{
  int index;

  if((Out)||(Out_T))return NO;
  index=X-1;
  while(index>=0)
	{
	  if(my_owner->is_Adversery_King_in(index,Y))return OK;
	  if(!my_owner->is_Empty_in(index,Y))break;
	  index--;
	}

  index=X+1;
  while(index<8)
	{
	  if(my_owner->is_Adversery_King_in(index,Y))return OK;
	  if(!my_owner->is_Empty_in(index,Y))break;
	  index++;
	}

  index=Y-1;
  while(index>=0)
	{
	  if(my_owner->is_Adversery_King_in(X,index))return OK;
	  if(!my_owner->is_Empty_in(X,index))break;
	  index--;
	}

  index=Y+1;
  while(index<8)
	{
	  if(my_owner->is_Adversery_King_in(X,index))return OK;
	  if(!my_owner->is_Empty_in(X,index))break;
	  index++;
	}

  return NO;
}

Rider::Rider(const int ident,Player * owner, const char *name,const int x,int const y):
Piece(ident,owner,name,RIDER,x,y)
{
}
Rider::~Rider()
{

}
int Rider::is_Ok_to_take_XSYS()
{
  int x_test,y_test,X_T,Y_T;
  if(!(Piece::is_Ok_to_take_XSYS())){Assert_Position();return NO;}

  x_test=(XS-CHESSBOARD_LEFT)/CHESSBOARD_WIDTH;
  y_test=(YS-CHESSBOARD_TOP )/CHESSBOARD_HEIGHT;
  if(my_owner->is_Mine_in(x_test,y_test))return Assert_Position();
  if((((X==x_test+1)||(X==x_test-1))&&((Y==y_test+2)||(Y==y_test-2)))
	 ||
	 (((X==x_test+2)||(X==x_test-2))&&((Y==y_test+1)||(Y==y_test-1))))
  {
  //if fine !
	 if(!Piece::NO_Echec(x_test,y_test))return Assert_Position();

	X_T=X; Y_T=Y;
	X=x_test;
	Y=y_test;
	Assert_Position();
	if(my_owner->I_Take_XY(X,Y))Draw();
	my_owner->Change_Piece(X_T,Y_T,x_test,y_test);
	Moved++;
	return OK;
  }
  return Assert_Position();
}

int Rider::getMax(int &x,int &y)
{
  int x_test,y_test;
  int MAX,max_t;

if((Out)||(Out_T))return -1000;

  MAX=max_t=-1000;
  x_test= X; y_test= Y;

 if((x_test<7)&&(y_test<6))
  {
	if(!my_owner->is_Mine_in(x_test+1,y_test+2))if(NO_Echec(x_test+1,y_test+2)){max_t=my_owner->getPiece_Value(x_test+1,y_test+2);if(MAX<max_t){x= x_test+1; y=y_test+2; MAX=max_t;}}
  }

if((x_test<7)&&(y_test>1))
  {
	if(!my_owner->is_Mine_in(x_test+1,y_test-2))if(NO_Echec(x_test+1,y_test-2)){max_t=my_owner->getPiece_Value(x_test+1,y_test-2);if(MAX<max_t){x= x_test+1; y=y_test-2; MAX=max_t;}}
  }

if((x_test>0)&&(y_test<6))
  {
	if(!my_owner->is_Mine_in(x_test-1,y_test+2))if(NO_Echec(x_test-1,y_test+2)){max_t=my_owner->getPiece_Value(x_test-1,y_test+2);if(MAX<max_t){x= x_test-1; y=y_test+2; MAX=max_t;}}
  }

 if((x_test>0)&&(y_test>1))
  {
	if(!my_owner->is_Mine_in(x_test-1,y_test-2))if(NO_Echec(x_test-1,y_test-2)){max_t=my_owner->getPiece_Value(x_test-1,y_test-2);if(MAX<max_t){x= x_test-1; y=y_test-2; MAX=max_t;}}
  }

 if((x_test<6)&&(y_test<7))
  {
	if(!my_owner->is_Mine_in(x_test+2,y_test+1))if(NO_Echec(x_test+2,y_test+1)){max_t=my_owner->getPiece_Value(x_test+2,y_test+1);if(MAX<max_t){x= x_test+2; y=y_test+1; MAX=max_t;}}
  }

 if((x_test<6)&&(y_test>0))
  {
	if(!my_owner->is_Mine_in(x_test+2,y_test-1))if(NO_Echec(x_test+2,y_test-1)){max_t=my_owner->getPiece_Value(x_test+2,y_test-1);if(MAX<max_t){x= x_test+2; y=y_test-1; MAX=max_t;}}
  }

if((x_test>1)&&(y_test<7))
  {
	if(!my_owner->is_Mine_in(x_test-2,y_test+1))if(NO_Echec(x_test-2,y_test+1)){max_t=my_owner->getPiece_Value(x_test-2,y_test+1);if(MAX<max_t){x= x_test-2; y=y_test+1; MAX=max_t;}}
  }

if((x_test>1)&&(y_test>0))
  {
	if(!my_owner->is_Mine_in(x_test-2,y_test-1))if(NO_Echec(x_test-2,y_test-1)){max_t=my_owner->getPiece_Value(x_test-2,y_test-1);if(MAX<max_t){x= x_test-2; y=y_test-1; MAX=max_t;}}
  }
return MAX;
}

int Rider::getMaxAbs(int &x,int &y)
{
  int x_test,y_test;
  int MAX,max_t,max_t2;
  int if_in,X_T,Y_T;

if((Out)||(Out_T))return -1000;

  MAX=max_t=-1000;
  x_test= X; y_test= Y;

 if((x_test<7)&&(y_test<6))
  {
	if(!my_owner->is_Mine_in(x_test+1,y_test+2))if(NO_Echec(x_test+1,y_test+2))
	 {
	  max_t=my_owner->getPiece_Value(x_test+1,y_test+2);
	  if_in=TakeOn(X_T,Y_T,x_test+1,y_test+2);
	  max_t2=my_owner->getMaxAdv();
	  if(MAX<=max_t-max_t2)
		{x=X;y=Y;MAX=max_t-max_t2;}
	  TakeOff(X_T,Y_T,x_test+1,y_test+2,if_in);
	 }
  }

if((x_test<7)&&(y_test>1))
  {
	if(!my_owner->is_Mine_in(x_test+1,y_test-2))if(NO_Echec(x_test+1,y_test-2))
	{
	  max_t=my_owner->getPiece_Value(x_test+1,y_test-2);
	  if_in=TakeOn(X_T,Y_T,x_test+1,y_test-2);
	  max_t2=my_owner->getMaxAdv();
	  if(MAX<=max_t-max_t2)
		{x=X;y=Y;MAX=max_t-max_t2;}
	  TakeOff(X_T,Y_T,x_test+1,y_test-2,if_in);
	}
  }

if((x_test>0)&&(y_test<6))
  {
	if(!my_owner->is_Mine_in(x_test-1,y_test+2))if(NO_Echec(x_test-1,y_test+2))
	{
	  max_t=my_owner->getPiece_Value(x_test-1,y_test+2);
	  if_in=TakeOn(X_T,Y_T,x_test-1,y_test+2);
	  max_t2=my_owner->getMaxAdv();
	  if(MAX<=max_t-max_t2)
		{x=X;y=Y;MAX=max_t-max_t2;}
	  TakeOff(X_T,Y_T,x_test-1,y_test+2,if_in);
	}
  }

 if((x_test>0)&&(y_test>1))
  {
	if(!my_owner->is_Mine_in(x_test-1,y_test-2))if(NO_Echec(x_test-1,y_test-2))
	 {
		max_t=my_owner->getPiece_Value(x_test-1,y_test-2);
	  if_in=TakeOn(X_T,Y_T,x_test-1,y_test-2);
	  max_t2=my_owner->getMaxAdv();
	  if(MAX<=max_t-max_t2)
		{x=X;y=Y;MAX=max_t-max_t2;}
	  TakeOff(X_T,Y_T,x_test-1,y_test-2,if_in);
	 }
  }

 if((x_test<6)&&(y_test<7))
  {
	if(!my_owner->is_Mine_in(x_test+2,y_test+1))if(NO_Echec(x_test+2,y_test+1))
	 {
		max_t=my_owner->getPiece_Value(x_test+2,y_test+1);
	  if_in=TakeOn(X_T,Y_T,x_test+2,y_test+1);
	  max_t2=my_owner->getMaxAdv();
	  if(MAX<=max_t-max_t2)
		{x=X;y=Y;MAX=max_t-max_t2;}
	  TakeOff(X_T,Y_T,x_test+2,y_test+1,if_in);
	 }
  }

 if((x_test<6)&&(y_test>0))
  {
	if(!my_owner->is_Mine_in(x_test+2,y_test-1))if(NO_Echec(x_test+2,y_test-1))
	 {
		max_t=my_owner->getPiece_Value(x_test+2,y_test-1);
	  if_in=TakeOn(X_T,Y_T,x_test+2,y_test-1);
	  max_t2=my_owner->getMaxAdv();
	  if(MAX<=max_t-max_t2)
		{x=X;y=Y;MAX=max_t-max_t2;}
	  TakeOff(X_T,Y_T,x_test+2,y_test-1,if_in);
	 }
  }

if((x_test>1)&&(y_test<7))
  {
	if(!my_owner->is_Mine_in(x_test-2,y_test+1))if(NO_Echec(x_test-2,y_test+1))
	 {
		max_t=my_owner->getPiece_Value(x_test-2,y_test+1);
	  if_in=TakeOn(X_T,Y_T,x_test-2,y_test+1);
	  max_t2=my_owner->getMaxAdv();
	  if(MAX<=max_t-max_t2)
		{x=X;y=Y;MAX=max_t-max_t2;}
	  TakeOff(X_T,Y_T,x_test-2,y_test+1,if_in);
	 }
  }

if((x_test>1)&&(y_test>0))
  {
	if(!my_owner->is_Mine_in(x_test-2,y_test-1))if(NO_Echec(x_test-2,y_test-1))
	 {
		max_t=my_owner->getPiece_Value(x_test-2,y_test-1);
	  if_in=TakeOn(X_T,Y_T,x_test-2,y_test-1);
	  max_t2=my_owner->getMaxAdv();
	  if(MAX<=max_t-max_t2)
		{x=X;y=Y;MAX=max_t-max_t2;}
	  TakeOff(X_T,Y_T,x_test-2,y_test-1,if_in);
	 }
  }
return MAX;
}

int Rider::Echec()
{
	 if((Out)||(Out_T))return NO;
  return((my_owner->is_Adversery_King_in(X-1,Y-2))||(my_owner->is_Adversery_King_in(X-1,Y+2))||(my_owner->is_Adversery_King_in(X+1,Y-2))||(my_owner->is_Adversery_King_in(X+1,Y+2))||(my_owner->is_Adversery_King_in(X-2,Y-1))||(my_owner->is_Adversery_King_in(X-2,Y+1))||(my_owner->is_Adversery_King_in(X+2,Y-1))||(my_owner->is_Adversery_King_in(X+2,Y+1)) );
}


Mad::Mad(const int ident,Player * owner, const char *name,const int x,int const y):
Piece(ident,owner,name,MAD,x,y)
{
}
Mad::~Mad()
{

}
int Mad::is_Ok_to_take_XSYS()
{
  int x_test,y_test,X_T,Y_T;

  if(!(Piece::is_Ok_to_take_XSYS())){Assert_Position();return NO;}
  x_test=(XS-CHESSBOARD_LEFT)/CHESSBOARD_WIDTH;
  y_test=(YS-CHESSBOARD_TOP )/CHESSBOARD_HEIGHT;
  if(my_owner->is_Mine_in(x_test,y_test))return Assert_Position();
  if(Move()==NO){Assert_Position();return NO;}
  //if fine !
  X_T=X; Y_T=Y;
  X=x_test;
  Y=y_test;
  Assert_Position();
  if(my_owner->I_Take_XY(X,Y))Draw();
  my_owner->Change_Piece(X_T,Y_T,x_test,y_test);
  Moved++;
  return OK;
}
int Mad::Move()
{
  int x_test,y_test;
  int dir_x,dir_y,indexX,indexY;

  x_test=(XS-CHESSBOARD_LEFT)/CHESSBOARD_WIDTH;
  y_test=(YS-CHESSBOARD_TOP )/CHESSBOARD_HEIGHT;
  dir_x=x_test-X; dir_y=y_test-Y;
  if((dir_x!=dir_y)&&(dir_x!=-dir_y))return NO;
  if(dir_x<0)dir_x=-1;else dir_x=1;
  if(dir_y<0)dir_y=-1;else dir_y=1;
  indexX=X+dir_x; indexY=Y+dir_y;
  while(dir_x*indexX<dir_x*x_test)
	{
	  if(!my_owner->is_Empty_in(indexX,indexY))break;
	  indexX=indexX+dir_x; indexY=indexY+dir_y;
	}
  if(indexX!=x_test) return NO;
  if(!Piece::NO_Echec(x_test,y_test))return NO;
  return OK;
}

int Mad::getMax(int &x,int &y)
{
  int temp_x,temp_y;
  int MAX,max_t;

if((Out)||(Out_T))return -1000;
	MAX=max_t=-1000;
  temp_x=X-1;	temp_y=Y-1;
  while((temp_x>=0)&&(temp_y>=0))
  {
	if(!my_owner->is_Mine_in(temp_x,temp_y))if(NO_Echec(temp_x,temp_y)){max_t=my_owner->getPiece_Value(temp_x,temp_y);if(MAX<max_t){x=temp_x; y=temp_y; MAX=max_t;}}
	if(!my_owner->is_Empty_in(temp_x,temp_y))break;
	temp_x--; temp_y--;
  }

  temp_x=X+1;	temp_y=Y-1;
  while((temp_x<8)&&(temp_y>=0))
  {
	if(!my_owner->is_Mine_in(temp_x,temp_y))if(NO_Echec(temp_x,temp_y)){max_t=my_owner->getPiece_Value(temp_x,temp_y);if(MAX<max_t){x=temp_x; y=temp_y; MAX=max_t;}}
	if(!my_owner->is_Empty_in(temp_x,temp_y))break;
	temp_x++; temp_y--;
  }


  temp_x=X-1;	temp_y=Y+1;
  while((temp_x>=0)&&(temp_y<8))
  {
	if(!my_owner->is_Mine_in(temp_x,temp_y))if(NO_Echec(temp_x,temp_y)){max_t=my_owner->getPiece_Value(temp_x,temp_y);if(MAX<max_t){x=temp_x; y=temp_y; MAX=max_t;}}
	if(!my_owner->is_Empty_in(temp_x,temp_y))break;
	temp_x--; temp_y++;
  }

  temp_x=X+1;	temp_y=Y+1;
  while((temp_x<8)&&(temp_y<8))
  {
	if(!my_owner->is_Mine_in(temp_x,temp_y))if(NO_Echec(temp_x,temp_y)){max_t=my_owner->getPiece_Value(temp_x,temp_y);if(MAX<max_t){x=temp_x; y=temp_y; MAX=max_t;}}
	if(!my_owner->is_Empty_in(temp_x,temp_y))break;
	temp_x++; temp_y++;
  }

  return MAX;
}

int Mad::getMaxAbs(int &x,int &y)
{
  int temp_x,temp_y;
  int MAX,max_t,max_t2;
  int if_in,X_T,Y_T;

if((Out)||(Out_T))return -1000;
	MAX=max_t=-1000;
  temp_x=X-1;	temp_y=Y-1;
  while((temp_x>=0)&&(temp_y>=0))
  {
	if(!my_owner->is_Mine_in(temp_x,temp_y))if(NO_Echec(temp_x,temp_y))
	 {
		max_t=my_owner->getPiece_Value(temp_x,temp_y);
	  if_in=TakeOn(X_T,Y_T,temp_x,temp_y);
	  max_t2=my_owner->getMaxAdv();
	  if(MAX<=max_t-max_t2)
		{x=X;y=Y;MAX=max_t-max_t2;}
	  TakeOff(X_T,Y_T,temp_x,temp_y,if_in);
	 }
	if(!my_owner->is_Empty_in(temp_x,temp_y))break;
	temp_x--; temp_y--;
  }

  temp_x=X+1;	temp_y=Y-1;
  while((temp_x<8)&&(temp_y>=0))
  {
	if(!my_owner->is_Mine_in(temp_x,temp_y))if(NO_Echec(temp_x,temp_y))
	 {
	  max_t=my_owner->getPiece_Value(temp_x,temp_y);
	  if_in=TakeOn(X_T,Y_T,temp_x,temp_y);
	  max_t2=my_owner->getMaxAdv();
	  if(MAX<=max_t-max_t2)
		{x=X;y=Y;MAX=max_t-max_t2;}
	  TakeOff(X_T,Y_T,temp_x,temp_y,if_in);
	 }
	if(!my_owner->is_Empty_in(temp_x,temp_y))break;
	temp_x++; temp_y--;
  }


  temp_x=X-1;	temp_y=Y+1;
  while((temp_x>=0)&&(temp_y<8))
  {
	if(!my_owner->is_Mine_in(temp_x,temp_y))if(NO_Echec(temp_x,temp_y))
	 {
	  max_t=my_owner->getPiece_Value(temp_x,temp_y);
	  if_in=TakeOn(X_T,Y_T,temp_x,temp_y);
	  max_t2=my_owner->getMaxAdv();
	  if(MAX<=max_t-max_t2)
		{x=X;y=Y;MAX=max_t-max_t2;}
	  TakeOff(X_T,Y_T,temp_x,temp_y,if_in);
	 }
	if(!my_owner->is_Empty_in(temp_x,temp_y))break;
	temp_x--; temp_y++;
  }

  temp_x=X+1;	temp_y=Y+1;
  while((temp_x<8)&&(temp_y<8))
  {
	if(!my_owner->is_Mine_in(temp_x,temp_y))if(NO_Echec(temp_x,temp_y))
	{
	 max_t=my_owner->getPiece_Value(temp_x,temp_y);
	  if_in=TakeOn(X_T,Y_T,temp_x,temp_y);
	  max_t2=my_owner->getMaxAdv();
	  if(MAX<=max_t-max_t2)
		{x=X;y=Y;MAX=max_t-max_t2;}
	  TakeOff(X_T,Y_T,temp_x,temp_y,if_in);
	}
	if(!my_owner->is_Empty_in(temp_x,temp_y))break;
	temp_x++; temp_y++;
  }

  return MAX;
}

int Mad::Echec()
{
 return echec();
}

int Mad::echec()
{
  int indexx,indexy;

  if((Out)||(Out_T))return NO;
  indexx=X-1;indexy=Y-1;
  while((indexx>=0)&&(indexy>=0))
	{
	  if(my_owner->is_Adversery_King_in(indexx,indexy))return OK;
	  if(!my_owner->is_Empty_in(indexx,indexy))break;
	  indexx--; indexy--;
	}

  indexx=X+1;indexy=Y-1;
  while((indexx<8)&&(indexy>=0))
	{
	  if(my_owner->is_Adversery_King_in(indexx,indexy))return OK;
	  if(!my_owner->is_Empty_in(indexx,indexy))break;
	  indexx++; indexy--;
	}

  indexx=X-1;indexy=Y+1;
  while((indexx>=0)&&(indexy<8))
	{
	  if(my_owner->is_Adversery_King_in(indexx,indexy))return OK;
	  if(!my_owner->is_Empty_in(indexx,indexy))break;
	  indexx--; indexy++;
	}

  indexx=X+1;indexy=Y+1;
  while((indexx<8)&&(indexy<8))
	{
	  if(my_owner->is_Adversery_King_in(indexx,indexy))return OK;
	  if(!my_owner->is_Empty_in(indexx,indexy))break;
	  indexx++; indexy++;
	}

  return NO;
}

King::King(const int ident,Player * owner, const char *name,const int x,int const y):
Piece(ident,owner,name,KING,x,y)
{
}
King::~King()
{

}

int King::is_Ok_to_take_XSYS()
{
  int x_test,y_test,X_T,Y_T,index;

 if(!(Piece::is_Ok_to_take_XSYS())){Assert_Position();return NO;}

  x_test=(XS-CHESSBOARD_LEFT)/CHESSBOARD_WIDTH;
  y_test=(YS-CHESSBOARD_TOP )/CHESSBOARD_HEIGHT;
 if(my_owner->is_Mine_in(x_test,y_test))return Assert_Position();

 if(((X==x_test)||(X==x_test+1)||(X==x_test-1))&&((Y==y_test)||(Y==y_test-1)||(Y==y_test+1)))
 {
  //if fine !

  if(!Piece::NO_Echec(x_test,y_test))return Assert_Position();

  X_T=X; Y_T=Y;
  X=x_test;
  Y=y_test;
  Assert_Position();
  if(my_owner->I_Take_XY(X,Y))Draw();
  my_owner->Change_Piece(X_T,Y_T,x_test,y_test);
  Moved++;
  return OK;
  }
  // if changing with the tower !!!

  if((!Moved)&&(X==x_test)&&((y_test==6)||(y_test==2))&&(my_owner->Tower_Not_Moved(y_test)))
	{
	 if(Piece::NO_Echec(X,Y))
	  {
		if(y_test==6)
		 {
	 for(index=5;index<=6;index++)
	  {
		 if(!my_owner->is_Empty_in(X,index))break;
		 if(!Piece::NO_Echec(X,index))break;
	  }
	 if(index==7)
	 {
		Moved++;
		my_owner->Change_Piece(X,Y,X,y_test);
		Y=y_test;
		Assert_Position();
		my_owner->Tower_King(X,5);
		return OK;
	 }
		}
	  else
		{
	 for(index=3;index>=1;index--)
	  {
		 if(!my_owner->is_Empty_in(X,index))break;
		 if(!Piece::NO_Echec(X,index))break;
	  }
	 if(index==0)
	 {
		Moved++;
		my_owner->Change_Piece(X,Y,X,y_test);
		Y=y_test;
		Assert_Position();
		my_owner->Tower_King(X,3);
		return OK;
	 }
		}
	  }
	}
  Assert_Position();
  return NO;
}

int King::getMax(int &x,int &y)
{
	 int MAX,max_t=-1000;

if((Out)||(Out_T))return -1000;

 MAX=max_t=-1000;
 if((X-1>=0)&&(Y-1>=0))
  {
	 if(!my_owner->is_Mine_in(X-1,Y-1))
	  {
	if(NO_Echec(X-1,Y-1))
	 {
		max_t=my_owner->getPiece_Value(X-1,Y-1);
		if(MAX<max_t){x=X-1; y=Y-1; MAX=max_t;}
	 }
	  }
  }
 if((X+1<8)&&(Y-1>=0))
  {
	if(!my_owner->is_Mine_in(X+1,Y-1))
	 {
		if(NO_Echec(X+1,Y-1)){max_t=my_owner->getPiece_Value(X+1,Y-1);if(MAX<max_t){x=X+1; y=Y-1; MAX=max_t;}}
	 }
  }
  if((X-1>=0)&&(Y+1<8))
  {
	if(!my_owner->is_Mine_in(X-1,Y+1))
	 {
		if(NO_Echec(X-1,Y+1)){max_t=my_owner->getPiece_Value(X-1,Y+1);if(MAX<max_t){x=X-1; y=Y+1; MAX=max_t;}}
	 }
  }
  if((X+1<8)&&(Y+1<8))
  {
	if(!my_owner->is_Mine_in(X+1,Y+1))
	 {
		if(NO_Echec(X+1,Y+1)){max_t=my_owner->getPiece_Value(X+1,Y+1);if(MAX<max_t){x=X+1; y=Y+1; MAX=max_t;}}
	 }
  }

  if(X-1>=0)
  {
	if(!my_owner->is_Mine_in(X-1,Y))
	 {
		if(NO_Echec(X-1,Y)){max_t=my_owner->getPiece_Value(X-1,Y);if(MAX<max_t){x=X-1; y=Y; MAX=max_t;}}
	 }
  }
  if(X+1<8)
  {
	if(!my_owner->is_Mine_in(X+1,Y))
	 {
		if(NO_Echec(X+1,Y)){max_t=my_owner->getPiece_Value(X+1,Y);if(MAX<max_t){x=X+1; y=Y; MAX=max_t;}}
	 }
  }
  if(Y-1>=0)
  {
	if(!my_owner->is_Mine_in(X,Y-1))
	 {
		if(NO_Echec(X,Y-1)){max_t=my_owner->getPiece_Value(X,Y-1);if(MAX<max_t){x=X; y=Y-1; MAX=max_t;}}
	 }
  }
  if(Y+1<8)
  {
	if(!my_owner->is_Mine_in(X,Y+1))
	 {
		if(NO_Echec(X,Y+1)){max_t=my_owner->getPiece_Value(X,Y+1);if(MAX<max_t){x=X; y=Y+1; MAX=max_t;}}
	 }
  }
  return MAX;
}

int King::getMaxAbs(int &x,int &y)
{
	 int MAX,max_t,max_t2;
	 int if_in,temp_x,temp_y,X_T,Y_T;

if((Out)||(Out_T))return -1000;

 MAX=max_t=-1000;
 if((X-1>=0)&&(Y-1>=0))
  {
	 if(!my_owner->is_Mine_in(X-1,Y-1))
	  {
	if(NO_Echec(X-1,Y-1))
	 {
	  temp_x=X-1; temp_y=Y-1;
	  max_t=my_owner->getPiece_Value(temp_x,temp_y);
	  if_in=TakeOn(X_T,Y_T,temp_x,temp_y);
	  max_t2=my_owner->getMaxAdv();
	  if(MAX<=max_t-max_t2)
		{x=X;y=Y;MAX=max_t-max_t2;}
	  TakeOff(X_T,Y_T,temp_x,temp_y,if_in);
	 }
	  }
  }
 if((X+1<8)&&(Y-1>=0))
  {
	if(!my_owner->is_Mine_in(X+1,Y-1))
	 {
		if(NO_Echec(X+1,Y-1))
		 {
	  temp_x=X+1; temp_y=Y-1;
	  max_t=my_owner->getPiece_Value(temp_x,temp_y);
	  if_in=TakeOn(X_T,Y_T,temp_x,temp_y);
	  max_t2=my_owner->getMaxAdv();
	  if(MAX<=max_t-max_t2)
		{x=X;y=Y;MAX=max_t-max_t2;}
	  TakeOff(X_T,Y_T,temp_x,temp_y,if_in);
		 }
	 }
  }
  if((X-1>=0)&&(Y+1<8))
  {
	if(!my_owner->is_Mine_in(X-1,Y+1))
	 {
		if(NO_Echec(X-1,Y+1))
		 {
	  temp_x=X-1; temp_y=Y+1;
	  max_t=my_owner->getPiece_Value(temp_x,temp_y);
	  if_in=TakeOn(X_T,Y_T,temp_x,temp_y);
	  max_t2=my_owner->getMaxAdv();
	  if(MAX<=max_t-max_t2)
		{x=X;y=Y;MAX=max_t-max_t2;}
	  TakeOff(X_T,Y_T,temp_x,temp_y,if_in);
		 }
	 }
  }
  if((X+1<8)&&(Y+1<8))
  {
	if(!my_owner->is_Mine_in(X+1,Y+1))
	 {
		if(NO_Echec(X+1,Y+1))
		 {
	  temp_x=X+1; temp_y=Y+1;
	  max_t=my_owner->getPiece_Value(temp_x,temp_y);
	  if_in=TakeOn(X_T,Y_T,temp_x,temp_y);
	  max_t2=my_owner->getMaxAdv();
	  if(MAX<=max_t-max_t2)
		{x=X;y=Y;MAX=max_t-max_t2;}
	  TakeOff(X_T,Y_T,temp_x,temp_y,if_in);
		 }
	 }
  }

  if(X-1>=0)
  {
	if(!my_owner->is_Mine_in(X-1,Y))
	 {
		if(NO_Echec(X-1,Y))
		 {
	  temp_x=X-1; temp_y=Y;
	  max_t=my_owner->getPiece_Value(temp_x,temp_y);
	  if_in=TakeOn(X_T,Y_T,temp_x,temp_y);
	  max_t2=my_owner->getMaxAdv();
	  if(MAX<=max_t-max_t2)
		{x=X;y=Y;MAX=max_t-max_t2;}
	  TakeOff(X_T,Y_T,temp_x,temp_y,if_in);
		 }
	 }
  }
  if(X+1<8)
  {
	if(!my_owner->is_Mine_in(X+1,Y))
	 {
		if(NO_Echec(X+1,Y))
		 {
	  temp_x=X+1; temp_y=Y;
	  max_t=my_owner->getPiece_Value(temp_x,temp_y);
	  if_in=TakeOn(X_T,Y_T,temp_x,temp_y);
	  max_t2=my_owner->getMaxAdv();
	  if(MAX<=max_t-max_t2)
		{x=X;y=Y;MAX=max_t-max_t2;}
	  TakeOff(X_T,Y_T,temp_x,temp_y,if_in);
		 }
	 }
  }
  if(Y-1>=0)
  {
	if(!my_owner->is_Mine_in(X,Y-1))
	 {
		if(NO_Echec(X,Y-1))
		 {
	  temp_x=X; temp_y=Y-1;
	  max_t=my_owner->getPiece_Value(temp_x,temp_y);
	  if_in=TakeOn(X_T,Y_T,temp_x,temp_y);
	  max_t2=my_owner->getMaxAdv();
	  if(MAX<=max_t-max_t2)
		{x=X;y=Y;MAX=max_t-max_t2;}
	  TakeOff(X_T,Y_T,temp_x,temp_y,if_in);
		 }
	 }
  }
  if(Y+1<8)
  {
	if(!my_owner->is_Mine_in(X,Y+1))
	 {
		if(NO_Echec(X,Y+1))
		 {
	  temp_x=X; temp_y=Y+1;
	  max_t=my_owner->getPiece_Value(temp_x,temp_y);
	  if_in=TakeOn(X_T,Y_T,temp_x,temp_y);
	  max_t2=my_owner->getMaxAdv();
	  if(MAX<=max_t-max_t2)
		{x=X;y=Y;MAX=max_t-max_t2;}
	  TakeOff(X_T,Y_T,temp_x,temp_y,if_in);
		 }
	 }
  }
  return MAX;
}

int King::Echec()
{
  if((Out)||(Out_T))return NO;
  return((my_owner->is_Adversery_King_in(X-1,Y))||(my_owner->is_Adversery_King_in(X+1,Y))||(my_owner->is_Adversery_King_in(X,Y-1))||(my_owner->is_Adversery_King_in(X,Y+1))||(my_owner->is_Adversery_King_in(X-1,Y-1))||(my_owner->is_Adversery_King_in(X+1,Y-1))||(my_owner->is_Adversery_King_in(X-1,Y+1))||(my_owner->is_Adversery_King_in(X+1,Y+1))) ;
}


Queen::Queen(const int ident,Player * owner, const char *name,const int x,int const y):
Piece(ident,owner,name,QUEEN,x,y),Tower(ident,owner,name,x,y),Mad(ident,owner,name,x,y)
{
 Kind=QUEEN;
}
Queen::~Queen()
{

}
int Queen::is_Ok_to_take_XSYS()
{
	int x_test,y_test,X_T,Y_T;

  if(!(Piece::is_Ok_to_take_XSYS())){Assert_Position();return NO;}
  x_test=(XS-CHESSBOARD_LEFT)/CHESSBOARD_WIDTH;
  y_test=(YS-CHESSBOARD_TOP )/CHESSBOARD_HEIGHT;
  if(my_owner->is_Mine_in(x_test,y_test))return Assert_Position();
  if((Mad::Move()==NO)&&(Tower::Move()==NO)){ Assert_Position();return NO;}
  //if fine !
  if(!Piece::NO_Echec(x_test,y_test))return Assert_Position();

  X_T=X; Y_T=Y;
  X=x_test;
  Y=y_test;
  Assert_Position();
  if(my_owner->I_Take_XY(X,Y))Draw();
  my_owner->Change_Piece(X_T,Y_T,X,Y);
  Moved++;
  return OK;
}

int Queen::getMax(int &x,int &y)
{
  int x_t,y_t,max_t,MAX;
  MAX=Mad::getMax(x,y);
  max_t=Tower::getMax(x_t,y_t);
  if(MAX<max_t){x=x_t; y=y_t; MAX=max_t;}
  return MAX;
}

int Queen::getMaxAbs(int &x,int &y)
{
  int x_t,y_t,max_t,MAX;
  MAX=Mad::getMaxAbs(x,y);
  max_t=Tower::getMaxAbs(x_t,y_t);
  if(MAX<=max_t){x=x_t; y=y_t; MAX=max_t;}
  return MAX;
}

int Queen::Echec()
{
  return ((Mad::echec())||(Tower::echec()));
}
