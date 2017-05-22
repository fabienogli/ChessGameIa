#include "Plateau.h"
#include "mainwindow.h"
#include "Coordonnee.h"
#include <stddef.h>
#include "ia.h"
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
    joueurActif = joueur2;
    coordDepart = new Coordonnee(0,0);
    coordArrivee= new Coordonnee(0,0);
    aSupprimer=new Piece();
    m_coupPrecedent = new QVector<QPoint>();
    m_coupPrecedent->append(QPoint(0,0));
    m_coupPrecedent->append(QPoint(0,0));
    IA = new ia(2);
    IA->setCoupPrecedent(m_coupPrecedent);
    initiatePosInGrid();
}
void Plateau::reinitialize(){

}

void Plateau::jouerIA(){
    std::cout << "je fais jouer IA"<< std::endl;
 QVector<QPoint> dep = IA->jouer(joueur1,IA->getLevel(),this);
 std::cout << "fin retour IA"<< std::endl;
 int usePion;
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
     if(getGrille()->getCase(dep.at(pion_ori).x(),dep.at(pion_ori).y())->getId() == 'P')
         {

             if(dep.at(pion_dest).y() != dep.at(pion_ori).y() && getGrille()->getCase(dep.at(pion_dest).x(),dep.at(pion_dest).y())->getId() == 'N' )
             {
                 coordArrivee->setX(dep.at(pion_dest).x());
                 coordArrivee->setY(dep.at(pion_dest).y()-1);
                // m_interface->addtoScore(Pion, 1);
                 //getGrille()->removePiece(coordArrivee);

             }
         }
     if(getGrille()->getCase(dep.at(pion_ori).x(),dep.at(pion_ori).y())->getId() == 'R')
         {
             m_Posi_Rois1.setX(dep.at(pion_dest).x());
             m_Posi_Rois1.setY(dep.at(pion_dest).y());
         }
         m_coupPrecedent[0][0].setX(dep.at(pion_ori).x());
         m_coupPrecedent[0][0].setY(dep.at(pion_ori).y());
         m_coupPrecedent[0][1].setX(dep.at(pion_dest).x());
         m_coupPrecedent[0][1].setY(dep.at(pion_dest).y());

         if(getGrille()->getCase(dep.at(pion_dest).x(),dep.at(pion_dest).y())->getId() != 'N')
             {
                // m_interface->addtoScore(m_matricePiece[dep.at(pion_dest).x()][dep.at(pion_dest).y()], 1);
             }
             m_matriceDeplacement[dep.at(pion_ori).x()][dep.at(pion_ori).y()] = 0;
             int i1=dep.at(pion_ori).x();
             int i2=dep.at(pion_ori).y();
             int i3=dep.at(pion_dest).x();
             int i4=dep.at(pion_dest).y();
             std::cout << "IA a fait son choix"<< std::endl;
             coordDepart->setX(i1);
             coordDepart->setY(i2);
             (*aSupprimer).setCoordonnee(new Coordonnee(i1,i2));
             joueur1->getPiece2(joueur1->isAnyPiece(Coordonnee(i1,i2)))->setCoordonne(i3,i4);
             //CaseDeplacementPossible =  IA->calc_echec_et_mat(joueur2,m_Posi_Rois2,this);
             emit affichSuppInit(joueur1->getPiece2(joueur1->isAnyPiece(Coordonnee(i1,i2))),0,0);
             emit affichSuppInit(aSupprimer,0,1);
             std::cout << "IA emet signal d'affichage"<< std::endl;
             getGrille()->putPiece(joueur1->getPiece2(joueur1->isAnyPiece(Coordonnee(i1,i2))));
             getGrille()->removePiece(coordDepart);
             std::cout<<"DEPLACEMENT IA : origine x="<<i2<<" y="<<i1<<" arrive x="<<i4<<" y="<<i3;
             movePiece(i2,i1,i4,i3);
             /*if(CaseDeplacementPossible.count() == 0)
                 {
                     int ret = QMessageBox::question(this,"Pauvre noob Partie Perdu","L'IA a gagnier la partie ! \nVoulez vous rejouer ?",QMessageBox::Yes | QMessageBox::No);
                     if(ret == QMessageBox::Yes)
                     {
                         this->reinitialisation();
                     }
                     else
                     {
                         this->destroyed();
                     }
                 }*/
             // augmentation du nombre de tours jouer
                // m_tourno++;
             //Detection de fin de partie par manque de nombre de tours
                /* if(m_nbTourMax <= m_tourno)
                 {
                     int ret = QMessageBox::question(this,"Match Nul","Le nombre de tour maximum est dépasser Math Nul ! \nVoulez vous rejouer ?",QMessageBox::Yes | QMessageBox::No);
                     if(ret == QMessageBox::Yes)
                     {
                         this->reinitialisation();
                     }
                     else
                     {
                         this->destroyed();
                     }
                 }*/
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

    //std::cout << getPiece(new Coordonnee(7,6))->;std::cout << std::endl;
    std::cout<<"X="<<joueur2->getDeck()[7]->getCoordonne()->getX()<<std::endl;
    std::cout<<"Y="<<joueur2->getDeck()[7]->getCoordonne()->getY()<<std::endl;
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
        if(joueurActif->getIdJoueur()==0){
            //idJoueurActif = 2;
            joueurActif = joueur2;
        }
        else{
            joueurActif = joueur1;
           // idJoueurActif =1;
           this->jouerIA();

            //idJoueurActif = 1;
        }

        emit displayPlayerId(1);
    }else{

        std::cout << "deplacement non autorise";std::cout << std::endl;
        emit badMove();
    }
    std::cout << "je suis 1-3";std::cout << std::endl;
    std::cout << "jai fini";std::cout << std::endl;
   // joueur2->getDeck()[7]->afficher();
   // delete tmpt;
    /*Erreur dans
     * this->jouerIA();
     *
     */
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
    Piece* piece= new Piece();
    double i1= joueur1->isAnyPiece(*coord);
    double i2= joueur2->isAnyPiece(*coord);
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
Joueur* Plateau::getJoueurActif()
{
    return joueurActif;
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
   // std::cout << "dans getgrille";std::cout << std::endl;
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

//    double tmp1=-1;
//    double tmp2=-1;
    for(int x = 0; x < 8; x++)
    {
        for(int y = 0; y < 8; y++)
        {
            double tmp1=-1;
            double tmp2=-1;
            std::cout << x;std::cout << std::endl;
            std::cout << y;std::cout << std::endl;
            Coordonnee coordtmp(x,y);
            std::cout << damier->getCase(x,y)->getCouleur()<<"et "<<couleur;std::cout << std::endl;
            if((damier->getCase(x,y)->getCouleur() != couleur) && (damier->getCase(x,y)->getCouleur() !=  -1) )
            {
                //coordtmp.setX(x);
                //coordtmp.setY(y);
                std::cout << coordtmp.getX();std::cout << std::endl;
                std::cout << coordtmp.getY();std::cout << std::endl;
                std::cout << "dans estenechecprim";std::cout << std::endl;
                if(damier->getCase(x,y)->getCouleur() == 1){
                    //on recherche dans le deck du premier joueur
                    std::cout<<"dans le joueur2"<<std::endl;
                    tmp1 = (*joueur2).isAnyPiece(coordtmp);
                }
                else if(damier->getCase(x,y)->getCouleur() == 0){
                    std::cout<<"dans le joueur1"<<std::endl;
                    tmp2 = (*joueur1).isAnyPiece(coordtmp);
                }
                std::cout<<"tmp1= "<<tmp1<<" tmp2="<<tmp2<<std::endl;
                std::cout << "dans estenechecprim2";std::cout << std::endl;
                if(tmp2!=-1){
                    switch(damier->getCase(x,y)->getId())
                    {
                    case 'P':
                        std::cout << "dans estenechec1";std::cout << std::endl;
                        destination = attaquePion(QPoint(joueur1->getDeck()[tmp2]->getCoordonne()->getX(),joueur1->getDeck()[tmp2]->getCoordonne()->getY()));
                        std::cout << "dans estenechec2";std::cout << std::endl;
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
                        std::cout << "dans estenechec3";std::cout << std::endl;
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
                            std::cout << "dans estenechec4";std::cout << std::endl;
                            destination = getJoueur1()->getDeck()[tmp2]->deplacementsPossible(0,this);
                            std::cout << "dans estenechec5";std::cout << std::endl;
                        }

                        for(int u = 0; u < destination.size(); u++)
                        {
                            std::cout << "dans estenechec6";std::cout << std::endl;
                            if(destination[u].x() == coordcase->x() && destination[u].y() == coordcase->y() )
                            {
                                std::cout << "dans estenechec7";std::cout << std::endl;
                                return true;
                            }
                        }
                        destination.clear();
                        break;

                    case 'F':
                        std::cout << "dans estenechec8";std::cout << std::endl;
                        if(testDestination(coordcase, tmp2,0))
                            return true;
                        break;
                    case 'T':
                        std::cout << "dans estenechec9";std::cout << std::endl;
                        if(testDestination(coordcase, tmp2,0))
                            return true;
                        break;
                    case 'C':
                        std::cout << "dans estenechec10";std::cout << std::endl;
                        if(testDestination(coordcase, tmp2,0))
                            return true;
                        break;

                    }
                }
                else if(tmp1!=-1){
                    switch(damier->getCase(x,y)->getId())
                    {
                    case 'P':
                        std::cout << "dans estenechec11";std::cout << std::endl;
                        destination =  attaquePion(QPoint(joueur2->getDeck()[tmp1]->getCoordonne()->getX(),getJoueur1()->getDeck()[tmp1]->getCoordonne()->getY()));
                        std::cout << "dans estenechec12";std::cout << std::endl;
                        for(int u = 0; u < destination.size(); u++)
                        {
                             std::cout << "dans estenechec13";std::cout << std::endl;
                            if(destination[u].x() == coordcase->x() && destination[u].y() == coordcase->y() )
                            {
                                return true;
                            }
                        }
                        destination.clear();
                        break;
                    case 'R':
                         std::cout << "dans estenechec14";std::cout << std::endl;
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
                             std::cout << "dans estenechec15";std::cout << std::endl;
                            destination = joueur2->getDeck()[tmp1]->deplacementsPossible(1,this);
                        }

                        for(int u = 0; u < destination.size(); u++)
                        {
                             std::cout << "dans estenechec16";std::cout << std::endl;
                            if(destination[u].x() == coordcase->x() && destination[u].y() == coordcase->y() )
                            {
                                return true;
                            }
                        }
                        destination.clear();
                        break;

                    case 'F':
                         std::cout << "dans estenechec17";std::cout << std::endl;
                        if(testDestination(coordcase, tmp1,1)){
                            std::cout << "dans estenechec18";std::cout << std::endl;
                            return true;
                        }
                        break;
                    case 'T':
                         std::cout << "dans estenechec18";std::cout << std::endl;
                        if(testDestination(coordcase, tmp1,1))
                        {
                                                    std::cout << "dans estenechec18";std::cout << std::endl;
                                                    return true;
                                                }
                        break;
                    case 'C':
                         std::cout << "dans estenechec19";std::cout << std::endl;
                        if(testDestination(coordcase, tmp1,1))
                            return true;
                        break;

                    }

                }
            }
            coordtmp.~Coordonnee();
        }
    }
    return false;
}

