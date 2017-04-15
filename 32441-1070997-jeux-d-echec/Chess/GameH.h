// GameH.h: interface for the Game, Player, Piece, and the ChessBoard class.
//
///////////////////////////////////////////////////////////////////////////

#include <alloc.h>
#include <string.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <dos.h>


//--------------------------------------------------------------------//


const GAME_CONTINUING    =-1;
const GAME_FINE          = 0;
const PLAYER1_ABORT_GAME = 1;
const PLAYER2_ABORT_GAME = 2;
const PLAYER1_WON        = 3;
const PLAYER2_WON        = 4;
const GAME_ERROR         = 5;

const PLAYER1            = 1;
const PLAYER2            = 2;

const NOTHING		 = 0;
const PAUSE		 ='p'; //Pause in the game !!!
const ECHAP		 =27;  //abort the game !!!
const LOSE               =7;   // whene the player know he's the loser.
const REPLAY		 =13;

const CHESSBOARD_TOP     =50;
const CHESSBOARD_LEFT    =150;
const CHESSBOARD_WIDTH   =40;
const CHESSBOARD_HEIGHT  =40;

const NO_PIECE		 =-1;
const PAWN               = 1;
const RIDER		 = 2;
const MAD		 = 3;
const TOWER		 = 4;
const QUEEN		 = 5;
const KING		 = 6;

const NO_BUTTON          = 0;
const LEFT_BUTTON        = 1;
const RIGTH_BUTTON       = 2;

const OK	    = (1==1);
const NO	    = (0==1);


//---------------------------------------------------------------------//
//                           SCREEN && MOUSE                           //
//---------------------------------------------------------------------//

//-------------------------------------------------------------------//

class Mouse
{
  public:
    Mouse();
    ~Mouse();

    void getInformation(int &x,int &y,int &button);
    void setXY(const int x, const int y);
    void Hide();
    void Show();
    void Hande();
    void Init();
  private:
    static int X,Y;
    static int Button;
    void State();
};

//-------------------------------------------------------------//
typedef struct{
		int X,Y;
		unsigned char far *Image;
	       }BitMap;

class Screen
{
  public:
    Screen();
    ~Screen();
    void Mode(char mode);
    void setImage(const int x,const int y,const int width,const int height,BitMap * bitmap);
    void getImage(const int x,const int y,const int width,const int height,BitMap * bitmap);
    void getImage_Transparent(const int x,const int y,const int width,const int height,BitMap * bitmap);
    void setPalette();
    void Clear(unsigned char Color);
    void Fill(const int,const int,const int,const int,unsigned char);
    int  LoadBmpToRC(void far *rc,char *FN);
  private:
};

//------------------------------------------------------------------//
//                            Stack                                 //

class Stack
{
  public:
     Stack();
     ~Stack();
     void Push(int x1,int x2,int x3,int x4,int kind,int kind_c);
     int  Pop(int &x1,int &x2,int &x3,int &x4,int &kind,int &kind_c);
    private:
      int X1,X2,X3,X4,Kind,Kind_c,Nbr_Element;
      Stack * Next;
};

class ChessButton
{
  public:
    ChessButton();
    ChessButton(int x,int y,int width,int height,int color,int bkcolor,char *caption);
    ~ChessButton();
    int Click();
    void Validate();
    void SetCaption(char *caption);
  private:
    char Caption[30];
    int  X,Y,Width,Height;
    int  Color,BkColor;
    void Draw();
};

class ChessEdit
{
  public:
    ChessEdit();
    ChessEdit(int x,int y,int width,int height,int color,int bkcolor,char *text);
    ~ChessEdit();
    void setText();
    void getText(char *text);
    int Click();
    void Validate();
  private:
    char Text[51];
    int  X,Y,Width,Height;
    int  Color,BkColor;
    void Draw();
};

class ChessDialog
{
  public:
    ChessDialog(int x,int y,int width,int height,char *title,char * caption);
    ~ChessDialog();

    virtual int DoModel();
  protected:
   int X,Y,Width,Height;
   char Title[30],Caption[30];
  private:
   void far* BkImage;
   void Draw();
};

class DialogPiece:public ChessDialog
{
  public:
    DialogPiece(int x,int y,int width,int height,char *title,char * caption);
    ~DialogPiece();
    int DoModel();
  private:
   ChessButton *BQ,*BT,*BR,*BM;
};

