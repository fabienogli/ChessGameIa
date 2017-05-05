#include "Roi.h"
#include <QVector>
#include "Plateau.h"
/**
Classe du roi
*/



Roi::Roi()
{
    id_piece = 'R';
}


Roi::~Roi()
{
}

bool Roi::testDeplacement(Coordonnee coord, Plateau * plateau)
{
    if (abs(coord.getX() - getCoordonne().getX()) < 2 && abs(coord.getY() - getCoordonne().getY()) < 2){
        return(testVertical(coord) || testHorizontal(coord));
    }
}

QVector<QPoint> Roi::deplacementsPossible(int idJoueur,Plateau * plateau){
    QVector<QPoint> resultat;
        for(int y = -1; y < 2 ; y++) // on fait les 3 zones de guauche a droite
        {
            if((getCoordonne().getY() +y) < 8 && (getCoordonne().getY()+y) >= 0) // si on depasse le x a droite ou a guauche on regarde pas le y
            {
                for(int x = -1; x < 2; x++) // pour chaque x on fait les 3 valeurs de y possible
                {
                    // si on sort de la carte ou que c'est notre case (notre piece) on l'ajoute pas
                    if((getCoordonne().getX()+x) < 8 && (getCoordonne().getX()+x) >= 0 && (getCoordonne().getX() != (getCoordonne().getX()+x) || getCoordonne().getY() != (getCoordonne().getY()+y)))
                    {
                        if(plateau->getGrille()->getCase(getCoordonne().getX()+x,getCoordonne().getY()+y)->getCouleur() != plateau->getGrille()->getCase(getCoordonne().getX(),getCoordonne().getY())->getCouleur())
                        {
                            if(x != 0 || y != 0)
                            {/*
                              if(estEnEchec(terrain,matriceGroupe,matriceGroupe[cas.x()][cas.y()], QPoint(cas.x()+x, (cas.y()+y)),&cas) == false)
                              {
                                    resultat.append(QPoint(cas.x()+x, (cas.y()+y)));
                              }*/
                            }
                        }
                    }
                }
            }
        }
        return resultat;
}