bool Plateau::testDestination(QPoint *coordcase, int i_piece, int i_joueur)
{
    QVector<QPoint> destination;
     std::cout << "dans estenechectest";std::cout << std::endl;
    if(i_joueur==0)
        destination =joueur1->getDeck()[i_piece]->deplacementsPossible(i_joueur,this);
    else
        destination =joueur2->getDeck()[i_piece]->deplacementsPossible(i_joueur,this);
    std::cout << "dans estenechectest2";std::cout << std::endl;
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
        std::cout << "dans attaquepion2";std::cout << std::endl;
        if(cas.x() > 0)
        {
            std::cout << "dans attaquepion3";std::cout << std::endl;
            if(damier->getCase(cas.x()-1,cas.y()+1)->getCouleur() != damier->getCase(cas.x(),cas.y())->getCouleur())
            {
                std::cout << "dans attaquepion4";std::cout << std::endl;
                resultat.append(QPoint(cas.x()-1,cas.y()+1));
            }
        }
        std::cout << "dans attaquepion5";std::cout << std::endl;
        if(cas.x() < 7)
        {
std::cout << "dans attaquepion6";std::cout << std::endl;
            if(damier->getCase(cas.x()+1,cas.y()+1)->getCouleur() != damier->getCase(cas.x(),cas.y())->getCouleur())
            {
                std::cout << "dans attaquepion7";std::cout << std::endl;
                resultat.append(QPoint(cas.x()+1,cas.y()+1));
            }
        }
    }
    else
    {
        std::cout << "dans attaquepion8";std::cout << std::endl;
        if(cas.x() > 0)
        {
            std::cout << "dans attaquepion9";std::cout << std::endl;
            if( damier->getCase(cas.x()-1,cas.y()-1)->getCouleur() != damier->getCase(cas.x(),cas.y())->getCouleur())
            {
                std::cout << "dans attaquepion10";std::cout << std::endl;
                resultat.append(QPoint(cas.x()-1,cas.y()-1));
            }
        }
        if(cas.x() < 7)
        {
            std::cout << "dans attaquepion7";std::cout << std::endl;
            if( damier->getCase(cas.x()+1,cas.y()-1)->getCouleur() != damier->getCase(cas.x(),cas.y())->getCouleur())
            {
                resultat.append(QPoint(cas.x()+1,cas.y()-1));
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
    delete IA;
}
