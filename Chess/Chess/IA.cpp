#include "ia.h"
#include "Plateau.h"
#include "Joueur.h"
#include "Piece.h"

/**
 * @brief ia::ia
 * constructeur de l'IA
 * @param level représente le niveau de difficulté de l'IA
 */
ia::ia(int level)
{
    setLevel(level);
}
/**
 * @brief ia::setCoupPrecedent
 * setter du coup précédent
 * @param coupPrecedent représente un vector de QPoint contenant le coup précédent
 */
void ia::setCoupPrecedent(QVector<QPoint> * coupPrecedent)
{
    this->m_coupPrecedent=coupPrecedent;
}
/**
 * @brief ia::gagnantEnCours
 * permet de savoir quelle joueur est gagnant
 * @param idJoueur id du joueur en cours
 * @param plateau pointeur sur le plateau
 * @return 0 si la partie n'est pas fini -1000 si le joueur a perdu et 1000 si il a gagne
 */
int ia::gagnantEnCours(int idJoueur,Plateau * plateau){
    int retour =0;
    if(idJoueur == 0)
    {
        if((this->calc_echec_et_mat(plateau->getJoueur1(),this->m_Posi_Rois1,plateau)).count() == 0)
            //if((this->calc_echec_et_mat(plateau->getJoueur1(),this->m_Posi_Rois1,plateau)) == 0)

        {
            std::cout<<"dans gagnant jeux 1"<<std::endl;
            retour=-1000;
        }
        if((this->calc_echec_et_mat(plateau->getJoueur2(),this->m_Posi_Rois2,plateau)).count() == 0)
            //     if((this->calc_echec_et_mat(plateau->getJoueur2(),this->m_Posi_Rois2,plateau)) == 0)

        {
            std::cout<<"dans gagnant jeux 2"<<std::endl;
            retour=1000;
        }
    }
    else if (idJoueur == 1)
    {
        //if((this->calc_echec_et_mat(plateau->getJoueur2(),this->m_Posi_Rois2,plateau)) == 0)

        if((this->calc_echec_et_mat(plateau->getJoueur2(),this->m_Posi_Rois2,plateau)).count() == 0)
        {
            std::cout<<"dans gagnant jeux 3"<<std::endl;
            retour= -1000;
        }
        //if((this->calc_echec_et_mat(plateau->getJoueur1(),this->m_Posi_Rois1,plateau)) == 0)

        if((this->calc_echec_et_mat(plateau->getJoueur1(),this->m_Posi_Rois1,plateau)).count() == 0)
        {
            std::cout<<"dans gagnant jeux 4"<<std::endl;
            retour= 1000;
        }
    }
    std::cout<<"dans gagnant jeux 5"<<std::endl;
    return retour;

}
/**
 * @brief ia::max
 * fonction max permettant de simuler le coup de l'IA
 * @param joueur pointeur sur le joueur que fait jouer l'IA
 * @param plateau pointeur sur le plateau
 * @param profondeur nombre de coup
 * @param alpha entier alpha
 * @param beta entier beta avec alpha < beta
 * @return valeur final du jeu ou valeur gagnant si fin de partie
 */
