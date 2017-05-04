#include "Pion.h"
#include "Plateau.h"
#include "Coordonnee.h"
#include <vector>


Pion::Pion(int i)
{
    wayToMove = i;
    //So wayToMove = 1 la piece descend dans le plateau, sinon elle monte
    //wayToMove vaut soit 1, soit -1
    nbCout =0;
}


Pion::~Pion()
{
}

bool Pion::testDeplacement(Coordonnee coord)
{ bool verif = false;
    std::cout << "test deplacement"<< std::endl;
    std::cout <<coord.getX()<< std::endl;
    std::cout <<getCoordonne().getX()<< std::endl;
    std::cout <<abs(coord.getY()-getCoordonne().getY())<<std::endl;
    //a updater pour prendre le deplacement de deux cases quau debut
    if (coord.getX() == getCoordonne().getX()  && ((abs(coord.getY()-getCoordonne().getY()) <3 )))
    {
        if(wayToMove==1)
        {
            if(coord.getY()-getCoordonne().getY()== 2 && nbCout==0)
                verif = true;
            else if(coord.getY()-getCoordonne().getY()== 1)
                verif = true;
        }
        else if(wayToMove==-1)
        {
            if((coord.getY()-getCoordonne().getY()== -2) && nbCout==0)
                verif = true;
            else if((abs(coord.getY()-getCoordonne().getY())== -1))
                verif = true;
        }
    }
    if(verif==true) {std::cout << "vrai"<< std::endl;}
    else            {std::cout << "faux"<< std::endl;}
	return verif;
}

void Pion::move(Coordonnee *coord, Coordonnee origin)
{
    Piece::move(coord, origin);
    if(nbCout==0)
        nbCout+=1;
}

