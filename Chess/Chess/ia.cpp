#include "ia.h"
#include "Plateau.h"
#include "Joueur.h"
#include "Piece.h"
#include <QVector>

ia::ia()
{
    this->level = 4;
}
int ia::gagnant(int idJoueur){
    if(idJoueur == 0)
        {
            if(this->calc_echec_et_mat(1,this->m_Posi_Rois1).count() == 0)
            {
               return -1000;
            }
            if(this->calc_echec_et_mat(2,this->m_Posi_Rois2).count() == 0)
            {
               return 1000;
            }
        }
        else
        {
            if(this->calc_echec_et_mat(2,this->m_Posi_Rois2).count() == 0)
            {
               return -1000;
            }
            if(this->calc_echec_et_mat(1,this->m_Posi_Rois1).count() == 0)
            {
               return 1000;
            }
        }

        return 0;

}
int ia::max(Joueur *joueur,Plateau *plateau,int profondeur,int alpha,int beta)
{
    int retour=0  ;
    int max = -10000;
    if(profondeur <= 0 || (retour = gagnant(joueur->getIdJoueur())) != 0)
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
                        if(listeCoup.at(i).x() != x && plateau->getGrille().getCase(listeCoup.at(i).x(),listeCoup.at(i).y()).isOccupied()==false )
                        {
                            deplacementSpecialFait = true;
                            if(x - listeCoup.at(i).x() > 0)
                            {
                                plateau->getGrille().getCase(x+1,y).removePiece();
                            }
                            else
                            {
                                plateau->getGrille().getCase(x-1,y).removePiece();
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
                    plateau->getGrille().getCase(listeCoup.at(i).x(),listeCoup.at(i).y()).setId(plateau->getGrille().getCase(x,y).getId()) ;
                    plateau->getGrille().getCase(listeCoup.at(i).x(),listeCoup.at(i).y()).setCouleur(plateau->getGrille().getCase(x,y).getCouleur()) ;
                    plateau->getGrille().getCase(x,y).removePiece();
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
                    if(plateau->getGrille().getCase(listeCoup.at(i).x(),listeCoup.at(i).y()).getId() == 'R')
                    {
                        if(plateau->getGrille().getCase(listeCoup.at(i).x(),listeCoup.at(i).y()).getCouleur() == 0)
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
                            plateau->getGrille().getCase(x-1,y).setPiece();
                            plateau->getGrille().getCase(x-1,y).setId('P');
                            if(joueur->getIdJoueur() == 0)
                            {
                                plateau->getGrille().getCase(x-1,y).setCouleur(1);
                            }
                            else
                            {
                                plateau->getGrille().getCase(x-1,y).setCouleur(0);
                            }
                        }
                        else
                        {
                            plateau->getGrille().getCase(x+1,y).setPiece();
                            plateau->getGrille().getCase(x+1,y).setId('P');
                            if(joueur->getIdJoueur() == 0)
                            {
                                plateau->getGrille().getCase(x+1,y).setCouleur(1);
                            }
                            else
                            {
                                plateau->getGrille().getCase(x+1,y).setCouleur(0);
                            }
                        }
                    }

                    plateau->getGrille().getCase(x,y).setId(plateau->getGrille().getCase(x,y).getId());
                    plateau->getGrille().getCase(x,y).setCouleur(plateau->getGrille().getCase(x,y).getCouleur());
                    plateau->getGrille().getCase(listeCoup.at(i).x(),listeCoup.at(i).y()).setId(tmp.getId());
                    plateau->getGrille().getCase(listeCoup.at(i).x(),listeCoup.at(i).y()).setCouleur(tmp.getCouleur());
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
    int retour=0  ;
    int min = 10000;
    if(profondeur <= 0 || (retour = gagnant(joueur->getIdJoueur())) != 0)
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
                        if(listeCoup.at(i).x() != x && plateau->getGrille().getCase(listeCoup.at(i).x(),listeCoup.at(i).y()).isOccupied()==false )
                        {
                            deplacementSpecialFait = true;
                            if(x - listeCoup.at(i).x() > 0)
                            {
                                plateau->getGrille().getCase(x+1,y).removePiece();
                            }
                            else
                            {
                                plateau->getGrille().getCase(x-1,y).removePiece();
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
                    plateau->getGrille().getCase(listeCoup.at(i).x(),listeCoup.at(i).y()).setId(plateau->getGrille().getCase(x,y).getId()) ;
                    plateau->getGrille().getCase(listeCoup.at(i).x(),listeCoup.at(i).y()).setCouleur(plateau->getGrille().getCase(x,y).getCouleur()) ;
                    plateau->getGrille().getCase(x,y).removePiece();
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
                    if(plateau->getGrille().getCase(listeCoup.at(i).x(),listeCoup.at(i).y()).getId() == 'R')
                    {
                        if(plateau->getGrille().getCase(listeCoup.at(i).x(),listeCoup.at(i).y()).getCouleur() == 0)
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
                            plateau->getGrille().getCase(x-1,y).setPiece();
                            plateau->getGrille().getCase(x-1,y).setId('P');
                            if(joueur->getIdJoueur() == 0)
                            {
                                plateau->getGrille().getCase(x-1,y).setCouleur(1);
                            }
                            else
                            {
                                plateau->getGrille().getCase(x-1,y).setCouleur(0);
                            }
                        }
                        else
                        {
                            plateau->getGrille().getCase(x+1,y).setPiece();
                            plateau->getGrille().getCase(x+1,y).setId('P');
                            if(joueur->getIdJoueur() == 0)
                            {
                                plateau->getGrille().getCase(x+1,y).setCouleur(1);
                            }
                            else
                            {
                                plateau->getGrille().getCase(x+1,y).setCouleur(0);
                            }
                        }
                    }

                    plateau->getGrille().getCase(x,y).setId(plateau->getGrille().getCase(x,y).getId());
                    plateau->getGrille().getCase(x,y).setCouleur(plateau->getGrille().getCase(x,y).getCouleur());
                    plateau->getGrille().getCase(listeCoup.at(i).x(),listeCoup.at(i).y()).setId(tmp.getId());
                    plateau->getGrille().getCase(listeCoup.at(i).x(),listeCoup.at(i).y()).setCouleur(tmp.getCouleur());
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
               if(plateau->getGrille().getCase(x,y).getId() == 'R')
               {
                        if(plateau->getGrille().getCase(x,y).getCouleur() == 0)
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
               char id;
               int idPiece=(joueur->isAnyPiece(Coordonnee(x,y)));
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

                   for (int i = 0; i < listeCoup.count(); i++)
                   {
                       int coup_origin_x = m_coupPrecedent->at(0).x();
                       int coup_origin_y = m_coupPrecedent->at(0).y();
                       int coup_dest_x = m_coupPrecedent->at(1).x();
                       int coup_dest_y = m_coupPrecedent->at(1).y();
                       // on joue le tour
                        Piece tmp = joueur->getPiece(idPiece);

                       ///////// GERER LA CAPTURE D'UN PION A LA VOLE !!!
                       bool deplacementSpecialFait = false;
                       if(id == 'P')
                       {
                        if(listeCoup.at(i).x() != x && plateau->getGrille().getCase(listeCoup.at(i).x(),listeCoup.at(i).y()).isOccupied()==false )
                           {
                               deplacementSpecialFait = true;
                            if(x - listeCoup.at(i).x() > 0)
                            {
                                plateau->getGrille().getCase(x+1,y).removePiece();
                            }
                            else
                            {
                                plateau->getGrille().getCase(x-1,y).removePiece();
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

                    plateau->getGrille().getCase(listeCoup.at(i).x(),listeCoup.at(i).y()).setId(plateau->getGrille().getCase(x,y).getId()) ;
                    plateau->getGrille().getCase(listeCoup.at(i).x(),listeCoup.at(i).y()).setCouleur(plateau->getGrille().getCase(x,y).getCouleur()) ;
                    plateau->getGrille().getCase(x,y).removePiece();
                    m_coupPrecedent[0][0].setX(x);
                    m_coupPrecedent[0][0].setY(y);
                    m_coupPrecedent[0][1].setX(listeCoup.at(i).x());
                    m_coupPrecedent[0][1].setY(listeCoup.at(i).y());
                     score = 0;
                    // on relance l'appel

                    if(joueur->getIdJoueur() == 0)
                    {
                        score = min(plateau->getJoueur2(),plateau,profondeur-1,-10000,100000);
                    }
                    else
                    {
                        score = min(plateau->getJoueur1(),plateau,profondeur-1,-10000,100000);
                    }

                    m_coupPrecedent[0][0].setX(coup_origin_x);
                    m_coupPrecedent[0][0].setY(coup_origin_y);
                    m_coupPrecedent[0][1].setX(coup_dest_x);
                    m_coupPrecedent[0][1].setY(coup_dest_y);
                    if(plateau->getGrille().getCase(listeCoup.at(i).x(),listeCoup.at(i).y()).getId() == 'R')
                    {
                        if(plateau->getGrille().getCase(listeCoup.at(i).x(),listeCoup.at(i).y()).getCouleur() == 0)
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
                            plateau->getGrille().getCase(x-1,y).setPiece();
                            plateau->getGrille().getCase(x-1,y).setId('P');
                            if(joueur->getIdJoueur() == 0)
                            {
                                plateau->getGrille().getCase(x-1,y).setCouleur(1);
                            }
                            else
                            {
                                plateau->getGrille().getCase(x-1,y).setCouleur(0);
                            }
                        }
                        else
                        {
                            plateau->getGrille().getCase(x+1,y).setPiece();
                            plateau->getGrille().getCase(x+1,y).setId('P');
                            if(joueur->getIdJoueur() == 0)
                            {
                                plateau->getGrille().getCase(x+1,y).setCouleur(1);
                            }
                            else
                            {
                                plateau->getGrille().getCase(x+1,y).setCouleur(0);
                            }
                        }
                    }

                    plateau->getGrille().getCase(x,y).setId(plateau->getGrille().getCase(x,y).getId());
                    plateau->getGrille().getCase(x,y).setCouleur(plateau->getGrille().getCase(x,y).getCouleur());
                    plateau->getGrille().getCase(listeCoup.at(i).x(),listeCoup.at(i).y()).setId(tmp.getId());
                    plateau->getGrille().getCase(listeCoup.at(i).x(),listeCoup.at(i).y()).setCouleur(tmp.getCouleur());
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
               if(plateau->getGrille().getCase(x,y).getId() == 'P' && plateau->getGrille().getCase(x,y).getCouleur() == 0)
               {
                   scoreJoueur1+=100;
               }
               else if(plateau->getGrille().getCase(x,y).getId() == 'P' && plateau->getGrille().getCase(x,y).getCouleur() == 1)
               {
                   scoreJoueur2+=100;
               }
               if((plateau->getGrille().getCase(x,y).getId() == 'F' || plateau->getGrille().getCase(x,y).getId() == 'C') && plateau->getGrille().getCase(x,y).getCouleur() == 0)
               {
                   scoreJoueur1 += 300;
               }
               else if((plateau->getGrille().getCase(x,y).getId() == 'F' || plateau->getGrille().getCase(x,y).getId() == 'C') && plateau->getGrille().getCase(x,y).getCouleur() == 1)
               {
                   scoreJoueur2 += 300;
               }
               if(plateau->getGrille().getCase(x,y).getId() == 'T' && plateau->getGrille().getCase(x,y).getCouleur() == 0)
               {
                   scoreJoueur1 += 500;
               }
               else if(plateau->getGrille().getCase(x,y).getId() == 'T' && plateau->getGrille().getCase(x,y).getCouleur() == 0)
               {
                  scoreJoueur2 += 500;
               }
           }
       }
       return  scoreJoueur1 - scoreJoueur2;
}
QVector<QPoint> ia::calc_echec_et_mat(int joueur,QPoint pos_rois_joueur){

    int score;

        QVector<QPoint> result;
        /*
        for(int x = 0; x < 8; x++)
        {
            for(int y = 0; y < 8; y++)
            {
                if(m_groupe[x][y] == joueur)
                {
                    QVector<QPoint> listeCoup;
                    switch(m_terrain[x][y])
                    {
                        case Pion:
                            listeCoup = deplacements::deplacementPion(m_groupe,this->m_terrain,QPoint(x,y),m_coupPrecedent);
                        break;
                        case Rois:
                            listeCoup = deplacements::deplacementRoi(m_terrain,m_groupe,QPoint(x,y));
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
                            }
                        break;
                        case Reine:
                            listeCoup = deplacements::deplacementReine(m_groupe,QPoint(x,y));
                        break;
                        case Fous:
                            listeCoup = deplacements::deplacementFou(m_groupe,QPoint(x,y));
                        break;
                        case Tour:
                            listeCoup = deplacements::deplacementTour(m_groupe,QPoint(x,y));
                        break;
                        case Cavalier:
                            listeCoup = deplacements::deplacementCavalier(m_groupe,QPoint(x,y));
                        break;
                        case Rien:
                            listeCoup = QVector<QPoint>();
                        break;
                    }

                    for (int i = 0; i < listeCoup.count(); i++)
                    {
                        int coup_origin_x = m_coupPrecedent->at(0).x();
                        int coup_origin_y = m_coupPrecedent->at(0).y();
                        int coup_dest_x = m_coupPrecedent->at(1).x();
                        int coup_dest_y = m_coupPrecedent->at(1).y();
                        // on joue le tour
                        piece tempPiece = m_terrain[listeCoup.at(i).x()][listeCoup.at(i).y()];
                        int tempGroupe = m_groupe[listeCoup.at(i).x()][listeCoup.at(i).y()];

                        ///////// SI LE ROI PEUT SE DEPLACER C'EST QU'IL PEUT S'ECHAPPER LE BOUGRE !
                        if(m_terrain[x][y] ==  Rois)
                        {
                          result.append(QPoint(x,y));
                          result.append(listeCoup.at(i));
                        }
                        else
                        {
                            ///////// GERER LA CAPTURE D'UN PION A LA VOLE !!!
                            bool deplacementSpecialFait = false;
                            if(m_terrain[x][y] == Pion)
                            {
                                if(listeCoup.at(i).y() != y && m_terrain[listeCoup.at(i).x()][listeCoup.at(i).y()] == Rien )
                                {
                                    deplacementSpecialFait = true;
                                    if(y - listeCoup.at(i).y() > 0)
                                    {
                                        m_terrain[x][y-1] = Rien;
                                        m_groupe[x][y-1] = 0;
                                    }
                                    else
                                    {
                                        m_terrain[x][y+1] = Rien;
                                        m_groupe[x][y+1] = 0;
                                    }
                                }
                            }


                            m_terrain[listeCoup.at(i).x()][listeCoup.at(i).y()] = m_terrain[x][y];
                            m_terrain[x][y] = Rien;
                            m_groupe[listeCoup.at(i).x()][listeCoup.at(i).y()] = m_groupe[x][y];
                            m_groupe[x][y] = 0;

                            m_coupPrecedent[0][0].setX(x);
                            m_coupPrecedent[0][0].setY(y);
                            m_coupPrecedent[0][1].setX(listeCoup.at(i).x());
                            m_coupPrecedent[0][1].setY(listeCoup.at(i).y());





                            if(deplacements::estEnEchec(m_terrain,m_groupe,joueur,QPoint(pos_rois_joueur.x(),pos_rois_joueur.y())))
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




                            m_coupPrecedent[0][0].setX(coup_origin_x);
                            m_coupPrecedent[0][0].setY(coup_origin_y);
                            m_coupPrecedent[0][1].setX(coup_dest_x);
                            m_coupPrecedent[0][1].setY(coup_dest_y);

                            if(deplacementSpecialFait)
                            {
                                if(y - listeCoup.at(i).y() > 0)
                                {
                                    m_terrain[x][y-1] = Pion;
                                    if(joueur == 1)
                                    {
                                      m_groupe[x][y-1] = 2;
                                    }
                                    else
                                    {
                                      m_groupe[x][y-1] = 1;
                                    }
                                }
                                else
                                {
                                    m_terrain[x][y+1] = Pion;
                                    if(joueur == 1)
                                    {
                                      m_groupe[x][y+1] = 2;
                                    }
                                    else
                                    {
                                      m_groupe[x][y+1] = 1;
                                    }
                                }
                            }



                              m_terrain[x][y] = m_terrain[listeCoup.at(i).x()][listeCoup.at(i).y()];
                              m_terrain[listeCoup.at(i).x()][listeCoup.at(i).y()] = tempPiece;

                              m_groupe[x][y] = m_groupe[listeCoup.at(i).x()][listeCoup.at(i).y()] ;
                              m_groupe[listeCoup.at(i).x()][listeCoup.at(i).y()] = tempGroupe;
                        }
                    }
                }
            }
        }*/
        return result;
}

