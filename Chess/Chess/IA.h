#ifndef IA_H
#define IA_H
#include <QVector>
#include <QPoint>
class Plateau;
class deplacement;
#include "Joueur.h"
class ia : public Joueur
{
public:
    //ia(int i_joueur, int level);
    ia(int level);
    void setLevel(int i);
    int getLevel();
    QVector<QPoint> jouer(Joueur *joueur,Plateau *plateau);
    int eval(int couleur[8][8],char idPiece[8][8]);
    QVector<QPoint> calc_echec_et_mat(int idJoueur,QPoint pos_rois_joueur,int couleur[8][8],char idPiece[8][8]);
    void initTableauTmp(Plateau * plateau);
    int max(int idJoueur,int profondeur,int alpha,int beta,int couleur[8][8],char idPiece[8][8]);
    int min(int idJoueur,int profondeur,int alpha,int beta,int couleur[8][8],char idPiece[8][8]);
    int gagnantEnCours(int idJoueur,int couleur[8][8],char idPiece[8][8]);
    void listerCouleur(int t[8][8]);
    void listerChar(char t[8][8]);
    ~ia();
private:
    int level;//represente la profondeur
    QPoint posi_roi_joueur1;//position du roi 1
    QPoint posi_roi_joueur2;//position du roi 2

    char tableauPieces[8][8];
    int  tableauCouleur[8][8];
    bool tableauOccup[8][8];
    int  matriceDep[8][8];
};

#endif // IA_H
