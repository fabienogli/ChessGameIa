#include "Plateau.h"
#include "mainwindow.h"
#include "Coordonnee.h"
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
    std::cout << "je suis 3"<< std::endl;
    coordDepart->setX(i2);
    coordDepart->setY(i1);
    coordArrivee->setX(i4);
    coordArrivee->setY(i3);
    std::cout << coordDepart->getX()<< std::endl;
    std::cout << coordDepart->getY()<< std::endl;
    std::cout << "je suis 3bis"<< std::endl;
    (*aSupprimer).setCoordonnee(new Coordonnee(coordDepart->getX(),coordDepart->getY()));
    //on recherche dans le deck du premier joueur
    double tmp1 = (*joueur1).isAnyPiece(*coordDepart);
    //on recherche dans le deck du deuxieme joueur
    double tmp2 = (*joueur2).isAnyPiece(*coordDepart);
    Joueur* joueur;
    double tmpActif;
    //double kmp;
    if (tmp1 != -1)
    {
        joueur = joueur1;
        tmpActif = tmp1;
        //kmp = joueur2->isAnyPiece(*coordArrivee);

    }
    //sinon c'est forcement occupe par une piece du joueur 2
    else if(tmp2 != -1)
    {
        joueur = joueur2;
        tmpActif = tmp2;
        //kmp = joueur1->isAnyPiece(*coordArrivee);
    }

    std::cout << "je suis 1-1";std::cout << std::endl;
    std::cout << tmpActif;std::cout << std::endl;
    bool b=(*joueur).getDeck()[tmpActif]->move(coordArrivee,(*joueur).getOrigin(), this);
    (*joueur).getDeck()[tmpActif]->afficher();
    //(*joueur).getPiece(int(tmpActif)).move(coordArrivee,(*joueur).getOrigin(), this);

    //DEBUT TEST DEPLACEMENT
    Piece* tmpt = (*joueur).getDeck()[tmpActif];
    std::cout<<"Piece prise"<<std::endl;
    QVector<QPoint> listeCoups = tmpt->deplacementsPossible((*joueur).getIdJoueur(),this);
    std::cout<<"Liste déplacement"<<std::endl;
    for (int i =0; i<listeCoups.size();i++)
    {
        std::cout<<"x = "<<listeCoups[i].x()<<" et y="<<listeCoups[i].y()<<std::endl;
    }
    std::cout<<"fin de liste déplacement"<<std::endl;
    //FIN DEPLACEMENT

    (*joueur).getDeck()[tmpActif]->afficher();
    std::cout << "je suis 1-2";std::cout << std::endl;
    if(b==true){

        //mettre a jour couleur des cases
        m_coupPrecedent[0][0].setX(coordDepart->getX());
        m_coupPrecedent[0][0].setY(coordDepart->getY());
        m_coupPrecedent[0][1].setX(coordArrivee->getX());
        m_coupPrecedent[0][1].setY(coordArrivee->getY());
        std::cout << "je suis 1-2bis";std::cout << std::endl;
        emit affichSuppInit((*joueur).getDeck()[tmpActif],(*joueur).getIdJoueur(),0);
        emit affichSuppInit(aSupprimer,(*joueur).getIdJoueur(),1);
        getGrille()->putPiece((*joueur).getDeck()[tmpActif]);
        getGrille()->removePiece(coordDepart);
    }else{

        std::cout << "deplacement non autorise";std::cout << std::endl;
        emit badMove();
    }
    std::cout << "je suis 1-3";std::cout << std::endl;
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

//récupérer une case a une coordonne x, y
Piece* Plateau::getPiece(Coordonnee* coord)
{
    Piece* piece;
    double i1= joueur1->isAnyPiece(*coord);
    double i2= joueur2->isAnyPiece(*coord);
    if(i1!=-1)
        piece =joueur1->getDeck()[i1];
    else{
        piece = joueur2->getDeck()[i2];
    }
    return piece;
}

