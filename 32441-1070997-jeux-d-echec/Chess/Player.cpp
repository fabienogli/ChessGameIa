// Player.cpp: implementation of the Player class.
//
//////////////////////////////////////////////////////////////////////

#include "GameH.h"

#include <graphics.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------//

Player::Player()
{
	identifier=0; // I have no game !!!
	Name[0]=0;
	Nbr_of_pieces=16;
	Nbr_Piece_In=0;
	the_game = NULL;
	Init_Pieces();
	X=Y=NULL;
	Player_Image=NULL;
}

Player::~Player()
{
  Destroy_Pieces();
  if(Player_Image)delete Player_Image;
  if(the_game)the_game->Player_destroy(identifier);
}

int Player::Init_Pieces()
{
 int index;
 switch(identifier)
  {
    case PLAYER1:
	    for(index=0;index<8;index++)
	     player_piece[index]=new Pawn(index,this,"Pawn_P1",1,index);

	    player_piece[8]=new Tower(index,this,"TOWER_P1",0,0);
	    player_piece[9]=new Rider(index,this,"RIDER_P1",0,1);
	    player_piece[10]=new Mad(index,this,"MAD_P1",0,2);

	    player_piece[11]=new Queen(index,this,"QUEEN_P1",0,3);
	    player_piece[12]=new King(index,this,"KING_P1",0,4);

	    player_piece[15]=new Tower(index,this,"TOWER_P1",0,7);
	    player_piece[14]=new Rider(index,this,"RIDER_P1",0,6);
	    player_piece[13]=new Mad(index,this,"MAD_P1",0,5);
	    break;
    case PLAYER2:
	    for(index=0;index<8;index++)
	     player_piece[index]=new Pawn(index,this,"Pawn_P2",6,index);

	    player_piece[8]=new Tower(index,this,"TOWER_P2",7,0);
	    player_piece[9]=new Rider(index,this,"RIDER_P2",7,1);
	    player_piece[10]=new Mad(index,this,"MAD_P2",7,2);

	    player_piece[11]=new Queen(index,this,"QUEEN_P2",7,3);
	    player_piece[12]=new King(index,this,"KING_P2",7,4);
	    player_piece[15]=new Tower(index,this,"TOWER_P2",7,7);
	    player_piece[14]=new Rider(index,this,"RIDER_P2",7,6);
	    player_piece[13]=new Mad(index,this,"MAD_P2",7,5);

	    break;
  }
 return 1;
}

void Player::Destroy_Pieces()
{

}

Player::Player(int iden, const char *name,  Game * game, const int x, const int y)
{
	identifier=iden;
	Name[0]=0;
	strcpy(Name,name);
	X=x; Y=y;
	Nbr_of_pieces=16;
	Nbr_Piece_In=0;
	the_game = game;
	Init_Pieces();
	Player_Image=new BitMap;
	Player_Image->X=CHESSBOARD_WIDTH; Player_Image->Y=CHESSBOARD_HEIGHT;
	if(iden==PLAYER1)
	   {
	      Player_Image->Image=(char *)Game::Default_Player1_Image;
	   }
	else
	  {
	    Player_Image->Image=(char *)Game::Default_Player2_Image;
	  }
	Replay_Btn=new ChessButton(X,Y+5*CHESSBOARD_HEIGHT,11*8,CHESSBOARD_HEIGHT/2,1,7,"you replay");
	Text_Name =new ChessEdit(X,Y-30,11*8,CHESSBOARD_HEIGHT/2,1,7,Name);
	Draw();
}

void Player::Piece_Die(const int the_piece)
{
  //Nbr_of_pieces--;
  player_piece[the_piece]=NULL;
}

int Player::Play()
{
   return GAME_FINE;
}

int Player::Choose_Piece(int & witch_piece)
{
  return GAME_FINE;
}

int Player::Move_Piece(const int piece)
{
  return GAME_CONTINUING;
}

int Player::No_King()
{
  int index;
  index=0;
  while(index<Nbr_of_pieces)
  {
     if((player_piece[index])->is_King())break;
     index++;
  }
 return (index>=Nbr_of_pieces);
}

