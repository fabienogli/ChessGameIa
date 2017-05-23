#include "ia.h"
#include "Plateau.h"
#include "Joueur.h"
#include "Piece.h"


ia::ia(int level)
{
    this->level = level;
}
void ia::setCoupPrecedent(QVector<QPoint> * coupPrecedent)
{
    this->m_coupPrecedent=coupPrecedent;
}

int ia::gagnantEnCours(int idJoueur,Plateau * plateau){
    if(idJoueur == 0)
    {
        if(calc_echec_et_mat(plateau->getJoueur1(),this->m_Posi_Rois1,plateau).size() == 0)
        {
            return -1000;
        }
        if(this->calc_echec_et_mat(plateau->getJoueur2(),this->m_Posi_Rois2,plateau).size() == 0)
        {
            return 1000;
        }
    }
    else
    {
        if(this->calc_echec_et_mat(plateau->getJoueur2(),this->m_Posi_Rois2,plateau).count() == 0)
        {
            return -1000;
        }
        if(this->calc_echec_et_mat(plateau->getJoueur1(),this->m_Posi_Rois1,plateau).count() == 0)
        {
            return 1000;
        }
    }

    return 0;

}
int ia::max(Joueur *joueur,Plateau *plateau,int profondeur,int alpha,int beta)
{
    std::cout<<"dans le max"<<std::endl;
   // int retour=gagnantEnCours(joueur->getIdJoueur(),plateau)  ;
    int retour=0;
    std::cout<<"jai fini le calcul du retour gagnantEnCours"<<std::endl;
    std::cout<<"retour="<<retour<<std::endl;
    int max = -10000;
    //if(profondeur <= 0 || (retour != 0))
        if(profondeur <= 0 )
    {
        if(profondeur <= 0)
        {
            std::cout << "jevalue le plateau";std::cout << std::endl;
            return eval(plateau);
        }
        else
        {
            return retour;
        }
    }
    for(int y=0;y<8;y++)
    {
        for(int x=0;x<8;x++)
        {
            char id='N';
            if(plateau->getGrille()->getCase(x,y)->getCouleur() == joueur->getIdJoueur())
            {
                int idPiece=(joueur->isAnyPiece(Coordonnee(x,y)));
                if(idPiece != (-1)){
                    QVector<QPoint> listeCoup;
                    listeCoup = joueur->getDeck()[idPiece]->deplacementsPossible(joueur->getIdJoueur(),plateau);
                    for(int i=0;i<listeCoup.size();i++){
                        int coup_origin_x = plateau->getCoupPrec().at(0).x();
                        int coup_origin_y =plateau->getCoupPrec().at(0).y();
                        int coup_dest_x = plateau->getCoupPrec().at(1).x();
                        int coup_dest_y = plateau->getCoupPrec().at(1).y();
                        bool occupiedtmp=plateau->getGrille()->getCase(listeCoup.at(i).x(),listeCoup.at(i).y())->isOccupied();
                        char idtmp=plateau->getGrille()->getCase(listeCoup.at(i).x(),listeCoup.at(i).y())->getId();
                        int couleurtmp=plateau->getGrille()->getCase(listeCoup.at(i).x(),listeCoup.at(i).y())->getCouleur();
                        // GERER LA CAPTURE D'UN PION A LA VOLE !!!
                        bool deplacementSpecialFait = false;
                        if(id == 'P')
                        {
                            //                        if(listeCoup.at(i).x() != x && !plateau->caseAtOccupy(listeCoup.at(i).x(),listeCoup.at(i).y()))
                            //                        {
                            //                            deplacementSpecialFait = true;
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
                        //                    if(deplacementSpecialFait)
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
            }
        }
    }

    return max;
}
int ia::min(Joueur *joueur,Plateau *plateau,int profondeur,int alpha,int beta){
    std::cout << "dans le min";std::cout << std::endl;
    std::cout << "dans jouer de la classe min1";std::cout << std::endl;
    //int retour=gagnantEnCours(joueur->getIdJoueur(),plateau)  ;
    int retour=0;
    std::cout << "dans jouer de la classe min2";std::cout << std::endl;
    int min = 10000;
    std::cout << "dans jouer de la classe min3";std::cout << std::endl;
    //if(profondeur <= 0 || (retour != 0))
        if(profondeur <= 0 )
    {
        if(profondeur <= 0)
        {
            std::cout << "jevalue le plateau";std::cout << std::endl;
            return eval(plateau);
        }
        else
        {
            return retour;
        }
    }
    for(int y=0;y<8;y++)
    {
        for(int x=0;x<8;x++)
        {
            char id='N';
            if(plateau->getGrille()->getCase(x,y)->getCouleur() == joueur->getIdJoueur())
            {
                int idPiece=(joueur->isAnyPiece(Coordonnee(x,y)));
                if(idPiece != (-1)){
                    QVector<QPoint> listeCoup;
                    listeCoup = joueur->getDeck()[idPiece]->deplacementsPossible(joueur->getIdJoueur(),plateau);

                    for(int i=0;i<listeCoup.count();i++){
                        int coup_origin_x = plateau->getCoupPrec().at(0).x();
                        int coup_origin_y =plateau->getCoupPrec().at(0).y();
                        int coup_dest_x = plateau->getCoupPrec().at(1).x();
                        int coup_dest_y = plateau->getCoupPrec().at(1).y();
                        bool occupiedtmp=plateau->getGrille()->getCase(listeCoup.at(i).x(),listeCoup.at(i).y())->isOccupied();
                        char idtmp=plateau->getGrille()->getCase(listeCoup.at(i).x(),listeCoup.at(i).y())->getId();
                        int couleurtmp=plateau->getGrille()->getCase(listeCoup.at(i).x(),listeCoup.at(i).y())->getCouleur();
                        // GERER LA CAPTURE D'UN PION A LA VOLE !!!
                        bool deplacementSpecialFait = false;
                        if(id == 'P')
                        {
                            //                        if(listeCoup.at(i).x() != x && !plateau->caseAtOccupy(listeCoup.at(i).x(),listeCoup.at(i).y()))
                            //                        {
                            //                            deplacementSpecialFait = true;
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
                        //                    if(deplacementSpecialFait)
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
            }
        }
    }
    return min;
}
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
                double idPiece=(joueur->isAnyPiece(Coordonnee(x,y)));
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
                        /* ///////// GERER LA CAPTURE D'UN PION A LA VOLE !!!
                    bool deplacementSpecialFait = false;
                    if(id == 'P')
                    {
                        if(listeCoup.at(i).x() != x && !plateau->caseAtOccupy(listeCoup.at(i).x(),listeCoup.at(i).y()))
                        {
                            deplacementSpecialFait = true;
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
                        //                    if(deplacementSpecialFait)
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
int ia::eval(Plateau * plateau){
    int scoreJoueur1 = 0;
    int scoreJoueur2 = 0;
    for(int x = 0; x < 8; x++)
    {
        for(int y = 0; y < 8; y++)
        {
            if(plateau->getGrille()->getCase(x,y)->getId() == 'P' && plateau->getGrille()->getCase(x,y)->getCouleur() == 0)
            {
                scoreJoueur1+= 100;
            }
            else if(plateau->getGrille()->getCase(x,y)->getId() == 'P' && plateau->getGrille()->getCase(x,y)->getCouleur() == 1)
            {
                scoreJoueur2+= 100;
            }
            if((plateau->getGrille()->getCase(x,y)->getId() == 'F' || plateau->getGrille()->getCase(x,y)->getId() == 'C') && plateau->getGrille()->getCase(x,y)->getCouleur() == 0)
            {
                scoreJoueur1 += 300;
            }
            else if((plateau->getGrille()->getCase(x,y)->getId() == 'F' || plateau->getGrille()->getCase(x,y)->getId() == 'C') && plateau->getGrille()->getCase(x,y)->getCouleur() == 1)
            {
                scoreJoueur2 += 300;
            }
            if(plateau->getGrille()->getCase(x,y)->getId() == 'T' && plateau->getGrille()->getCase(x,y)->getCouleur() == 0)
            {
                scoreJoueur1 += 500;
            }
            else if(plateau->getGrille()->getCase(x,y)->getId() == 'T' && plateau->getGrille()->getCase(x,y)->getCouleur() == 0)
            {
                scoreJoueur2 += 500;
            }
        }
    }
    return  scoreJoueur1 - scoreJoueur2;
}
QVector<QPoint> ia::calc_echec_et_mat(Joueur * joueur,QPoint pos_rois_joueur,Plateau * plateau){

    int score;

    QVector<QPoint> result;
    QPoint *coordtmp1 = new QPoint(0,0);

    for(int x = 0; x < 8; x++)
    {
        std::cout << "dans calc echec mat tmp";std::cout << std::endl;
        for(int y = 0; y < 8; y++)
        {
            std::cout << "dans calc echec mat tmpt";std::cout << std::endl;
            std::cout << x <<"et"<< y;std::cout << std::endl;
            std::cout <<"couleur case =" <<plateau->getGrille()->getCase(x,y)->getCouleur();std::cout << std::endl;
            std::cout <<"idjoueur =" <<joueur->getIdJoueur();std::cout << std::endl;

            std::cout << "dans calc echec mat tmp1";std::cout << std::endl;
            if((plateau->getGrille()->getCase(x,y)->getCouleur()) == joueur->getIdJoueur())
            {
                std::cout << "dans calc echec mat tmp2";std::cout << std::endl;
                std::cout << x <<"et"<<y;std::cout << std::endl;
                std::cout <<"couleur case =" <<plateau->getGrille()->getCase(x,y)->getCouleur();std::cout << std::endl;
                std::cout <<"idjoueur =" <<joueur->getIdJoueur();std::cout << std::endl;
                //coordtmp.setX(x);
                //coordtmp.setY(y);
                double tmpt;
                std::cout << "dans calc echec mat tmp3";std::cout << std::endl;
                /*if(joueur->getIdJoueur() == 0)
                    //on recherche dans le deck du premier joueur
                    tmpt = plateau->getJoueur1()->isAnyPiece(Coordonnee(x,y));
                else if(joueur->getIdJoueur()==1)
                    tmpt = plateau->getJoueur2()->isAnyPiece(Coordonnee(x,y));*/
                tmpt=joueur->isAnyPiece(Coordonnee(x,y));
                std::cout << tmpt;std::cout << std::endl;
                QVector<QPoint> listeCoup;
                if(tmpt != -1){
                    std::cout << "dans calc echec mat 1";std::cout << std::endl;
                    listeCoup = joueur->getDeck()[tmpt]->deplacementsPossible(joueur->getIdJoueur(),plateau);
                    std::cout << "dans calc echec mat 2";std::cout << std::endl;
                    //int idPiece=(joueur->isAnyPiece(Coordonnee(x,y)));
                    std::cout << "dans calc echec mat 3";std::cout << std::endl;
                    switch(plateau->getGrille()->getCase(x,y)->getId())
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
                        //tmp = plateau->getPiece(new Coordonnee(listeCoup.at(i).x(),listeCoup.at(i).y()));

                        ///////// SI LE ROI PEUT SE DEPLACER C'EST QU'IL PEUT S'ECHAPPER LE BOUGRE !
                        std::cout << "dans calc echec mat 7";std::cout << std::endl;
                        if(plateau->getGrille()->getCase(x,y)->getId() ==  'R')
                        {
                            std::cout << "dans calc echec mat 7-1";std::cout << std::endl;
                            result.append(QPoint(x,y));
                            result.append(listeCoup.at(i));
                        }
                        else
                        {
                            bool deplacementSpecialFait = false;
                            if(plateau->getGrille()->getCase(x,y)->getId() == 'P')
                            {
                                //                            if(listeCoup.at(i).x() != x && !plateau->caseAtOccupy(listeCoup.at(i).x(),listeCoup.at(i).y()))
                                //                            {
                                //                                deplacementSpecialFait = true;
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
                            coordtmp1->setX(pos_rois_joueur.x());
                            coordtmp1->setY(pos_rois_joueur.y());
                            std::cout << "dans calc echec mat 9";std::cout << std::endl;
                            if(plateau->est_en_echec(coordtmp1,NULL,joueur->getIdJoueur()))
                            {
                                score = -1000;
                            }
                            else
                            {
                                score =  1000;
                            }
                            std::cout << "dans calc echec mat 10";std::cout << std::endl;
                            if(score > -500) // si on peut eviter un echec et mat un score superieur a -1000 devrai apparaitre
                            {
                                // on a sacrifie une piece pour sauver le roi \o/ longue vie au roi !
                                result.append(QPoint(x,y));
                                result.append(listeCoup.at(i));
                            }

                            m_coupPrecedent[0][0].setX(coup_origin_x);
                            m_coupPrecedent[0][0].setY(coup_origin_y);
                            m_coupPrecedent[0][1].setX(coup_dest_x);
                            m_coupPrecedent[0][1].setY(coup_dest_y);

                            if(deplacementSpecialFait)
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
                            plateau->getGrille()->getCase(x,y)->setId(plateau->getGrille()->getCase(listeCoup.at(i).x(),listeCoup.at(i).y())->getId());
                            plateau->getGrille()->getCase(x,y)->setCouleur(plateau->getGrille()->getCase(listeCoup.at(i).x(),listeCoup.at(i).y())->getCouleur());
                            plateau->getGrille()->getCase(x,y)->setPiece();

                            plateau->getGrille()->getCase(listeCoup.at(i).x(),listeCoup.at(i).y())->setId(idtmp);
                            plateau->getGrille()->getCase(listeCoup.at(i).x(),listeCoup.at(i).y())->setCouleur(couleurtmp);
                            plateau->getGrille()->getCase(listeCoup.at(i).x(),listeCoup.at(i).y())->setOccupied(occupiedtmp);
                            /*std::cout << "dans calc echec mat 11";std::cout << std::endl;
                        plateau->getGrille()->getCase(x,y)->setId(plateau->getGrille()->getCase(x,y)->getId());
                         std::cout << "dans calc echec mat 12";std::cout << std::endl;
                        plateau->getGrille()->getCase(x,y)->setCouleur(plateau->getGrille()->getCase(x,y)->getCouleur());
                         std::cout << "dans calc echec mat 13";std::cout << std::endl;
                        plateau->getGrille()->getCase(listeCoup.at(i).x(),listeCoup.at(i).y())->setId(tmp->getId());
                         std::cout << "dans calc echec mat 14";std::cout << std::endl;
                        plateau->getGrille()->getCase(listeCoup.at(i).x(),listeCoup.at(i).y())->setCouleur(tmp->getCouleur());*/
                            //delete coordtmp1;
                            std::cout << "dans calc echec mat 15";std::cout << std::endl;

                        }
                        std::cout << "calc echec mat 16";std::cout << std::endl;
                        //delete tmp;
                    }
                }
                std::cout << "calc echec mat 17";std::cout << std::endl;
                //coordtmp.~Coordonnee();
            }
            std::cout << "calc echec mat 18";std::cout << std::endl;
        }
        std::cout << "calc echec mat 19";std::cout << std::endl;



    }
    std::cout << "fin calc echec mat ";std::cout << std::endl;
    //delete tmp;
    //delete coordtmp1;
    return result;
}


