// Auteur : nicof31@everyday.com


#include <stdlib.h>
#include <string.h>
#include "chess.h"



/////////////
// InitGame()
/////////////
void InitGame(GAME *game, int first_color)
{
  int  l, c;
  

  // Debut de partie
  game->state = NO_CHESS;

  // Couleur qui commence
  game->cur_color = first_color;
  
  // On remplit les cases de l'échiquier
  game->tab[0][0] = game->tab[0][7] = ROOK;
  game->tab[0][1] = game->tab[0][6] = KNIGHT;
  game->tab[0][2] = game->tab[0][5] = BISHOP;
  game->tab[0][3] = KING;
  game->tab[0][4] = QUEEN;
  
  for(c = 0; c < 8; c++)
    game->tab[1][c] = PAWN;

  for(l = 2; l < 6; l++)
    for(c = 0; c < 8; c++)
      game->tab[l][c] = NONE;

  for(c = 0; c < 8; c++)
    game->tab[6][c] = -PAWN;

  game->tab[7][0] = game->tab[7][7] = -ROOK;
  game->tab[7][1] = game->tab[7][6] = -KNIGHT;
  game->tab[7][2] = game->tab[7][5] = -BISHOP;
  game->tab[7][3] = -KING;
  game->tab[7][4] = -QUEEN;

  // On initialise la valeur de chaque piece
  piece_values[KING]   = 100000000;
  piece_values[QUEEN]  = 10000;
  piece_values[BISHOP] = 3000;
  piece_values[KNIGHT] = 3000;
  piece_values[ROOK]   = 5000;
  piece_values[PAWN]   = 1000;

  // On initialise les bonus ajoute aux pieces en fonctions de leur position
  memset(piece_position_bonus, 0, sizeof(piece_position_bonus));
  //piece_position_bonus[KNIGHT][0][0] = 

  // On initialise la selection courante pour le premier tour (aucune piece selectionnee)
  game->cur_sel_state = SELECTION_ERROR;
}


////////////////
// IsColonFree()
////////////////
int IsColonFree(GAME *game, int c, int l1, int l2)
{
  int  l, step_l;


  step_l = (l2 - l1) > 0 ? 1: -1;

  for(l = l1 + step_l; l != l2; l += step_l)
  {
    if(game->tab[l][c] != NONE)
      return 0;
  }

  return 1;
}


//////////////
// IsRowFree()
//////////////
int IsRowFree(GAME *game, int l, int c1, int c2)
{
  int  c, step_c;
  

  step_c = (c2 - c1) > 0 ? 1: -1;

  for(c = c1 + step_c; c != c2; c += step_c)
  {
    if(game->tab[l][c] != NONE)
      return 0;
  }

  return 1;
}


///////////////////
// IsDiagonalFree()
///////////////////
int IsDiagonalFree(GAME *game, int l1, int c1, int l2, int c2)
{
  int  l, c, step_l, step_c;


  step_l = (l2 - l1) > 0 ? 1: -1;
  step_c = (c2 - c1) > 0 ? 1: -1;

  for(l = l1 + step_l, c = c1 + step_c; l != l2; l += step_l, c += step_c)
  {
    if(game->tab[l][c] != NONE)
      return 0;
  }

  return 1;
}


//////////////////
// CheckForChess()
//////////////////
int CheckForChess(GAME *game, int color)
{
  int   score, state;
  MOVE  best_move;


  score = abs(GetBestMove(&best_move, game, -color, 1, 1));

  if(score > (piece_values[KING] / 10))
  {
    state = IN_CHESS;

    // S'il y a echec, on verifie s'il s'agit d'un echec et mat
    score = abs(GetBestMove(&best_move, game, color, 1, 1));

    if(score > (piece_values[KING] / 10))
    {
      state = CHESS_MATE;
    }
  }
  else
  {
    state = NO_CHESS;
  }

  return state;
}


////////////////
// SelectPiece()
////////////////
int SelectPiece(GAME *game, int l, int c)
{
  // La selection est effectuee si la case choisie est occupee par une piece de la couleur 'color'
  if(game->tab[l][c] * game->cur_color > 0)
  {
    game->cur_sel_pos.l = l;
    game->cur_sel_pos.c = c;
    
    game->cur_sel_state = SELECTION_OK;
  }

  return game->cur_sel_state;
}


