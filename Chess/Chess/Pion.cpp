#include "Pion.h"
#include "Joueur.h"

Pion::Pion(int i) :Piece()
{
    wayToMove = i;
    //So wayToMove = 1 la piece descend dans le plateau, sinon elle monte
    //wayToMove vaut soit 1, soit -1
    nbCout =0;
    id_piece= 'P';
}


Pion::~Pion()
{
}

bool Pion::testDeplacement(Coordonnee coord, Plateau* plateau)
{
    bool verif = false;
    std::cout << "test deplacement"<< std::endl;
    std::cout <<coord.getX()<< std::endl;
    std::cout <<coordonnee->getX()<< std::endl;
    std::cout <<abs(coord.getY()-coordonnee->getY())<<std::endl;
    //a updater pour prendre le deplacement de deux cases quau debut
    if(!plateau->caseAtOccupy(coord.getX(), coord.getY()))
    {if (coord.getX() == coordonnee->getX()  && ((abs(coord.getY()-coordonnee->getY()) <3 )))
    {
        if(wayToMove==1)
        {
            if(coord.getY()-coordonnee->getY()== 2 && nbCout==0)
                verif = true;
            else if(coord.getY()-coordonnee->getY()== 1)
                verif = true;
        }
        else if(wayToMove==-1)
        {
            if((coord.getY()-coordonnee->getY()== -2) && nbCout==0)
                verif = true;
            else if(coord.getY()-coordonnee->getY()== -1)
                verif = true;
        }
    }
    }
    else if((coord.getX() == coordonnee->getX()-1 ||coord.getX() == coordonnee->getX()+1)&&coord.getY()==coordonnee->getY()+wayToMove && plateau->caseAtOccupy(coord.getX(), coord.getY()))
    {
        if(plateau->getPiece(&coord)->getCouleur()!=couleur)
            verif =true;
        else
            verif =false;
    }
    if(verif==true) {std::cout << "vrai"<< std::endl;}
    else            {std::cout << "faux"<< std::endl;}
    return verif;
}


void Pion::move(Coordonnee *coord, Coordonnee origin, Plateau* plateau)
{
    Piece::move(coord, origin, plateau);
    if(nbCout==0)
        nbCout+=1;
}

