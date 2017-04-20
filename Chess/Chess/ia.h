#ifndef IA_H
#define IA_H
class Plateau;

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
    int gagnant(Joueur * joueur);
private:
    int level;
};

#endif // IA_H