class DialogQuestion:public ChessDialog
{
  public:
    DialogQuestion(int x,int y,int width,int height,char *title,char * caption);
    ~DialogQuestion();

    int DoModel();
  private:
   ChessButton *BYes,*BNo;
};

class DialogDesign:public ChessDialog
{
  public:
    DialogDesign(int x,int y,int width,int height,char *title,char * caption);
    ~DialogDesign();

    int DoModel();
  private:
   ChessButton *BStandard,*BNew;
};

#define HUMAIN   0
#define COMPUTER 1

class DialogPlayer:public ChessDialog
{
  public:
    DialogPlayer(int x,int y,int width,int height,char *title,char * caption);
    ~DialogPlayer();

    int DoModel();
  
    ChessEdit *Name1,*Name2;
    int P1,P2;
  private:
   ChessButton *BOK;
   ChessButton *HO1,*HO2; 
};

//------------------------------------------------------------------//
//-------------------------------------------------------------------------//
class Game;             // to can declare them in an other class
class Player;           // before to declare them-selves !!!
class Piece;
class Board;


//********************************************************************//
class Player
{
public:
	Player();
	Player(int iden, const char *name, Game * game,const int x,const int y);
	//Player(Player *);
	virtual ~Player();
	void Piece_Die(const int the_piece);
	virtual int Play();
	int getIdentifier();
	void Put_Piece(const int x,const int y);
	void Change_Piece(const int form_x,const int form_y,const int to_x,const int to_y);
	int is_Adversery_in(const int x,const int y);
	int is_Mine_in(const int x,const int y);
	int is_Empty_in(const int x,const int y);
	int Out_Side_Piece(const int x,const int y);
	int In_Side_Piece(const int x,const int y);
	int In_Side_Piece(const int x,const int y,const int kind);
	int Out_Side_Piece_Temp(const int x,const int y);
	int In_Side_Piece_Temp(const int x,const int y);
	int Out_Side_Adversery_Piece(const int x,const int y);
	void In_Side_Adversery_Piece(const int x,const int y);
	int Out_Side_Adversery_Piece_Temp(const int x,const int y);
	void In_Side_Adversery_Piece_Temp(const int x,const int y);
	int I_Take_XY(const int x,const int y);
	int Echec();
	int Echec_To_Me();
	int is_Adversery_King_in(const int x,const int y);
	int is_my_King_in(const int x,const int y);
	virtual int Replay();
	virtual void Change_Pawn(int iden,int x,int y);
	void Validate();
	int getKind(int x,int y);
	int Tower_Not_Moved(int y);
	void Tower_King(int x,int y);
	void Piece_In();
	void Piece_Out();
	int  Echec_And_Mate_To_Me();
	int  Echec_And_Mate();
	int  getPiece_Value(int x,int y);
	int  getMax();
	int  getMaxAdv();

protected:
	void Destroy_Pieces();
	Game * the_game;
	int Init_Pieces();
	int Nbr_of_pieces;
	int Nbr_Piece_In;
	char Name[20];
	int identifier;
	Piece * player_piece[16];

	virtual int Choose_Piece(int & witch_piece);
	virtual int Move_Piece(const int piece);
	int No_King();
	int Witch_Piece(const int x,const int y);

	int X,Y;
	BitMap * Player_Image;
	ChessButton *Replay_Btn;
	ChessEdit   *Text_Name;
	void Draw();
	int X_From,Y_From,X_To,Y_To,Kind,Kind_c;
};

class HPlayer: public Player
{
  public:
	HPlayer(int iden, const char *name, Game * game,const int x,const int y);
	//Player(Player *);
	virtual ~HPlayer();
	virtual int Play();
	virtual int Replay();
	virtual void Change_Pawn(int iden,int x,int y);

  protected:
	virtual int Choose_Piece(int & witch_piece);
	virtual int Move_Piece(const int piece);

};

class OPlayer: public Player
{
  public:
	OPlayer(int iden, const char *name, Game * game,const int x,const int y);
	//Player(Player *);
	virtual ~OPlayer();
	virtual int Play();
	virtual int Replay();
	virtual void Change_Pawn(int iden,int x,int y);

  protected:
	virtual int Choose_Piece(int & witch_piece);
	virtual int Move_Piece(const int piece);

};

//*********************************************************************//

