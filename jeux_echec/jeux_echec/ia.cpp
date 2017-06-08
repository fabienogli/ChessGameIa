#include "ia.h"
#include <QDebug>
/**
 * \brief IA::IA
 * Initialise IA avec la partie en cours :
 *   - pieces et couleurs des pieces sur l'echiquier
 *   - ou nous en sommes dans la partie (coups precedants et pieces deplacees)
 * \param[in] matriceTerrain Matrice de l'echiquier de la partie
 * \param[in] matriceGroupe Matrice de couleur des pieces
 * \param[in] mattriceDeplacement Matrice des pieces qui ont bouge
 * \param[in] m_coupPrecedent Vecteur des coups precedants
 * \param parent
 */
IA::IA(piece matriceTerrain[][8],int matriceGroupe[][8],int mattriceDeplacement[][8],QVector<QPoint> *m_coupPrecedent,QObject * parent) : QObject(parent)
{

    this->m_terrain = matriceTerrain;
    this->m_groupe = matriceGroupe;
    this->m_deplacement = mattriceDeplacement;
    this->m_profondeur = 4;
    this->m_coupPrecedent = m_coupPrecedent;
}
/**
 * \brief IA::setDifficulter
 * Initialisation du comportement que va avoir l'ia
 * En facile l'IA ira a une profondeur de 2 coups d'avance en normal 4 coups d'avance et dificille 6 coups d'avance.
 * \param diff Difficulte du l'ia 1 = facile,2 normal sinon Difficulte maximum
 */
void IA::setDifficulter(int diff)
{
    if(diff == 1)
    {
        this->m_profondeur = 2;
    }
    else if(diff == 2)
    {
        this->m_profondeur = 4;
    }
    else
    {
        this->m_profondeur = 6;
    }
}
/**
 * @brief IA::getDifficulter
 * Donne la difficulte de l'ia en cours
 * @return Valeur difficulte ia 1|2|3
 */
unsigned int IA::getDifficulter()
{
    if(this->m_profondeur == 2)
    {
        return 1;
    }
    else if(this->m_profondeur == 4)
    {
        return 2;
    }
    else
    {
        return 3;
    }
}
/**
 * \brief IA::calc_echec_et_mat
 * Calcule si le joueur peut encore jouer, si il est en echec alors cette fonction lui
 * renverra un vecteur vide lui indiquant qu'aucun coup n'est possible
 * \param joueur Numero du joueur qui joue
 * \param pos_rois_joueur Position du roi du joueur qui joue
 * \return Liste des coups jouable par le joueur sans que le roi soit en echec
 */
QVector<QPoint> IA::calc_echec_et_mat(int joueur,QPoint pos_rois_joueur)
{
    int score;

    QVector<QPoint> result;
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
    }
    return result;
}

/**
 * \brief IA::jouer
 * Fait jouer le joueur ordinateur
 * \param joueur Numero du joueur
 * \return Liste des coups possible pour l'ordinateur
 */
