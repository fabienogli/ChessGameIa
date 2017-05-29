#include "Plateau.h"
#include "mainwindow.h"
#include "Coordonnee.h"
#include <stddef.h>
#include "ia.h"
#include <QMessageBox>
//Constructeur du plateau
Plateau::Plateau() :QObject()
{
    //initialisation du plateau
    initialize();
    //setJoueurActif(*joueur1);
}



void Plateau::initialize(){
    damier = new Grille();
    joueur1 = new Joueur("joueur 1",0);
    joueur2 = new Joueur("joueur 2",1);
    joueurActif = joueur2;
    coordDepart = new Coordonnee(0,0);
    coordArrivee= new Coordonnee(0,0);
    aSupprimer=new Piece();
    IA = new ia(1);
    initiatePosInGrid();
}
void Plateau::reinitialize(){

}
/**
 * @brief Plateau::jouerIA
 * la fonction jouerIA permet de faire jouer l'IA
 */
void Plateau::jouerIA(){
    std::cout << "je fais jouer IA"<< std::endl;
    //on retourne les coups possibles dans un vecteur
    //chaque se compose de la position de depart et celle d'arrivée
    QVector<QPoint> dep = IA->jouer(joueur1,this);
    std::cout << "fin jeu IA"<< std::endl;

    for(int i=0;i<dep.count();i++){
        std::cout << "x="<<dep.at(i).x()<<std::endl;
        std::cout << "y="<<dep.at(i).y()<<std::endl;
    }
    std::cout << "fin retour IA"<< std::endl;
    int usePion;
    //si le nombre de coups est différent de 2, on tire au sort
    if(dep.count() != 2)
    {
        usePion = qrand() % ((dep.count()/2)-1);
    }
    else
    {
        usePion = 0;
    }
    int pion_ori = usePion * 2;
    int pion_dest = (usePion * 2)+1;
    //si c'est un pion qui se déplace
    if(getGrille()->getCase(dep.at(pion_ori).x(),dep.at(pion_ori).y())->getId() == 'P')
    {
        if(dep.at(pion_dest).y() != dep.at(pion_ori).y() && getGrille()->getCase(dep.at(pion_dest).x(),dep.at(pion_dest).y())->getId() == 'N' )
        {
            std::cout <<"IF 2 IA"<< std::endl;
            coordArrivee->setX(dep.at(pion_dest).x());
            coordArrivee->setY(dep.at(pion_dest).y()-1);
            // m_interface->addtoScore(Pion, 1);
            //getGrille()->removePiece(coordArrivee);

        }
    }
    //si c'est un roi qui se déplace
    if(getGrille()->getCase(dep.at(pion_ori).x(),dep.at(pion_ori).y())->getId() == 'R')
    {
        m_Posi_Rois1.setX(dep.at(pion_dest).x());
        m_Posi_Rois1.setY(dep.at(pion_dest).y());
    }

    if(getGrille()->getCase(dep.at(pion_dest).x(),dep.at(pion_dest).y())->getId() != 'N')
    {
        // m_interface->addtoScore(m_matricePiece[dep.at(pion_dest).x()][dep.at(pion_dest).y()], 1);
    }
    //on set la valeur à 0 pour montrer que la pièce a bougé
    m_matriceDeplacement[dep.at(pion_ori).x()][dep.at(pion_ori).y()] = 0;
    int i1=dep.at(pion_ori).x();
    int i2=dep.at(pion_ori).y();
    int i3=dep.at(pion_dest).x();
    int i4=dep.at(pion_dest).y();
    std::cout << "IA a fait son choix"<< std::endl;
    std::cout << "IA i1="<<i1<< std::endl;
    std::cout << "IA i2="<<i2 <<std::endl;
    std::cout << "IA i3="<<i3 <<std::endl;
    std::cout << "IA i4="<<i4<< std::endl;
    coordDepart->setX(i1);
    coordDepart->setY(i2);
    (*aSupprimer).setCoordonnee(new Coordonnee(i1,i2));
    int idPiece = joueur1->isAnyPiece(Coordonnee(i1,i2));
    if(this->getGrille()->getCase(i3,i4)->getCouleur()==joueur2->getIdJoueur()){
        this->getPiece(new Coordonnee(i3,i4))->~Piece();
    }
    joueur1->getPiece2(idPiece)->setCoordonne(i3,i4);
    CaseDeplacementPossible =  IA->calc_echec_et_mat(joueur2->getIdJoueur(),m_Posi_Rois2);
    emit affichSuppInit(joueur1->getPiece2(joueur1->isAnyPiece(Coordonnee(i3,i4))),0,0);
    emit affichSuppInit(aSupprimer,0,1);
    emit coupJoue(joueur1->getIdJoueur(),i1,i2,i3,i4);
    std::cout << "IA emet signal d'affichage"<< std::endl;
    getGrille()->putPiece(joueur1->getPiece2(joueur1->isAnyPiece(Coordonnee(i3,i4))));
    getGrille()->removePiece(coordDepart);

    joueurActif = joueur2;
    std::cout<<"DEPLACEMENT IA : origine x="<<i1<<" y="<<i2<<" arrive x="<<i3<<" y="<<i4;
    if(CaseDeplacementPossible.count() == 0)
                 {
        emit loseSignal();

                 }
}
/**
 * @brief Plateau::initiatePosInGrid
 * Positionne les pieces des differentes piece des joueurs dans le plateau
 */