int ia::max(Joueur *joueur,Plateau *plateau,int profondeur,int alpha,int beta)
{
    std::cout<<"dans le max"<<std::endl;
    int retour=gagnantEnCours(joueur->getIdJoueur(),plateau)  ;
    //int retour=0;
    std::cout<<"jai fini le calcul du retour gagnantEnCours dans max"<<std::endl;
    std::cout<<"retour="<<retour<<std::endl;
    int max = -10000;
    if(profondeur <= 0 || (retour != 0))
        //if(profondeur <= 0 )
    {
        if(profondeur <= 0)
        {
            std::cout << "jevalue le plateau dans max";std::cout << std::endl;
            return eval(plateau);
        }
        else
        {
            return retour;
        }
    }

    for(int i =0;i<joueur->getDeckSize();i++){

        int x = joueur->getDeck()[i]->getCoordonne()->getX();
        int y = joueur->getDeck()[i]->getCoordonne()->getY();
        char id = joueur->getDeck()[i]->getId();
        QVector<QPoint> listeCoup;
        listeCoup = joueur->getDeck()[i]->deplacementsPossible(joueur->getIdJoueur(),plateau);
        for(int i=0;i<listeCoup.size();i++){
            int coup_origin_x = plateau->getCoupPrec().at(0).x();
            int coup_origin_y =plateau->getCoupPrec().at(0).y();
            int coup_dest_x = plateau->getCoupPrec().at(1).x();
            int coup_dest_y = plateau->getCoupPrec().at(1).y();
            bool occupiedtmp=plateau->getGrille()->getCase(listeCoup.at(i).x(),listeCoup.at(i).y())->isOccupied();
            char idtmp=plateau->getGrille()->getCase(listeCoup.at(i).x(),listeCoup.at(i).y())->getId();
            int couleurtmp=plateau->getGrille()->getCase(listeCoup.at(i).x(),listeCoup.at(i).y())->getCouleur();
            bool specialMoveDone = false;
            if(id == 'P')
            {
                //                        if(listeCoup.at(i).x() != x && !plateau->caseAtOccupy(listeCoup.at(i).x(),listeCoup.at(i).y()))
                //                        {
                //                            specialMoveDone = true;
                //                            if(x - listeCoup.at(i).x() > 0)
                //                            {
                //                                plateau->getGrille()->getCase(x+1,y)->removePiece();
                //                            }
                //                            else
                //                            {
                //                                plateau->getGrille()->getCase(x-1,y)->removePiece();
                //                            }
                //                        }
            }
            if(id == 'R')
            {
                if(joueur->getIdJoueur() == 0)
                {
                    this->m_Posi_Rois1.setX(listeCoup.at(i).x());
                    this->m_Posi_Rois1.setY(listeCoup.at(i).y());
                }
                else
                {
                    this->m_Posi_Rois2.setX(listeCoup.at(i).x());
                    this->m_Posi_Rois2.setY(listeCoup.at(i).y());
                }
            }
            //on simule le coup
            plateau->getGrille()->getCase(listeCoup.at(i).x(),listeCoup.at(i).y())->setId(plateau->getGrille()->getCase(x,y)->getId()) ;
            plateau->getGrille()->getCase(listeCoup.at(i).x(),listeCoup.at(i).y())->setCouleur(plateau->getGrille()->getCase(x,y)->getCouleur()) ;
            plateau->getGrille()->getCase(listeCoup.at(i).x(),listeCoup.at(i).y())->setPiece();
            plateau->getGrille()->removePiece(new Coordonnee(x,y));
            m_coupPrecedent[0][0].setX(x);
            m_coupPrecedent[0][0].setY(y);
            m_coupPrecedent[0][1].setX(listeCoup.at(i).x());
            m_coupPrecedent[0][1].setY(listeCoup.at(i).y());
            int score = 0;
            // on relance l'appel

            if(joueur->getIdJoueur() == 0)
            {
                std::cout << "profondeur max="<<profondeur-1;std::cout << std::endl;
                score = min(plateau->getJoueur2(),plateau,profondeur-1,alpha,beta);
            }
            else
            {
                std::cout << "profondeur max="<<profondeur-1;std::cout << std::endl;
                score = min(plateau->getJoueur1(),plateau,profondeur-1,alpha,beta);
            }

            m_coupPrecedent[0][0].setX(coup_origin_x);
            m_coupPrecedent[0][0].setY(coup_origin_y);
            m_coupPrecedent[0][1].setX(coup_dest_x);
            m_coupPrecedent[0][1].setY(coup_dest_y);
            if(plateau->getGrille()->getCase(listeCoup.at(i).x(),listeCoup.at(i).y())->getId() == 'R')
            {
                if(plateau->getGrille()->getCase(listeCoup.at(i).x(),listeCoup.at(i).y())->getCouleur() == 0)
                {
                    this->m_Posi_Rois1.setX(x);
                    this->m_Posi_Rois1.setY(y);
                }
                else
                {
                    this->m_Posi_Rois2.setX(x);
                    this->m_Posi_Rois2.setY(y);
                }
            }
            //                    if(specialMoveDone)
            //                    {
            //                        if(x - listeCoup.at(i).x() > 0)
            //                        {
            //                            plateau->getGrille()->getCase(x-1,y)->setPiece();
            //                            plateau->getGrille()->getCase(x-1,y)->setId('P');
            //                            if(joueur->getIdJoueur() == 0)
            //                            {
            //                                plateau->getGrille()->getCase(x-1,y)->setCouleur(1);
            //                            }
            //                            else
            //                            {
            //                                plateau->getGrille()->getCase(x-1,y)->setCouleur(0);
            //                            }
            //                        }
            //                        else
            //                        {
            //                            plateau->getGrille()->getCase(x+1,y)->setPiece();
            //                            plateau->getGrille()->getCase(x+1,y)->setId('P');
            //                            if(joueur->getIdJoueur() == 0)
            //                            {
            //                                plateau->getGrille()->getCase(x+1,y)->setCouleur(1);
            //                            }
            //                            else
            //                            {
            //                                plateau->getGrille()->getCase(x+1,y)->setCouleur(0);
            //                            }
            //                        }
            //                    }
            //on reset les cases modifiées
            plateau->getGrille()->getCase(x,y)->setId(plateau->getGrille()->getCase(listeCoup.at(i).x(),listeCoup.at(i).y())->getId());
            plateau->getGrille()->getCase(x,y)->setCouleur(plateau->getGrille()->getCase(listeCoup.at(i).x(),listeCoup.at(i).y())->getCouleur());
            plateau->getGrille()->getCase(x,y)->setPiece();
            plateau->getGrille()->getCase(listeCoup.at(i).x(),listeCoup.at(i).y())->setId(idtmp);
            plateau->getGrille()->getCase(listeCoup.at(i).x(),listeCoup.at(i).y())->setCouleur(couleurtmp);
            plateau->getGrille()->getCase(listeCoup.at(i).x(),listeCoup.at(i).y())->setOccupied(occupiedtmp);

            if (score > max)
            {
                max = score;
            }
            if(max >= beta)
            {
                return max;
            }

            if(max > alpha)
            {
                alpha = max;
            }
        }

    }

    return max;
}
/**
 * @brief ia::min
 * fonction permettant de simuler le coup de l'adversaire
 * @param joueur pointeur sur le joueur adverse
 * @param plateau pointeur sur le plateau
 * @param profondeur nombre de coup
 * @param alpha entier alpha
 * @param beta entier beta
 * @return valeur final du jeu ou valeur gagnant si fin de partie
 */