class Board
{
public:
	Board();
	virtual ~Board();
	Board(const int x, const int y, const int width, const int height, Game * const game);
	void Init_Image();
	void Draw();
	void Put_Piece(const int x,const int y,const unsigned char the_player);
	void Change_Piece(const int form_x,const int form_y,const int to_x,const int to_y);
	int is_Adversery_in(const int x,const int y,unsigned char the_player);
	int is_Mine_in(const int x,const int y,unsigned char the_player);
	int is_Empty_in(const int x,const int y);

private:
	Game * the_game;
	int Height;
	int Width;
	int Y;
	int X;
	BitMap * White_Image, * Black_Image;
	BitMap * Board_Image;
	void Destroy_Image();
	void Init_the_board();
	unsigned char the_board[8][8];

	//static char Default_White_Image[CHESSBOARD_WIDTH/2][CHESSBOARD_HEIGHT];
	//static char Default_Black_Image[CHESSBOARD_WIDTH/2][CHESSBOARD_HEIGHT];

};


class Game
{
public:
	Game(char * Dir_Name);
	void Player_destroy(const int ident);
	void Chessboard_destroy();
	Game();
	virtual ~Game();
	int Start();
	void Put_Piece(const int x,const int y,const unsigned char the_player);
	void Change_Piece(const int form_x,const int form_y,const int to_x,const int to_y);
	int is_Adversery_in(const int x,const int y,unsigned char the_player);
	int is_Mine_in(const int x,const int y,unsigned char the_player);
	int is_Empty_in(const int x,const int y);
	int Player_Take_XY(const int x,const int y,const int ident);
	int is_King_in(const int x,const int y,const int iden);
	int Echec(int);
	int Out_Side_Piece(const int x,const int y,const int iden);
	int In_Side_Piece(const int x,const int y,const int iden);
	int In_Side_Piece(const int x,const int y,const int kind,const int iden);
	int Out_Side_Piece_Temp(const int x,const int y,const int iden);
	int In_Side_Piece_Temp(const int x,const int y,const int iden);
	int Replay(const int iden);
	int getLast_Movment(int &from_x,int &from_y,int &to_x,int &to_y,int &kind,int &kind_c);
	void Add_Movment(int X_From,int Y_From,int X_To,int Y_To,int kind,int kind_c);
	void Change_Ressource();
	int getKind(int iden,int x,int y);
	int Echec_And_Mate(int iden);
	int getMax(int iden);

static unsigned char Default_White_Image[CHESSBOARD_WIDTH/2][CHESSBOARD_HEIGHT];
static unsigned char Default_Black_Image[CHESSBOARD_WIDTH/2][CHESSBOARD_HEIGHT];


static unsigned char Default_Player1_Image[CHESSBOARD_WIDTH/2][CHESSBOARD_HEIGHT];
static unsigned char Default_Player2_Image[CHESSBOARD_WIDTH/2][CHESSBOARD_HEIGHT];

static unsigned char Default_Piece_Image[CHESSBOARD_WIDTH/2][CHESSBOARD_HEIGHT];

static unsigned char Default_Pawn_Image2[CHESSBOARD_WIDTH/2][CHESSBOARD_HEIGHT];
static unsigned char Default_Tower_Image2[CHESSBOARD_WIDTH/2][CHESSBOARD_HEIGHT];
static unsigned char Default_Rider_Image2[CHESSBOARD_WIDTH/2][CHESSBOARD_HEIGHT];
static unsigned char Default_Mad_Image2[CHESSBOARD_WIDTH/2][CHESSBOARD_HEIGHT];
static unsigned char Default_King_Image2[CHESSBOARD_WIDTH/2][CHESSBOARD_HEIGHT];
static unsigned char Default_Queen_Image2[CHESSBOARD_WIDTH/2][CHESSBOARD_HEIGHT];

static unsigned char Default_Pawn_Image1[CHESSBOARD_WIDTH/2][CHESSBOARD_HEIGHT];
static unsigned char Default_Tower_Image1[CHESSBOARD_WIDTH/2][CHESSBOARD_HEIGHT];
static unsigned char Default_Rider_Image1[CHESSBOARD_WIDTH/2][CHESSBOARD_HEIGHT];
static unsigned char Default_Mad_Image1[CHESSBOARD_WIDTH/2][CHESSBOARD_HEIGHT];
static unsigned char Default_King_Image1[CHESSBOARD_WIDTH/2][CHESSBOARD_HEIGHT];
static unsigned char Default_Queen_Image1[CHESSBOARD_WIDTH/2][CHESSBOARD_HEIGHT];

