#ifndef IA_H
#define IA_H
#include <QVector>
#include <QPoint>
class Plateau;
class Joueur;

class ia
{
public:
    ia();
    void setLevel(int i);
    int getLevel();
    QVector<QPoint> jouer(Joueur *joueur,int profondeur,Plateau *plateau);
    int eval(Plateau * plateau );
    QVector<QPoint>calc_echec_et_mat(Joueur * joueur,QPoint pos_rois_joueur,Plateau * plateau);
    int max(Joueur *joueur,Plateau *plateau,int profondeur,int alpha,int beta);
    int min(Joueur *joueur,Plateau *plateau,int profondeur,int alpha,int beta);
    int gagnant(int idJoueur,Plateau * Plateau);
private:
    int level;//represente la profondeur
    QVector<QPoint> *m_coupPrecedent;
    QPoint m_Posi_Rois1;
    QPoint m_Posi_Rois2;
};

#endif // IA_H