int Player::Witch_Piece(const int x,const int y)
{
  int index;
  index=0;
  while(index<Nbr_of_pieces)
  {
     if((player_piece[index])->is_Me(x,y))break;
     index++;
  }
 if(index<Nbr_of_pieces)return index;
 return NO_PIECE;
}

int Player::getIdentifier()
{
 return identifier;
}

void Player::Change_Piece(const int form_x,const int form_y,const int to_x,const int to_y)
{
 the_game->Change_Piece(form_x,form_y,to_x,to_y);
}

void Player::Put_Piece(const int x,const int y)
{
  the_game->Put_Piece(x,y,identifier);
}

int Player::is_Adversery_in(const int x,const int y)
{
  return the_game->is_Adversery_in(x,y,identifier);
}

int Player::is_Mine_in(const int x,const int y)
{
  return the_game->is_Mine_in(x,y,identifier);
}

int Player::is_Empty_in(const int x,const int y)
{
  return the_game->is_Empty_in(x,y);
}

int Player::Out_Side_Piece(const int x,const int y)
{
  int index;
  index=Witch_Piece(CHESSBOARD_LEFT+(x*CHESSBOARD_WIDTH),CHESSBOARD_TOP+(y*CHESSBOARD_HEIGHT));
  if(index!=NO_PIECE)
   {
     player_piece[index]->Go_out();
     the_game->Put_Piece(x,y,0);
     return OK;
   }
  return NO;
}

int Player::Out_Side_Piece_Temp(const int x,const int y)
{
  int index;
  index=Witch_Piece(CHESSBOARD_LEFT+(x*CHESSBOARD_WIDTH),CHESSBOARD_TOP+(y*CHESSBOARD_HEIGHT));
  if(index!=NO_PIECE)
   {
     player_piece[index]->Go_out_Temp();
     the_game->Put_Piece(x,y,0);
     return OK;
   }
  return NO;
}

int Player::Out_Side_Adversery_Piece(const int x,const int y)
{
   return the_game->Out_Side_Piece(x,y,identifier);
}

int Player::Out_Side_Adversery_Piece_Temp(const int x,const int y)
{
   return the_game->Out_Side_Piece_Temp(x,y,identifier);
}

int Player::In_Side_Piece(const int x,const int y)
{
  int index;
  for(index=0; index<Nbr_of_pieces; index++)
   {
     if(player_piece[index]->Go_in(x,y))break;
   }
  return (index<Nbr_of_pieces);
}

int Player::In_Side_Piece(const int x,const int y,const int kind)
{
  int index;
  for(index=0; index<Nbr_of_pieces; index++)
   {
     if(player_piece[index]->Go_in(x,y,kind))break;
   }
  return OK;
}

int Player::In_Side_Piece_Temp(const int x,const int y)
{
  int index;
  for(index=0; index<Nbr_of_pieces; index++)
   {
     if(player_piece[index]->Go_in_Temp(x,y))break;
   }
  return (index<Nbr_of_pieces);
}

void Player::In_Side_Adversery_Piece(const int x,const int y)
{
   the_game->In_Side_Piece(x,y,identifier);
}


void Player::In_Side_Adversery_Piece_Temp(const int x,const int y)
{
   the_game->In_Side_Piece_Temp(x,y,identifier);
}

int Player::I_Take_XY(const int x,const int y)
{
  return the_game->Player_Take_XY(x,y,identifier);
}

int Player::getKind(int x,int y)
{
  int index;
  index=Witch_Piece(CHESSBOARD_LEFT+(x*CHESSBOARD_WIDTH),CHESSBOARD_TOP+(y*CHESSBOARD_HEIGHT));
  if(index==NO_PIECE) return NO_PIECE;
  return player_piece[index]->getKind();
}