QVector<QPoint> Pion::deplacementsPossible(int idJoueur,Plateau * plateau){
    QVector<QPoint> tabDep;
    QPoint dest_precedent = plateau->getCoupPrec().at(1);
    QPoint origin_precedent = plateau->getCoupPrec().at(0);
    std::cout<<"Dans la fonction deplacementPossible"<<std::endl;
    std::cout << coordonnee->getX();std::cout << std::endl;
    std::cout << coordonnee->getY();std::cout << std::endl;
    /*std::cout << i4;std::cout << std::endl;
    std::cout << i3;std::cout << std::endl;*/
    //int b = plateau->getGrille2()->getCase2(coordonnee->getX(),coordonnee->getY()+2)->getCouleur();
    switch(idJoueur){
    case 0:
        //black

        std::cout<<b<<std::endl;
        std::cout<<"dans le switch"<<std::endl;
        if((coordonnee->getY() == 1 || coordonnee->getY()==2) && (plateau->getGrille().getCase(coordonnee->getX(),coordonnee->getY()+2).isOccupied()==false) && (plateau->getGrille().getCase(coordonnee->getX(),coordonnee->getY()+1).isOccupied()==false) )
            {
            std::cout<<"premier if"<<std::endl;

                tabDep.append(QPoint(getCoordonne().getX(),getCoordonne().getY()+2));

            }
//        if(getCoordonne().getY() < 7)
//                {
//            std::cout<<"deuxième if"<<std::endl;
//                    if(plateau->getGrille().getCase(getCoordonne().getX(),getCoordonne().getY()+1).isOccupied()==false)
//                    {
//                        std::cout<<"deuxième 1 if"<<std::endl;
//                        tabDep.append(QPoint(getCoordonne().getX(),getCoordonne().getY()+1));
//                    }
//                }
//                if(getCoordonne().getX() > 0)
//                {
//                    std::cout<<"premier if"<<std::endl;

//                    if(plateau->getJoueur1()->isAnyPiece(Coordonnee(getCoordonne().getX()-1,getCoordonne().getY()+1)) == -1 && plateau->getGrille().getCase(getCoordonne().getX()-1,getCoordonne().getY()+1).isOccupied()==true)
//                    {
//                        std::cout<<"premier if"<<std::endl;

//                        tabDep.append(QPoint(getCoordonne().getX()-1,getCoordonne().getY()+1));
//                    }
//                }
//                if(getCoordonne().getX() < 7)
//                {
//                    std::cout<<"premier if"<<std::endl;

//                    if(plateau->getJoueur1()->isAnyPiece(Coordonnee(getCoordonne().getX()+1,getCoordonne().getY()+1)) == -1 && plateau->getGrille().getCase(getCoordonne().getX()+1,getCoordonne().getY()+1).isOccupied()==true)
//                    {
//                        std::cout<<"premier if"<<std::endl;

//                        tabDep.append(QPoint(getCoordonne().getX()+1,getCoordonne().getY()+1));
//                    }
//                }

//                //si c'est un pion qui c'est deplace : l'attaque est possible
//                if(plateau->getGrille().getCase(dest_precedent.x(),dest_precedent.y()).getId() == 'P'  && (origin_precedent.y() == 6 || origin_precedent.y() == 5))
//                {
//                    std::cout<<"premier if"<<std::endl;

//                    // si le pion fait pas parti de mon groupe
//                    if(plateau->getGrille().getCase(dest_precedent.x(),dest_precedent.y()).getCouleur() != 0)
//                    {
//                        std::cout<<"premier if"<<std::endl;

//                        //si il a fait le deplacement qui m'interesse
//                        if ((dest_precedent.y() - origin_precedent.y()) == -2)
//                        {
//                            std::cout<<"premier if"<<std::endl;

//                            //je verifie qu'il est dans mon champs d'attaque
//                            if (dest_precedent.x()+1 == getCoordonne().getX() && getCoordonne().getY() == dest_precedent.y())
//                            {
//                                std::cout<<"premier if"<<std::endl;

//                                tabDep.append(QPoint(getCoordonne().getX()+1,getCoordonne().getY()+1));
//                            }
//                            else if(dest_precedent.y() == getCoordonne().getY() && getCoordonne().getX() == dest_precedent.x()-1)
//                            {
//                                std::cout<<"premier if"<<std::endl;

//                                tabDep.append(QPoint(getCoordonne().getX()-1,getCoordonne().getY()+1));
//                            }
//                        }
//                    }
//                }

        break;
//    case 1:
//        if((getCoordonne().getY() == 5 || getCoordonne().getY()==6) && plateau->getGrille().getCase(getCoordonne().getX(),getCoordonne().getY()-2).isOccupied()==false && plateau->getGrille().getCase(getCoordonne().getX(),getCoordonne().getY()-1).isOccupied()==false )
//            {
//               tabDep.append(QPoint(getCoordonne().getX(),getCoordonne().getY()-2));

//            }
//        if(getCoordonne().getY() > 0)
//                {
//                    if(plateau->getGrille().getCase(getCoordonne().getX(),getCoordonne().getY()-1).isOccupied()==false)
//                    {
//                       tabDep.append(QPoint(getCoordonne().getX(),getCoordonne().getY()-1));
//                    }
//                }
//                if(getCoordonne().getX() > 0)
//                {
//                    if(plateau->getJoueur2()->isAnyPiece(Coordonnee(getCoordonne().getX()-1,getCoordonne().getY()-1)) == -1 && plateau->getGrille().getCase(getCoordonne().getX()-1,getCoordonne().getY()-1).isOccupied()==true)
//                    {
//                        tabDep.append(QPoint(getCoordonne().getX()-1,getCoordonne().getY()-1));
//                    }
//                }
//                if(getCoordonne().getX() < 7)
//                {
//                    if(plateau->getJoueur2()->isAnyPiece(Coordonnee(getCoordonne().getX()+1,getCoordonne().getY()-1)) == -1 && plateau->getGrille().getCase(getCoordonne().getX()+1,getCoordonne().getY()-1).isOccupied()==true)
//                    {
//                       tabDep.append(QPoint(getCoordonne().getX()+1,getCoordonne().getY()-1));
//                    }
//                }
//                //si c'est un pion qui c'est deplace : l'attaque est possible
//                if(plateau->getGrille().getCase(dest_precedent.x(),dest_precedent.y()).getId() == 'P'  && (origin_precedent.y() == 1 || origin_precedent.y() == 2))
//                {
//                    // si le pion fait pas parti de mon groupe
//                    if(plateau->getGrille().getCase(dest_precedent.x(),dest_precedent.y()).getCouleur() != 1)
//                    {
//                        //si il a fait le deplacement qui m'interesse
//                        if ((dest_precedent.y() - origin_precedent.y()) == 2)
//                        {
//                            //je verifie qu'il est dans mon champs d'attaque
//                            if (dest_precedent.x()+1 == getCoordonne().getX() && getCoordonne().getY() == dest_precedent.y())
//                            {
//                                tabDep.append(QPoint(getCoordonne().getX()+1,getCoordonne().getY()+1));
//                            }
//                            else if(dest_precedent.y() == getCoordonne().getY() && getCoordonne().getX() == dest_precedent.x()-1)
//                            {
//                                tabDep.append(QPoint(getCoordonne().getX()-1,getCoordonne().getY()+1));
//                            }
//                        }
//                    }
//                }
//        break;
    default:
        std::cout<<"Dans le default"<<std::endl;
        break;
    }

return tabDep;
}