int ia::min(Joueur *joueur,Plateau *plateau,int profondeur,int alpha,int beta){
    std::cout << "dans le min";std::cout << std::endl;
    std::cout << "dans jouer de la classe min1";std::cout << std::endl;
    int retour=gagnantEnCours(joueur->getIdJoueur(),plateau)  ;
    //int retour=0;
    std::cout << "dans jouer de la classe min2";std::cout << std::endl;
    int min = 10000;
    std::cout << "dans jouer de la classe min3";std::cout << std::endl;
    if(profondeur <= 0 || (retour != 0))
        //if(profondeur <= 0 )
    {
        if(profondeur <= 0)
        {
            std::cout << "jevalue le plateau dans min";std::cout << std::endl;
            return eval(plateau);
        }
        else
        {
            return retour;
        }
    }

    for(int i =0;i<joueur->getDeckSize();i++){

        int x = joueur->getDeck()[i]->getCoordonne()->getX();
        int y = joueur->getDeck()[i]->getCoordonne()->getY();
        char id = joueur->getDeck()[i]->getId();
        QVector<QPoint> listeCoup;
        listeCoup = joueur->getDeck()[i]->deplacementsPossible(joueur->getIdJoueur(),plateau);

        for(int i=0;i<listeCoup.count();i++){
            int coup_origin_x = plateau->getCoupPrec().at(0).x();
            int coup_origin_y =plateau->getCoupPrec().at(0).y();
            int coup_dest_x = plateau->getCoupPrec().at(1).x();
            int coup_dest_y = plateau->getCoupPrec().at(1).y();
            bool occupiedtmp=plateau->getGrille()->getCase(listeCoup.at(i).x(),listeCoup.at(i).y())->isOccupied();
            char idtmp=plateau->getGrille()->getCase(listeCoup.at(i).x(),listeCoup.at(i).y())->getId();
            int couleurtmp=plateau->getGrille()->getCase(listeCoup.at(i).x(),listeCoup.at(i).y())->getCouleur();

            bool specialMoveDone = false;
            if(id == 'P')
            {
                //                        if(listeCoup.at(i).x() != x && !plateau->caseAtOccupy(listeCoup.at(i).x(),listeCoup.at(i).y()))
                //                        {
                //                            specialMoveDone = true;
                //                            if(x - listeCoup.at(i).x() > 0)
                //                            {
                //                                plateau->getGrille()->getCase(x+1,y)->removePiece();
                //                            }
                //                            else
                //                            {
                //                                plateau->getGrille()->getCase(x-1,y)->removePiece();
                //                            }
                //                        }
            }
            if(id == 'R')
            {
                if(joueur->getIdJoueur() == 0)
                {
                    this->m_Posi_Rois1.setX(listeCoup.at(i).x());
                    this->m_Posi_Rois1.setY(listeCoup.at(i).y());
                }
                else
                {
                    this->m_Posi_Rois2.setX(listeCoup.at(i).x());
                    this->m_Posi_Rois2.setY(listeCoup.at(i).y());
                }
            }
            plateau->getGrille()->getCase(listeCoup.at(i).x(),listeCoup.at(i).y())->setId(plateau->getGrille()->getCase(x,y)->getId()) ;
            plateau->getGrille()->getCase(listeCoup.at(i).x(),listeCoup.at(i).y())->setCouleur(plateau->getGrille()->getCase(x,y)->getCouleur()) ;
            plateau->getGrille()->getCase(listeCoup.at(i).x(),listeCoup.at(i).y())->setPiece();
            plateau->getGrille()->removePiece(new Coordonnee(x,y));
            m_coupPrecedent[0][0].setX(x);
            m_coupPrecedent[0][0].setY(y);
            m_coupPrecedent[0][1].setX(listeCoup.at(i).x());
            m_coupPrecedent[0][1].setY(listeCoup.at(i).y());
            int score = 0;
            // on relance l'appel
            if(joueur->getIdJoueur() == 0)
            {
                std::cout << "profondeur min="<<profondeur-1;std::cout << std::endl;
                score = max(plateau->getJoueur2(),plateau,profondeur-1,alpha,beta);
            }
            else
            {
                std::cout << "profondeur min="<<profondeur-1;std::cout << std::endl;
                score = max(plateau->getJoueur1(),plateau,profondeur-1,alpha,beta);
            }

            m_coupPrecedent[0][0].setX(coup_origin_x);
            m_coupPrecedent[0][0].setY(coup_origin_y);
            m_coupPrecedent[0][1].setX(coup_dest_x);
            m_coupPrecedent[0][1].setY(coup_dest_y);
            if(plateau->getGrille()->getCase(listeCoup.at(i).x(),listeCoup.at(i).y())->getId() == 'R')
            {
                if(plateau->getGrille()->getCase(listeCoup.at(i).x(),listeCoup.at(i).y())->getCouleur() == 0)
                {
                    this->m_Posi_Rois1.setX(x);
                    this->m_Posi_Rois1.setY(y);
                }
                else
                {
                    this->m_Posi_Rois2.setX(x);
                    this->m_Posi_Rois2.setY(y);
                }
            }
            //                    if(specialMoveDone)
            //                    {
            //                                                if(x - listeCoup.at(i).x() > 0)
            //                                                {
            //                                                    plateau->getGrille()->getCase(x-1,y)->setPiece();
            //                                                    plateau->getGrille()->getCase(x-1,y)->setId('P');
            //                                                    if(joueur->getIdJoueur() == 0)
            //                                                    {
            //                                                        plateau->getGrille()->getCase(x-1,y)->setCouleur(1);
            //                                                    }
            //                                                    else
            //                                                    {
            //                                                        plateau->getGrille()->getCase(x-1,y)->setCouleur(0);
            //                                                    }
            //                        }
            //                        else
            //                        {
            //                            plateau->getGrille()->getCase(x+1,y)->setPiece();
            //                            plateau->getGrille()->getCase(x+1,y)->setId('P');
            //                            if(joueur->getIdJoueur() == 0)
            //                            {
            //                                plateau->getGrille()->getCase(x+1,y)->setCouleur(1);
            //                            }
            //                            else
            //                            {
            //                                plateau->getGrille()->getCase(x+1,y)->setCouleur(0);
            //                            }
            //                        }
            //                    }

            plateau->getGrille()->getCase(x,y)->setId(plateau->getGrille()->getCase(listeCoup.at(i).x(),listeCoup.at(i).y())->getId());
            plateau->getGrille()->getCase(x,y)->setCouleur(plateau->getGrille()->getCase(listeCoup.at(i).x(),listeCoup.at(i).y())->getCouleur());
            plateau->getGrille()->getCase(x,y)->setPiece();
            plateau->getGrille()->getCase(listeCoup.at(i).x(),listeCoup.at(i).y())->setId(idtmp);
            plateau->getGrille()->getCase(listeCoup.at(i).x(),listeCoup.at(i).y())->setCouleur(couleurtmp);
            plateau->getGrille()->getCase(listeCoup.at(i).x(),listeCoup.at(i).y())->setOccupied(occupiedtmp);
            if (score < min)
            {
                min = score;
            }
            if(alpha >= min)
            {
                return min;
            }
            if(beta > min)
            {
                beta = min;
            }
        }
    }

    return min;
}
/**
 * @brief ia::setLevel
 * setter du niveau de difficulté de l'IA
 * @param i i est le niveau de difficulté
 */