//Affichage du plateau dans la console
void Plateau::afficher()
{
    for (int j = 0; j<(*damier).getHauteur(); j++) {
        for (int i = 0; i<(*damier).getLargeur(); i++) {
            //on teste si la case est occupee
            if (damier->getCase(i, j)->isOccupied()) {
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

Grille* Plateau::getGrille(){
    std::cout << "dans getgrille";std::cout << std::endl;
    return damier;
}


QVector<QPoint> Plateau::getCoupPrec(){
    return *m_coupPrecedent;
}

void Plateau::setCoupPrec(QVector<QPoint> CoupPrec){
    *m_coupPrecedent=CoupPrec;
}

bool Plateau::caseAtOccupy(int x, int y)
{
    return damier->getCase(x,y)->isOccupied();
}

bool Plateau::est_en_echec(QPoint *coordcase, QPoint *coordpion,int couleur){
    //permet de savoir si une piece dont la couleur est donnée peut etre mangée par le joueur adverse
    QVector<QPoint> destination;
    //Coordonnee coordtmp = new Coordonnee(0,0);
    Coordonnee coordtmp(0,0);
    double tmp1;
    double tmp2;
    for(int x = 0; x < 8; x++)
    {
        for(int y = 0; y < 8; y++)
        {
            if(damier->getCase(x,y)->getCouleur() !=  couleur  )
            {
                coordtmp.setX(x);
                coordtmp.setY(y);
                if(couleur == 0)
                    //on recherche dans le deck du premier joueur
                    tmp1 = (*joueur1).isAnyPiece(coordtmp);
                else if(couleur==1)
                    tmp2 = (*joueur1).isAnyPiece(coordtmp);
                if(tmp1!=-1){
                    switch(damier->getCase(x,y)->getId())
                    {
                    case 'P':
                        destination = attaquePion(QPoint(joueur1->getDeck()[tmp1]->getCoordonne().getX(),getJoueur1()->getDeck()[tmp1]->getCoordonne().getY()));
                        for(int u = 0; u < destination.size(); u++)
                        {
                            if(destination[u].x() == coordcase->x() && destination[u].y() == coordcase->y() )
                            {
                                return true;
                            }
                        }
                        destination.clear();
                        break;
                    case 'R':
                        if(coordpion != NULL)
                        {
                            if(damier->getCase(coordpion->x(),coordpion->y())->getId() != 'R') // on rois ne peu pas attaquer un autre rois !
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
                            destination = getJoueur1()->getDeck()[tmp1]->deplacementsPossible(0,this);
                        }

                        for(int u = 0; u < destination.size(); u++)
                        {
                            if(destination[u].x() == coordcase->x() && destination[u].y() == coordcase->y() )
                            {
                                return true;
                            }
                        }
                        destination.clear();
                        break;

                    case 'F':
                        if(testDestination(coordcase, tmp1,0))
                            return true;
                        break;
                    case 'T':
                        if(testDestination(coordcase, tmp1,0))
                            return true;
                        break;
                    case 'C':
                        if(testDestination(coordcase, tmp1,0))
                            return true;
                        break;

                    }
                }
                else if(tmp2!=-1){
                    switch(damier->getCase(x,y)->getId())
                    {
                    case 'P':
                        destination =  attaquePion(QPoint(joueur1->getDeck()[tmp1]->getCoordonne().getX(),getJoueur1()->getDeck()[tmp1]->getCoordonne().getY()));
                        for(int u = 0; u < destination.size(); u++)
                        {
                            if(destination[u].x() == coordcase->x() && destination[u].y() == coordcase->y() )
                            {
                                return true;
                            }
                        }
                        destination.clear();
                        break;
                    case 'R':
                        if(coordpion != NULL)
                        {
                            if(damier->getCase(coordpion->x(),coordpion->y())->getId() != 'R') // on rois ne peu pas attaquer un autre rois !
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
                            destination = joueur2->getDeck()[tmp2]->deplacementsPossible(1,this);
                        }

                        for(int u = 0; u < destination.size(); u++)
                        {
                            if(destination[u].x() == coordcase->x() && destination[u].y() == coordcase->y() )
                            {
                                return true;
                            }
                        }
                        destination.clear();
                        break;

                    case 'F':
                        if(testDestination(coordcase, tmp2,1))
                            return true;
                        break;
                    case 'T':
                        if(testDestination(coordcase, tmp2,1))
                            return true;
                        break;
                    case 'C':
                        if(testDestination(coordcase, tmp2,1))
                            return true;
                        break;

                    }

                }
            }
        }
    }
    return false;
}

bool Plateau::testDestination(QPoint *coordcase, int i_piece, int i_joueur)
{
    QVector<QPoint> destination;
    if(i_joueur==0)
        destination =joueur1->getDeck()[i_piece]->deplacementsPossible(i_joueur,this);
    else
        destination =joueur2->getDeck()[i_piece]->deplacementsPossible(i_joueur,this);
    bool verif = false;
    for(int u = 0; u < destination.size(); u++)
    {
        if(destination[u].x() == coordcase->x() && destination[u].y() == coordcase->y() )
        {
            verif = true;;
        }
    }
    destination.clear();
    return verif;
}

QVector<QPoint> Plateau::attaquePion(QPoint cas){
    QVector<QPoint> resultat;
    bool noir = true;
    if(getGrille()->getCase(cas.x(),cas.y())->getCouleur() != 0)
    {
        noir = false;
    }
    //puis apres on avance toujours de devant et on prend sur les cotes
    if(noir == true)
    {
        if(cas.y() > 0)
        {
            if(damier->getCase(cas.x()+1,cas.y()-1)->getCouleur() != damier->getCase(cas.x(),cas.y())->getCouleur())
            {
                resultat.append(QPoint(cas.x()+1,cas.y()-1));
            }
        }
        if(cas.y() < 8)
        {
            if(damier->getCase(cas.x()+1,cas.y()+1)->getCouleur() != damier->getCase(cas.x(),cas.y())->getCouleur())
            {
                resultat.append(QPoint(cas.x()+1,cas.y()+1));
            }
        }
    }
    else
    {
        if(cas.y() > 0)
        {
            if( damier->getCase(cas.x()-1,cas.y()-1)->getCouleur() != damier->getCase(cas.x(),cas.y())->getCouleur())
            {
                resultat.append(QPoint(cas.x()-1,cas.y()-1));
            }
        }
        if(cas.y() < 8)
        {
            if( damier->getCase(cas.x()-1,cas.y()+1)->getCouleur() != damier->getCase(cas.x(),cas.y())->getCouleur())
            {
                resultat.append(QPoint(cas.x()-1,cas.y()+1));
            }
        }
    }

    return resultat;
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
