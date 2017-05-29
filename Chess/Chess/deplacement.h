#ifndef DEPLACEMENT_H
#define DEPLACEMENT_H

#include <QPoint>
#include <QVector>


class deplacement
{
public:
    static bool checkPetitRoque(int joueur, int couleur[8][8], int matriceDeplacement[8][8], char idPiece[8][8]);
    static bool checkGrandRoque(int joueur, int couleur[8][8], int matriceDeplacement[8][8], char idPiece[8][8]);
    static QVector<QPoint> kingMove( char idPiece[8][8], int couleur[8][8],  QPoint& coord);
    static QVector<QPoint> madMove( int couleur[8][8],  QPoint coord);
    static QVector<QPoint> knightMove( const int couleur[8][8], const  QPoint cas);
    static QVector<QPoint> towerMove( int couleur[8][8],  QPoint coord);
    static QVector<QPoint> pawnAttackList( int couleur[8][8], QPoint cas);
    static QVector<QPoint> pawnMove(int idJoueur,int couleur[8][8],  QPoint coord,int matriceDeplacement[8][8]);
    static bool inCheck(char idPiece[8][8],int couleur[8][8],int idjoueur,  QPoint,  QPoint* coord = NULL);
};

#endif // DEPLACEMENT_H