void ia::setLevel(int i){
    if(i == 1)
    {
        this->level = 2;
    }
    else if(i == 2)
    {
        this->level = 4;
    }
    else
    {
        this->level = 6;
    }
}
int ia::getLevel(){
    return level;
}

/**
 * @brief ia::jouer
 * fait jouer l'IA
 * @param joueur pointeur
 * @param profondeur nombre de coups
 * @param plateau pointeur sur le plateau
 * @return retourne une vecteur de coups possibles
 */
QVector<QPoint> ia::jouer(Joueur *joueur,int profondeur,Plateau *plateau)
{
    int max = -10000;
    int score;
    QVector<QPoint> result;
    for(int x=0;x<8;x++)
    {
        for(int y=0;y<8;y++)
        {
            std::cout << "dans jouer de la classe IA";std::cout << std::endl;
            if(plateau->getGrille()->getCase(x,y)->getId() == 'R')
            {
                if(plateau->getGrille()->getCase(x,y)->getCouleur() == 0)
                {
                    this->m_Posi_Rois1.setX(x);
                    this->m_Posi_Rois1.setY(y);
                }
                else
                {
                    this->m_Posi_Rois2.setX(x);
                    this->m_Posi_Rois2.setY(y);
                }
            }
            if(plateau->getGrille()->getCase(x,y)->getCouleur() == joueur->getIdJoueur())
            {
                std::cout << "dans jouer de la classe IA 1";std::cout << std::endl;
                int idPiece=(joueur->isAnyPiece(Coordonnee(x,y)));
                std::cout << "dans jouer de la classe IA 1-1";std::cout << std::endl;
                std::cout << "dans jouer de la classe IA 1-2";std::cout << std::endl;
                if(idPiece != (-1)){
                    char id = joueur->getDeck()[idPiece]->getId();
                    QVector<QPoint> listeCoup;
                    listeCoup = joueur->getDeck()[idPiece]->deplacementsPossible(joueur->getIdJoueur(),plateau);
                    std::cout << "dans jouer de la classe IA2";std::cout << std::endl;
                    std::cout << "nombre de coups="<<listeCoup.count();std::cout << std::endl;
                    for (int i = 0; i < listeCoup.count(); i++)
                    {
                        std::cout << "liste coup x="<<listeCoup.at(i).x();std::cout << std::endl;
                        std::cout << "liste coup y="<<listeCoup.at(i).y();std::cout << std::endl;
                        int coup_origin_x = m_coupPrecedent->at(0).x();
                        int coup_origin_y = m_coupPrecedent->at(0).y();
                        int coup_dest_x = m_coupPrecedent->at(1).x();
                        int coup_dest_y = m_coupPrecedent->at(1).y();
                        std::cout << "dans jouer de la classe IA3";std::cout << std::endl;
                        // on joue le tour
                        bool occupiedtmp=plateau->getGrille()->getCase(listeCoup.at(i).x(),listeCoup.at(i).y())->isOccupied();
                        char idtmp=plateau->getGrille()->getCase(listeCoup.at(i).x(),listeCoup.at(i).y())->getId();
                        int couleurtmp=plateau->getGrille()->getCase(listeCoup.at(i).x(),listeCoup.at(i).y())->getCouleur();
                        /* ///////
                    bool specialMoveDone = false;
                    if(id == 'P')
                    {
                        if(listeCoup.at(i).x() != x && !plateau->caseAtOccupy(listeCoup.at(i).x(),listeCoup.at(i).y()))
                        {
                            specialMoveDone = true;
                            if(x - listeCoup.at(i).x() > 0)
                            {
                                plateau->getGrille()->getCase(x+1,y)->removePiece();
                            }
                            else
                            {
                                plateau->getGrille()->getCase(x-1,y)->removePiece();
                            }
                        }
                    }*/
                        std::cout << "dans jouer de la classe IA4";std::cout << std::endl;
                        if(id == 'R')
                        {
                            if(joueur->getIdJoueur() == 0)
                            {
                                this->m_Posi_Rois1.setX(listeCoup.at(i).x());
                                this->m_Posi_Rois1.setY(listeCoup.at(i).y());
                            }
                            else
                            {
                                this->m_Posi_Rois2.setX(listeCoup.at(i).x());
                                this->m_Posi_Rois2.setY(listeCoup.at(i).y());
                            }
                        }
                        //on simule le coup
                        plateau->getGrille()->getCase(listeCoup.at(i).x(),listeCoup.at(i).y())->setId(plateau->getGrille()->getCase(x,y)->getId()) ;
                        plateau->getGrille()->getCase(listeCoup.at(i).x(),listeCoup.at(i).y())->setCouleur(plateau->getGrille()->getCase(x,y)->getCouleur()) ;
                        plateau->getGrille()->getCase(listeCoup.at(i).x(),listeCoup.at(i).y())->setPiece();
                        plateau->getGrille()->removePiece(new Coordonnee(x,y));
                        std::cout << "dans jouer de la classe IA5";std::cout << std::endl;
                        m_coupPrecedent[0][0].setX(x);
                        m_coupPrecedent[0][0].setY(y);
                        m_coupPrecedent[0][1].setX(listeCoup.at(i).x());
                        m_coupPrecedent[0][1].setY(listeCoup.at(i).y());
                        score = 0;
                        std::cout << "dans jouer de la classe IA6";std::cout << std::endl;
                        // on relance l'appel

                        if(joueur->getIdJoueur() == 0)
                        {
                            std::cout << "dans jouer de la classe IA7";std::cout << std::endl;
                            std::cout << "profondeur min="<<profondeur-1;std::cout << std::endl;
                            score = min(plateau->getJoueur2(),plateau,profondeur-1,-10000,100000);
                            std::cout << "dans jouer de la classe IA7-1";std::cout << std::endl;
                        }
                        else
                        {
                            std::cout << "dans jouer de la classe IA8";std::cout << std::endl;
                            std::cout << "profondeur min="<<profondeur-1;std::cout << std::endl;
                            score = min(plateau->getJoueur1(),plateau,profondeur-1,-10000,100000);
                            std::cout << "dans jouer de la classe IA8-1";std::cout << std::endl;
                        }
                        std::cout << "dans jouer de la classe IA9";std::cout << std::endl;
                        m_coupPrecedent[0][0].setX(coup_origin_x);
                        m_coupPrecedent[0][0].setY(coup_origin_y);
                        m_coupPrecedent[0][1].setX(coup_dest_x);
                        m_coupPrecedent[0][1].setY(coup_dest_y);
                        if(plateau->getGrille()->getCase(listeCoup.at(i).x(),listeCoup.at(i).y())->getId() == 'R')
                        {
                            if(plateau->getGrille()->getCase(listeCoup.at(i).x(),listeCoup.at(i).y())->getCouleur() == 0)
                            {
                                this->m_Posi_Rois1.setX(x);
                                this->m_Posi_Rois1.setY(y);
                            }
                            else
                            {
                                this->m_Posi_Rois2.setX(x);
                                this->m_Posi_Rois2.setY(y);
                            }
                        }
                        //                    if(specialMoveDone)
                        //                    {
                        //                        if(x - listeCoup.at(i).x() > 0)
                        //                        {
                        //                            plateau->getGrille()->getCase(x-1,y)->setPiece();
                        //                            plateau->getGrille()->getCase(x-1,y)->setId('P');
                        //                            if(joueur->getIdJoueur() == 0)
                        //                            {
                        //                                plateau->getGrille()->getCase(x-1,y)->setCouleur(1);
                        //                            }
                        //                            else
                        //                            {
                        //                                plateau->getGrille()->getCase(x-1,y)->setCouleur(0);
                        //                            }
                        //                        }
                        //                        else
                        //                        {
                        //                            plateau->getGrille()->getCase(x+1,y)->setPiece();
                        //                            plateau->getGrille()->getCase(x+1,y)->setId('P');
                        //                            if(joueur->getIdJoueur() == 0)
                        //                            {
                        //                                plateau->getGrille()->getCase(x+1,y)->setCouleur(1);
                        //                            }
                        //                            else
                        //                            {
                        //                                plateau->getGrille()->getCase(x+1,y)->setCouleur(0);
                        //                            }
                        //                        }
                        //                    }
                        //on reset les cases déplacées
                        plateau->getGrille()->getCase(x,y)->setId(plateau->getGrille()->getCase(listeCoup.at(i).x(),listeCoup.at(i).y())->getId());
                        plateau->getGrille()->getCase(x,y)->setCouleur(plateau->getGrille()->getCase(listeCoup.at(i).x(),listeCoup.at(i).y())->getCouleur());
                        plateau->getGrille()->getCase(x,y)->setPiece();
                        plateau->getGrille()->getCase(listeCoup.at(i).x(),listeCoup.at(i).y())->setId(idtmp);
                        plateau->getGrille()->getCase(listeCoup.at(i).x(),listeCoup.at(i).y())->setCouleur(couleurtmp);
                        plateau->getGrille()->getCase(listeCoup.at(i).x(),listeCoup.at(i).y())->setOccupied(occupiedtmp);
                        if(score > max)
                        {
                            max = score;
                            result.clear();
                            result.append(QPoint(x,y));
                            result.append(listeCoup.at(i));
                        }
                        else if(score == max) // on a deux coups qui sont a peut prets egaux on les mets a la suite
                        {
                            result.append(QPoint(x,y));
                            result.append(listeCoup.at(i));
                        }

                    }
                }
            }
        }
    }





    return result;

}
/**
 * @brief ia::eval
 * fonction d'evaluation du plateau
 * @param plateau pointeur sur le plateau
 * @return Difference des valeurs des pieces de chaque joueur
 */
