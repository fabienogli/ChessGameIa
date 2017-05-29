#include "ia.h"
#include "Plateau.h"
#include "Joueur.h"
#include "Piece.h"
#include "deplacement.h"

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
        if((this->calc_echec_et_mat(0,this->posi_roi_joueur1)).count() == 0)
            //if((this->calc_echec_et_mat(plateau->getJoueur1(),this->posi_roi_joueur1,plateau)) == 0)
        {
            std::cout<<"dans gagnant jeux 1"<<std::endl;
            return -1000;
        }
        else if((this->calc_echec_et_mat(1,this->posi_roi_joueur2)).count() == 0)
            //     if((this->calc_echec_et_mat(plateau->getJoueur2(),this->posi_roi_joueur2,plateau)) == 0)
        {
            std::cout<<"dans gagnant jeux 2"<<std::endl;
            return 1000;

        }
    }
    else if (idJoueur == 1)
    {

        if((this->calc_echec_et_mat(1,this->posi_roi_joueur2)).count() == 0)
        {
            std::cout<<"dans gagnant jeux 3"<<std::endl;
            return -1000;
        }

        else if((this->calc_echec_et_mat(0,this->posi_roi_joueur1)).count() == 0)
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
int ia::max(int idJoueur,int profondeur,int alpha,int beta,int couleur[8][8],char idPiece[8][8])
{
    int retour = 0;
    // eval IA ne prend pas en compte l'echec et mat vu que celui-ci est verifie dans gagnant jeux
    if(profondeur <= 0 || (retour = gagnantEnCours(idJoueur)) != 0)
    {
        if(profondeur <= 0)
        {
            return eval(couleur,idPiece);
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
            if(couleur[x][y] == idJoueur)
            {
                QVector<QPoint> listeCoup;
                switch(idPiece[x][y])
                {
                case 'P':
                    std::cout<<"ici3"<<std::endl;
                    listeCoup = deplacement::deplacementPion(idJoueur, couleur,QPoint(x,y),matriceDep);
                    break;
                case 'R':
                    listeCoup = deplacement::deplacementRoi(idPiece,couleur,QPoint(x,y));
                    break;
                case 'F':
                    listeCoup = deplacement::deplacementFou(couleur,QPoint(x,y));
                    break;
                case 'T':
                    listeCoup = deplacement::deplacementTour(couleur,QPoint(x,y));
                    break;
                case 'C':
                    listeCoup = deplacement::deplacementCavalier(couleur,QPoint(x,y));
                    break;
                default:
                    listeCoup = QVector<QPoint>();
                    break;
                }
                for (int i = 0; i < listeCoup.count(); i++)
                {
                    char idPieceTmp = idPiece[listeCoup.at(i).x()][listeCoup.at(i).y()];
                    int couleurTmp = couleur[listeCoup.at(i).x()][listeCoup.at(i).y()];

                    if(tableauPieces[x][y] == 'R')
                    {
                        if(tableauCouleur[x][y] == 0)
                        {
                            this->posi_roi_joueur1.setX(listeCoup.at(i).x());
                            this->posi_roi_joueur1.setY(listeCoup.at(i).y());
                        }
                        else
                        {
                            this->posi_roi_joueur2.setX(listeCoup.at(i).x());
                            this->posi_roi_joueur2.setY(listeCoup.at(i).y());
                        }
                    }

                    idPiece[listeCoup.at(i).x()][listeCoup.at(i).y()] =idPiece[x][y];
                    idPiece[x][y] = 'N';
                    couleur[listeCoup.at(i).x()][listeCoup.at(i).y()] = couleur[x][y];
                    couleur[x][y] = -1;

                    int score = 0;
                    // on relance l'appel

                    if(idJoueur == 0)
                    {
                        std::cout<<"profondeur min ="<<profondeur-1<<std::endl;
                        score = min(1,profondeur-1,alpha,beta,couleur,idPiece);
                    }
                    else
                    {
                        std::cout<<"profondeur min ="<<profondeur-1<<std::endl;
                        score = min(0,profondeur-1,alpha,beta,couleur,idPiece);
                    }

                    if(tableauPieces[listeCoup.at(i).x()][listeCoup.at(i).y()] == 'R')
                    {
                        if(tableauCouleur[listeCoup.at(i).x()][listeCoup.at(i).y()] == 0)
                        {
                            this->posi_roi_joueur1.setX(x);
                            this->posi_roi_joueur1.setY(y);
                        }
                        else
                        {
                            this->posi_roi_joueur2.setX(x);
                            this->posi_roi_joueur2.setY(y);
                        }
                    }


                    idPiece[x][y] = idPiece[listeCoup.at(i).x()][listeCoup.at(i).y()];
                    idPiece[listeCoup.at(i).x()][listeCoup.at(i).y()] = idPieceTmp;

                    couleur[x][y] = couleur[listeCoup.at(i).x()][listeCoup.at(i).y()] ;
                    couleur[listeCoup.at(i).x()][listeCoup.at(i).y()] = couleurTmp;

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
int ia::min(int idJoueur,int profondeur,int alpha,int beta,int couleur[8][8],char idPiece[8][8]){
    int retour = 0;

        // eval  ne prend pas en compte l'echec et mat vu que celui-ci est verifie dans gagnant
        if(profondeur <= 0 || (retour = gagnantEnCours(idJoueur)) != 0)
        {
            if(profondeur <= 0)
            {
                return eval(couleur,idPiece);
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
                  if(couleur[x][y] == idJoueur)
                  {
                      QVector<QPoint> listeCoup;
                      switch(idPiece[x][y])
                      {
                          case 'P':
                          std::cout<<"ici2"<<std::endl;
                              listeCoup = deplacement::deplacementPion(idJoueur,couleur,QPoint(x,y),matriceDep);
                          break;
                          case 'R':
                              listeCoup = deplacement::deplacementRoi(idPiece,couleur,QPoint(x,y));
                          break;
                          case 'F':
                              listeCoup = deplacement::deplacementFou(couleur,QPoint(x,y));
                          break;
                          case 'T':
                              listeCoup = deplacement::deplacementTour(couleur,QPoint(x,y));
                          break;
                          case 'C':
                              listeCoup = deplacement::deplacementCavalier(couleur,QPoint(x,y));
                          break;
                          default:
                              listeCoup = QVector<QPoint>();
                          break;
                      }
                      for (int i = 0; i < listeCoup.count(); i++)
                      {                         
                          char idPieceTmp = idPiece[listeCoup.at(i).x()][listeCoup.at(i).y()];
                          int couleurTmp = couleur[listeCoup.at(i).x()][listeCoup.at(i).y()];

                          if(tableauPieces[x][y] == 'R')
                          {
                              if(tableauCouleur[x][y] == 0)
                              {
                                  this->posi_roi_joueur1.setX(listeCoup.at(i).x());
                                  this->posi_roi_joueur1.setY(listeCoup.at(i).y());
                              }
                              else
                              {
                                  this->posi_roi_joueur2.setX(listeCoup.at(i).x());
                                  this->posi_roi_joueur2.setY(listeCoup.at(i).y());
                              }
                          }

                          idPiece[listeCoup.at(i).x()][listeCoup.at(i).y()] = idPiece[x][y];
                          idPiece[x][y] = 'N';
                          couleur[listeCoup.at(i).x()][listeCoup.at(i).y()] = couleur[x][y];
                          couleur[x][y] = -1;

                          int score = 0;
                          if(idJoueur == 0)

                          { std::cout<<"profondeur max ="<<profondeur-1<<std::endl;
                              score = max(1,profondeur-1,alpha,beta,couleur,idPiece);
                          }
                          else
                          {
                              std::cout<<"profondeur max ="<<profondeur-1<<std::endl;
                              score = max(0,profondeur-1,alpha,beta,couleur,idPiece);
                          }

                          if(tableauPieces[listeCoup.at(i).x()][listeCoup.at(i).y()] == 'R')
                          {
                              if(tableauCouleur[listeCoup.at(i).x()][listeCoup.at(i).y()] == 0)
                              {
                                  this->posi_roi_joueur1.setX(x);
                                  this->posi_roi_joueur1.setY(y);
                              }
                              else
                              {
                                  this->posi_roi_joueur2.setX(x);
                                  this->posi_roi_joueur2.setY(y);
                              }
                          }

                          idPiece[x][y] = idPiece[listeCoup.at(i).x()][listeCoup.at(i).y()];
                          idPiece[listeCoup.at(i).x()][listeCoup.at(i).y()] = idPieceTmp;

                          couleur[x][y] = couleur[listeCoup.at(i).x()][listeCoup.at(i).y()] ;
                          couleur[listeCoup.at(i).x()][listeCoup.at(i).y()] = couleurTmp;

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
QVector<QPoint> ia::jouer(Joueur *joueur,Plateau *plateau)
{
    int max = -10000;
 int idJoueur=joueur->getIdJoueur();
 int score =0;
    initTableauTmp(plateau);
    QVector<QPoint> result;
        for(int x = 0; x < 8; x++)
        {
            for(int y = 0; y < 8; y++)
            {
                if( tableauPieces[x][y] == 'R')
                {
                    if(tableauCouleur[x][y] == 0)
                    {
                        this->posi_roi_joueur1.setX(x);
                        this->posi_roi_joueur1.setY(y);
                    }
                    else
                    {
                        this->posi_roi_joueur2.setX(x);
                        this->posi_roi_joueur2.setY(y);
                    }
                }
                if(tableauCouleur[x][y] == idJoueur)
                {
                    QVector<QPoint> listeCoup;
                    switch(tableauPieces[x][y])
                    {
                        case 'P':
                        std::cout<<"ici1 ="<<std::endl;
                            listeCoup = deplacement::deplacementPion(idJoueur,tableauCouleur,QPoint(x,y),matriceDep);
                        break;
                        case 'R':
                            listeCoup = deplacement::deplacementRoi(tableauPieces,tableauCouleur,QPoint(x,y));
                        break;
                        case 'F':
                            listeCoup = deplacement::deplacementFou(tableauCouleur,QPoint(x,y));
                        break;
                        case 'T':
                            listeCoup = deplacement::deplacementTour(tableauCouleur,QPoint(x,y));
                        break;
                        case 'C':
                            listeCoup = deplacement::deplacementCavalier(tableauCouleur,QPoint(x,y));
                        break;
                        default:
                            listeCoup = QVector<QPoint>();
                        break;
                    }

                    for (int i = 0; i < listeCoup.count(); i++)
                    {
                        char idPieceTmp = tableauPieces[listeCoup.at(i).x()][listeCoup.at(i).y()];
                        int couleurTmp = tableauCouleur[listeCoup.at(i).x()][listeCoup.at(i).y()];

                        if(tableauPieces[x][y] == 'R')
                        {
                            if(tableauCouleur[x][y] == 0)
                            {
                                this->posi_roi_joueur1.setX(listeCoup.at(i).x());
                                this->posi_roi_joueur1.setY(listeCoup.at(i).y());
                            }
                            else
                            {
                                this->posi_roi_joueur2.setX(listeCoup.at(i).x());
                                this->posi_roi_joueur2.setY(listeCoup.at(i).y());
                            }
                        }

                        tableauPieces[listeCoup.at(i).x()][listeCoup.at(i).y()] = tableauPieces[x][y];
                        tableauPieces[x][y] = 'N';
                        tableauCouleur[listeCoup.at(i).x()][listeCoup.at(i).y()] = tableauCouleur[x][y];
                        tableauCouleur[x][y] = -1;

                        if(idJoueur == 0)
                        {
                            std::cout<<"profondeur min ="<<this->getLevel()-1<<std::endl;
                            score = min(1,this->getLevel()-1,-10000,100000,tableauCouleur,tableauPieces);
                        }
                        else
                        {
                            std::cout<<"profondeur min ="<<this->getLevel()-1<<std::endl;
                            score = min(0,this->getLevel()-1,-10000,100000,tableauCouleur,tableauPieces);
                        }


                        if(tableauPieces[listeCoup.at(i).x()][listeCoup.at(i).y()] == 'R')
                        {
                            if(tableauCouleur[listeCoup.at(i).x()][listeCoup.at(i).y()] == 0)
                            {
                                this->posi_roi_joueur1.setX(x);
                                this->posi_roi_joueur1.setY(y);
                            }
                            else
                            {
                                this->posi_roi_joueur2.setX(x);
                                this->posi_roi_joueur2.setY(y);
                            }
                        }


                        tableauPieces[x][y] = tableauPieces[listeCoup.at(i).x()][listeCoup.at(i).y()];
                        tableauPieces[listeCoup.at(i).x()][listeCoup.at(i).y()] = idPieceTmp;

                        tableauCouleur[x][y] = tableauCouleur[listeCoup.at(i).x()][listeCoup.at(i).y()] ;
                        tableauCouleur[listeCoup.at(i).x()][listeCoup.at(i).y()] = couleurTmp;

                          if(score > max)
                          {
                                max = score;
                                result.clear();
                                result.append(QPoint(x,y));
                                result.append(listeCoup.at(i));
                          }
                          else if(score == max) // si deux coups sont  a peu près égaux on les mets a la suite
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
int ia::eval(int couleur[8][8],char idPiece[8][8]){
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
 * @return un vecteur vide si le joueur a perdu sinon la liste des deplacement sans mettre le roi en echec
 */
QVector<QPoint> ia::calc_echec_et_mat(int idJoueur,QPoint pos_roi){
    int score;

    QVector<QPoint> result;
    for(int x = 0; x < 8; x++)
    {
        for(int y = 0; y < 8; y++)
        {
            if(tableauCouleur[x][y] == idJoueur)
            {
                QVector<QPoint> listeCoup;
                switch(tableauPieces[x][y])
                {
                case 'P':
                    listeCoup = deplacement::deplacementPion(idJoueur,tableauCouleur,QPoint(x,y),matriceDep);
                    break;
                case 'R':
                    listeCoup = deplacement::deplacementRoi(tableauPieces,tableauCouleur,QPoint(x,y));

                    if(deplacement::checkGrandRoque(idJoueur,tableauCouleur,matriceDep,tableauPieces))
                    {
                        if(tableauCouleur[x][y] == 0)
                        {
                            listeCoup.append(QPoint(0,2));
                        }
                        else
                        {
                            listeCoup.append(QPoint(7,2));
                        }
                    }
                    if(deplacement::checkPetitRoque(idJoueur,tableauCouleur,matriceDep,tableauPieces))
                    {
                        if(tableauCouleur[x][y] == 0)
                        {
                            listeCoup.append(QPoint(0,6));
                        }
                        else
                        {
                            listeCoup.append(QPoint(7,6));
                        }
                    }
                    break;
                case 'F':
                    listeCoup = deplacement::deplacementFou(tableauCouleur,QPoint(x,y));
                    break;
                case 'T':
                    listeCoup = deplacement::deplacementTour(tableauCouleur,QPoint(x,y));
                    break;
                case 'C':
                    listeCoup = deplacement::deplacementCavalier(tableauCouleur,QPoint(x,y));
                    break;
                default:
                    listeCoup = QVector<QPoint>();
                    break;
                }

                for (int i = 0; i < listeCoup.count(); i++)
                {
                    char idPieceTmp = tableauPieces[listeCoup.at(i).x()][listeCoup.at(i).y()];
                    int couleurTmp = tableauCouleur[listeCoup.at(i).x()][listeCoup.at(i).y()];

                    // si le roi est en position de se déplacer, il peut donc s'échapper
                    if(tableauPieces[x][y] == 'R')
                    {
                        result.append(QPoint(x,y));
                        result.append(listeCoup.at(i));
                    }
                    else
                    {
                        tableauPieces[listeCoup.at(i).x()][listeCoup.at(i).y()] = tableauPieces[x][y];
                        tableauPieces[x][y] = 'N';
                        tableauCouleur[listeCoup.at(i).x()][listeCoup.at(i).y()] = tableauCouleur[x][y];
                        tableauCouleur[x][y] = -1;

                        if(deplacement::inCheck(tableauPieces,tableauCouleur,idJoueur,QPoint(pos_roi.x(),pos_roi.y())))
                        {
                            score = -1000;
                        }
                        else
                        {
                            score =  1000;
                        }

                        if(score > -500) // si on peut eviter un echec et mat
                        {
                            // on a sacrifie une piece pour sauver le roi !
                            std::cout<<"DEPLACEMENT IA"<<std::endl;
                            result.append(QPoint(x,y));
                            result.append(listeCoup.at(i));
                        }
                        tableauPieces[x][y] = tableauPieces[listeCoup.at(i).x()][listeCoup.at(i).y()];
                        tableauPieces[listeCoup.at(i).x()][listeCoup.at(i).y()] = idPieceTmp;

                        tableauCouleur[x][y] = tableauCouleur[listeCoup.at(i).x()][listeCoup.at(i).y()] ;
                        tableauCouleur[listeCoup.at(i).x()][listeCoup.at(i).y()] = couleurTmp;
                    }
                }
            }
        }
    }
    return result;
}
/**
 * @brief ia::initTableauTmp
 * fonction qui permet de creer des tableaux temporaires sur lesquelles nous ferons nos simulations
 * @param plateau un pointeur sur le plateau
 */
void ia::initTableauTmp(Plateau * plateau){
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
