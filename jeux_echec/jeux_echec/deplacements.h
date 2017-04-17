#ifndef DEPLACEMENTS_H
#define DEPLACEMENTS_H
#include <QPoint>
#include <QVector>
#include "Definement.h"

class deplacements
{
public:
    static bool petitRoguePossible(int joueur,const int matriceGroupe[8][8],const int matriceDeplacement[8][8],const piece terrain[8][8]);
    static bool grandRoguePossible(int joueur,const int matriceGroupe[8][8],const int matriceDeplacement[8][8],const piece terrain[8][8]);
    static QVector<QPoint> deplacementRoi(const piece terrain[8][8],const int matriceGroupe[8][8], const QPoint& coord);
    static QVector<QPoint> deplacementReine(const int matriceGroupe[8][8], const QPoint& coord);
    static QVector<QPoint> deplacementFou(const int matriceGroupe[8][8], const QPoint& coord);
    static QVector<QPoint> deplacementCavalier(const int matriceGroupe[8][8], const QPoint& coord);
    static QVector<QPoint> deplacementTour(const int matriceGroupe[8][8], const QPoint& coord);
    static QVector<QPoint> attaquePion(const int matriceGroupe[8][8],const QPoint& cas);
    static QVector<QPoint> deplacementPion(const int matriceGroupe[8][8],const piece terrain[8][8], const QPoint& coord,QVector<QPoint> *coup_precedent);
    static bool estEnEchec(const piece tab_piece[8][8],const int matriceGroupe[8][8],int groupe_piece, const QPoint&, const QPoint* coord = NULL);
};

#endif // DEPLACEMENTS_H
