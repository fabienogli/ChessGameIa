// Auteur : nicof31@everyday.com


#include <stdio.h>
#include <windows.h>
#include "chess.h"
#include "resource.h"



LPARAM CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  static HINSTANCE    hInstance;
  static HDC          hdc, hdcMemPiece, hdcMemKing, hdcMemQueen, hdcMemBishop, hdcMemKnight, hdcMemRook, hdcMemPawn;
  static HBITMAP      hBmpKing, hBmpQueen, hBmpBishop, hBmpKnight, hBmpRook, hBmpPawn;
  static PAINTSTRUCT  ps;
  static HBRUSH       brush, brush_even, brush_odd;
  static GAME         game;
  static MOVE         best_move;
  static int          l, c, x, y;
  static int          move_state;
  static int          shift;
  static char         buffer[50];
  

  switch(message)
  {
  case WM_CREATE:
    InitGame(&game, WHITE);

    shift = (SQUARE_LENGHT - PIECE_LENGHT) / 2;
    
    brush_even = CreateSolidBrush(RGB(182, 192, 192));
    brush_odd  = CreateSolidBrush(RGB(0, 174, 174));

    hInstance = ((LPCREATESTRUCT)lParam)->hInstance;
    
    hBmpKing   = LoadBitmap(hInstance, "BMP_KING");
    hBmpQueen  = LoadBitmap(hInstance, "BMP_QUEEN");
    hBmpBishop = LoadBitmap(hInstance, "BMP_BISHOP");
    hBmpKnight = LoadBitmap(hInstance, "BMP_KNIGHT");
    hBmpRook   = LoadBitmap(hInstance, "BMP_ROOK");
    hBmpPawn   = LoadBitmap(hInstance, "BMP_PAWN");

    hdc = GetDC(hwnd);
    
    hdcMemKing   = CreateCompatibleDC(hdc);
    hdcMemQueen  = CreateCompatibleDC(hdc);
    hdcMemBishop = CreateCompatibleDC(hdc);
    hdcMemKnight = CreateCompatibleDC(hdc);
    hdcMemRook   = CreateCompatibleDC(hdc);
    hdcMemPawn   = CreateCompatibleDC(hdc);

    SelectObject(hdcMemKing,   hBmpKing);
    SelectObject(hdcMemQueen,  hBmpQueen);
    SelectObject(hdcMemBishop, hBmpBishop);
    SelectObject(hdcMemKnight, hBmpKnight);
    SelectObject(hdcMemRook,   hBmpRook);
    SelectObject(hdcMemPawn,   hBmpPawn);

    return 0;

  case WM_PAINT:
    hdc = BeginPaint(hwnd, &ps);

    SelectObject(hdc, CreatePen(PS_NULL, 0, 0));

    // On dessine l'echiquier et on place les pieces
    for(l = 0, brush = brush_even; l < 8; l++)
    {
      for(c = 0; c < 8; c++)
      {
        SelectObject(hdc, brush);
        Rectangle(hdc, c * SQUARE_LENGHT, l * SQUARE_LENGHT, (c + 1) * SQUARE_LENGHT + 1, (l + 1) * SQUARE_LENGHT + 1);

        if(game.tab[l][c] != NONE)
        {
          if(abs(game.tab[l][c]) & KING)
          {
            hdcMemPiece = hdcMemKing;
          }
          else if(abs(game.tab[l][c]) & QUEEN)
          {
            hdcMemPiece = hdcMemQueen;
          }
          else if(abs(game.tab[l][c]) & BISHOP)
          {
            hdcMemPiece = hdcMemBishop;
          }
          else if(abs(game.tab[l][c]) & KNIGHT)
          {
            hdcMemPiece = hdcMemKnight;
          }
          else if(abs(game.tab[l][c]) & ROOK)
          {
            hdcMemPiece = hdcMemRook;
          }
          else if(abs(game.tab[l][c]) & PAWN)
          {
            hdcMemPiece = hdcMemPawn;
          }
          
          if(game.tab[l][c] < 0)
          {
            BitBlt(hdc, c * SQUARE_LENGHT + shift, l * SQUARE_LENGHT + shift, SQUARE_LENGHT, SQUARE_LENGHT, hdcMemPiece, 0, 0, SRCAND);
          }
          else
          {
            BitBlt(hdc, c * SQUARE_LENGHT + shift, l * SQUARE_LENGHT + shift, SQUARE_LENGHT, SQUARE_LENGHT, hdcMemPiece, 0, 0, MERGEPAINT);
          }
        }

        brush = (brush == brush_even) ? brush_odd: brush_even;
      }
      brush = (brush == brush_even) ? brush_odd: brush_even;
    }

    
    // On verifie si un des 2 joueurs est en echec ou echec et mat
    if(game.state == NO_CHESS)
    {
      sprintf(buffer, "Les %s jouent", (game.cur_color == WHITE) ? "blancs": "noirs");
      TextOut(hdc, 0, 8 * SQUARE_LENGHT, buffer, lstrlen(buffer));
    }
    else if(game.state == IN_CHESS)
    {
      sprintf(buffer, "Roi %s en echec!", (game.cur_color == WHITE) ? "blanc": "noir");
      TextOut(hdc, 0, 8 * SQUARE_LENGHT, buffer, lstrlen(buffer));
    }
    else if(game.state == CHESS_MATE)
    {
      sprintf(buffer, "Roi %s en echec et mat!", (game.cur_color == WHITE) ? "blanc": "noir");
      TextOut(hdc, 0, 8 * SQUARE_LENGHT, buffer, lstrlen(buffer));
    }
    // Affichage des informations (score, echec...) sous le plateau de jeu
    sprintf(buffer, "Score : %d", EvaluateGame(&game));
    TextOut(hdc, 0, 8 * SQUARE_LENGHT + 15, buffer, lstrlen(buffer));


    // Un joueur a selectionne une case valide : on encadre cette case en rouge
    if(game.state != CHESS_MATE && game.cur_sel_state == SELECTION_OK)
    {
      SelectObject(hdc, CreatePen(PS_SOLID, 2, RGB(255, 0, 0)));
      SelectObject(hdc, GetStockObject(NULL_BRUSH));

      Rectangle(hdc, game.cur_sel_pos.c * SQUARE_LENGHT + 1, game.cur_sel_pos.l * SQUARE_LENGHT + 1, (game.cur_sel_pos.c + 1) * SQUARE_LENGHT, (game.cur_sel_pos.l + 1) * SQUARE_LENGHT);
    }

    // C'est a l'ordinateur de jouer
    if(game.state != CHESS_MATE && game.cur_color == BLACK)
    {
      // Calcul du coup que va jouer l'ordinateur
      GetBestMove(&best_move, &game, BLACK, 3, 3);

      game.tab[best_move.l2][best_move.c2] = game.tab[best_move.l1][best_move.c1];
      game.tab[best_move.l1][best_move.c1] = NONE;
      
      // On effectue le deplacement
      //SelectPiece(&game, best_move.l1, best_move.c1);
      //MovePiece(&game, best_move.l2, best_move.c2);

      // Changement de joueur
      game.cur_color = WHITE;
            
      // On regarde si l'autre joueur est en position d'echec, echec et mat ou rien
      game.state = CheckForChess(&game, game.cur_color);
                    
      InvalidateRect(hwnd, NULL, TRUE);
    }

    EndPaint(hwnd, &ps);
    return 0;

  case WM_LBUTTONDOWN:
    // C'est au joueur humain de jouer
    if(game.state != CHESS_MATE && game.cur_color == WHITE)
    {
      x = LOWORD(lParam);
      y = HIWORD(lParam);

      l = y / SQUARE_LENGHT;
      c = x / SQUARE_LENGHT;

      if(l >= 0 && l < 8 && c >= 0 && c < 8)
      {
        if(SelectPiece(&game, l, c) == SELECTION_OK)
        {
          InvalidateRect(hwnd, NULL, FALSE);
        }

        if(game.cur_sel_state == SELECTION_OK)
        {
          move_state = MovePiece(&game, l, c);

          if(move_state)
          {
            // Changement de joueur
            game.cur_color = BLACK;
            
            // On regarde si l'autre joueur est en position d'echec, echec et mat ou rien
            game.state = CheckForChess(&game, game.cur_color);
                    
            InvalidateRect(hwnd, NULL, TRUE);
          }
        }
      }
    }
    return 0;

  case WM_DESTROY:
    PostQuitMessage(0);
    return 0;
  }

  return DefWindowProc(hwnd, message, wParam, lParam);
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int iCmdShow)
{
  HWND      hwnd;
  MSG       msg;
  WNDCLASS  wndclass;
  char      szAppName[] = "Jeu d'échecs (par Caribou)";
  int       cxScreen, cyScreen;
  int       width, height;


  wndclass.style         = CS_HREDRAW | CS_VREDRAW;
  wndclass.lpfnWndProc   = WndProc;
  wndclass.cbClsExtra    = 0;
  wndclass.cbWndExtra    = 0;
  wndclass.hInstance     = hInstance;
  wndclass.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
  wndclass.hCursor       = LoadCursor(NULL, IDC_ARROW);
  wndclass.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
  wndclass.lpszMenuName  = NULL;
  wndclass.lpszClassName = szAppName;
  RegisterClass(&wndclass);

  cxScreen = GetSystemMetrics(SM_CXSCREEN);
  cyScreen = GetSystemMetrics(SM_CYSCREEN);

  width  = 8 * SQUARE_LENGHT + 6;   // +6 pour les bords de la fenetre
  height = 8 * SQUARE_LENGHT + 100; // +100 pour les informations diverses inscrites sous le plateau

  hwnd = CreateWindow(szAppName, szAppName, WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX,
                      (cxScreen - width) / 2, (cyScreen - height) / 2, width, height,
                      NULL, NULL, hInstance, NULL);

  ShowWindow(hwnd, iCmdShow);
  UpdateWindow(hwnd);

  while(GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return msg.wParam;
}