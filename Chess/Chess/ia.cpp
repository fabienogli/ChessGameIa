#include "ia.h"
#include "Plateau.h"
#include "Joueur.h"
#include "Piece.h"

ia::ia(int i_joueur, int level) : Joueur("IA",i_joueur)
{
    this->level = level;
}

void ia::setCoupPrecedent(QVector<QPoint> * coupPrecedent)
{
    this->m_coupPrecedent=coupPrecedent;
}

int ia::gagnant(int idJoueur,Plateau * plateau){
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
        if(this->calc_echec_et_mat(plateau->getJoueur2(),this->m_Posi_Rois2,plateau).size() == 0)
        {
            return -1000;
        }
        if(this->calc_echec_et_mat(plateau->getJoueur1(),this->m_Posi_Rois1,plateau).size() == 0)
        {
            return 1000;
        }
    }

    return 0;

}
int ia::max(Joueur *joueur,Plateau *plateau,int profondeur,int alpha,int beta)
{
    int retour=gagnant(joueur->getIdJoueur(),plateau)  ;
    int max = -10000;
    if(profondeur <= 0 || (retour != 0))
    {
        if(profondeur <= 0)
        {
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
            char id;
            int idPiece=(joueur->isAnyPiece(Coordonnee(x,y)));
            if(idPiece != (-1)){
                QVector<QPoint> listeCoup;
                /*
                switch(id=joueur->getDeck()[idPiece]->getId())
                {
                case 'P':

                    break;
                case 'R':

                    break;
                case 'F':

                    break;
                case 'C':

                    break;
                case 'T':

                    break;
                default:

                    break;
                }*/
                listeCoup = joueur->getDeck()[idPiece]->deplacementsPossible(joueur->getIdJoueur(),plateau);

                for(int i=0;i<listeCoup.size();i++){
                    int coup_origin_x = plateau->getCoupPrec().at(0).x();
                    int coup_origin_y =plateau->getCoupPrec().at(0).y();
                    int coup_dest_x = plateau->getCoupPrec().at(1).x();
                    int coup_dest_y = plateau->getCoupPrec().at(1).y();
                    Piece tmp = joueur->getPiece(idPiece);
                    // GERER LA CAPTURE D'UN PION A LA VOLE !!!
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
                    plateau->getGrille()->getCase(x,y)->removePiece();
                    m_coupPrecedent[0][0].setX(x);
                    m_coupPrecedent[0][0].setY(y);
                    m_coupPrecedent[0][1].setX(listeCoup.at(i).x());
                    m_coupPrecedent[0][1].setY(listeCoup.at(i).y());
                    int score = 0;
                    // on relance l'appel

                    if(joueur->getIdJoueur() == 0)
                    {
                        score = min(plateau->getJoueur2(),plateau,profondeur-1,alpha,beta);
                    }
                    else
                    {
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
                    if(deplacementSpecialFait)
                    {
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
                        }
                    }

                    plateau->getGrille()->getCase(x,y)->setId(plateau->getGrille()->getCase(x,y)->getId());
                    plateau->getGrille()->getCase(x,y)->setCouleur(plateau->getGrille()->getCase(x,y)->getCouleur());
                    plateau->getGrille()->getCase(listeCoup.at(i).x(),listeCoup.at(i).y())->setId(tmp.getId());
                    plateau->getGrille()->getCase(listeCoup.at(i).x(),listeCoup.at(i).y())->setCouleur(tmp.getCouleur());
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

    return max;
}
int ia::min(Joueur *joueur,Plateau *plateau,int profondeur,int alpha,int beta){
    std::cout << "dans jouer de la classe min1";std::cout << std::endl;
    int retour=gagnant(joueur->getIdJoueur(),plateau)  ;
    std::cout << "dans jouer de la classe min2";std::cout << std::endl;
    int min = 10000;
     std::cout << "dans jouer de la classe min3";std::cout << std::endl;
    if(profondeur <= 0 || (retour != 0))
    {
        if(profondeur <= 0)
        {
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
            char id;
            int idPiece=(joueur->isAnyPiece(Coordonnee(x,y)));
            if(idPiece != (-1)){
                QVector<QPoint> listeCoup;
                /*
                switch(id=joueur->getDeck()[idPiece]->getId())
                {
                case 'P':

                    break;
                case 'R':

                    break;
                case 'F':

                    break;
                case 'C':

                    break;
                case 'T':

                    break;
                default:

                    break;
                }*/
                listeCoup = joueur->getDeck()[idPiece]->deplacementsPossible(joueur->getIdJoueur(),plateau);

                for(int i=0;i<listeCoup.count();i++){
                    int coup_origin_x = plateau->getCoupPrec().at(0).x();
                    int coup_origin_y =plateau->getCoupPrec().at(0).y();
                    int coup_dest_x = plateau->getCoupPrec().at(1).x();
                    int coup_dest_y = plateau->getCoupPrec().at(1).y();
                    Piece tmp = joueur->getPiece(idPiece);
                    // GERER LA CAPTURE D'UN PION A LA VOLE !!!
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
                    plateau->getGrille()->getCase(x,y)->removePiece();
                    m_coupPrecedent[0][0].setX(x);
                    m_coupPrecedent[0][0].setY(y);
                    m_coupPrecedent[0][1].setX(listeCoup.at(i).x());
                    m_coupPrecedent[0][1].setY(listeCoup.at(i).y());
                    int score = 0;
                    // on relance l'appel

                    if(joueur->getIdJoueur() == 0)
                    {
                        score = max(plateau->getJoueur2(),plateau,profondeur-1,alpha,beta);
                    }
                    else
                    {
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
                    if(deplacementSpecialFait)
                    {
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
                        }
                    }

                    plateau->getGrille()->getCase(x,y)->setId(plateau->getGrille()->getCase(x,y)->getId());
                    plateau->getGrille()->getCase(x,y)->setCouleur(plateau->getGrille()->getCase(x,y)->getCouleur());
                    plateau->getGrille()->getCase(listeCoup.at(i).x(),listeCoup.at(i).y())->setId(tmp.getId());
                    plateau->getGrille()->getCase(listeCoup.at(i).x(),listeCoup.at(i).y())->setCouleur(tmp.getCouleur());
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
    for(int y=0;y<8;y++)
    {
        for(int x=0;x<8;x++)
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
            std::cout << "dans jouer de la classe IA 1";std::cout << std::endl;
            int idPiece=(joueur->isAnyPiece(Coordonnee(x,y)));

            char id = joueur->getDeck()[idPiece]->getId();
            if(idPiece != (-1)){
                QVector<QPoint> listeCoup;
                /*
                   switch(id=joueur->getDeck()[idPiece]->getId())
                   {
                   case 'P':
                    listeCoup= joueur->getDeck()[idPiece]->deplacement
                       break;
                   case 'R':

                       break;
                   case 'F':

                       break;
                   case 'C':

                       break;
                   case 'T':

                       break;
                   default:

                       break;
                   }*/
                listeCoup = joueur->getDeck()[idPiece]->deplacementsPossible(joueur->getIdJoueur(),plateau);
                std::cout << "dans jouer de la classe IA2";std::cout << std::endl;
                for (int i = 0; i < listeCoup.count(); i++)
                {

                    int coup_origin_x = m_coupPrecedent->at(0).x();
                    int coup_origin_y = m_coupPrecedent->at(0).y();
                    int coup_dest_x = m_coupPrecedent->at(1).x();
                    int coup_dest_y = m_coupPrecedent->at(1).y();
                    std::cout << "dans jouer de la classe IA3";std::cout << std::endl;
                    // on joue le tour
                    Piece tmp = joueur->getPiece(idPiece);

                    ///////// GERER LA CAPTURE D'UN PION A LA VOLE !!!
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
                    }
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
                    plateau->getGrille()->getCase(x,y)->removePiece();
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
                        score = min(plateau->getJoueur2(),plateau,profondeur-1,-10000,100000);
                         std::cout << "dans jouer de la classe IA7-1";std::cout << std::endl;
                    }
                    else
                    {
                         std::cout << "dans jouer de la classe IA8";std::cout << std::endl;
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
                    if(deplacementSpecialFait)
                    {
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
                        }
                    }

                    plateau->getGrille()->getCase(x,y)->setId(plateau->getGrille()->getCase(x,y)->getId());
                    plateau->getGrille()->getCase(x,y)->setCouleur(plateau->getGrille()->getCase(x,y)->getCouleur());
                    plateau->getGrille()->getCase(listeCoup.at(i).x(),listeCoup.at(i).y())->setId(tmp.getId());
                    plateau->getGrille()->getCase(listeCoup.at(i).x(),listeCoup.at(i).y())->setCouleur(tmp.getCouleur());
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
                scoreJoueur1+=100;
            }
            else if(plateau->getGrille()->getCase(x,y)->getId() == 'P' && plateau->getGrille()->getCase(x,y)->getCouleur() == 1)
            {
                scoreJoueur2+=100;
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

    for(int x = 0; x < 8; x++)
    {
        for(int y = 0; y < 8; y++)
        {
            if((plateau->getGrille()->getCase(x,y)->getCouleur()) == joueur->getIdJoueur())
            {
                Coordonnee coordtmp(0,0);
                coordtmp.setX(x);
                coordtmp.setY(y);
                int tmp;
                if(joueur->getIdJoueur() == 0)
                    //on recherche dans le deck du premier joueur
                    tmp = plateau->getJoueur1()->isAnyPiece(coordtmp);
                else if(joueur->getIdJoueur()==1)
                    tmp = plateau->getJoueur2()->isAnyPiece(coordtmp);
                QVector<QPoint> listeCoup;
                std::cout << "dans calc echec mat 1";std::cout << std::endl;
                listeCoup = joueur->getDeck()[tmp]->deplacementsPossible(joueur->getIdJoueur(),plateau);
                std::cout << "dans calc echec mat 2";std::cout << std::endl;
                int idPiece=(joueur->isAnyPiece(Coordonnee(x,y)));
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
                    Piece tmp = joueur->getPiece(idPiece);

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
                        if(idPiece == 'P')
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
                        }

                        std::cout << "dans calc echec mat 8";std::cout << std::endl;
                        plateau->getGrille()->getCase(listeCoup.at(i).x(),listeCoup.at(i).y())->setId(plateau->getGrille()->getCase(x,y)->getId()) ;
                        plateau->getGrille()->getCase(listeCoup.at(i).x(),listeCoup.at(i).y())->setCouleur(plateau->getGrille()->getCase(x,y)->getCouleur()) ;
                        plateau->getGrille()->getCase(x,y)->removePiece();
                        m_coupPrecedent[0][0].setX(x);
                        m_coupPrecedent[0][0].setY(y);
                        m_coupPrecedent[0][1].setX(listeCoup.at(i).x());
                        m_coupPrecedent[0][1].setY(listeCoup.at(i).y());
                        QPoint *coordtmp1 = new QPoint(pos_rois_joueur.x(),pos_rois_joueur.y());

                        if(plateau->est_en_echec(coordtmp1,NULL,joueur->getIdJoueur()))
                        {
                            score = -1000;
                        }
                        else
                        {
                            score =  1000;
                        }



                        if(score > -500) // si on peut eviter un echec et mat un score superieur a -1000 devrai apparaitre
                        {
                            // on a sacrifie une piece pour sauver le roi \o/ longue vie au roi !
                            result.append(QPoint(x,y));
                            result.append(listeCoup.at(i));
                        }
                        delete coordtmp1;
                        m_coupPrecedent[0][0].setX(coup_origin_x);
                        m_coupPrecedent[0][0].setY(coup_origin_y);
                        m_coupPrecedent[0][1].setX(coup_dest_x);
                        m_coupPrecedent[0][1].setY(coup_dest_y);

                        if(deplacementSpecialFait)
                        {
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
                            }
                        }
                        plateau->getGrille()->getCase(x,y)->setId(plateau->getGrille()->getCase(x,y)->getId());
                        plateau->getGrille()->getCase(x,y)->setCouleur(plateau->getGrille()->getCase(x,y)->getCouleur());
                        plateau->getGrille()->getCase(listeCoup.at(i).x(),listeCoup.at(i).y())->setId(tmp.getId());
                        plateau->getGrille()->getCase(listeCoup.at(i).x(),listeCoup.at(i).y())->setCouleur(tmp.getCouleur());
                    }

                }
            }
        }
    }
    return result;
}