//////////////
// MovePiece()
//////////////
int MovePiece(GAME *game, int l2, int c2)
{
  int  l1, c1;
  int  piece, arrival;
  int  move_possible;
  int  sav_arrival;


  if(game->cur_sel_state == SELECTION_OK)
  {
    l1 = game->cur_sel_pos.l;
    c1 = game->cur_sel_pos.c;
    
    arrival = game->tab[l1][c1] * game->tab[l2][c2];
    piece = abs(game->tab[l1][c1]);

    move_possible = 0;
    
    // La case d'arrivee est soit inoccupee, soit occupee par une piece d'une autre couleur
    if(arrival <= 0)
    {
      // Deplacement du roi
      if(piece & KING)
      {
        if(abs(l2 - l1) <= 1 && abs(c2 - c1) <= 1)
        {
          move_possible = 1;
        }
      }
      // Deplacement de la reine
      else if(piece & QUEEN)
      {
        if(l2 == l1)
        {
          move_possible = IsRowFree(game, l1, c1, c2);
        }
        else if(c2 == c1)
        {
          move_possible = IsColonFree(game, c1, l1, l2);
        }
        else if(abs(l2 - l1) == abs(c2 - c1))
        {
          move_possible = IsDiagonalFree(game, l1, c1, l2, c2);
        }
      }
      // Deplacement du fou
      else if(piece & BISHOP)
      {
        if(abs(l2 - l1) == abs(c2 - c1))
        {
          move_possible = IsDiagonalFree(game, l1, c1, l2, c2);
        }
      }
      // Deplacement du cavalier
      else if(piece & KNIGHT)
      {
        if((abs(l2 - l1) == 2 && abs(c2 - c1) == 1) || (abs(l2 - l1) == 1 && abs(c2 - c1) == 2))
        {
          move_possible = 1;
        }
      }
      // Deplacement de la tour
      else if(piece & ROOK)
      {
        if(l2 == l1)
        {
          move_possible = IsRowFree(game, l1, c1, c2);
        }
        else if(c2 == c1)
        {
          move_possible = IsColonFree(game, c1, l1, l2);
        }
      }
      // Deplacement du pion
      else if(piece & PAWN)
      {
        // Le pion ne mange pas
        if(arrival == 0 && c2 == c1)
        {
          if((l2 - l1) == (1 * game->cur_color))
          {
            move_possible = 1;
          }
          else
          {
            if(l1 == 1 && (l2 - l1) == 2 && game->tab[2][c2] == NONE)
            {
              move_possible = 1;
            }
            else if(l1 == 6 && (l2 - l1) == -2 && game->tab[5][c2] == NONE)
            {
              move_possible = 1;
            }
          }
        }
        // Le pion mange
        else if(arrival < 0)
        {
          if((l2 - l1) == (1 * game->cur_color) && abs(c2 - c1) == 1)
          {
            move_possible = 1;
          }
        }
      }
    }

    // Si un deplacement est possible, on le fait
    if(move_possible)
    {
      sav_arrival = game->tab[l2][c2];
      game->tab[l2][c2] = game->tab[l1][c1];
      game->tab[l1][c1] = NONE;

      if(CheckForChess(game, game->cur_color) == NO_CHESS)
      {
        // On invalide la selection de la piece courante
        game->cur_sel_state = SELECTION_ERROR;
        
        // Le delacement est correct
        return MOVE_OK;
      }
      else
      {
        game->tab[l1][c1] = game->tab[l2][c2];
        game->tab[l2][c2] = sav_arrival;
      }
    }
  }

  return MOVE_ERROR;
}


////////////
// AddMove()
////////////
void AddMove(MOVE *move, int *n, int l1, int c1, int l2, int c2)
{
  MOVE  *next, *cur_move;


  if(move != NULL)
  {
    next = move;
    while(next->next_move != NULL)
    {
      next = (MOVE *)next->next_move;
    }

    cur_move = malloc(sizeof(MOVE));

    cur_move->l1 = l1;
    cur_move->c1 = c1;
    cur_move->l2 = l2;
    cur_move->c2 = c2;
    cur_move->next_move = NULL;
    
    next->next_move = cur_move;
  }

  (*n)++;
}