void Plateau::initiatePosInGrid()
{

    for (int i=0; i < (*joueur1).getDeckSize(); i++)
    {
        damier->putPiece(joueur1->getDeck()[i]);
        damier->putPiece(joueur2->getDeck()[i]);
        if(i<8){
            m_matriceDeplacement[0][i] = 1;
            m_matriceDeplacement[1][i] = 1;
            m_matriceDeplacement[6][i] = 1;
            m_matriceDeplacement[7][i] = 1;
        }
    }
}
//
/**
 * @brief Plateau::movePiece
 * permet de déplacer une piece
 * @param i1 il represente le y de départ
 * @param i2 il represente le x de départ
 * @param i3 il represente le y d'arrivée
 * @param i4 il represente le x d'arrivée
 */
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
    int tmp1 = (*joueur1).isAnyPiece(*coordDepart);
    //on recherche dans le deck du deuxieme joueur
    int tmp2 = (*joueur2).isAnyPiece(*coordDepart);
    Joueur* joueur;
    int tmpActif;
    //int kmp;
    if (tmp1 != -1)
    {
        joueur = joueur1;
        tmpActif = tmp1;
        std::cout << "joueur 1"<< std::endl;
        //kmp = joueur2->isAnyPiece(*coordArrivee);

    }
    //sinon c'est forcement occupe par une piece du joueur 2
    else if(tmp2 != -1)
    {
        joueur = joueur2;
        tmpActif = tmp2;
        std::cout << "joueur 2"<< std::endl;
        //kmp = joueur1->isAnyPiece(*coordArrivee);
    }

    /*
    //DEBUT TEST DEPLACEMENT
    Piece* tmpt = (*joueur).getDeck()[tmpActif];
    std::cout<<"Piece prise"<<std::endl;
    QVector<QPoint> listeCoups = tmpt->deplacementsPossible((*joueur).getIdJoueur(),this);
    std::cout<<"Liste déplacement"<<std::endl;

    for (int i =0; i<listeCoups.size();i++)
    {
        std::cout<<"x = "<<listeCoups[i].x()<<" et y="<<listeCoups[i].y()<<std::endl;
    }*/
    std::cout<<"fin de liste déplacement"<<std::endl;
    //FIN DEPLACEMENT
    (*joueur).afficherPiece();

    std::cout << "je suis 1-1";std::cout << std::endl;
    std::cout << tmpActif;std::cout << std::endl;
    bool b=(*joueur).getDeck()[tmpActif]->move(coordArrivee,(*joueur).getOrigin(), this);
    (*joueur).getDeck()[tmpActif]->afficher();

    std::cout << "je suis 1-2";std::cout << std::endl;
    if(b==true){

        //mettre a jour couleur des cases
        std::cout << "je suis 1-2bis";std::cout << std::endl;
        emit affichSuppInit((*joueur).getDeck()[tmpActif],(*joueur).getIdJoueur(),0);
        emit affichSuppInit(aSupprimer,(*joueur).getIdJoueur(),1);
        emit coupJoue(joueur->getIdJoueur(),i2,i1,i4,i3);
        getGrille()->putPiece((*joueur).getDeck()[tmpActif]);
        getGrille()->removePiece(coordDepart);
        if(joueurActif->getIdJoueur()==0){
            joueurActif = joueur2;
        }
        else if(joueurActif->getIdJoueur()==1){
            joueurActif = joueur1;
            this->jouerIA();
        }
        emit displayPlayerId(1);
    }else{

        std::cout << "deplacement non autorise";std::cout << std::endl;
        emit badMove();
    }
    std::cout << "je suis 1-3";std::cout << std::endl;
    std::cout << "jai fini";std::cout << std::endl;
    // delete tmpt;
}