void Player::Draw()
{
  char str[5];
 setfillstyle(1,0);
 bar(X-12,Y-42,X+102,Y+232);
 setfillstyle(1,11);
 bar(X-10,Y-40,X+100,Y+230);
 if(Player_Image)
   {
     Screen *s=new Screen;
      s->getImage(X,Y,CHESSBOARD_WIDTH,CHESSBOARD_HEIGHT,Player_Image);
     delete s;
   }
  setfillstyle(1,11);
  setcolor(4);
  itoa(Nbr_Piece_In,str,10);
  bar(X+2,Y+4*40-2,X+100,Y+4*40+10);
  outtextxy(X+4,Y+4*40,str);
  outtextxy(X+4+2*8+5,Y+4*40,"Pieces");
  Text_Name->Validate();
  Replay_Btn->Validate();
}

int Player::Echec()
{
 int index;
 for(index=0;index<Nbr_of_pieces;index++)
  {
    if(player_piece[index]->Echec())
    return OK;
  }
  return NO;
}

int Player::is_Adversery_King_in(const int x,const int y)
{
  if(identifier==PLAYER1)return (the_game->is_King_in(x,y,PLAYER2));
  return (the_game->is_King_in(x,y,PLAYER1));
}

int Player::is_my_King_in(const int x,const int y)
{
  int index;
  index=0;
  while(index<Nbr_of_pieces)
   {
     if(player_piece[index]->is_King(x,y))return OK;
     index++;
   }
   return NO;
}

int Player::Echec_To_Me()
{
  return the_game->Echec(identifier);
}

int Player::Replay()
{
  return NO;
}

void Player::Change_Pawn(int iden,int x,int y)
{
}

void Player::Validate()
{
  int index;
  for(index=0; index<Nbr_of_pieces;index++)
   player_piece[index]->Validate();
  Draw();
}

int Player::Tower_Not_Moved(int y)
{
  if(y==6)return player_piece[15]->Tower_Not_Moved();
  return player_piece[8]->Tower_Not_Moved();
}

void Player::Tower_King(int x,int y)
{
  if(y==5)
    {
      player_piece[15]->Take(x,y);
      player_piece[15]->Moved++;
    }
  else
    {
      player_piece[8]->Take(x,y);
      player_piece[8]->Moved++;
    }
}

void Player::Piece_Out()
{
  char str[5]="";
  Nbr_Piece_In--;
  setfillstyle(1,11);
  setcolor(4);
  itoa(Nbr_Piece_In,str,10);
  bar(X+2,Y+4*40-2,X+100,Y+4*40+10);
  outtextxy(X+4,Y+4*40,str);
  outtextxy(X+4+2*8+5,Y+4*40,"Pieces");
}

void Player::Piece_In()
{
  char str[5]="";
  Nbr_Piece_In++;
  setfillstyle(1,11);
  setcolor(4);
  itoa(Nbr_Piece_In,str,10);
  bar(X+2,Y+4*40-2,X+100,Y+4*40+10);
  outtextxy(X+4,Y+4*40,str);
  outtextxy(X+4+2*8+5,Y+4*40,"Pieces");
}

int Player::Echec_And_Mate_To_Me()
{
  int index;
	for(index=0; index<Nbr_of_pieces; index++)
	{
		if(player_piece[index]->Can_Play())return NO;
	}
 return OK;
}

int Player::Echec_And_Mate()
{
  return the_game->Echec_And_Mate(identifier);
}

int Player::getPiece_Value(int x,int y)
{
  switch(the_game->getKind(identifier,x,y))
  {
	case NO_PIECE : return 0;
	case PAWN:      return 1;
	case MAD:
	case RIDER:	    return 3;
    case TOWER:		return 4;
	case QUEEN:		return 9;
	case KING:		return 1000; //ALL THE GAME !!!
	default:
				return 0;
  }
}

int Player::getMax()
{
  int x,y,MAX,max_t,index;
  MAX=-1000;
  for(index=0;index<Nbr_of_pieces;index++)
   {
     max_t=player_piece[index]->getMax(x,y);
     if(MAX<max_t)
       {
	 MAX=max_t;
       }
   }
  return MAX;
}

int Player::getMaxAdv()
{
  int xx,yy;
  return the_game->getMax(identifier);
}

//****************************************************//

HPlayer::HPlayer(int iden, const char *name, Game * game,const int x,const int y):
Player(iden,name,game,x,y)
{
}
HPlayer::~HPlayer()
{
}

