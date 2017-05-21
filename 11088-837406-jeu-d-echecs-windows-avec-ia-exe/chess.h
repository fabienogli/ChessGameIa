// Auteur : nicof31@everyday.com


#ifndef  chess_h
#define  chess_h



#define  INF              100000000

#define  SQUARE_LENGHT    64
#define  PIECE_LENGHT     32

#define  WHITE            1
#define  BLACK            -1
#define  NONE             0

#define  KING             1
#define  QUEEN            2 
#define  BISHOP           4
#define  KNIGHT           8
#define  ROOK             16
#define  PAWN             32

#define  NO_CHESS         1
#define  IN_CHESS         2
#define  CHESS_MATE       4

#define  CASTLING         128
#define  WHITE_CASTLING   256
#define  BLACK_CASTLING   512
#define  SMALL_CASTLING   1024
#define  BIG_CASTLING     2048

#define  SELECTION_ERROR  0
#define  SELECTION_OK     1

#define  MOVE_ERROR       0
#define  MOVE_OK          1


typedef struct
{
  int           l1, c1, l2, c2;
  struct MOVE   *next_move;
} MOVE;

typedef struct
{
  int  l, c;
} POSITION;

typedef struct
{
  int       tab[8][8];
  
  int       cur_color;
  int       cur_sel_state;
  POSITION  cur_sel_pos;

  int       state;

  MOVE      *movelist;
} GAME;


int  piece_values[PAWN+1];            // seules les cases 1, 2, 4, 8, 16, 32 sont utilisees -> astuce pour gagner du temps de calcul -> voir EvaluateGame()
                                      // comme le pion a la plus grande valeur, le tableau comporte PAWN+1 cases
int  piece_position_bonus[PAWN+1][8][8]; // idem, mais il s'agit de bonus ou de malus ajoute selon la position de la piece
                                         // les cases centrales ont les plus forts bonus -> possession du centre de l'echiquier

void InitGame(GAME *game, int first_color);
int  IsColonFree(GAME *game, int c, int l1, int l2);
int  IsRowFree(GAME *game, int l, int c1, int c2);
int  IsDiagonalFree(GAME *game, int l1, int c1, int l2, int c2);
int  CheckForChess(GAME *game, int color);
int  SelectPiece(GAME *game, int l, int c);
int  MovePiece(GAME *game, int l2, int c2);
void AddMove(MOVE *move, int *n, int l1, int c1, int l2, int c2);
int  GenerateMoveList(GAME *game, int color, MOVE *move);
int  GetBestMove(MOVE *best_move, GAME *game, int color, int depth, int org_depth);
int  EvaluateGame(GAME *game);



#endif // chess_h