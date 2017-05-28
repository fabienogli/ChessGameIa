#ifndef DEPLACEMENTS_H
#define DEPLACEMENTS_H
#include <QPoint>
#include <QVector>


class deplacements
{
public:
    static bool petitRoguePossible(int joueur,const int couleur[8][8],const int matriceDeplacement[8][8],const char idPiece[8][8]);
    static bool grandRoguePossible(int joueur,const int couleur[8][8],const int matriceDeplacement[8][8],const char idPiece[8][8]);
    static QVector<QPoint> deplacementRoi(const char idPiece[8][8],const int couleur[8][8], const QPoint& coord);
    static QVector<QPoint> deplacementFou(const int couleur[8][8], const QPoint& coord);
    static QVector<QPoint> deplacementCavalier(const int couleur[8][8], const QPoint& coord);
    static QVector<QPoint> deplacementTour(const int couleur[8][8], const QPoint& coord);
    static QVector<QPoint> attaquePion(const int couleur[8][8],const QPoint& cas);
    static QVector<QPoint> deplacementPion(int idJoueur,const int couleur[8][8],const char idPiece[8][8], const QPoint& coord,QVector<QPoint> *coup_precedent);
    static bool estEnEchec(const char tab_char[8][8],const int couleur[8][8],int idjoueur, const QPoint&, const QPoint* coord = NULL);
};

#endif // DEPLACEMENTS_H