int ia::eval(Plateau * plateau){
    int scoreJoueur1 = 0;
    int scoreJoueur2 = 0;
    for(int x = 0; x < 8; x++)
    {
        for(int y = 0; y < 8; y++)
        {
            if(plateau->getGrille()->getCase(x,y)->getId() == 'P' && plateau->getGrille()->getCase(x,y)->getCouleur() == 0)
            {
                scoreJoueur1++;
            }
            else if(plateau->getGrille()->getCase(x,y)->getId() == 'P' && plateau->getGrille()->getCase(x,y)->getCouleur() == 1)
            {
                scoreJoueur2++;
            }
            if((plateau->getGrille()->getCase(x,y)->getId() == 'F' || plateau->getGrille()->getCase(x,y)->getId() == 'C') && plateau->getGrille()->getCase(x,y)->getCouleur() == 0)
            {
                scoreJoueur1 += 3;
            }
            else if((plateau->getGrille()->getCase(x,y)->getId() == 'F' || plateau->getGrille()->getCase(x,y)->getId() == 'C') && plateau->getGrille()->getCase(x,y)->getCouleur() == 1)
            {
                scoreJoueur2 += 3;
            }
            if(plateau->getGrille()->getCase(x,y)->getId() == 'T' && plateau->getGrille()->getCase(x,y)->getCouleur() == 0)
            {
                scoreJoueur1 += 5;
            }
            else if(plateau->getGrille()->getCase(x,y)->getId() == 'T' && plateau->getGrille()->getCase(x,y)->getCouleur() == 1)
            {
                scoreJoueur2 += 5;
            }
        }
    }
    return  scoreJoueur1 - scoreJoueur2;
}

