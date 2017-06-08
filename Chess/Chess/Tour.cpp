#include "Tour.h"
#include <QVector>
#include "Plateau.h"


Tour::Tour()
{
    id_piece = 'T';
}


Tour::~Tour()
{
}

bool Tour::testDeplacement(Coordonnee coord, Plateau * plateau)
{
    return Piece::testHorizontal(coord,plateau) || Piece::testVertical(coord,plateau);
}

QVector<QPoint> Tour::deplacementsPossible(int idJoueur,Plateau * plateau){
    QVector<QPoint> resultat;
        int x = getCoordonne().getX();
        while(x > 0)
        {
            x--;
            if(plateau->getGrille()->getCase(x,getCoordonne().getY())->getCouleur() != plateau->getGrille()->getCase(getCoordonne().getX(),getCoordonne().getY())->getCouleur()) // si on rencontre un blanc ou un pion ennemi
            {
                resultat.append(QPoint(x,getCoordonne().getY()));
            }
            if(plateau->getGrille()->getCase(x,getCoordonne().getY())->getCouleur() != -1) // on a rencontre un obstacle ami ou ennemi
            {
                x = 0; // on stoppe la boucle
            }
        }
        x = getCoordonne().getX();
        while(x < 7)
        {
            x++;
            if(plateau->getGrille()->getCase(x,getCoordonne().getY())->getCouleur() != plateau->getGrille()->getCase(getCoordonne().getX(),getCoordonne().getY())->getCouleur()) // si on rencontre un blanc ou une piece ennemie
            {
                resultat.append(QPoint(x, getCoordonne().getY()));
            }
            if(plateau->getGrille()->getCase(x,getCoordonne().getY())->getCouleur() != -1) // on a rencontre un obstacle ami ou ennemi
            {
                x = 7; // on stoppe la boucle
            }
        }
        int y = getCoordonne().getY();
        while(y > 0)
        {
            y--;
            if(plateau->getGrille()->getCase(x,getCoordonne().getY())->getCouleur() != plateau->getGrille()->getCase(getCoordonne().getX(),getCoordonne().getY())->getCouleur()) // si on rencontre un blanc ou une piece ennemie
            {
                resultat.append(QPoint(getCoordonne().getX(), y));
            }
            if(plateau->getGrille()->getCase(getCoordonne().getX(),y)->getCouleur() != -1) // on a rencontre un obsacle ami ou ennemi
            {
                y = 0; // on stoppe la boucle
            }
        }
        y = getCoordonne().getY();
        while(y < 7)
        {
            y++;
            if(plateau->getGrille()->getCase(getCoordonne().getX(),y)->getCouleur() != plateau->getGrille()->getCase(getCoordonne().getX(),getCoordonne().getY())->getCouleur()) // si on rencontre un blanc ou une piece ennemie
            {
                resultat.append(QPoint(getCoordonne().getX(), y));
            }
            if(plateau->getGrille()->getCase(getCoordonne().getX(),y)->getCouleur() != -1) // on a rencontre un obstacle ami ou ennemi
            {
                y = 7; // on stoppe la boucle
            }
        }
        return resultat;
}
