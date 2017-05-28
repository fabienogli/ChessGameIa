#ifndef IA_H
#define IA_H
#include <QVector>
#include <QPoint>
class Plateau;
#include "Joueur.h"
class ia : public Joueur
{
public:
    //ia(int i_joueur, int level);
    ia(int level);
    void setCoupPrecedent(QVector<QPoint> * coupPrecedent);
    void setLevel(int i);
    int getLevel();
    QVector<QPoint> jouer(Joueur *joueur,int profondeur,Plateau *plateau);
    int eval();
    QVector<QPoint> calc_echec_et_mat(int idJoueur,QPoint pos_rois_joueur);
    void initTableauTmp(Plateau * plateau);
    int max(int idJoueur,int profondeur,int alpha,int beta);
    int min(int idJoueur,int profondeur,int alpha,int beta);
    int gagnantEnCours(int idJoueur);

    ~ia();
private:
    int level;//represente la profondeur
    QVector<QPoint> *m_coupPrecedent;
    QPoint m_Posi_Rois1;//position du roi 1
    QPoint m_Posi_Rois2;//position du roi 2
    char *tableauPieces[8];
    int  *tableauCouleur[8];
    bool *tableauOccup[8];
    int  *matriceDep[8];
};

#endif // IA_H