int HPlayer::Play()
{
   int ident_piece;
   int if_not_ok;

chose:  setfillstyle(1,11);
	setcolor(1);
	bar(X,Y+16+CHESSBOARD_HEIGHT,X+8*8,Y+CHESSBOARD_HEIGHT+16+16);
	bar(X,Y+48+CHESSBOARD_HEIGHT,X+8*8,Y+CHESSBOARD_HEIGHT+48+16);
   if_not_ok=ECHAP; // just to go in !!!
   while(if_not_ok!=GAME_FINE)
    {
      if_not_ok=Choose_Piece(ident_piece);
       if(if_not_ok==LOSE)
	{
	  if(identifier==PLAYER1)return PLAYER2_WON;
	  return PLAYER1_WON;
	}
       if(if_not_ok==ECHAP)
	{ // game abort !!!
	  setfillstyle(1,11);
	  setcolor(1);
	  bar(X,Y+16+CHESSBOARD_HEIGHT,X+8*8,Y+CHESSBOARD_HEIGHT+16+16);
	  outtextxy(X,Y+16+CHESSBOARD_HEIGHT,"Tired  !");
	  if(identifier==PLAYER1)return PLAYER1_ABORT_GAME;
	  return PLAYER2_ABORT_GAME;
	}

    if(if_not_ok==REPLAY)
	{ // game abort !!!
	  setfillstyle(1,11);
	  setcolor(1);
	  bar(X,Y+16+CHESSBOARD_HEIGHT,X+8*8,Y+CHESSBOARD_HEIGHT+16+16);
	  if(the_game->Replay(identifier))
	    {
	     outtextxy(X,Y+16+CHESSBOARD_HEIGHT,"Replay !");
	     return GAME_FINE;
	    }
	  else goto chose;
	}

    setfillstyle(1,11);
    setcolor(1);
    bar(X,Y+48+CHESSBOARD_HEIGHT,X+8*8,Y+CHESSBOARD_HEIGHT+48+16);
    outtextxy(X,Y+48+CHESSBOARD_HEIGHT,player_piece[ident_piece]->getName());
	if_not_ok=Move_Piece(ident_piece);
    if(if_not_ok==ECHAP)
	{ // game abort !!!
	  outtextxy(X,Y+16+CHESSBOARD_HEIGHT,"Tired  !");
	  if(identifier==PLAYER1)return PLAYER1_ABORT_GAME;
	  return PLAYER2_ABORT_GAME;
	}
     }
    setfillstyle(1,11);
    setcolor(1);
    bar(X,Y+16+CHESSBOARD_HEIGHT,X+8*8,Y+CHESSBOARD_HEIGHT+16+16);
       if(Echec_And_Mate())
	{
	  outtextxy(X,Y+16+CHESSBOARD_HEIGHT,"Echec & Mate!");
	  printf("%c",7);
	  if(identifier==PLAYER1)return PLAYER1_WON;
	  return PLAYER2_WON;
	}
    if(Echec())
     {
       outtextxy(X,Y+16+CHESSBOARD_HEIGHT,"Echec !!");
       printf("%c",7);
     }
    else
     outtextxy(X,Y+16+CHESSBOARD_HEIGHT,"Play !!!");

   the_game->Add_Movment(X_From,Y_From,X_To,Y_To,Kind,Kind_c);
   return if_not_ok;
}