/**
 * @brief ia::calc_echec_et_mat
 * fonction permettant de calculer l'echec et mat
 * @param joueur pointeur sur le joueur courant
 * @param pos_rois_joueur position du roi du joueur
 * @param plateau pointeur sur le plateaju
 * @return un vecteur vide si le joueur a perdu sinon la liste des deplacements sans mettre le roi en echec
 */
QVector<QPoint> ia::calc_echec_et_mat(Joueur * joueur,QPoint pos_rois_joueur,Plateau * plateau){
    //int ia::calc_echec_et_mat(Joueur * joueur,QPoint pos_rois_joueur,Plateau * plateau){
    int score=0;

    QVector<QPoint> result(0);
    int nbDep=0;
    int nbit=0;
    for(int i =0;i<joueur->getDeckSize();i++){

        int x = joueur->getDeck()[i]->getCoordonne()->getX();
        int y = joueur->getDeck()[i]->getCoordonne()->getY();
        char id = joueur->getDeck()[i]->getId();
        nbit++;
        std::cout << "nbitcalc="<<nbit;std::cout << std::endl;
        // joueur->afficherPiece();
        std::cout << "dans calc echec mat tmp2";std::cout << std::endl;
        std::cout << x <<"et"<<y;std::cout << std::endl;
        std::cout <<"couleur case =" <<plateau->getGrille()->getCase(x,y)->getCouleur();std::cout << std::endl;
        std::cout <<"idjoueur =" <<joueur->getIdJoueur();std::cout << std::endl;
        //coordtmp.setX(x);
        //coordtmp.setY(y);

        QVector<QPoint> listeCoup;
        std::cout << "dans calc echec mat 1";std::cout << std::endl;
        listeCoup = joueur->getDeck()[i]->deplacementsPossible(joueur->getIdJoueur(),plateau);
        std::cout << "dans calc echec mat 2";std::cout << std::endl;
        std::cout << "dans calc echec mat 3";std::cout << std::endl;
        std::cout << "IDPIECE="<<id;std::cout << std::endl;
        std::cout << "x="<<x<<"et y="<<y;std::cout << std::endl;
        switch(id)
        {
        case 'R':
            /*
                            if(deplacements::grandRoguePossible(m_groupe[x][y],m_groupe,m_deplacement,m_terrain))
                            {
                                if(m_groupe[x][y] == 1)
                                {
                                    listeCoup.append(QPoint(0,2));
                                }
                                else
                                {
                                    listeCoup.append(QPoint(7,2));
                                }
                            }
                            if(deplacements::petitRoguePossible(m_groupe[x][y],m_groupe,m_deplacement,m_terrain))
                            {
                                if(m_groupe[x][y] == 1)
                                {
                                    listeCoup.append(QPoint(0,6));
                                }
                                else
                                {
                                    listeCoup.append(QPoint(7,6));
                                }
                            }*/
            break;
        default:
            break;

        }
        std::cout << "dans calc echec mat 4";std::cout << std::endl;
        for (int i = 0; i < listeCoup.count(); i++)
        {

            std::cout << "dans calc echec mat 5";std::cout << std::endl;
            int coup_origin_x = m_coupPrecedent->at(0).x();
            int coup_origin_y = m_coupPrecedent->at(0).y();
            int coup_dest_x = m_coupPrecedent->at(1).x();
            int coup_dest_y = m_coupPrecedent->at(1).y();
            // on joue le tour
            std::cout << "dans calc echec mat 6";std::cout << std::endl;
            bool occupiedtmp=plateau->getGrille()->getCase(listeCoup.at(i).x(),listeCoup.at(i).y())->isOccupied();
            char idtmp=plateau->getGrille()->getCase(listeCoup.at(i).x(),listeCoup.at(i).y())->getId();
            int couleurtmp=plateau->getGrille()->getCase(listeCoup.at(i).x(),listeCoup.at(i).y())->getCouleur();
            ///////// SI LE ROI PEUT SE DEPLACER C'EST QU'IL PEUT S'ECHAPPER LE BOUGRE !
            std::cout << "dans calc echec mat 7";std::cout << std::endl;

            if(id=='R')
            {
                std::cout << "dans calc echec mat 7-1";std::cout << std::endl;
                result.append(QPoint(x,y));
                result.append(listeCoup.at(i));
                nbDep++;
            }
            else
            {
                bool specialMoveDone = false;
                if(id == 'P')
                {
                    //                            if(listeCoup.at(i).x() != x && !plateau->caseAtOccupy(listeCoup.at(i).x(),listeCoup.at(i).y()))
                    //                            {
                    //                                specialMoveDone = true;
                    //                                if(x - listeCoup.at(i).x() > 0)
                    //                                {
                    //                                    plateau->getGrille()->getCase(x+1,y)->removePiece();
                    //                                }
                    //                                else
                    //                                {
                    //                                    plateau->getGrille()->getCase(x-1,y)->removePiece();
                    //                                }
                    //                            }
                }

                std::cout << "dans calc echec mat 8";std::cout << std::endl;
                plateau->getGrille()->getCase(listeCoup.at(i).x(),listeCoup.at(i).y())->setId(plateau->getGrille()->getCase(x,y)->getId()) ;
                plateau->getGrille()->getCase(listeCoup.at(i).x(),listeCoup.at(i).y())->setCouleur(plateau->getGrille()->getCase(x,y)->getCouleur()) ;
                plateau->getGrille()->getCase(listeCoup.at(i).x(),listeCoup.at(i).y())->setPiece();
                plateau->getGrille()->removePiece(new Coordonnee(x,y));
                m_coupPrecedent[0][0].setX(x);
                m_coupPrecedent[0][0].setY(y);
                m_coupPrecedent[0][1].setX(listeCoup.at(i).x());
                m_coupPrecedent[0][1].setY(listeCoup.at(i).y());

                std::cout << "dans calc echec mat 9";std::cout << std::endl;
                bool b=plateau->est_en_echec(pos_rois_joueur,NULL,joueur->getIdJoueur());
                //bool b =false;
                if(b==true)
                {
                    score = -1000;
                    //result.append(QPoint(x,y));
                    //result.append(listeCoup.at(i));
                }
                else
                {
                    score =  1000;
                    //result.append(QPoint(x,y));
                    //result.append(listeCoup.at(i));
                    // nbDep++;
                    // on a sacrifie une piece pour sauver le roi
                }
                if(score > -500)
                {
                    result.append(QPoint(x,y));
                    result.append(listeCoup.at(i));
                }
                std::cout << "dans calc echec mat 10";std::cout << std::endl;
                std::cout << "score="<<score;std::cout << std::endl;
                m_coupPrecedent[0][0].setX(coup_origin_x);
                m_coupPrecedent[0][0].setY(coup_origin_y);
                m_coupPrecedent[0][1].setX(coup_dest_x);
                m_coupPrecedent[0][1].setY(coup_dest_y);

                if(specialMoveDone)
                {/*
                                if(x - listeCoup.at(i).x() > 0)
                                {
                                    plateau->getGrille()->getCase(x-1,y)->setPiece();
                                    plateau->getGrille()->getCase(x-1,y)->setId('P');
                                    if(joueur->getIdJoueur() == 0)
                                    {
                                        plateau->getGrille()->getCase(x-1,y)->setCouleur(1);
                                    }
                                    else
                                    {
                                        plateau->getGrille()->getCase(x-1,y)->setCouleur(0);
                                    }
                                }
                                else
                                {
                                    plateau->getGrille()->getCase(x+1,y)->setPiece();
                                    plateau->getGrille()->getCase(x+1,y)->setId('P');
                                    if(joueur->getIdJoueur() == 0)
                                    {
                                        plateau->getGrille()->getCase(x+1,y)->setCouleur(1);
                                    }
                                    else
                                    {
                                        plateau->getGrille()->getCase(x+1,y)->setCouleur(0);
                                    }
                                }*/
                }
                //reset des cases
                plateau->getGrille()->getCase(x,y)->setId(plateau->getGrille()->getCase(listeCoup.at(i).x(),listeCoup.at(i).y())->getId());
                plateau->getGrille()->getCase(x,y)->setCouleur(plateau->getGrille()->getCase(listeCoup.at(i).x(),listeCoup.at(i).y())->getCouleur());
                plateau->getGrille()->getCase(x,y)->setPiece();

                plateau->getGrille()->getCase(listeCoup.at(i).x(),listeCoup.at(i).y())->setId(idtmp);
                plateau->getGrille()->getCase(listeCoup.at(i).x(),listeCoup.at(i).y())->setCouleur(couleurtmp);
                plateau->getGrille()->getCase(listeCoup.at(i).x(),listeCoup.at(i).y())->setOccupied(occupiedtmp);
                std::cout << "dans calc echec mat 11";std::cout << std::endl;

                //delete coordtmp1;
                std::cout << "dans calc echec mat 15";std::cout << std::endl;

            }
            std::cout << "calc echec mat 16";std::cout << std::endl;
            //delete tmp;

        }
    }
    std::cout << "calc echec mat 17";std::cout << std::endl;
    //coordtmp.~Coordonnee();

    std::cout << "fin calc echec mat ";std::cout << std::endl;
    //delete tmp;
    //delete coordtmp1;
    return result;
    // return nbDep;
}

ia::~ia()
{

}
