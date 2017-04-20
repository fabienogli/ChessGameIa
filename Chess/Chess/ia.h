#ifndef IA_H
#define IA_H
#include "Plateau.h";


class ia
{
public:
    ia();
    void setLevel(int i);
    int jouer();
    int eval(Plateau * plateau );
    int max();
    int min();
    int gagnant(Joueur * joueur);
private:
    int level;
};

#endif // IA_H
