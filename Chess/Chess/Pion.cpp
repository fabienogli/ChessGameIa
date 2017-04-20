#include "Pion.h"



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
    else{ std::cout << "faux";std::cout << std::endl;}
	return verif;
}

std::vector<Coordonnee> Pion::deplacementsPossible(int idJoueur,Plateau plateau){
    std::vector<Coordonnee> tabDep;
    switch(idJoueur){
    case 0:
        //black
        if((getCoordonne().getY() == 1 || getCoordonne().getY()==2) && plateau.getGrille().getCase(getCoordonne().getX(),getCoordonne().getY()+2).isOccupied()==false && plateau.getGrille().getCase(getCoordonne().getX(),getCoordonne().getY()+1).isOccupied()==false )
            {
                tabDep.push_back(Coordonnee(getCoordonne().getX(),getCoordonne().getY()+2));

            }
        if(getCoordonne().getY() < 7)
                {
                    if(plateau.getGrille().getCase(getCoordonne().getX(),getCoordonne().getY()+1).isOccupied()==false)
                    {
                        tabDep.push_back(Coordonnee(getCoordonne().getX(),getCoordonne().getY()+1));
                    }
                }
                if(getCoordonne().getX() > 0)
                {
                    if(plateau.getJoueur1().isAnyPiece(Coordonnee(getCoordonne().getX()-1,getCoordonne().getY()+1)) == -1 && plateau.getGrille().getCase(getCoordonne().getX()-1,getCoordonne().getY()+1).isOccupied()==true)
                    {
                        tabDep.push_back(Coordonnee(getCoordonne().getX()-1,getCoordonne().getY()+1));
                    }
                }
                if(getCoordonne().getX() < 7)
                {
                    if(plateau.getJoueur1().isAnyPiece(Coordonnee(getCoordonne().getX()+1,getCoordonne().getY()+1)) == -1 && plateau.getGrille().getCase(getCoordonne().getX()+1,getCoordonne().getY()+1).isOccupied()==true)
                    {
                        tabDep.push_back(Coordonnee(getCoordonne().getX()+1,getCoordonne().getY()+1));
                    }
                }
                //si c'est un pion qui c'est deplace : l'attaque est possible
                if(terrain[dest_precedent.x()][dest_precedent.y()] == Pion  && origin_precedent.x() == 6)
                {
                    // si le pion fait pas parti de mon groupe
                    if(groupe[dest_precedent.x()][dest_precedent.y()] != groupe[cas.x()][cas.y()])
                    {
                        //si il a fait le deplacement qui m'interesse
                        if ((dest_precedent.x() - origin_precedent.x()) == -2)
                        {
                            //je verifie qu'il est dans mon champs d'attaque
                            if (dest_precedent.x() == cas.x() && (cas.y()+1) == dest_precedent.y())
                            {
                                resultat.append(QPoint(cas.x()+1,cas.y()+1));
                            }
                            else if(dest_precedent.x() == cas.x() && (cas.y()-1) == dest_precedent.y())
                            {
                                resultat.append(QPoint(cas.x()+1,cas.y()-1));
                            }
                        }
                    }
                }
        break;
    case 1:
        if((getCoordonne().getY() == 5 || getCoordonne().getY()==6) && plateau.getGrille().getCase(getCoordonne().getX(),getCoordonne().getY()-2).isOccupied()==false && plateau.getGrille().getCase(getCoordonne().getX(),getCoordonne().getY()-1).isOccupied()==false )
            {
                tabDep.push_back(Coordonnee(getCoordonne().getX(),getCoordonne().getY()-2));

            }
        if(getCoordonne().getY() > 0)
                {
                    if(plateau.getGrille().getCase(getCoordonne().getX(),getCoordonne().getY()-1).isOccupied()==false)
                    {
                        tabDep.push_back(Coordonnee(getCoordonne().getX(),getCoordonne().getY()-1));
                    }
                }
                if(getCoordonne().getX() > 0)
                {
                    if(plateau.getJoueur2().isAnyPiece(Coordonnee(getCoordonne().getX()-1,getCoordonne().getY()-1)) == -1 && plateau.getGrille().getCase(getCoordonne().getX()-1,getCoordonne().getY()-1).isOccupied()==true)
                    {
                        tabDep.push_back(Coordonnee(getCoordonne().getX()-1,getCoordonne().getY()-1));
                    }
                }
                if(getCoordonne().getX() < 7)
                {
                    if(plateau.getJoueur2().isAnyPiece(Coordonnee(getCoordonne().getX()+1,getCoordonne().getY()-1)) == -1 && plateau.getGrille().getCase(getCoordonne().getX()+1,getCoordonne().getY()-1).isOccupied()==true)
                    {
                        tabDep.push_back(Coordonnee(getCoordonne().getX()+1,getCoordonne().getY()-1));
                    }
                }
        break;
    default:
        break;
    }
return tabDep;
}