/**
 * @brief Plateau::displayPlateau
 * slot pour affichage gui des pieces
 */
void Plateau::displayPlateau(){

    for (int i=0; i < (*joueur1).getDeckSize(); i++)
    {
        emit affichSuppInit((*joueur1).getDeck()[i],(*joueur1).getIdJoueur(),0);
        emit affichSuppInit((*joueur2).getDeck()[i],(*joueur2).getIdJoueur(),0);
    }

}

/**
 * @brief Plateau::setLevel
 * @param level représente le niveau de difficulté
 */
void Plateau::setLevel(int level)
{
    IA->setLevel(level);
}
/**
 * @brief Plateau::sentDisplayPlayerId
 * slot permettant d'afficher le nom du joueur actif
 */
void Plateau::sentDisplayPlayerId(){
    emit displayPlayerId((*joueurActif).getIdJoueur());
}


//
/**
 * @brief Plateau::getPiece
 * récupérer une case a une coordonne x, y
 * @param coord coordonnées de la pièce q'on cherche
 * @return un pointeur sur la piece de coordonnées x et y
 */
Piece* Plateau::getPiece(Coordonnee* coord)
{
    Piece* piece= new Piece();
    int i1= joueur1->isAnyPiece(*coord);
    int i2= joueur2->isAnyPiece(*coord);
    std::cout <<"i1="<<i1;std::cout << std::endl;
    std::cout <<"i2="<<i2;std::cout << std::endl;
    if(i1!=-1)
        piece =joueur1->getDeck()[i1];
    else if(i2!=-1){
        piece = joueur2->getDeck()[i2];
    }
    std::cout <<"jai fini"<<std::endl;
    return piece;
}

/**
 * @brief Plateau::afficher
 * Affichage du plateau dans la console

 */
void Plateau::afficher()
{
    for (int j = 0; j<(*damier).getHauteur(); j++) {
        for (int i = 0; i<(*damier).getLargeur(); i++) {
            //on teste si la case est occupee
            if (damier->getCase(i, j)->isOccupied()) {
                Coordonnee coord(i, j);
                //on recherche dans le deck du premier joueur
                int i1 = (*joueur1).isAnyPiece(coord);
                //on recherche dans le deck du deuxieme joueur
                int i2 = (*joueur2).isAnyPiece(coord);
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



/**
 * @brief Plateau::getJoueurActif
 * @return Retourne le pointeur du joueur actif
 */
Joueur* Plateau::getJoueurActif()
{
    return joueurActif;
}

/**
 * @brief Plateau::getJoueur1
 * @return Retourne le pointeur sur le joueur 1
 */
Joueur* Plateau::getJoueur1(){
    return joueur1;
}
/**
 * @brief Plateau::getJoueur2
 * @return Retourne le pointeur sur le joueur 2
 */
Joueur* Plateau::getJoueur2(){
    return joueur2;
}

void Plateau::setJoueurActif(Joueur  joueur){
    *joueurActif=joueur;
}

/**
 * @brief Plateau::getGrille
 * @return Retourne le pointeur sur le grille
 */
Grille* Plateau::getGrille(){
    // std::cout << "dans getgrille";std::cout << std::endl;
    return damier;
}


/**
 * @brief Plateau::caseAtOccupy
 * @param x coordonnee x
 * @param y coordonne y
 * @return  true si la case est occupée et false sinon
 */
bool Plateau::caseAtOccupy(int x, int y)
{
    return damier->getCase(x,y)->isOccupied();
}

/**
 * @brief Plateau::est_en_echec
 * permet de savoir si une pièce est en echec
 * @param coordcase coordonnées de la case à tester
 * @param coordpion Un pointeur qui peut etre NULL,permetant d'indiquer la position de la piece qu'on souhaite deplacer
 * @param couleur id du joueur
 * @return True si echec, sinon False
 */


/**
 * @brief Plateau::listeAttaquePion
 * permet de calculer la liste d'attaque du pion
 * @param cas coordonnées du pion à calculer
 * @return
 */

/**
 * @brief Plateau::checkPetitRoque
 * permet de vérifier si le petit roque est possible
 * @param joueur pointeur du joueur
 * @return true si possible false sinon
 */

/**
 * @brief Plateau::checkGrandRoque
 * permet de savoir si le grand roque est possible
 * @param joueur pointeur du joueur
 * @return true si possible false sinon
 */


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
    delete IA;
}