int HPlayer::Choose_Piece(int & witch_piece)
{
  int x,y,btn;
  char c;
  Mouse M;

  witch_piece=NO_PIECE; // No piece choosen !!!

  // if there is a loser
  if(No_King()) return LOSE;

  btn=NO_BUTTON;
  while(witch_piece==NO_PIECE)
   {
     M.getInformation(x,y,btn);
     while(btn!=LEFT_BUTTON)
     {
       if(kbhit())
	{
	  c=getch();
	  if(c==ECHAP)return ECHAP;
	  if((c=='r')||(c=='R')) return REPLAY;
	  if((c=='n')||(c=='N')) Text_Name->setText();
	  if((c=='d')||(c=='D'))the_game->Change_Ressource();
	}
       M.getInformation(x,y,btn);
     }
     witch_piece=Witch_Piece(x,y);
       if(kbhit())
	{
	  c=getch();
	  if(c==ECHAP)return ECHAP;
	  if((c=='r')||(c=='R')) return REPLAY;
	}
     if(Replay_Btn->Click())return REPLAY;
     if(Text_Name->Click())Text_Name->setText();
   }
  X_From=(x-CHESSBOARD_LEFT)/CHESSBOARD_WIDTH;
  Y_From=(y-CHESSBOARD_TOP)/CHESSBOARD_HEIGHT;

  return GAME_FINE;
}

int HPlayer::Move_Piece(const int piece)
{
  Mouse M;
  int x,y,btn;
  int oldx,oldy;
  int Xor;

  btn=LEFT_BUTTON; //if we are here ,we are sure the LEFT_BUTTON is clicked !!
  M.getInformation(oldx,oldy,btn);
  Xor=0;
  while(btn==LEFT_BUTTON)
   {
     M.getInformation(x,y,btn);
     player_piece[piece]->setScreen_Position(oldx-20,oldy-20);
     if((oldx-x>5)||(oldx-x<-5)||(oldy-y>5)||(oldy-y<-5))
     {
       oldx=x;
       oldy=y;
     }
     delay(50);
   }
  player_piece[piece]->setScreen_Position(oldx,oldy);
  X_To=(oldx-CHESSBOARD_LEFT)/CHESSBOARD_WIDTH;
  Y_To=(oldy-CHESSBOARD_TOP)/CHESSBOARD_HEIGHT;
  Kind=player_piece[piece]->getKind();
  Kind_c=the_game->getKind(identifier,X_To,Y_To);
  if(player_piece[piece]->is_Ok_to_take_XSYS())
    {
      return GAME_FINE;
    }
  return GAME_CONTINUING;
}

void HPlayer::Change_Pawn(int iden,int x,int y)
{
  int Chose;
  Out_Side_Piece(x,y);
  delete (player_piece[iden]);

  DialogPiece * D =new DialogPiece(200,200,120,150,"Choisir","Quelle Piece ?");
  Chose=D->DoModel();
  delete D;

  if(identifier==PLAYER1)
   {
     switch(Chose)
      {
	case QUEEN:player_piece[iden]=new Queen(iden,this,"QUEEN_P1",x,y);
		   break;
	case TOWER:player_piece[iden]=new Tower(iden,this,"TOWER_P1",x,y);
		   break;
	case RIDER:player_piece[iden]=new Rider(iden,this,"RIDER_P1",x,y);
		   break;
	case MAD  :player_piece[iden]=new Mad(iden,this,"MAD_P1",x,y);
		   break;
      }
   }
  else
   {
     switch(Chose)
      {
	case QUEEN:player_piece[iden]=new Queen(iden,this,"QUEEN_P2",x,y);
		   break;
	case TOWER:player_piece[iden]=new Tower(iden,this,"TOWER_P2",x,y);
		   break;
	case RIDER:player_piece[iden]=new Rider(iden,this,"RIDER_P2",x,y);
		   break;
	case MAD  :player_piece[iden]=new Mad(iden,this,"MAD_P2",x,y);
		   break;
      }
   }

  Put_Piece(x,y);
}

