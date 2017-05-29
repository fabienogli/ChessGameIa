#ifndef DEPLACEMENT_H
#define DEPLACEMENT_H

#include <QPoint>
#include <QVector>


class deplacement
{
public:
    static bool checkPetitRoque(int joueur, int couleur[8][8], int matriceDeplacement[8][8], char idPiece[8][8]);
    static bool checkGrandRoque(int joueur, int couleur[8][8], int matriceDeplacement[8][8], char idPiece[8][8]);
    static QVector<QPoint> deplacementRoi( char idPiece[8][8], int couleur[8][8],  QPoint& coord);
    static QVector<QPoint> deplacementFou( int couleur[8][8],  QPoint coord);
    static QVector<QPoint> deplacementCavalier( const int couleur[8][8], const  QPoint cas);
    static QVector<QPoint> deplacementTour( int couleur[8][8],  QPoint coord);
    static QVector<QPoint> attaquePion( int couleur[8][8], QPoint cas);
    static QVector<QPoint> deplacementPion(int idJoueur,int couleur[8][8],  QPoint coord,int matriceDeplacement[8][8]);
    static bool inCheck(char idPiece[8][8],int couleur[8][8],int idjoueur,  QPoint,  QPoint* coord = NULL);
};

#endif // DEPLACEMENT_H
