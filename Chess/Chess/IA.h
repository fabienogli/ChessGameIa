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
    int t1[8],t2[8],t3[8],t4[8],t5[8],t6[8],t7[8],t8[8];
    int u1[8],u2[8],u3[8],u4[8],u5[8],u6[8],u7[8],u8[8];
    int v1[8],v2[8],v3[8],v4[8],v5[8],v6[8],v7[8],v8[8];
    int w1[8],w2[8],w3[8],w4[8],w5[8],w6[8],w7[8],w8[8];
    char *tableauPieces[]={t1,t2,t3,t4,t5,t6,t7,t8};
    int  *tableauCouleur[]={u1,u2,u3,u4,u5,u6,u7,u8};
    bool *tableauOccup[]={v1,v2,v3,v4,v5,v6,v7,v8};
    int  *matriceDep[]={w1,w2,w3,w4,w5,w6,w7,w8};
};

#endif // IA_H