	int Save;
private:
	Player * player1;
	Player * player2;
	Board  * chessboard;
	Stack  * my_stack;

	void Load_Ressource(char * Dir);
	void Validate();

};


class Piece
{
public:
	Piece();
	virtual ~Piece();
	Piece(const int ident,Player * owner, const char *name,const int kind,const int x,int const y);
	int is_Me(const int x,const int y);
	int is_King();
	void setXY(const int x,const int y);
	void getXY(int &x,int &y);
	void setXSYS(const int x,const int y);
	void getXSYS(int &x,int &y);
	int setScreen_Position(const int x,const int y);
	virtual int is_Ok_to_take_XSYS();
	void Go_out();
	int  Go_in();
	void Go_out_Temp();
	int Go_in(const int x,const int y);
	int Go_in(const int x,const int y,const int kind);
	int Go_in_Temp(const int x,const int y);
	virtual int Echec()=0;
	int NO_Echec(int,int);
	int is_King(const int x,const int y);
	void Take(const int x,const int y);
	int  getKind();
	void Validate();
	char * getName();
	int Can_Play();
	virtual int getMax(int &x,int &y);
	virtual int Tower_Not_Moved(); //just for the tower !!!
	virtual int getMaxAbs(int &x,int &y){return 0;}
	int TakeOn(int &,int &,int,int);
	void TakeOff(int ,int ,int,int,int);
	int Moved;
protected:

	int identifier_for_my_owner;
	int X,Y;
	int XS,YS; // (X,Y) at the screen !!!
	char Name[15];
	Player * my_owner;
	int Kind;
	int Out;
	int Out_T;

	BitMap * Piece_Image;
	BitMap * Back_Ground;
	//static unsigned char Default_Piece_Image[CHESSBOARD_WIDTH/2][CHESSBOARD_HEIGHT];
	int Assert_Position();
	void Draw();
	void Redraw();
};

//----------------------------------------------------------------//
//                    The real pieces !!!                         //
//----------------------------------------------------------------//
class Pawn : public Piece
{
  public:
	Pawn(const int ident,Player * owner, const char *name,const int x,int const y);
	~Pawn();
	int is_Ok_to_take_XSYS();
	int Echec();
	int getMax(int &x,int &y);
	int getMaxAbs(int &x,int &y);
  private:
	int Advance(const int x,const int y);
	int First_Advance(const int x,const int y);
	int Eat(const int x,const int y);
};

class Tower : virtual public Piece
{
  public:
	Tower(const int ident,Player * owner, const char *name,const int x,int const y);
	~Tower();
	int is_Ok_to_take_XSYS();
	int Move();
	virtual int Echec();
	int echec();
	int Tower_Not_Moved();
	virtual int getMax(int &x,int &y);
	virtual int getMaxAbs(int &x,int &y);
  private:
};

class Rider : public Piece
{
  public:
	Rider(const int ident,Player * owner, const char *name,const int x,int const y);
	~Rider();
	int is_Ok_to_take_XSYS();
	int Echec();
	int getMax(int &x,int &y);
	int getMaxAbs(int &x,int &y);
  private:
};

class Mad : virtual public Piece
{
  public:
	Mad(const int ident,Player * owner, const char *name,const int x,int const y);
	~Mad();
	int is_Ok_to_take_XSYS();
	int Move();
	virtual int Echec();
	int echec();
	virtual int getMax(int &x,int &y);
	virtual int getMaxAbs(int &x,int &y);
  private:
};

class King : public Piece
{
  public:
	King(const int ident,Player * owner, const char *name,const int x,int const y);
	~King();
	int is_Ok_to_take_XSYS();
	int Echec();
	int getMax(int &x,int &y);
	int getMaxAbs(int &x,int &y);
  private:
};

class Queen : public Tower, public Mad
{
  public:
	Queen(const int ident,Player * owner, const char *name,const int x,int const y);
	~Queen();
	int is_Ok_to_take_XSYS();
	int Echec();
	int getMax(int &x,int &y);
	int getMaxAbs(int &x,int &y);
  private:
};

//--------------------       Pieces   ----------------------------//