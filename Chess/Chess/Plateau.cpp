#include "Plateau.h"
#include "mainwindow.h"
#include "Piece.h"
#include "Coordonnee.h"
#include "ia.h"
#include <stddef.h>
//Constructeur du plateau
Plateau::Plateau() :QObject()
{
    initialize();
    //setJoueurActif(*joueur1);
}

void Plateau::initialize(){
    damier = new Grille();
    joueur1 = new Joueur("joueur 1",0);
    joueur2 = new Joueur("joueur 2",1);
    joueurActif = new Joueur();
    coordDepart = new Coordonnee(0,0);
    coordArrivee= new Coordonnee(0,0);
    aSupprimer=new Piece();
    m_coupPrecedent = new QVector<QPoint>();
    m_coupPrecedent->append(QPoint(0,0));
    m_coupPrecedent->append(QPoint(0,0));
    initiatePosInGrid();
}
void Plateau::reinitialize(){

}
//Positionne les pieces des differentes piece des joueurs dans le plateau
void Plateau::initiatePosInGrid()
{

    for (int i=0; i < (*joueur1).getDeckSize(); i++)
    {
        (*damier).putPiece((*joueur1).getDeck()[i]);
        (*damier).putPiece((*joueur2).getDeck()[i]);

    }
}
//deplacer une piece
void Plateau::movePiece(int i1, int i2, int i3, int i4){
    std::cout << i2;std::cout << std::endl;
    std::cout << i1;std::cout << std::endl;
    std::cout << i4;std::cout << std::endl;
    std::cout << i3;std::cout << std::endl;
    //prendre la piece en i1,i2 et l'envoyer en i3,i4
    std::cout << "je suis 3";std::cout << std::endl;
    coordDepart->setX(i2);
    coordDepart->setY(i1);
    coordArrivee->setX(i4);
    coordArrivee->setY(i3);
    std::cout << coordDepart->getX();std::cout << std::endl;
    std::cout << coordDepart->getY();std::cout << std::endl;
    std::cout << "je suis 3bis";std::cout << std::endl;
    (*aSupprimer).setCoordonnee(new Coordonnee(coordDepart->getX(),coordDepart->getY()));
    //on recherche dans le deck du premier joueur
    double tmp1 = (*joueur1).isAnyPiece(*coordDepart);
    //on recherche dans le deck du deuxieme joueur
    double tmp2 = (*joueur2).isAnyPiece(*coordDepart);
    if (tmp1 != -1)
    {   std::cout << "je suis 1-1";std::cout << std::endl;
        std::cout << tmp1;std::cout << std::endl;
        (*joueur1).getDeck()[tmp1]->afficher();
        //(*joueur1).getPiece(int(tmp1)).move(coordArrivee,(*joueur1).getOrigin());
        bool b=(*joueur1).getDeck()[tmp1]->move(coordArrivee,(*joueur1).getOrigin());
        (*joueur1).getDeck()[tmp1]->afficher();
        std::cout << "je suis 1-2";std::cout << std::endl;
        if(b==true){
                m_coupPrecedent[0][0].setX(coordDepart->getX());
                m_coupPrecedent[0][0].setY(coordDepart->getY());
                m_coupPrecedent[0][1].setX(coordArrivee->getX());
                m_coupPrecedent[0][1].setY(coordArrivee->getY());
            std::cout << "je suis 1-2bis";std::cout << std::endl;
            emit affichSuppInit((*joueur1).getDeck()[tmp1],(*joueur1).getIdJoueur(),0);
            emit affichSuppInit(aSupprimer,(*joueur1).getIdJoueur(),1);
        }else{

            std::cout << "deplacement non autorise";std::cout << std::endl;
            emit badMove();
        }
        std::cout << "je suis 1-3";std::cout << std::endl;
    }
    //sinon c'est forcement occupe par une piece du joueur 2
    else if(tmp2 != -1)
    {

        std::cout << "je suis 2";
        std::cout << "je suis 2-1";
        std::cout << tmp2;
        //(*joueur2).getPiece(tmp2).afficher();
        bool b=(*joueur2).getDeck()[tmp2]->move(coordArrivee,(*joueur2).getOrigin());
        (*joueur2).getDeck()[tmp2]->afficher();
        //(*joueur2).getPiece(tmp2).afficher();
        std::cout << "je suis 2-2";
        if(b==true){
            //mettre a jour couleur des cases
            m_coupPrecedent[0][0].setX(coordDepart->getX());
            m_coupPrecedent[0][0].setY(coordDepart->getY());
            m_coupPrecedent[0][1].setX(coordArrivee->getX());
            m_coupPrecedent[0][1].setY(coordArrivee->getY());
            std::cout << "je suis 2-2bis";std::cout << std::endl;
            emit affichSuppInit((*joueur2).getDeck()[tmp2],(*joueur2).getIdJoueur(),0);
            emit affichSuppInit(aSupprimer,(*joueur2).getIdJoueur(),1);
        }
        else{
            std::cout << "deplacement non autorise";std::cout << std::endl;
            std::cout << "je suis 2-3";std::cout << std::endl;
            emit badMove();}
    }
    std::cout << "jai fini";std::cout << std::endl;
}
//slot pour affichage gui des pieces
void Plateau::displayPlateau(){

    for (int i=0; i < (*joueur1).getDeckSize(); i++)
    {
        emit affichSuppInit((*joueur1).getDeck()[i],(*joueur1).getIdJoueur(),0);
        emit affichSuppInit((*joueur2).getDeck()[i],(*joueur2).getIdJoueur(),0);
    }

}
void Plateau::sentDisplayPlayerId(){
    emit displayPlayerId((*joueurActif).getIdJoueur());
}

