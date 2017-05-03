#include "Cavalier.h"
#include <QVector>
#include "Plateau.h"


Cavalier::Cavalier()
{
}


Cavalier::~Cavalier()
{
}
QVector<QPoint> Cavalier::deplacementsPossible(int idJoueur,Plateau * plateau){
    QVector<QPoint> resultat;
        /////////// HAUT
        if(getCoordonne().getY()>= 1){

            if(getCoordonne().getX()>=2)
            {
                if(plateau->getGrille().getCase(getCoordonne().getX()-2,getCoordonne().getY()-1).getCouleur() != plateau->getGrille().getCase(getCoordonne().getX(),getCoordonne().getY()).getCouleur() )
                    // sinon est pas sur une piece aliee mais une piece adverse ou un Rien
                {
                    resultat.append(QPoint(getCoordonne().getX()-2, (getCoordonne().getY()-1)));
                }
            }
            if(getCoordonne().getX() <= 5)
            {
                if(plateau->getGrille().getCase(getCoordonne().getX()+2,getCoordonne().getY()-1).getCouleur() != plateau->getGrille().getCase(getCoordonne().getX(),getCoordonne().getY()).getCouleur() )
                {
                    resultat.append(QPoint(getCoordonne().getX()+2, (getCoordonne().getY()-1)));
                }
            }
        }/////////BAS
        if(getCoordonne().getY()<=6)
        {
            if(getCoordonne().getX()>=2)
            {
                if(plateau->getGrille().getCase(getCoordonne().getX()-2,getCoordonne().getY()+1).getCouleur() != plateau->getGrille().getCase(getCoordonne().getX(),getCoordonne().getY()).getCouleur() )
                {
                    resultat.append(QPoint(getCoordonne().getX()-2, (getCoordonne().getY()+1)));
                }
            }
            if(getCoordonne().getX() <= 5)
            {
                if(plateau->getGrille().getCase(getCoordonne().getX()+2,getCoordonne().getY()+1).getCouleur() != plateau->getGrille().getCase(getCoordonne().getX(),getCoordonne().getY()).getCouleur() )
                {
                    resultat.append(QPoint(getCoordonne().getX()+2, (getCoordonne().getY()+1)));
                }
            }
        }/////// GAUCHE
        if(getCoordonne().getY()>= 2){

            if(getCoordonne().getX()>=1)
            {
                if(plateau->getGrille().getCase(getCoordonne().getX()-1,getCoordonne().getY()-2).getCouleur() != plateau->getGrille().getCase(getCoordonne().getX(),getCoordonne().getY()).getCouleur() )
                {
                    resultat.append(QPoint(getCoordonne().getX()-1, (getCoordonne().getY()-2)));
                }
            }
            if(getCoordonne().getX() <= 6)
            {
                if(plateau->getGrille().getCase(getCoordonne().getX()+1,getCoordonne().getY()-2).getCouleur() != plateau->getGrille().getCase(getCoordonne().getX(),getCoordonne().getY()).getCouleur() )
                {
                    resultat.append(QPoint(getCoordonne().getX()+1, (getCoordonne().getY()-2)));
                }
            }
        }/////////DROITE
        if(getCoordonne().getY()<=5)
        {
            if(getCoordonne().getX()>=1)
            {
                if(plateau->getGrille().getCase(getCoordonne().getX()-1,getCoordonne().getY()+2).getCouleur() != plateau->getGrille().getCase(getCoordonne().getX(),getCoordonne().getY()).getCouleur() )
                {
                    resultat.append(QPoint(getCoordonne().getX()-1, (getCoordonne().getY()+2)));
                }
            }
            if(getCoordonne().getX() <= 6)
            {
                if(plateau->getGrille().getCase(getCoordonne().getX()+1,getCoordonne().getY()+2).getCouleur() != plateau->getGrille().getCase(getCoordonne().getX(),getCoordonne().getY()).getCouleur() )
                {
                    resultat.append(QPoint(getCoordonne().getX()+1, (getCoordonne().getY()+2)));
                }
            }
        }
        return resultat;
}

bool Cavalier::testDeplacement(Coordonnee coord)
{
	int x = coord.getX();
	int y = coord.getY();
	bool moveAble = false;
	int i = getCoordonne().getX();
	int j = getCoordonne().getY();

	if (x == i + 2 || x == i - 2)
	{
		if (y == j - 1 || y == j + 1)
			moveAble = true;
	}
	else if (y == j - 2 || y == j + 2)
	{
		if (x == i + 1 || x == i - 1)
			moveAble = true;
	}
	return moveAble;

}