QVector<QPoint> Pion::deplacementsPossible(int idJoueur,Plateau * plateau){
    std::cout<<"Dans la fonction deplacementPossible 1"<<std::endl;
    QVector<QPoint> tabDep;
    std::cout<<"Dans la fonction deplacementPossible 2"<<std::endl;
    QPoint dest_precedent = plateau->getCoupPrec().at(1);
    std::cout<<"Dans la fonction deplacementPossible 3"<<std::endl;
    QPoint origin_precedent = plateau->getCoupPrec().at(0);
    std::cout<<"Dans la fonction deplacementPossible"<<std::endl;
    std::cout << coordonnee->getX();std::cout << std::endl;
    std::cout << coordonnee->getY();std::cout << std::endl;
    /*std::cout << i4;std::cout << std::endl;
    std::cout << i3;std::cout << std::endl;*/
    switch(idJoueur){
    case 0:
        //black

        std::cout<<"dans le switch 0"<<std::endl;
        if((coordonnee->getY() == 1 || coordonnee->getY()==2) &&
                (!plateau->caseAtOccupy(coordonnee->getX(),coordonnee->getY()+2) && (!plateau->caseAtOccupy(coordonnee->getX(),coordonnee->getY()+1))))
        {
            std::cout << "premier dep";std::cout << std::endl;
            tabDep.append(QPoint(coordonnee->getX(),coordonnee->getY()+2));
        }
        if(coordonnee->getY() < 7)
        {
            std::cout<<"deuxieme if"<<plateau->caseAtOccupy(coordonnee->getX(),coordonnee->getY()+1)<<std::endl;
            if(!(plateau->caseAtOccupy(coordonnee->getX(),coordonnee->getY()+1)))
            {
                std::cout<<"deuxieme 1 if"<<std::endl;
                tabDep.append(QPoint(coordonnee->getX(),coordonnee->getY()+1));
            }
        }
        if(coordonnee->getX() > 0)
        {
            std::cout<<"premier if special"<<std::endl;
            std::cout<<(coordonnee->getX())<<std::endl;
            std::cout<<(coordonnee->getY())<<std::endl;
            std::cout<<plateau->getGrille()->getCase(coordonnee->getX()-1,coordonnee->getY()+1)->isOccupied()<<std::endl;


            if(plateau->getJoueur1()->isAnyPiece(Coordonnee(coordonnee->getX()-1,coordonnee->getY()+1)) == -1 && plateau->caseAtOccupy(coordonnee->getX()-1,coordonnee->getY()+1)==true && plateau->getGrille()->getCase(coordonnee->getX()-1,coordonnee->getY()+1)->getCouleur()!=
                    this->couleur)
            {
                std::cout<<"premier if special 2"<<std::endl;
                std::cout<<coordonnee->getX()-1<<std::endl;
                std::cout<<coordonnee->getY()+1<<std::endl;
                std::cout<<plateau->getGrille()->getCase(coordonnee->getX()-1,coordonnee->getY()+1)->isOccupied()<<std::endl;
                std::cout<<"premier if 2"<<std::endl;
                std::cout<<"jajoute"<<std::endl;
                tabDep.append(QPoint(coordonnee->getX()-1,coordonnee->getY()+1));
            }
        }
        if(coordonnee->getX() < 7)
        {
            std::cout<<"premier if"<<std::endl;

            if(plateau->getJoueur1()->isAnyPiece(Coordonnee(coordonnee->getX()+1,coordonnee->getY()+1)) == -1 && plateau->caseAtOccupy(coordonnee->getX()+1,coordonnee->getY()+1)==true &&
                    plateau->getGrille()->getCase(coordonnee->getX()+1,coordonnee->getY()+1)->getCouleur()!=this->couleur)
            {
                std::cout<<"premier if"<<std::endl;

                tabDep.append(QPoint(coordonnee->getX()+1,coordonnee->getY()+1));
            }
        }

        //si c'est un pion qui c'est deplace : l'attaque est possible
        if(plateau->getGrille()->getCase(dest_precedent.x(),dest_precedent.y())->getId() == 'P'  && (origin_precedent.y() == 6 || origin_precedent.y() == 5))
        {
            std::cout<<"premier if"<<std::endl;

            // si le pion fait pas parti de mon deck
            if(plateau->getGrille()->getCase(dest_precedent.x(),dest_precedent.y())->getCouleur() != 0)
            {
                std::cout<<"premier if"<<std::endl;

                //si il a fait le bon deplacement
                if ((dest_precedent.y() - origin_precedent.y()) == -2)
                {
                    std::cout<<"premier if"<<std::endl;

                    //je verifie qu'il est dans mon champs d'attaque
                    if (dest_precedent.x()+1 == coordonnee->getX() && coordonnee->getY() == dest_precedent.y())
                    {
                        std::cout<<"premier if"<<std::endl;

                        tabDep.append(QPoint(coordonnee->getX()+1,coordonnee->getY()+1));
                    }
                    else if(dest_precedent.y() == coordonnee->getY() && coordonnee->getX() == dest_precedent.x()-1)
                    {
                        std::cout<<"premier if"<<std::endl;

                        tabDep.append(QPoint(coordonnee->getX()-1,coordonnee->getY()+1));
                    }
                }
            }
        }

        break;
    case 1:
        std::cout<<"dans le switch 1"<<std::endl;
        if((coordonnee->getY() == 5 || coordonnee->getY()==6) && !plateau->caseAtOccupy(coordonnee->getX(),coordonnee->getY()-2) && !plateau->caseAtOccupy(coordonnee->getX(),coordonnee->getY()-1) )
        {

            tabDep.append(QPoint(coordonnee->getX(),coordonnee->getY()-2));
            std::cout<<"dans le switch1 1"<<std::endl;

        }
        std::cout<<"dans le switch 2"<<std::endl;
        if(coordonnee->getY() > 0)
        {
            if(!plateau->caseAtOccupy(coordonnee->getX(),coordonnee->getY()-1))
            {
                tabDep.append(QPoint(coordonnee->getX(),coordonnee->getY()-1));
                std::cout<<"dans le switch2 1"<<std::endl;
            }
        }
        std::cout<<"dans le switch3"<<std::endl;
        if(coordonnee->getX() > 0)
        {
            std::cout<<"dans le switch3 1"<<std::endl;
            if(plateau->getJoueur2()->isAnyPiece(Coordonnee(coordonnee->getX()-1,coordonnee->getY()-1)) == -1 && plateau->caseAtOccupy(coordonnee->getX()-1,coordonnee->getY()-1)==true && plateau->getGrille()->getCase(coordonnee->getX()-1,coordonnee->getY()-1)->getCouleur()!=
                    this->couleur)
            {
                std::cout<<"dans le switch3 2"<<std::endl;
                tabDep.append(QPoint(coordonnee->getX()-1,coordonnee->getY()-1));
            }
        }

        std::cout<<"dans le switch 4"<<std::endl;
        if(coordonnee->getX() < 7)
        {
            int tt= plateau->getJoueur2()->isAnyPiece(Coordonnee(coordonnee->getX()+1,coordonnee->getY()-1));
            std::cout<<tt<<std::endl;
            std::cout<<"dans le switch4 1"<< plateau->getJoueur2()->isAnyPiece(Coordonnee(coordonnee->getX()+1,coordonnee->getY()-1))<<std::endl;
            if((plateau->getJoueur2()->isAnyPiece(Coordonnee(coordonnee->getX()+1,coordonnee->getY()-1)) == -1) && plateau->caseAtOccupy(coordonnee->getX()+1,coordonnee->getY()-1)==true &&
                    plateau->getGrille()->getCase(coordonnee->getX()+1,coordonnee->getY()-1)->getCouleur()!=
                                        this->couleur)
            {
                std::cout<<"dans le switch4 2"<<std::endl;
                tabDep.append(QPoint(coordonnee->getX()+1,coordonnee->getY()-1));
                std::cout<<"dans le switch 4 3"<<std::endl;
            }
        }
        //si c'est un pion qui c'est deplace : l'attaque est possible
        if(plateau->getGrille()->getCase(dest_precedent.x(),dest_precedent.y())->getId() == 'P'  && (origin_precedent.y() == 1 || origin_precedent.y() == 2))
        {
            // si le pion fait pas parti de mon groupe
            if(plateau->getGrille()->getCase(dest_precedent.x(),dest_precedent.y())->getCouleur() != 1)
            {
                //si il a fait le deplacement qui m'interesse
                if ((dest_precedent.y() - origin_precedent.y()) == 2)
                {
                    //je verifie qu'il est dans mon champs d'attaque
                    if (dest_precedent.x()+1 == coordonnee->getX() && coordonnee->getY() == dest_precedent.y())
                    {
                        tabDep.append(QPoint(coordonnee->getX()+1,coordonnee->getY()+1));
                    }
                    else if(dest_precedent.y() == coordonnee->getY() && coordonnee->getX() == dest_precedent.x()-1)
                    {
                        tabDep.append(QPoint(coordonnee->getX()-1,coordonnee->getY()+1));
                    }
                }
            }
        }
        break;
    default:
        std::cout<<"Dans le default"<<std::endl;
        break;
    }
    std::cout<<"fin methode"<<std::endl;
    return tabDep;
}