/**
 * @brief Plateau::displayPiece affiche une piece dans le GUI
 */

//Affichage du plateau dans la console
void Plateau::afficher()
{
    for (int j = 0; j<(*damier).getHauteur(); j++) {
        for (int i = 0; i<(*damier).getLargeur(); i++) {
            //on teste si la case est occupee
            if ((*damier).getCase(i, j).isOccupied()) {
                Coordonnee coord(i, j);
                //on recherche dans le deck du premier joueur
                double i1 = (*joueur1).isAnyPiece(coord);
                //on recherche dans le deck du deuxieme joueur
                double i2 = (*joueur2).isAnyPiece(coord);
                // on verifie si la case est occupee par une piece du joueur
                if (i1 != -1)
                {
                    std::cout << (*joueur1).getPiece(i1).getId();
                }
                //sinon c'est forcement occupe par une piece du joueur 2
                else
                {
                    std::cout << (*joueur2).getPiece(i2).getId();
                }
                coord.~Coordonnee();
            }
            else
            {
                std::cout << 0;
            }
            std::cout << "|";
        }
        std::cout << std::endl;
        std::cout << "-------------" << std::endl;
    }
}
//mettre a jour l'etat d'une case après le deplacement
void Plateau::updateCaseStatus(Piece piece,Coordonnee oldCoord){
}

//Retourne le pointeur du joueur actif
Joueur Plateau::getJoueurActif()
{
    return *joueurActif;
}

Joueur* Plateau::getJoueur1(){
    return joueur1;
}
Joueur* Plateau::getJoueur2(){
    return joueur2;
}
void Plateau::setJoueurActif(Joueur  joueur){
    *joueurActif=joueur;
}

Grille Plateau::getGrille(){
    return *damier;
}

QVector<QPoint> Plateau::getCoupPrec(){
    return *m_coupPrecedent;
}

void Plateau::setCoupPrec(QVector<QPoint> CoupPrec){
    *m_coupPrecedent=CoupPrec;
}

bool Plateau::est_en_echec(QPoint *coordcase, QPoint *coordpion,int couleur){
    //permet de savoir si une piece dont la couleur est donnée peut etre mangée par le joueur adverse
    QVector<QPoint> destination;
        for(int x = 0; x < 8; x++)
        {
            for(int y = 0; y < 8; y++)
            {
                if(getGrille().getCase(x,y).getCouleur() !=  couleur  )
                {
                    if(couleur == 0)
                    {//on recherche dans le deck du premier joueur
                    double tmp1 = (*joueur1).isAnyPiece(*coordDepart);
                    }
                    else if(couleur==1){
                   double tmp1 = (*joueur1).isAnyPiece(*coordDepart);

                    }


                    switch(getGrille().getCase(x,y).getId())
                    {
                        case 'P':
                           destination = getGrille(). attaquePion(matriceGroupe,QPoint(x,y));
                            for(int u = 0; u < destination.count(); u++)
                            {
                                if(destination.at(u).x() == coordcase.x() && destination.at(u).y() == coordcase.y() )
                                {
                                    return true;
                                }
                            }
                            destination.clear();
                        break;
                        case 'R':
                            if(coordpion != NULL)
                            {
                                if(getGrille().getCase(coordpion->x(),coordpion->y()).getId() != 'R') // on rois ne peu pas attaquer un autre rois !
                                {
                                   // destination = deplacements::deplacementRoi(matricePiece,matriceGroupe,QPoint(x,y));
                                }
                                else
                                {
                                    //on ne peut simplement ignorer l'autre roi, il faut calculer si on peut etre sur la piece
                                }

                            }
                            else
                            {
                                destination = deplacements::deplacementRoi(matricePiece,matriceGroupe,QPoint(x,y));
                            }

                            for(int u = 0; u < destination.count(); u++)
                            {
                                if(destination.at(u).x() == coordcase.x() && destination.at(u).y() == coordcase.y() )
                                {
                                    return true;
                                }
                            }
                            destination.clear();
                        break;

                        case 'F':
                            destination = deplacements::deplacementFou(matriceGroupe,QPoint(x,y));
                            for(int u = 0; u < destination.count(); u++)
                            {
                                if(destination.at(u).x() == coordcase.x() && destination.at(u).y() == coordcase.y() )
                                {
                                    return true;
                                }
                            }
                            destination.clear();
                        break;
                        case 'T':
                            destination =  deplacements::deplacementTour(matriceGroupe,QPoint(x,y));
                            for(int u = 0; u < destination.count(); u++)
                            {
                                if(destination.at(u).x() == coordcase.x() && destination.at(u).y() == coordcase.y() )
                                {
                                    return true;
                                }
                            }
                            destination.clear();
                        break;
                        case 'C':
                            destination = deplacements::deplacementCavalier(matriceGroupe,QPoint(x,y));
                            for(int u = 0; u < destination.count(); u++)
                            {
                                if(destination.at(u).x() == coordcase.x() && destination.at(u).y() == coordcase.y() )
                                {
                                    return true;
                                }
                            }
                            destination.clear();
                        break;

                    }
                }
            }
        }
        return false;
}
//Destructeur du plateau
Plateau::~Plateau()
{
    delete damier;
    delete joueur1;
    delete joueur2;
    delete joueurActif;
    delete coordArrivee;
    delete coordDepart;
    delete aSupprimer;
}
