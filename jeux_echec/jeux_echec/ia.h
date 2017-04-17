#ifndef IA_H
#define IA_H
#include <QObject>
#include "Definement.h"
#include "terrain.h"
class IA : public QObject
{
public:
    IA(piece m_terrain[][8],int groupe[][8],int deplacement[][8],QVector<QPoint> *coup_precedent,QObject * parent = 0);
    QVector<QPoint> calc_echec_et_mat(int joueur,QPoint pos_rois_joueur);
    QVector<QPoint> jouer(int joueur);
    void setDifficulter(int diff);
    unsigned int getDifficulter();

private:

    int evalIA(piece terrain[8][8],int groupe[8][8]);
    int gagnantJeux(int joueur);
    int max(int joueur,piece terrain[8][8],int groupe[8][8],int profondeur, int alpha, int beta);
    int min(int joueur,piece terrain[8][8],int groupe[8][8],int profondeur, int alpha, int beta);


    int m_profondeur;
    int m_max;

    //pointeur en reference vers des element de terrain, on ne les delete pas avec un destructeur ici :)
    QVector<QPoint> *m_coupPrecedent;
    piece (*m_terrain)[8];
    QPoint m_Posi_Rois1;
    QPoint m_Posi_Rois2;
    int (*m_groupe)[8];
    int (*m_deplacement)[8];

};

#endif // IA_H
