#include "Pion.h"
#include "Joueur.h"
#include "deplacements.h"

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

QVector<QPoint> Pion::deplacementsPossible(int idJoueur,const int couleur[8][8],const char idPiece[8][8],QVector<QPoint> *coupPrec){
    return deplacements::deplacementPion(idJoueur,couleur,idPiece,QPoint(this->getCoordonne()->getX(),this->getCoordonne()->getY()),coupPrec)
}
