#include "Pion.h"
#include "Plateau.h"
#include "Coordonnee.h"
#include <vector>



Pion::Pion()
{
}


Pion::~Pion()
{
}

bool Pion::testDeplacement(Coordonnee coord)
{ bool verif = false;
    std::cout << "test deplacement";std::cout << std::endl;
    std::cout <<coord.getX();std::cout << std::endl;
    std::cout <<getCoordonne().getX();std::cout << std::endl;
    std::cout <<abs(coord.getY()-getCoordonne().getY());std::cout << std::endl;
    //a updater pour prendre le deplacement de deux cases quau debut
    if (coord.getX() == getCoordonne().getX()  && ((abs(coord.getY()-getCoordonne().getY()) == 1) || (abs(coord.getY()-getCoordonne().getY())== 2)))
            verif = true;
    if(verif==true) {std::cout << "vrai";std::cout << std::endl;}
    else
    {
        std::cout << "faux";
        std::cout << std::endl;
    }
	return verif;
}

virtual QVector<QPoint> Pion::deplacementsPossible(int idJoueur,Plateau * plateau){
    QVector<QPoint> tabDep;
    QPoint dest_precedent = plateau->getCoupPrec().at(1);
    QPoint origin_precedent = plateau->getCoupPrec().at(0);
    switch(idJoueur){
    case 0:
        //black
        if((getCoordonne().getY() == 1 || getCoordonne().getY()==2) && plateau->getGrille().getCase(getCoordonne().getX(),getCoordonne().getY()+2).isOccupied()==false && plateau->getGrille().getCase(getCoordonne().getX(),getCoordonne().getY()+1).isOccupied()==false )
            {
                tabDep.append(QPoint(getCoordonne().getX(),getCoordonne().getY()+2));

            }
        if(getCoordonne().getY() < 7)
                {
                    if(plateau->getGrille().getCase(getCoordonne().getX(),getCoordonne().getY()+1).isOccupied()==false)
                    {
                        tabDep.append(QPoint(getCoordonne().getX(),getCoordonne().getY()+1));
                    }
                }
                if(getCoordonne().getX() > 0)
                {
                    if(plateau->getJoueur1().isAnyPiece(Coordonnee(getCoordonne().getX()-1,getCoordonne().getY()+1)) == -1 && plateau->getGrille().getCase(getCoordonne().getX()-1,getCoordonne().getY()+1).isOccupied()==true)
                    {
                        tabDep.append(QPoint(getCoordonne().getX()-1,getCoordonne().getY()+1));
                    }
                }
                if(getCoordonne().getX() < 7)
                {
                    if(plateau->getJoueur1().isAnyPiece(Coordonnee(getCoordonne().getX()+1,getCoordonne().getY()+1)) == -1 && plateau->getGrille().getCase(getCoordonne().getX()+1,getCoordonne().getY()+1).isOccupied()==true)
                    {
                        tabDep.append(QPoint(getCoordonne().getX()+1,getCoordonne().getY()+1));
                    }
                }

                //si c'est un pion qui c'est deplace : l'attaque est possible
                if(plateau->getGrille().getCase(dest_precedent.x(),dest_precedent.y()).getId() == 'P'  && (origin_precedent.y() == 6 || origin_precedent.y() == 5))
                {
                    // si le pion fait pas parti de mon groupe
                    if(plateau->getGrille().getCase(dest_precedent.x(),dest_precedent.y()).getCouleur() != 0)
                    {
                        //si il a fait le deplacement qui m'interesse
                        if ((dest_precedent.y() - origin_precedent.y()) == -2)
                        {
                            //je verifie qu'il est dans mon champs d'attaque
                            if (dest_precedent.x()+1 == getCoordonne().getX() && getCoordonne().getY() == dest_precedent.y())
                            {
                                resultat.append(QPoint(getCoordonne().getX()+1,getCoordonne().getY()+1));
                            }
                            else if(dest_precedent.y() == getCoordonne().getY() && getCoordonne().getX() == dest_precedent.x()-1)
                            {
                                resultat.append(QPoint(getCoordonne().getX()-1,getCoordonne().getY()+1));
                            }
                        }
                    }
                }

        break;
    case 1:
        if((getCoordonne().getY() == 5 || getCoordonne().getY()==6) && plateau.getGrille().getCase(getCoordonne().getX(),getCoordonne().getY()-2).isOccupied()==false && plateau.getGrille().getCase(getCoordonne().getX(),getCoordonne().getY()-1).isOccupied()==false )
            {
               tabDep.append(QPoint(getCoordonne().getX(),getCoordonne().getY()-2));

            }
        if(getCoordonne().getY() > 0)
                {
                    if(plateau.getGrille().getCase(getCoordonne().getX(),getCoordonne().getY()-1).isOccupied()==false)
                    {
                       tabDep.append(QPoint(getCoordonne().getX(),getCoordonne().getY()-1));
                    }
                }
                if(getCoordonne().getX() > 0)
                {
                    if(plateau.getJoueur2().isAnyPiece(Coordonnee(getCoordonne().getX()-1,getCoordonne().getY()-1)) == -1 && plateau.getGrille().getCase(getCoordonne().getX()-1,getCoordonne().getY()-1).isOccupied()==true)
                    {
                        tabDep.append(QPoint(getCoordonne().getX()-1,getCoordonne().getY()-1));
                    }
                }
                if(getCoordonne().getX() < 7)
                {
                    if(plateau.getJoueur2().isAnyPiece(Coordonnee(getCoordonne().getX()+1,getCoordonne().getY()-1)) == -1 && plateau.getGrille().getCase(getCoordonne().getX()+1,getCoordonne().getY()-1).isOccupied()==true)
                    {
                       tabDep.append(QPoint(getCoordonne().getX()+1,getCoordonne().getY()-1));
                    }
                }
                //si c'est un pion qui c'est deplace : l'attaque est possible
                if(plateau->getGrille().getCase(dest_precedent.x(),dest_precedent.y()).getId() == 'P'  && (origin_precedent.y() == 1 || origin_precedent.y() == 2))
                {
                    // si le pion fait pas parti de mon groupe
                    if(plateau->getGrille().getCase(dest_precedent.x(),dest_precedent.y()).getCouleur() != 1)
                    {
                        //si il a fait le deplacement qui m'interesse
                        if ((dest_precedent.y() - origin_precedent.y()) == 2)
                        {
                            //je verifie qu'il est dans mon champs d'attaque
                            if (dest_precedent.x()+1 == getCoordonne().getX() && getCoordonne().getY() == dest_precedent.y())
                            {
                                resultat.append(QPoint(getCoordonne().getX()+1,getCoordonne().getY()+1));
                            }
                            else if(dest_precedent.y() == getCoordonne().getY() && getCoordonne().getX() == dest_precedent.x()-1)
                            {
                                resultat.append(QPoint(getCoordonne().getX()-1,getCoordonne().getY()+1));
                            }
                        }
                    }
                }
        break;
    default:
        break;
    }

return tabDep;
}
