#include "Fou.h"
#include <QVector>
#include "Plateau.h"


Fou::Fou()
{
}


Fou::~Fou()
{
}
QVector<QPoint> Fou::deplacementsPossible(int idJoueur,Plateau * plateau){

 QVector<QPoint> resultat;

    int x = getCoordonne().getX();
    int y = getCoordonne().getY();

    while (x > 0 && y > 0)
    {
        x--;
        y--;
        if(plateau->getGrille()->getCase(x,y).getCouleur() != plateau->getGrille()->getCase(getCoordonne().getX(), getCoordonne().getY()).getCouleur())
        {
            resultat.append(QPoint(x, y));
        }
        if(plateau->getGrille()->getCase(x,y).getCouleur() != -1) // on a rencontre un obstacle ami ou ennemis
        {
            x = 0; // on stoppe la boucle
        }
    }
    x = getCoordonne().getX();

    y = getCoordonne().getY();
    while (x != 7 && y != 7)
    {
        x++;
        y++;
        if(plateau->getGrille()->getCase(x,y).getCouleur() != plateau->getGrille()->getCase(getCoordonne().getX(),getCoordonne().getY()).getCouleur())
        {
            resultat.append(QPoint(x, y));
        }
        if(plateau->getGrille()->getCase(x,y).getCouleur() != -1) // on a rencontre un obstacle ami ou ennemis
        {
            x = 7; // on stoppe la boucle
        }
    }
    x = getCoordonne().getX();
    y = getCoordonne().getY();
    while (x > 0 && y < 7)
    {
        x--;
        y++;
        if(plateau->getGrille()->getCase(x,y).getCouleur() != plateau->getGrille()->getCase(getCoordonne().getX(),getCoordonne().getY()).getCouleur())
        {
            resultat.append(QPoint(x, y));
        }
        if(plateau->getGrille()->getCase(x,y).getCouleur() != -1) // on a rencontre un obstacle ami ou ennemi
        {
            x = 0; // on stoppe la boucle
        }
    }
    x = getCoordonne().getX();
    y = getCoordonne().getY();
    while (x < 7 && y > 0)
    {
        x++;
        y--;
        if(plateau->getGrille()->getCase(x,y).getCouleur() != plateau->getGrille()->getCase(getCoordonne().getX(),getCoordonne().getY()).getCouleur() )
        {
            resultat.append(QPoint(x, y));
        }
        if(plateau->getGrille()->getCase(x,y).getCouleur() != -1) // on a rencontre un obstacle ami ou ennemi
        {
            x = 7; // on stoppe la boucle
        }
    }
    return resultat;

}

bool Fou::testDeplacement(Coordonnee coord)
{
	return Piece::testDiagonal(coord);
}
