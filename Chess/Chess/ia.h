#ifndef IA_H
#define IA_H
#include <QVector>
class Plateau;
class Joueur;

class ia
{
public:
    ia();
    void setLevel(int i);
    int getLevel();
    int jouer();
    int eval(Plateau * plateau );
    int max(Joueur *joueur,Plateau *plateau,int profondeur,int alpha,int beta);
    int min(Joueur *joueur,Plateau *plateau,int profondeur,int alpha,int beta);
    int gagnant(int idJoueur);
private:
    int level;//represente la profondeur
    QVector<QPoint> *m_coupPrecedent;
};

#endif // IA_H