int HPlayer::Replay()
{
  int from_x,from_y,to_x,to_y,kind,kind_c,index;

  if(the_game->getLast_Movment(from_x,from_y,to_x,to_y,kind,kind_c))
   {
     index=Witch_Piece(CHESSBOARD_LEFT+(to_x*CHESSBOARD_WIDTH),CHESSBOARD_TOP+(to_y*CHESSBOARD_HEIGHT));
     if(index==NO_PIECE)
      {
	printf("ERREUR");
	return NO;
      }
     player_piece[index]->Take(from_x,from_y);
     player_piece[index]->Moved--;
     if((kind==PAWN)&&(player_piece[index]->getKind()!=PAWN))
      {
	 Out_Side_Piece(from_x,from_y);
	 delete (player_piece[index]);
	if(identifier==PLAYER1)
	 player_piece[index]=new Pawn(index,this,"Pawn_P1",from_x,from_y);
	else
	 player_piece[index]=new Pawn(index,this,"Pawn_P2",from_x,from_y);
	 Put_Piece(from_x,from_y);
      }
     else
      {
	 if((kind==KING)&&(from_y!=to_y-1)&&(from_y!=to_y+1)&&(from_y!=to_y))
	  {
	    if(to_y==6)
	      {
		player_piece[15]->Take(from_x,7);
		player_piece[15]->Moved--;
	      }
	     else
	      {
		player_piece[8]->Take(from_x,0);
		player_piece[8]->Moved--;
	      }
	  }
      }
     the_game->In_Side_Piece(to_x,to_y,kind_c,identifier);
     return OK;
   }
  return NO;
}

//*********************************************************************//
OPlayer::OPlayer(int iden, const char *name, Game * game,const int x,const int y):
Player(iden,name,game,x,y)
{
}
OPlayer::~OPlayer()
{
}

int OPlayer::Play()
{
	int ident_piece;
	int if_not_ok;

	setfillstyle(1,11);
	setcolor(1);
	bar(X,Y+16+CHESSBOARD_HEIGHT,X+8*8,Y+CHESSBOARD_HEIGHT+16+16);
	bar(X,Y+48+CHESSBOARD_HEIGHT,X+8*8,Y+CHESSBOARD_HEIGHT+48+16);

		 randomize();

		if_not_ok=Choose_Piece(ident_piece);
		 if(if_not_ok==ECHAP)
	{ // game abort !!!
	  setfillstyle(1,11);
	  setcolor(1);
	  bar(X,Y+16+CHESSBOARD_HEIGHT,X+8*8,Y+CHESSBOARD_HEIGHT+16+16);
	  outtextxy(X,Y+16+CHESSBOARD_HEIGHT,"Tired  !");
	  if(identifier==PLAYER1)return PLAYER1_ABORT_GAME;
	  return PLAYER2_ABORT_GAME;
	}
		 if(if_not_ok==LOSE)
	{
	  if(identifier==PLAYER1)return PLAYER2_WON;
	  return PLAYER1_WON;
	}

	 setfillstyle(1,11);
	 setcolor(1);
	 bar(X,Y+48+CHESSBOARD_HEIGHT,X+8*8,Y+CHESSBOARD_HEIGHT+48+16);
	 outtextxy(X,Y+48+CHESSBOARD_HEIGHT,player_piece[ident_piece]->getName());
	 if_not_ok=Move_Piece(ident_piece);

	 setfillstyle(1,11);
	 setcolor(1);
	 bar(X,Y+16+CHESSBOARD_HEIGHT,X+8*8,Y+CHESSBOARD_HEIGHT+16+16);
		 if(Echec_And_Mate())
	{
	  outtextxy(X,Y+16+CHESSBOARD_HEIGHT,"Echec & Mate!");
	  printf("%c",7);
	  if(identifier==PLAYER1)return PLAYER1_WON;
	  return PLAYER2_WON;
	}
	 if(Echec())
	  {
		 outtextxy(X,Y+16+CHESSBOARD_HEIGHT,"Echec !!");
		 printf("%c",7);
	  }
	 else
	  outtextxy(X,Y+16+CHESSBOARD_HEIGHT,"Play !!!");

	  if(the_game->Save)the_game->Add_Movment(X_From,Y_From,X_To,Y_To,Kind,Kind_c);
	return GAME_FINE;
}