/////////////////////
// GenerateMoveList()
/////////////////////
int GenerateMoveList(GAME *game, int color, MOVE *move)
{
  int  l, c, i, j;
  int  piece, square;
  int  nb_moves;
   
  
  // On initialise la liste chainee des coups
  // Dans la premiere structure, seul le pointeur est utilise
  // La liste commence veritablement a partir du 2eme maillon
  // Ainsi, on evite la gestion particuliere du premier maillon
  if(move != NULL)
  {
    move->next_move = NULL;
  }

  nb_moves = 0;

  for(l = 0; l < 8; l++)
  {
    for(c = 0; c < 8; c++)
    {
      // Sélection d'une piece de la couleur 'color'
      if(game->tab[l][c] * color <= 0)
        continue;

      piece = abs(game->tab[l][c]);

      // Mouvements du roi
      if(piece & KING)
      {
        if(l >= 1)
        {
          if(game->tab[l][c] * game->tab[l-1][c] <= 0)
            AddMove(move, &nb_moves, l, c, l-1, c);

          if(c >= 1 && (game->tab[l][c] * game->tab[l-1][c-1]) <= 0)
            AddMove(move, &nb_moves, l, c, l-1, c-1);
          
          if(c <= 6 && (game->tab[l][c] * game->tab[l-1][c+1]) <= 0)
            AddMove(move, &nb_moves, l, c, l-1, c+1);
        }
        if(l <= 6)
        {
          if(game->tab[l][c] * game->tab[l+1][c] <= 0)
            AddMove(move, &nb_moves, l, c, l+1, c);

          if(c >= 1 && (game->tab[l][c] * game->tab[l+1][c-1]) <= 0)
            AddMove(move, &nb_moves, l, c, l+1, c-1);
          
          if(c <= 6 && (game->tab[l][c] * game->tab[l+1][c+1]) <= 0)
            AddMove(move, &nb_moves, l, c, l+1, c+1);
        }
        if(c >= 1 && (game->tab[l][c] * game->tab[l][c-1]) <= 0)
        {
          AddMove(move, &nb_moves, l, c, l, c-1);
        }
        if(c <= 6 && (game->tab[l][c] * game->tab[l][c+1]) <= 0)
        {
          AddMove(move, &nb_moves, l, c, l, c+1);
        }
        // Gestion des roques
        /*if(color == WHITE)
        {
          if(l == 0 && c == 3)
          {
            if(tab[0][0] == ROOK && tab[0][1] == NONE && tab[0][2] == NONE)
            {
              AddMove();
            }
            if(tab[0][7] == ROOK && tab[0][4] == NONE && tab[0][5] == NONE && tab[0][6] == NONE)
            {
              AddMove();
            }
          }
        }
        else
        {
        }*/
      }
      // Mouvements du cavalier
      else if(piece & KNIGHT)
      {
        if(l >= 2)
        {
          if(c >= 1 && (game->tab[l][c] * game->tab[l-2][c-1]) <= 0)
            AddMove(move, &nb_moves, l, c, l-2, c-1);

          if(c <= 6 && (game->tab[l][c] * game->tab[l-2][c+1]) <= 0)
            AddMove(move, &nb_moves, l, c, l-2, c+1);
        }
        if(l >= 1)
        {
          if(c >= 2 && (game->tab[l][c] * game->tab[l-1][c-2]) <= 0)
            AddMove(move, &nb_moves, l, c, l-1, c-2);

          if(c <= 5 && (game->tab[l][c] * game->tab[l-1][c+2]) <= 0)
            AddMove(move, &nb_moves, l, c, l-1, c+2);
        }
        if(l <= 5)
        {
          if(c >= 1 && (game->tab[l][c] * game->tab[l+2][c-1]) <= 0)
            AddMove(move, &nb_moves, l, c, l+2, c-1);

          if(c <= 6 && (game->tab[l][c] * game->tab[l+2][c+1]) <= 0)
            AddMove(move, &nb_moves, l, c, l+2, c+1);
        }
        if(l <= 6)
        {
          if(c >= 2 && (game->tab[l][c] * game->tab[l+1][c-2]) <= 0)
            AddMove(move, &nb_moves, l, c, l+1, c-2);

          if(c <= 5 && (game->tab[l][c] * game->tab[l+1][c+2]) <= 0)
            AddMove(move, &nb_moves, l, c, l+1, c+2);
        }
      }
      // Mouvements du pion
      else if(piece & PAWN)
      {
        if(color == WHITE)
        {
          if(l <= 6)
          {
            if(c >= 1 && game->tab[l+1][c-1] < 0)
              AddMove(move, &nb_moves, l, c, l+1, c-1);

            if(c <= 6 && game->tab[l+1][c+1] < 0)
              AddMove(move, &nb_moves, l, c, l+1, c+1);

            if(game->tab[l+1][c] == NONE)
            {
              AddMove(move, &nb_moves, l, c, l+1, c);

              if(l == 1 && game->tab[3][c] == NONE)
                AddMove(move, &nb_moves, 1, c, 3, c);
            }
          }
        }
        else
        {
          if(l >= 1)
          {
            if(c >= 1 && game->tab[l-1][c-1] > 0)
              AddMove(move, &nb_moves, l, c, l-1, c-1);

            if(c <= 6 && game->tab[l-1][c+1] > 0)
              AddMove(move, &nb_moves, l, c, l-1, c+1);

            if(game->tab[l-1][c] == NONE)
            {
              AddMove(move, &nb_moves, l, c, l-1, c);

              if(l == 6 && game->tab[4][c] == NONE)
                AddMove(move, &nb_moves, 6, c, 4, c);
            }
          }
        }
      }
      // Mouvements de la tour
      else if(piece & ROOK)
      {
        // Mouvements possibles sur la colonne, en bas
        for(i = l+1; i < 8; i++)
        {
          square = game->tab[l][c] * game->tab[i][c];

          if(square == 0)
          {
            AddMove(move, &nb_moves, l, c, i, c);
          }
          else if(square < 0)
          {
            AddMove(move, &nb_moves, l, c, i, c);
            break;
          }
          else
          {
            break;
          }
        }
        // Mouvements possibles sur la colonne, en haut
        for(i = l-1; i >= 0; i--)
        {
          square = game->tab[l][c] * game->tab[i][c];

          if(square == 0)
          {
            AddMove(move, &nb_moves, l, c, i, c);;
          }
          else if(square < 0)
          {
            AddMove(move, &nb_moves, l, c, i, c);
            break;
          }
          else
          {
            break;
          }
        }
        // Mouvements possibles sur la ligne, a droite
        for(i = c+1; i < 8; i++)
        {
          square = game->tab[l][c] * game->tab[l][i];

          if(square == 0)
          {
            AddMove(move, &nb_moves, l, c, l, i);
          }
          else if(square < 0)
          {
            AddMove(move, &nb_moves, l, c, l, i);
            break;
          }
          else
          {
            break;
          }
        }
        // Mouvements possibles sur la ligne, a gauche
        for(i = c-1; i >= 0; i--)
        {
          square = game->tab[l][c] * game->tab[l][i];

          if(square == 0)
          {
            AddMove(move, &nb_moves, l, c, l, i);
          }
          else if(square < 0)
          {
            AddMove(move, &nb_moves, l, c, l, i);
            break;
          }
          else
          {
            break;
          }
        }
      }
      // Mouvements du fou
      else if(piece & BISHOP)
      {
        // Mouvements possibles sur la diagonale bas, droite
        for(i = l+1, j = c+1; i < 8 && j < 8; i++, j++)
        {
          square = game->tab[l][c] * game->tab[i][j];

          if(square == 0)
          {
            AddMove(move, &nb_moves, l, c, i, j);
          }
          else if(square < 0)
          {
            AddMove(move, &nb_moves, l, c, i, j);
            break;
          }
          else
          {
            break;
          }
        }
        // Mouvements possibles sur la diagonale bas, gauche
        for(i = l+1, j = c-1; i < 8 && j >= 0; i++, j--)
        {
          square = game->tab[l][c] * game->tab[i][j];

          if(square == 0)
          {
            AddMove(move, &nb_moves, l, c, i, j);
          }
          else if(square < 0)
          {
            AddMove(move, &nb_moves, l, c, i, j);
            break;
          }
          else
          {
            break;
          }
        }
        // Mouvements possibles sur la diagonale haut, droite
        for(i = l-1, j = c+1; i >= 0 && j < 8; i--, j++)
        {
          square = game->tab[l][c] * game->tab[i][j];

          if(square == 0)
          {
            AddMove(move, &nb_moves, l, c, i, j);
          }
          else if(square < 0)
          {
            AddMove(move, &nb_moves, l, c, i, j);
            break;
          }
          else
          {
            break;
          }
        }
        // Mouvements possibles sur la diagonale haut, gauche
        for(i = l-1, j = c-1; i >= 0 && j >= 0; i--, j--)
        {
          square = game->tab[l][c] * game->tab[i][j];

          if(square == 0)
          {
            AddMove(move, &nb_moves, l, c, i, j);
          }
          else if(square < 0)
          {
            AddMove(move, &nb_moves, l, c, i, j);
            break;
          }
          else
          {
            break;
          }
        }
      }
      // Mouvements de la dame
      else if(piece && QUEEN)
      {
        // Mouvements possibles sur la colonne, en bas
        for(i = l+1; i < 8; i++)
        {
          square = game->tab[l][c] * game->tab[i][c];

          if(square == 0)
          {
            AddMove(move, &nb_moves, l, c, i, c);
          }
          else if(square < 0)
          {
            AddMove(move, &nb_moves, l, c, i, c);
            break;
          }
          else
          {
            break;
          }
        }
        // Mouvements possibles sur la colonne, en haut
        for(i = l-1; i >= 0; i--)
        {
          square = game->tab[l][c] * game->tab[i][c];

          if(square == 0)
          {
            AddMove(move, &nb_moves, l, c, i, c);;
          }
          else if(square < 0)
          {
            AddMove(move, &nb_moves, l, c, i, c);
            break;
          }
          else
          {
            break;
          }
        }
        // Mouvements possibles sur la ligne, a droite
        for(i = c+1; i < 8; i++)
        {
          square = game->tab[l][c] * game->tab[l][i];

          if(square == 0)
          {
            AddMove(move, &nb_moves, l, c, l, i);
          }
          else if(square < 0)
          {
            AddMove(move, &nb_moves, l, c, l, i);
            break;
          }
          else
          {
            break;
          }
        }
        // Mouvements possibles sur la ligne, a gauche
        for(i = c-1; i >= 0; i--)
        {
          square = game->tab[l][c] * game->tab[l][i];

          if(square == 0)
          {
            AddMove(move, &nb_moves, l, c, l, i);
          }
          else if(square < 0)
          {
            AddMove(move, &nb_moves, l, c, l, i);
            break;
          }
          else
          {
            break;
          }
        }
        // Mouvements possibles sur la diagonale bas, droite
        for(i = l+1, j = c+1; i < 8 && j < 8; i++, j++)
        {
          square = game->tab[l][c] * game->tab[i][j];

          if(square == 0)
          {
            AddMove(move, &nb_moves, l, c, i, j);
          }
          else if(square < 0)
          {
            AddMove(move, &nb_moves, l, c, i, j);
            break;
          }
          else
          {
            break;
          }
        }
        // Mouvements possibles sur la diagonale bas, gauche
        for(i = l+1, j = c-1; i < 8 && j >= 0; i++, j--)
        {
          square = game->tab[l][c] * game->tab[i][j];

          if(square == 0)
          {
            AddMove(move, &nb_moves, l, c, i, j);
          }
          else if(square < 0)
          {
            AddMove(move, &nb_moves, l, c, i, j);
            break;
          }
          else
          {
            break;
          }
        }
        // Mouvements possibles sur la diagonale haut, droite
        for(i = l-1, j = c+1; i >= 0 && j < 8; i--, j++)
        {
          square = game->tab[l][c] * game->tab[i][j];

          if(square == 0)
          {
            AddMove(move, &nb_moves, l, c, i, j);
          }
          else if(square < 0)
          {
            AddMove(move, &nb_moves, l, c, i, j);
            break;
          }
          else
          {
            break;
          }
        }
        // Mouvements possibles sur la diagonale haut, gauche
        for(i = l-1, j = c-1; i >= 0 && j >= 0; i--, j--)
        {
          square = game->tab[l][c] * game->tab[i][j];

          if(square == 0)
          {
            AddMove(move, &nb_moves, l, c, i, j);
          }
          else if(square < 0)
          {
            AddMove(move, &nb_moves, l, c, i, j);
            break;
          }
          else
          {
            break;
          }
        }
      }
    }
  }

  return nb_moves;
}