QVector<QPoint> IA::jouer(int joueur)
{
    int max = -10000;
    int score;

    QVector<QPoint> result;
    for(int x = 0; x < 8; x++)
    {
        for(int y = 0; y < 8; y++)
        {
            if( m_terrain[x][y] == Rois)
            {
                if(m_groupe[x][y] == 1)
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

                    if(m_terrain[x][y] == Rois)
                    {
                        if(m_groupe[x][y] == 1)
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

                    m_terrain[listeCoup.at(i).x()][listeCoup.at(i).y()] = m_terrain[x][y];
                    m_terrain[x][y] = Rien;
                    m_groupe[listeCoup.at(i).x()][listeCoup.at(i).y()] = m_groupe[x][y];
                    m_groupe[x][y] = 0;

                    m_coupPrecedent[0][0].setX(x);
                    m_coupPrecedent[0][0].setY(y);
                    m_coupPrecedent[0][1].setX(listeCoup.at(i).x());
                    m_coupPrecedent[0][1].setY(listeCoup.at(i).y());


                    if(joueur == 1)
                    {
                        score = min(2,m_terrain,m_groupe,m_profondeur-1,-10000,100000);
                    }
                    else
                    {
                        score = min(1,m_terrain,m_groupe,m_profondeur-1,-10000,100000);
                    }


                    m_coupPrecedent[0][0].setX(coup_origin_x);
                    m_coupPrecedent[0][0].setY(coup_origin_y);
                    m_coupPrecedent[0][1].setX(coup_dest_x);
                    m_coupPrecedent[0][1].setY(coup_dest_y);

                    if(m_terrain[listeCoup.at(i).x()][listeCoup.at(i).y()] == Rois)
                    {
                        if(m_groupe[listeCoup.at(i).x()][listeCoup.at(i).y()] == 1)
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
 * \brief IA::evalIA
 * Calcule la valeur cummule de toutes les pieces des deux joueurs et soustrait la valeur du premier par celle du second
 * pour etablir qui est en train de gagner sur la partie si le joueur 1 gagne le resultat sera positif sinon negatif
 * \param terrain Matrice des pieces de l'echiquier
 * \param groupe Matrice de couleur des pieces
 * \return Difference des valeurs des pieces de chaque joueur
 */
int IA::evalIA(piece terrain[8][8],int groupe[8][8])
{
    int scoreJoueur1 = 0;
    int scoreJoueur2 = 0;
    for(int x = 0; x < 8; x++)
    {
        for(int y = 0; y < 8; y++)
        {
            if(terrain[x][y] == Pion && groupe[x][y] == 1)
            {
                scoreJoueur1++;
            }
            else if(terrain[x][y] == Pion && groupe[x][y] == 2)
            {
                scoreJoueur2++;
            }
            if((terrain[x][y] == Fous || terrain[x][y] == Cavalier) && groupe[x][y] == 1)
            {
                scoreJoueur1 += 3;
            }
            else if((terrain[x][y] == Fous || terrain[x][y] == Cavalier) && groupe[x][y] == 2)
            {
                scoreJoueur2 += 3;
            }
            if(terrain[x][y] == Tour && groupe[x][y] == 1)
            {
                scoreJoueur1 += 5;
            }
            else if(terrain[x][y] == Tour && groupe[x][y] == 2)
            {
               scoreJoueur2 += 5;
            }
            if(terrain[x][y] == Reine && groupe[x][y] == 1)
            {
                scoreJoueur1 += 10;
            }
            else if(terrain[x][y] == Reine && groupe[x][y] == 2)
            {
               scoreJoueur2 += 10;
            }
        }
    }
    return  scoreJoueur1 - scoreJoueur2;
}
/**
 * \brief IA::gagnantJeux
 * Calcule si la partie est fini ou pas, si elle est finie (echec et mat donc)
 * elle nous renvoie si joueur a gagner 1000 et si le joueur a perdu -1000
 * \param joueur Numero du joueur en cours
 * \return 0 si la partie n'est pas fini -1000 si le joueur a perdu 1000 si il a gagne
 */
int IA::gagnantJeux(int joueur)
{
    if(joueur == 1)
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
/**
 * \brief IA::max
 * La fonction max calcule le maximum de score que peut esperer gagner le joueur
 * en deplacant tout ces pieces, il va renvoyer le meilleur deplacement possible.
 * si la profondeur max est atteinte ou que l'on a gagner on renvoie une evaluation des scores du terrain
 * si la profondeur n'est pas atteinte a chaque deplacement de ces pieces il appele a min sur l'autre joueur
 * pour le faire jouer et recuperer le score minimum que peut atteindre l'autre joueur si je jouais cette piece.
 * \param joueur Numero du joueur
 * \param terrain Matrice de pieces de l'echiquier
 * \param groupe Matrice de couleurs des pieces
 * \param profondeur Nombre de coups a prevoir
 * \param alpha Score maximum possible
 * \param beta Score minimum possible
 * \return Valeur final du jeu ou valeur gagnant si fin ou minimum calcule
 */
int IA::max(int joueur,piece terrain[8][8],int groupe[8][8],int profondeur, int alpha, int beta)
{
    int retour = 0;
    // /!\ ATTENTION eval IA ne prend pas en compte l'echec et mat vu que celui-ci est verifie dans gagnant jeux
    if(profondeur <= 0 || (retour = gagnantJeux(joueur)) != 0)
    {
        if(profondeur <= 0)
        {
            return evalIA(terrain,groupe);
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
              if(groupe[x][y] == joueur)
              {
                  QVector<QPoint> listeCoup;
                  switch(terrain[x][y])
                  {
                      case Pion:
                          listeCoup = deplacements::deplacementPion(groupe,this->m_terrain,QPoint(x,y),m_coupPrecedent);
                      break;
                      case Rois:
                          listeCoup = deplacements::deplacementRoi(terrain,groupe,QPoint(x,y));
                      break;
                      case Reine:
                          listeCoup = deplacements::deplacementReine(groupe,QPoint(x,y));
                      break;
                      case Fous:
                          listeCoup = deplacements::deplacementFou(groupe,QPoint(x,y));
                      break;
                      case Tour:
                          listeCoup = deplacements::deplacementTour(groupe,QPoint(x,y));
                      break;
                      case Cavalier:
                          listeCoup = deplacements::deplacementCavalier(groupe,QPoint(x,y));
                      break;
                      case Rien:
                          listeCoup = QVector<QPoint>();
                      break;
                  }
                  for (int i = 0; i < listeCoup.count(); i++)
                  { 
                      // on joue le tour
                      int coup_origin_x = m_coupPrecedent->at(0).x();
                      int coup_origin_y = m_coupPrecedent->at(0).y();
                      int coup_dest_x = m_coupPrecedent->at(1).x();
                      int coup_dest_y = m_coupPrecedent->at(1).y();

                      piece tempPiece = terrain[listeCoup.at(i).x()][listeCoup.at(i).y()];
                      int tempGroupe = groupe[listeCoup.at(i).x()][listeCoup.at(i).y()];

                      /////// GERER LA CAPTURE D'UN PION A LA VOLE !!!
                      bool deplacementSpecialFait = false;
                      if(terrain[x][y] == Pion)
                      {
                          if(listeCoup.at(i).y() != y && terrain[listeCoup.at(i).x()][listeCoup.at(i).y()] == Rien )
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

                      if(m_terrain[x][y] == Rois)
                      {
                          if(m_groupe[x][y] == 1)
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

                      terrain[listeCoup.at(i).x()][listeCoup.at(i).y()] = terrain[x][y];
                      terrain[x][y] = Rien;
                      groupe[listeCoup.at(i).x()][listeCoup.at(i).y()] = groupe[x][y];
                      groupe[x][y] = 0;

                      m_coupPrecedent[0][0].setX(x);
                      m_coupPrecedent[0][0].setY(y);
                      m_coupPrecedent[0][1].setX(listeCoup.at(i).x());
                      m_coupPrecedent[0][1].setY(listeCoup.at(i).y());

                      int score = 0;
                      // on relance l'appel

                      if(joueur == 1)
                      {
                          score = min(2,terrain,groupe,profondeur-1,alpha,beta);
                      }
                      else
                      {
                          score = min(1,terrain,groupe,profondeur-1,alpha,beta);
                      }

                      m_coupPrecedent[0][0].setX(coup_origin_x);
                      m_coupPrecedent[0][0].setY(coup_origin_y);
                      m_coupPrecedent[0][1].setX(coup_dest_x);
                      m_coupPrecedent[0][1].setY(coup_dest_y);

                      if(m_terrain[listeCoup.at(i).x()][listeCoup.at(i).y()] == Rois)
                      {
                          if(m_groupe[listeCoup.at(i).x()][listeCoup.at(i).y()] == 1)
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

                      terrain[x][y] = terrain[listeCoup.at(i).x()][listeCoup.at(i).y()];
                      terrain[listeCoup.at(i).x()][listeCoup.at(i).y()] = tempPiece;

                      groupe[x][y] = groupe[listeCoup.at(i).x()][listeCoup.at(i).y()] ;
                      groupe[listeCoup.at(i).x()][listeCoup.at(i).y()] = tempGroupe;

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
 * \brief IA::min
 * La fonction min calcule le minimum de score que peut esperer perdre le joueur
 * en deplacant tout ces pieces, il va renvoyer le deplacement qui lui fera perdre le moins de point.
 * si la profondeur max est atteinte ou que l'on a gagner on renvoie une evaluation des scores du terrain
 * si la profondeur n'est pas atteinte a chaque deplacements de ces pieces il appele a max sur l'autre joueur
 * pour le faire jouer et recuperer le score maximum que peut atteindre l'autre joueur si je jouais cette piece.
 * \param joueur Numero du joueur
 * \param terrain Matrice de pieces de l'echiquier
 * \param groupe Matrice de couleurs des pieces
 * \param profondeur Nombre de coups a prevoir
 * \param alpha Score maximum
 * \param beta Score minimum
 * \return Valeur final du jeu ou valeur gagnant si fin ou minimum calcule
 */
int IA::min(int joueur,piece terrain[8][8],int groupe[8][8],int profondeur,int alpha,int beta)
{
    int retour = 0;

    // /!\ ATTENTION eval IA ne prend pas en compte l'echec et mat vu que celui-ci est verifie dans gagnant jeux
    if(profondeur <= 0 || (retour = gagnantJeux(joueur)) != 0)
    {
        if(profondeur <= 0)
        {
            return evalIA(terrain,groupe);
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
              if(groupe[x][y] == joueur)
              {
                  QVector<QPoint> listeCoup;
                  switch(terrain[x][y])
                  {
                      case Pion:
                          listeCoup = deplacements::deplacementPion(groupe,this->m_terrain,QPoint(x,y),m_coupPrecedent);
                      break;
                      case Rois:
                          listeCoup = deplacements::deplacementRoi(terrain,groupe,QPoint(x,y));
                      break;
                      case Reine:
                          listeCoup = deplacements::deplacementReine(groupe,QPoint(x,y));
                      break;
                      case Fous:
                          listeCoup = deplacements::deplacementFou(groupe,QPoint(x,y));
                      break;
                      case Tour:
                          listeCoup = deplacements::deplacementTour(groupe,QPoint(x,y));
                      break;
                      case Cavalier:
                          listeCoup = deplacements::deplacementCavalier(groupe,QPoint(x,y));
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
                      piece tempPiece = terrain[listeCoup.at(i).x()][listeCoup.at(i).y()];
                      int tempGroupe = groupe[listeCoup.at(i).x()][listeCoup.at(i).y()];

                      ///////// GERER LA CAPTURE D'UN PION A LA VOLE !!!
                      bool deplacementSpecialFait = false;
                      if(terrain[x][y] == Pion)
                      {
                          if(listeCoup.at(i).y() != y && terrain[listeCoup.at(i).x()][listeCoup.at(i).y()] == Rien )
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

                      if(m_terrain[x][y] == Rois)
                      {
                          if(m_groupe[x][y] == 1)
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

                      terrain[listeCoup.at(i).x()][listeCoup.at(i).y()] = terrain[x][y];
                      terrain[x][y] = Rien;
                      groupe[listeCoup.at(i).x()][listeCoup.at(i).y()] = groupe[x][y];
                      groupe[x][y] = 0;

                      int score = 0;
                      m_coupPrecedent[0][0].setX(x);
                      m_coupPrecedent[0][0].setY(y);
                      m_coupPrecedent[0][1].setX(listeCoup.at(i).x());
                      m_coupPrecedent[0][1].setY(listeCoup.at(i).y());
                      // on relance l'appel

                      if(joueur == 1)
                      {
                          score = max(2,terrain,groupe,profondeur-1,alpha,beta);
                      }
                      else
                      {
                          score = max(1,terrain,groupe,profondeur-1,alpha,beta);
                      }


                      m_coupPrecedent[0][0].setX(coup_origin_x);
                      m_coupPrecedent[0][0].setY(coup_origin_y);
                      m_coupPrecedent[0][1].setX(coup_dest_x);
                      m_coupPrecedent[0][1].setY(coup_dest_y);

                      if(m_terrain[listeCoup.at(i).x()][listeCoup.at(i).y()] == Rois)
                      {
                          if(m_groupe[listeCoup.at(i).x()][listeCoup.at(i).y()] == 1)
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

                      terrain[x][y] = terrain[listeCoup.at(i).x()][listeCoup.at(i).y()];
                      terrain[listeCoup.at(i).x()][listeCoup.at(i).y()] = tempPiece;

                      groupe[x][y] = groupe[listeCoup.at(i).x()][listeCoup.at(i).y()] ;
                      groupe[listeCoup.at(i).x()][listeCoup.at(i).y()] = tempGroupe;

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