int OPlayer::Choose_Piece(int & witch_piece)
{
  int x,y,MAX,max_t,max_t2,x_t,y_t,index,x_p,y_p,if_in;
  char c;
  int can_play;

  witch_piece=NO_PIECE; // No piece choosen !!!
  can_play=NO;

  if(No_King()) return LOSE;

  MAX=-1000;

  for(index=0;index<Nbr_of_pieces;index++)
	{
	  max_t=player_piece[index]->getMaxAbs(x_t,y_t);

	 if(max_t!=-1000)
		{
		 can_play=OK;
	/*
		 player_piece[index]->getXY(x_p,y_p);
		 if_in=Out_Side_Adversery_Piece_Temp(x_t,y_t);
		 Change_Piece(x_p,y_p,x_t,y_t);
		 player_piece[index]->setXY(x_t,y_t);

		 max_t2=the_game->getMax(identifier);

		 player_piece[index]->setXY(x_p,y_p);
		 Change_Piece(x_t,y_t,x_p,y_p);
		 if(if_in)In_Side_Adversery_Piece_Temp(x_t,y_t);
	  */


	if(random(1515)%2==0)
	  {
		 if(MAX<max_t)
		  {
			 MAX=max_t; x=x_t; y=y_t;
			 witch_piece=index;
		  }
	  }
	else
	  {
		 if(MAX<=max_t)
			 {
				MAX=max_t-max_t2; x=x_t; y=y_t;
				witch_piece=index;
			 }
	  }
		 }
	}

  if(!can_play)return LOSE;

  player_piece[witch_piece]->getXY(X_From,Y_From);
  //X_From=x_p;
  //Y_From=y_p;
  X_To=x;
  Y_To=y;
  if(kbhit())
	{
	  c=getch();
	  if(c==ECHAP)return ECHAP;
	}
  return GAME_FINE;
}

int OPlayer::Move_Piece(const int piece)
{
  int x,y;

  x=CHESSBOARD_LEFT+(CHESSBOARD_WIDTH*X_To);
  y=CHESSBOARD_TOP+(CHESSBOARD_HEIGHT*Y_To);

  Kind=player_piece[piece]->getKind();
  Kind_c=the_game->getKind(identifier,X_To,Y_To);
  player_piece[piece]->setScreen_Position(x,y);
  player_piece[piece]->is_Ok_to_take_XSYS();
  Put_Piece(X_To,Y_To);
  return GAME_FINE;
}

void OPlayer::Change_Pawn(int iden,int x,int y)
{

  Out_Side_Piece(x,y);
  delete (player_piece[iden]);

  if(identifier==PLAYER1)
   {
       player_piece[iden]=new Queen(iden,this,"QUEEN_P1",x,y);
   }
  else
   {
       player_piece[iden]=new Queen(iden,this,"QUEEN_P2",x,y);
   }

  Put_Piece(x,y);
}

int OPlayer::Replay()
{
  int from_x,from_y,to_x,to_y,kind,kind_c,index;

  if(the_game->getLast_Movment(from_x,from_y,to_x,to_y,kind,kind_c))
   {
     index=Witch_Piece(CHESSBOARD_LEFT+(to_x*CHESSBOARD_WIDTH),CHESSBOARD_TOP+(to_y*CHESSBOARD_HEIGHT));
     if(index==NO_PIECE)
      {
	printf("ERREUR");
	return NO;
      }
     player_piece[index]->Take(from_x,from_y);
     player_piece[index]->Moved--;
     if((kind==PAWN)&&(player_piece[index]->getKind()!=PAWN))
      {
	 Out_Side_Piece(from_x,from_y);
	 delete (player_piece[index]);
	if(identifier==PLAYER1)
	 player_piece[index]=new Pawn(index,this,"Pawn_P1",from_x,from_y);
	else
	 player_piece[index]=new Pawn(index,this,"Pawn_P2",from_x,from_y);
	 Put_Piece(from_x,from_y);
      }
     else
      {
	 if((kind==KING)&&(from_y!=to_y-1)&&(from_y!=to_y+1)&&(from_y!=to_y))
	  {
	    if(to_y==6)
	      {
		player_piece[15]->Take(from_x,7);
		player_piece[15]->Moved--;
	      }
	     else
	      {
		player_piece[8]->Take(from_x,0);
		player_piece[8]->Moved--;
	      }
	  }
      }
     the_game->In_Side_Piece(to_x,to_y,kind_c,identifier);
     if(identifier==PLAYER1)the_game->Replay(PLAYER1);
     else the_game->Replay(PLAYER2);
     return NO;
   }
  return NO;
}