/////////////
// MakeMove()
/////////////
void MakeMove(GAME *game, MOVE *cur_move, int *sav_arrival)
{
  // Gestion speciale des roques (car plus de 2 mouvements de pieces)
  /*if(cur_move->l1 | CASTLING)
  {
    if(cur_move->l1 | WHITE_CASTLING)
    {
      color = WHITE;
      row = 0;
    }
    else if(cur_move->l1 | BLACK_CASTLING)
    {
      color = BLACK
      row = 7;
    }

    if(cur_move->l1 | SMALL_CASTLING)
    {
      game->tab[row][1] = KING * color;
      game->tab[row][3] = NONE;
      game->tab[row][2] = ROOK * color;
      game->tab[row][0] = NONE;
    }
    else if(cur_move->l1 | BIG_CASTLING)
    {
      game->tab[row][5] = KING * color;
      game->tab[row][3] = NONE;
      game->tab[row][4] = ROOK * color;
      game->tab[row][7] = NONE;
    }
  }
  // Deplacements normaux
  else
  {*/
    // Sauvegarde de la case d'arrivee (si ecrasement)
    *sav_arrival = game->tab[cur_move->l2][cur_move->c2];
    game->tab[cur_move->l2][cur_move->c2] = game->tab[cur_move->l1][cur_move->c1];
    game->tab[cur_move->l1][cur_move->c1] = NONE;
  //}
}


