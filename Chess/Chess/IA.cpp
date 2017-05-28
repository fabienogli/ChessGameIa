#include "ia.h"
#include "Plateau.h"
#include "Joueur.h"
#include "Piece.h"
#include "deplacements.h"

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
int ia::gagnantEnCours(int idJoueur){
    int retour =0;

    if(idJoueur == 0)
    {
        if((this->calc_echec_et_mat(0,this->m_Posi_Rois1)).count() == 0)
            //if((this->calc_echec_et_mat(plateau->getJoueur1(),this->m_Posi_Rois1,plateau)) == 0)
        {
            std::cout<<"dans gagnant jeux 1"<<std::endl;
            return -1000;
        }
        else if((this->calc_echec_et_mat(1,this->m_Posi_Rois2)).count() == 0)
            //     if((this->calc_echec_et_mat(plateau->getJoueur2(),this->m_Posi_Rois2,plateau)) == 0)
        {
            std::cout<<"dans gagnant jeux 2"<<std::endl;
            return 1000;

        }
    }
    else if (idJoueur == 1)
    {

        if((this->calc_echec_et_mat(1,this->m_Posi_Rois2)).count() == 0)
        {
            std::cout<<"dans gagnant jeux 3"<<std::endl;
            return -1000;
        }

        else if((this->calc_echec_et_mat(0,this->m_Posi_Rois1)).count() == 0)
        {
            std::cout<<"dans gagnant jeux 4"<<std::endl;
            return 1000;
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
int ia::max(int idJoueur,const int couleur[8][8],const char idPiece[8][8],int profondeur,int alpha,int beta)
{
    int retour = 0;
    // /!\ ATTENTION eval IA ne prend pas en compte l'echec et mat vu que celui-ci est verifie dans gagnant jeux
    if(profondeur <= 0 || (retour = gagnantEnCours(idJoueur)) != 0)
    {
        if(profondeur <= 0)
        {
            return eval(couleur,couleur);
        }
        else
        {
            return retour;
        }
    }
    int max = -10000;
    for(int x=0;x<8;x++)
    {
        for(int y=0;y<8;y++)
        {
            if(couleur[x][y] == joueur)
            {
                QVector<QPoint> listeCoup;
                switch(couleur[x][y])
                {
                case 'P':
                    listeCoup = deplacements::deplacementPion(joueur->getIdJoueur(),this->tableauCouleur,this->tableauPieces,QPoint(x,y),this->m_coupPrecedent);
                    break;
                case 'R':
                    listeCoup = deplacements::deplacementRoi(idPiece,couleur,QPoint(x,y));
                    break;
                case 'F':
                    listeCoup = deplacements::deplacementFou(couleur,QPoint(x,y));
                    break;
                case 'T':
                    listeCoup = deplacements::deplacementTour(couleur,QPoint(x,y));
                    break;
                case 'C':
                    listeCoup = deplacements::deplacementCavalier(couleur,QPoint(x,y));
                    break;
                case Rien:
                    listeCoup = QVector<QPoint>();
                    break;
                }
                for (int i = 0; i < listeCoup.count(); i++)
                {
                    // on joue le 'T'
                    int coup_origin_x = m_coupPrecedent->at(0).x();
                    int coup_origin_y = m_coupPrecedent->at(0).y();
                    int coup_dest_x = m_coupPrecedent->at(1).x();
                    int coup_dest_y = m_coupPrecedent->at(1).y();

                    char tempPiece = idPiece[listeCoup.at(i).x()][listeCoup.at(i).y()];
                    int tempGroupe = couleur[listeCoup.at(i).x()][listeCoup.at(i).y()];

                    /////// GERER LA CAPTURE D'UN 'P' A LA VOLE !!!
                    bool deplacementSpecialFait = false;
                    if(couleur[x][y] == 'P')
                    {
                        if(listeCoup.at(i).y() != y && idPiece[listeCoup.at(i).x()][listeCoup.at(i).y()] == Rien )
                        {
                            deplacementSpecialFait = true;
                            if(y - listeCoup.at(i).y() > 0)
                            {
                                idPiece[x][y-1] = Rien;
                                couleur[x][y-1] = 0;
                            }
                            else
                            {
                                idPiece[x][y+1] = Rien;
                                couleur[x][y+1] = 0;
                            }
                        }
                    }

                    if(idPiece[x][y] == 'R')
                    {
                        if(couleur[x][y] == 1)
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

                    idPiece[listeCoup.at(i).x()][listeCoup.at(i).y()] = idPiece[x][y];
                    idPiece[x][y] = Rien;
                    couleur[listeCoup.at(i).x()][listeCoup.at(i).y()] = couleur[x][y];
                    couleur[x][y] = 0;

                    m_coupPrecedent[0][0].setX(x);
                    m_coupPrecedent[0][0].setY(y);
                    m_coupPrecedent[0][1].setX(listeCoup.at(i).x());
                    m_coupPrecedent[0][1].setY(listeCoup.at(i).y());

                    int score = 0;
                    // on relance l'appel

                    if(joueur == 0)
                    {
                        score = min(1,profondeur-1,alpha,beta);
                    }
                    else
                    {
                        score = min(0,profondeur-1,alpha,beta);
                    }

                    m_coupPrecedent[0][0].setX(coup_origin_x);
                    m_coupPrecedent[0][0].setY(coup_origin_y);
                    m_coupPrecedent[0][1].setX(coup_dest_x);
                    m_coupPrecedent[0][1].setY(coup_dest_y);

                    if(idPiece[listeCoup.at(i).x()][listeCoup.at(i).y()] == 'R')
                    {
                        if(couleur[listeCoup.at(i).x()][listeCoup.at(i).y()] == 1)
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
                        if(y - listeCoup.at(i).y() > 0)
                        {
                            idPiece[x][y-1] = 'P';
                            if(joueur == 1)
                            {
                                couleur[x][y-1] = 2;
                            }
                            else
                            {
                                couleur[x][y-1] = 1;
                            }
                        }
                        else
                        {
                            idPiece[x][y+1] = 'P';
                            if(joueur == 1)
                            {
                                couleur[x][y+1] = 2;
                            }
                            else
                            {
                                couleur[x][y+1] = 1;
                            }
                        }
                    }

                    idPiece[x][y] = idPiece[listeCoup.at(i).x()][listeCoup.at(i).y()];
                    idPiece[listeCoup.at(i).x()][listeCoup.at(i).y()] = tempPiece;

                    couleur[x][y] = couleur[listeCoup.at(i).x()][listeCoup.at(i).y()] ;
                    couleur[listeCoup.at(i).x()][listeCoup.at(i).y()] = tempGroupe;

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
int ia::min(int idJoueur,int profondeur,int alpha,int beta){
    int retour = 0;

        // /!\ ATTENTION eval IA ne prend pas en compte l'echec et mat vu que celui-ci est verifie dans gagnant jeux
        if(profondeur <= 0 || (retour = gagnantEnCours(idJoueur)) != 0)
        {
            if(profondeur <= 0)
            {
                return eval();
            }
            else
            {
                return retour;
            }
        }
         int min = 10000;
         for(int x=0;x<8;x++)
         {
              for(int y=0;y<8;y++)
              {
                  if(couleur[x][y] == joueur)
                  {
                      QVector<QPoint> listeCoup;
                      switch(idPiece[x][y])
                      {
                          case 'P':
                              listeCoup = deplacements::deplacementPion(idJoueur,couleur,idPiece,QPoint(x,y),m_coupPrecedent);
                          break;
                          case 'R':
                              listeCoup = deplacements::deplacementRoi(idPiece,couleur,QPoint(x,y));
                          break;
                          case Reine:
                              listeCoup = deplacements::deplacementReine(couleur,QPoint(x,y));
                          break;
                          case 'F':
                              listeCoup = deplacements::deplacementFou(couleur,QPoint(x,y));
                          break;
                          case 'T':
                              listeCoup = deplacements::deplacementTour(couleur,QPoint(x,y));
                          break;
                          case 'C':
                              listeCoup = deplacements::deplacementCavalier(couleur,QPoint(x,y));
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
                          // on joue le 'T'
                          piece tempPiece = idPiece[listeCoup.at(i).x()][listeCoup.at(i).y()];
                          int tempGroupe = couleur[listeCoup.at(i).x()][listeCoup.at(i).y()];
/*
                          ///////// GERER LA CAPTURE D'UN 'P' A LA VOLE !!!
                          bool deplacementSpecialFait = false;
                          if(idPiece[x][y] == 'P')
                          {
                              if(listeCoup.at(i).y() != y && idPiece[listeCoup.at(i).x()][listeCoup.at(i).y()] == Rien )
                              {
                                  deplacementSpecialFait = true;
                                  if(y - listeCoup.at(i).y() > 0)
                                  {
                                      idPiece[x][y-1] = Rien;
                                      couleur[x][y-1] = 0;
                                  }
                                  else
                                  {
                                      idPiece[x][y+1] = Rien;
                                      couleur[x][y+1] = 0;
                                  }
                              }
                          }
*/
                          if(idPiece[x][y] == 'R')
                          {
                              if(couleur[x][y] == 1)
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

                          idPiece[listeCoup.at(i).x()][listeCoup.at(i).y()] = idPiece[x][y];
                          idPiece[x][y] = Rien;
                          couleur[listeCoup.at(i).x()][listeCoup.at(i).y()] = couleur[x][y];
                          couleur[x][y] = 0;

                          int score = 0;
                          m_coupPrecedent[0][0].setX(x);
                          m_coupPrecedent[0][0].setY(y);
                          m_coupPrecedent[0][1].setX(listeCoup.at(i).x());
                          m_coupPrecedent[0][1].setY(listeCoup.at(i).y());
                          // on relance l'appel

                          if(joueur == 1)
                          {
                              score = max(2,profondeur-1,alpha,beta);
                          }
                          else
                          {
                              score = max(1,profondeur-1,alpha,beta);
                          }


                          m_coupPrecedent[0][0].setX(coup_origin_x);
                          m_coupPrecedent[0][0].setY(coup_origin_y);
                          m_coupPrecedent[0][1].setX(coup_dest_x);
                          m_coupPrecedent[0][1].setY(coup_dest_y);

                          if(idPiece[listeCoup.at(i).x()][listeCoup.at(i).y()] == 'R')
                          {
                              if(couleur[listeCoup.at(i).x()][listeCoup.at(i).y()] == 1)
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
/*
                          if(deplacementSpecialFait)
                          {
                              if(y - listeCoup.at(i).y() > 0)
                              {
                                  idPiece[x][y-1] = 'P';
                                  if(joueur == 1)
                                  {
                                    couleur[x][y-1] = 2;
                                  }
                                  else
                                  {
                                    couleur[x][y-1] = 1;
                                  }
                              }
                              else
                              {
                                  idPiece[x][y+1] = 'P';
                                  if(joueur == 1)
                                  {
                                    couleur[x][y+1] = 2;
                                  }
                                  else
                                  {
                                    couleur[x][y+1] = 1;
                                  }
                              }
                          }
*/
                          idPiece[x][y] = idPiece[listeCoup.at(i).x()][listeCoup.at(i).y()];
                          idPiece[listeCoup.at(i).x()][listeCoup.at(i).y()] = tempPiece;

                          couleur[x][y] = couleur[listeCoup.at(i).x()][listeCoup.at(i).y()] ;
                          couleur[listeCoup.at(i).x()][listeCoup.at(i).y()] = tempGroupe;

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

    initTableauTmp(plateau);
    QVector<QPoint> result;
        for(int x = 0; x < 8; x++)
        {
            for(int y = 0; y < 8; y++)
            {
                if( idPiece[x][y] == 'R')
                {
                    if(couleur[x][y] == 1)
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
                if(couleur[x][y] == joueur)
                {
                    QVector<QPoint> listeCoup;
                    switch(idPiece[x][y])
                    {
                        case 'P':
                            listeCoup = deplacements::deplacementPion(idJoueur,couleur,this->idPiece,QPoint(x,y),m_coupPrecedent);
                        break;
                        case 'R':
                            listeCoup = deplacements::deplacementRoi(idPiece,couleur,QPoint(x,y));
                        break;
                        case Reine:
                            listeCoup = deplacements::deplacementReine(couleur,QPoint(x,y));
                        break;
                        case 'F':
                            listeCoup = deplacements::deplacementFou(couleur,QPoint(x,y));
                        break;
                        case 'T':
                            listeCoup = deplacements::deplacementTour(couleur,QPoint(x,y));
                        break;
                        case 'C':
                            listeCoup = deplacements::deplacementCavalier(couleur,QPoint(x,y));
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
                        // on joue le 'T'
                        piece tempPiece = idPiece[listeCoup.at(i).x()][listeCoup.at(i).y()];
                        int tempGroupe = couleur[listeCoup.at(i).x()][listeCoup.at(i).y()];
/*
                        ///////// GERER LA CAPTURE D'UN 'P' A LA VOLE !!!
                        bool deplacementSpecialFait = false;
                        if(idPiece[x][y] == 'P')
                        {
                            if(listeCoup.at(i).y() != y && idPiece[listeCoup.at(i).x()][listeCoup.at(i).y()] == Rien )
                            {
                                deplacementSpecialFait = true;
                                if(y - listeCoup.at(i).y() > 0)
                                {
                                    idPiece[x][y-1] = Rien;
                                    couleur[x][y-1] = 0;
                                }
                                else
                                {
                                    idPiece[x][y+1] = Rien;
                                    couleur[x][y+1] = 0;
                                }
                            }
                        }
*/
                        if(idPiece[x][y] == 'R')
                        {
                            if(couleur[x][y] == 1)
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

                        idPiece[listeCoup.at(i).x()][listeCoup.at(i).y()] = idPiece[x][y];
                        idPiece[x][y] = Rien;
                        couleur[listeCoup.at(i).x()][listeCoup.at(i).y()] = couleur[x][y];
                        couleur[x][y] = 0;

                        m_coupPrecedent[0][0].setX(x);
                        m_coupPrecedent[0][0].setY(y);
                        m_coupPrecedent[0][1].setX(listeCoup.at(i).x());
                        m_coupPrecedent[0][1].setY(listeCoup.at(i).y());


                        if(joueur == 1)
                        {
                            score = min(2,profondeur-1,-10000,100000);
                        }
                        else
                        {
                            score = min(1,profondeur-1,-10000,100000);
                        }


                        m_coupPrecedent[0][0].setX(coup_origin_x);
                        m_coupPrecedent[0][0].setY(coup_origin_y);
                        m_coupPrecedent[0][1].setX(coup_dest_x);
                        m_coupPrecedent[0][1].setY(coup_dest_y);

                        if(idPiece[listeCoup.at(i).x()][listeCoup.at(i).y()] == 'R')
                        {
                            if(couleur[listeCoup.at(i).x()][listeCoup.at(i).y()] == 1)
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
/*
                        if(deplacementSpecialFait)
                        {
                            if(y - listeCoup.at(i).y() > 0)
                            {
                                idPiece[x][y-1] = 'P';
                                if(joueur == 1)
                                {
                                  couleur[x][y-1] = 2;
                                }
                                else
                                {
                                  couleur[x][y-1] = 1;
                                }
                            }
                            else
                            {
                                idPiece[x][y+1] = 'P';
                                if(joueur == 1)
                                {
                                  couleur[x][y+1] = 2;
                                }
                                else
                                {
                                  couleur[x][y+1] = 1;
                                }
                            }
                        }
*/

                        idPiece[x][y] = idPiece[listeCoup.at(i).x()][listeCoup.at(i).y()];
                        idPiece[listeCoup.at(i).x()][listeCoup.at(i).y()] = tempPiece;

                        couleur[x][y] = couleur[listeCoup.at(i).x()][listeCoup.at(i).y()] ;
                        couleur[listeCoup.at(i).x()][listeCoup.at(i).y()] = tempGroupe;

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
/**
 * @brief ia::eval
 * fonction d'evaluation du plateau
 * @param plateau pointeur sur le plateau
 * @return Difference des valeurs des pieces de chaque joueur
 */
int ia::eval(){
    int scoreJoueur1 = 0;
    int scoreJoueur2 = 0;
    for(int x = 0; x < 8; x++)
    {
        for(int y = 0; y < 8; y++)
        {
            if(idPiece[x][y] == 'P' && couleur[x][y] == 0)
            {
                scoreJoueur1++;
            }
            else if(idPiece[x][y] == 'P' && couleur[x][y] == 1)
            {
                scoreJoueur2++;
            }
            if((idPiece[x][y] == 'F' || idPiece[x][y] == 'C') && couleur[x][y] == 0)
            {
                scoreJoueur1 += 3;
            }
            else if((idPiece[x][y] == 'F' || idPiece[x][y] == 'C') && couleur[x][y] == 1)
            {
                scoreJoueur2 += 3;
            }
            if(idPiece[x][y] == 'T' && couleur[x][y] == 0)
            {
                scoreJoueur1 += 5;
            }
            else if(idPiece[x][y] == 'T' && couleur[x][y] == 1)
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
         * @param pos_'R'_joueur position du roi du joueur
         * @param plateau pointeur sur le plateaju
         * @return un vecteur vide si le joueur a perdu sinon la liste des deplacements sans mettre le roi en echec
         */
QVector<QPoint> ia::calc_echec_et_mat(int idJoueur,QPoint pos_roi){
    int score;

    QVector<QPoint> result;
    for(int x = 0; x < 8; x++)
    {
        for(int y = 0; y < 8; y++)
        {
            if(couleur[x][y] == idJoueur)
            {
                QVector<QPoint> listeCoup;
                switch(idPiece[x][y])
                {
                case 'P':
                    listeCoup = deplacements::deplacementPion(idJoueur,couleur,this->idPiece,QPoint(x,y),m_coupPrecedent);
                    break;
                case 'R':
                    listeCoup = deplacements::deplacementRoi(idPiece,couleur,QPoint(x,y));
                    /*
                    if(deplacements::grandRoguePossible(couleur[x][y],couleur,m_deplacement,idPiece))
                    {
                        if(couleur[x][y] == 1)
                        {
                            listeCoup.append(QPoint(0,2));
                        }
                        else
                        {
                            listeCoup.append(QPoint(7,2));
                        }
                    }
                    if(deplacements::petitRoguePossible(couleur[x][y],couleur,m_deplacement,idPiece))
                    {
                        if(couleur[x][y] == 1)
                        {
                            listeCoup.append(QPoint(0,6));
                        }
                        else
                        {
                            listeCoup.append(QPoint(7,6));
                        }
                    }*/
                    break;
                case 'F':
                    listeCoup = deplacements::deplacementFou(couleur,QPoint(x,y));
                    break;
                case 'T':
                    listeCoup = deplacements::deplacementTour(couleur,QPoint(x,y));
                    break;
                case 'C':
                    listeCoup = deplacements::deplacementCavalier(couleur,QPoint(x,y));
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
                    // on joue le 'T'
                    piece tempPiece = idPiece[listeCoup.at(i).x()][listeCoup.at(i).y()];
                    int tempGroupe = couleur[listeCoup.at(i).x()][listeCoup.at(i).y()];

                    ///////// SI LE ROI PEUT SE DEPLACER C'EST QU'IL PEUT S'ECHAPPER LE BOUGRE !
                    if(idPiece[x][y] ==  'R')
                    {
                        result.append(QPoint(x,y));
                        result.append(listeCoup.at(i));
                    }
                    else
                    {
                        ///////// GERER LA CAPTURE D'UN 'P' A LA VOLE !!!
                        bool deplacementSpecialFait = false;
                        /*
                        if(idPiece[x][y] == 'P')
                        {
                            if(listeCoup.at(i).y() != y && idPiece[listeCoup.at(i).x()][listeCoup.at(i).y()] == Rien )
                            {
                                deplacementSpecialFait = true;
                                if(y - listeCoup.at(i).y() > 0)
                                {
                                    idPiece[x][y-1] = Rien;
                                    couleur[x][y-1] = 0;
                                }
                                else
                                {
                                    idPiece[x][y+1] = Rien;
                                    couleur[x][y+1] = 0;
                                }
                            }
                        }*/


                        idPiece[listeCoup.at(i).x()][listeCoup.at(i).y()] = idPiece[x][y];
                        idPiece[x][y] = Rien;
                        couleur[listeCoup.at(i).x()][listeCoup.at(i).y()] = couleur[x][y];
                        couleur[x][y] = 0;

                        m_coupPrecedent[0][0].setX(x);
                        m_coupPrecedent[0][0].setY(y);
                        m_coupPrecedent[0][1].setX(listeCoup.at(i).x());
                        m_coupPrecedent[0][1].setY(listeCoup.at(i).y());





                        if(deplacements::inCheck(idPiece,couleur,idJoueur,QPoint(pos_roi.x(),pos_roi.y())))
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
                                idPiece[x][y-1] = 'P';
                                if(joueur == 1)
                                {
                                    couleur[x][y-1] = 2;
                                }
                                else
                                {
                                    couleur[x][y-1] = 1;
                                }
                            }
                            else
                            {
                                idPiece[x][y+1] = 'P';
                                if(joueur == 1)
                                {
                                    couleur[x][y+1] = 2;
                                }
                                else
                                {
                                    couleur[x][y+1] = 1;
                                }
                            }
                        }



                        idPiece[x][y] = idPiece[listeCoup.at(i).x()][listeCoup.at(i).y()];
                        idPiece[listeCoup.at(i).x()][listeCoup.at(i).y()] = tempPiece;

                        couleur[x][y] = couleur[listeCoup.at(i).x()][listeCoup.at(i).y()] ;
                        couleur[listeCoup.at(i).x()][listeCoup.at(i).y()] = tempGroupe;
                    }
                }
            }
        }
    }
    return result;
}

void ia::initTableauTmp(Plateau * plateau){
    this->m_coupPrecedent=plateau->getCoupPrec();
    //init des couleurs
    for(int x=0;x<8;x++){
        for(int y=0;y<8;y++){
            this->tableauCouleur[x][y]=plateau->getGrille()->getCase(x,y)->getCouleur();
            this->tableauPieces[x][y]=plateau->getGrille()->getCase(x,y)->getId();
            this->tableauOccup[x][y]=plateau->getGrille()->getCase(x,y)->isOccupied();
            this->matriceDep[x][y]=plateau->m_matriceDeplacement[x][y];
        }
    }

}

ia::~ia()
{

}