///////////////
// UnmakeMove()
///////////////
void UnmakeMove(GAME *game, MOVE *cur_move, int sav_arrival)
{
  // Gestion des roques
  /*if(cur_move->l1 | CASTLING)
  {
    if(cur_move->l1 | WHITE_CASTLING)
    {
      color = WHITE;
      row = 0;
    }
    else if(cur_move->l1 | BLACK_CASTLING)
    {
      color = BLACK
      row = 7;
    }

    if(cur_move->l1 | SMALL_CASTLING)
    {
      game->tab[row][1] = NONE;
      game->tab[row][3] = KING * color;
      game->tab[row][2] = NONE;
      game->tab[row][0] = ROOK * color;
    }
    else if(cur_move->l1 | BIG_CASTLING)
    {
      game->tab[row][5] = NONE;
      game->tab[row][3] = KING * color;
      game->tab[row][4] = NONE;
      game->tab[row][7] = ROOK * color;
    }
  }
  // Deplacements normaux
  else
  {*/
    game->tab[cur_move->l1][cur_move->c1] = game->tab[cur_move->l2][cur_move->c2];
    game->tab[cur_move->l2][cur_move->c2] = sav_arrival;
  //}
}


////////////////
// GetBestMove()
////////////////
int GetBestMove(MOVE *best_move, GAME *game, int color, int depth, int org_depth)
{
  MOVE        move;
  MOVE        *cur_move;
  int         score, best_score;
  int         sav_arrival;
    

  if(depth == 0)
  {
    score = EvaluateGame(game);
    return score;
  }
  else
  {
    GenerateMoveList(game, color, &move);

    score = -color * INF;
    best_score = score;

    cur_move = (MOVE *)(move.next_move);
    while(cur_move != NULL)
    {
      MakeMove(game, cur_move, &sav_arrival);
      score = GetBestMove(best_move, game, -color, depth-1, org_depth);
      UnmakeMove(game, cur_move, sav_arrival);
      
      if((color == WHITE && score > best_score) || (color == BLACK && score < best_score))
      {
        best_score = score;

        if(depth == org_depth)
        {
          best_move->l1 = cur_move->l1;
          best_move->c1 = cur_move->c1;
          best_move->l2 = cur_move->l2;
          best_move->c2 = cur_move->c2;
        }
      }

      cur_move = (MOVE *)(cur_move->next_move);
    }

    return best_score;
  }
}


/////////////////
// EvaluateGame()
/////////////////
int EvaluateGame(GAME *game)
{
  int  l, c;
  int  piece;
  int  score;
    
  
  score = 0;

  for(l = 0; l < 8; l++)
  {
    for(c = 0; c < 8; c++)
    {
      if(game->tab[l][c] == NONE)
        continue;

      piece = abs(game->tab[l][c]);
      
      // on effectue une 1ere evaluation fonction uniquement des possessions materielles des 2 camps
      // ainsi qu'une 2eme evaluation, en meme temps, fonction de l'emplacement des pieces sur l'echiquier
      
      if(game->tab[l][c] > 0)
      {
        score = score + piece_values[piece] + piece_position_bonus[piece][l][c];
      }
      else
      {
        score = score - piece_values[piece] - piece_position_bonus[piece][l][c];
      }
    }
  }

  // 3eme evaluation fonction du nombre de deplacements possibles
  // 1/10 de points du PION sont attribues pour chaque deplacement possible
  score += (GenerateMoveList(game, WHITE, NULL) - GenerateMoveList(game, BLACK, NULL)) * (piece_values[PAWN] / 10);

  return score;
}