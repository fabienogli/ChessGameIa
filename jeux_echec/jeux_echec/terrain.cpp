#include "terrain.h"
#include <QDebug>
#include <QMessageBox>

/**
 * \brief terrain::terrain()
 * Constructeur d'un terrain
 */
terrain::terrain(QWidget *parent) : QWidget(parent)
{
    this->m_interface = (MainWindow *)parent;
    initialisation();
}
/**
 * \brief terrain::~terrain()
 * Destructeur d'un terrain
 */
terrain::~terrain()
{
    delete m_IA;
    delete m_layout;
    delete m_coupPrecedent;
}
/**
 * \brief terrain::reinitialisation
 * Permet de reinitialiser la partie de jeux d'echec
 */
void terrain::reinitialisation()
{
    this->m_interface->resetScore();
    m_tourno = 1;
    m_joueurQuiJoue = 1;
    // initialisation du damage
    for(int i = 0; i < 8; i++)
    {
        for(int y = 0; y < 8 ; y++)
        {
            echiquier[i][y].setPiece(Rien,0);
            m_matricePiece[i][y] = Rien;
            m_matriceGroupe[i][y] = 0;
        }
    }
    //initialisation de la matrice piece
    for(int i = 0; i < 8; i++)
    {
        m_matricePiece[1][i] = Pion;
        echiquier[1][i].setPiece(Pion,1);
        m_matricePiece[6][i] = Pion;
        echiquier[6][i].setPiece(Pion,2);

        m_matriceDeplacement[0][i] = 1;
        m_matriceDeplacement[1][i] = 1;
        m_matriceDeplacement[6][i] = 1;
        m_matriceDeplacement[7][i] = 1;
        //on initialise les groupes(couleur joueur), les deux premieres lignes de chaque partie est a lui
        m_matriceGroupe[0][i] = 1;
        m_matriceGroupe[1][i] = 1;
        m_matriceGroupe[6][i] = 2;
        m_matriceGroupe[7][i] = 2;
    }

    m_matricePiece[0][0] = Tour;
    m_matricePiece[0][1] = Cavalier;
    m_matricePiece[0][2] = Fous;
    m_matricePiece[0][3] = Reine;
    m_matricePiece[0][4] = Rois;
    m_matricePiece[0][5] = Fous;
    m_matricePiece[0][6] = Cavalier;
    m_matricePiece[0][7] = Tour;

    m_matricePiece[7][0] = Tour;
    m_matricePiece[7][1] = Cavalier;
    m_matricePiece[7][2] = Fous;
    m_matricePiece[7][3] = Reine;
    m_matricePiece[7][4] = Rois;
    m_matricePiece[7][5] = Fous;
    m_matricePiece[7][6] = Cavalier;
    m_matricePiece[7][7] = Tour;

    echiquier[0][0].setPiece(Tour,1);
    echiquier[0][1].setPiece(Cavalier,1);
    echiquier[0][2].setPiece(Fous,1);
    echiquier[0][3].setPiece(Reine,1);
    echiquier[0][4].setPiece(Rois,1);
    echiquier[0][5].setPiece(Fous,1);
    echiquier[0][6].setPiece(Cavalier,1);
    echiquier[0][7].setPiece(Tour,1);

    echiquier[7][0].setPiece(Tour,2);
    echiquier[7][1].setPiece(Cavalier,2);
    echiquier[7][2].setPiece(Fous,2);
    echiquier[7][3].setPiece(Reine,2);
    echiquier[7][4].setPiece(Rois,2);
    echiquier[7][5].setPiece(Fous,2);
    echiquier[7][6].setPiece(Cavalier,2);
    echiquier[7][7].setPiece(Tour,2);

    //definition de la position des rois (evite de les chercher plus tard)
    m_Posi_Rois1.setX(0);
    m_Posi_Rois1.setY(4);
    m_Posi_Rois2.setX(7);
    m_Posi_Rois2.setY(4);

    CaseDeplacementPossible =  m_IA->calc_echec_et_mat(m_joueurQuiJoue,QPoint(0,4));
    // si l'ia est activee lors de la reinitialisation de la partie on le fait jouer :)
    if(this->m_joueurIA)
    {
        this->faireJouerIA();
    }
}
/**
 * \brief terrain::initialisation()
 * Permet de d'inititialiser tout le terrain et mettre en memoire le necessaire
 */
void terrain::initialisation()
{
    //initialisation global
    m_nbTourMax = 50;
    m_tourno = 1;
    m_joueurIA = false;
    m_joueurQuiJoue = 1;

    // definition des layouts
    m_layout = new QGridLayout(this);
    m_layout->setSpacing(0);
    this->setLayout(m_layout);

    //on initialise les coups précédents sert pour le pion et certain coups speciaux
    m_coupPrecedent = new QVector<QPoint>();
    m_coupPrecedent->append(QPoint(0,0));
    m_coupPrecedent->append(QPoint(0,0));

    //initialisation de l'IA
    m_IA = new IA(m_matricePiece,m_matriceGroupe,m_matriceDeplacement,m_coupPrecedent);


    /////////////////// INITIALISATION DU DAMAGE /////////////////////////////////////////
    for(int i = 0; i < 8; i++)
    {
        for(int y = 0; y < 8 ; y++)
        {
            // on profite de la boucle pour initialiser les trucs qui peuvent l'etre
            m_matricePiece[i][y] = Rien;
            m_matriceGroupe[i][y] = 0;

            // on initialise l'echiquier qui affiche les pieces
            echiquier[i][y].setTerrain(this);
            echiquier[i][y].setPosition(i,y);
            connect(&(echiquier[i][y]),SIGNAL(clicked(int,int)),this,SLOT(caseCliquer(int,int)));
            m_layout->addWidget(&echiquier[i][y],i,y);

            // association des images aux cases du terrain
            if(i % 2 == 0)
            {
                if(y % 2 == 0)
                {
                    this->echiquier[i][y].setCouleur(1); // 1 noir
                }
                else
                {
                    this->echiquier[i][y].setCouleur(0); // 0 blanc
                }
            }
            else
            {
                if(y % 2 == 0)
                {
                    this->echiquier[i][y].setCouleur(0); // 0 blanc
                }
                else
                {
                    this->echiquier[i][y].setCouleur(1); // 1 noir
                }
            }
        }
    }

    //initialisation de la matrice piece
    for(int i = 0; i < 8; i++)
    {
        m_matricePiece[1][i] = Pion;
        echiquier[1][i].setPiece(Pion,1);
        m_matricePiece[6][i] = Pion;
        echiquier[6][i].setPiece(Pion,2);

        //on initialise les groupes (couleur des joueurs), les deux premieres lignes de chaque partie est a lui
        m_matriceDeplacement[0][i] = 1;
        m_matriceDeplacement[1][i] = 1;
        m_matriceDeplacement[6][i] = 1;
        m_matriceDeplacement[7][i] = 1;
        m_matriceGroupe[0][i] = 1;
        m_matriceGroupe[1][i] = 1;
        m_matriceGroupe[6][i] = 2;
        m_matriceGroupe[7][i] = 2;
    }

    m_matricePiece[0][0] = Tour;
    m_matricePiece[0][1] = Cavalier;
    m_matricePiece[0][2] = Fous;
    m_matricePiece[0][3] = Reine;
    m_matricePiece[0][4] = Rois;
    m_matricePiece[0][5] = Fous;
    m_matricePiece[0][6] = Cavalier;
    m_matricePiece[0][7] = Tour;

    m_matricePiece[7][0] = Tour;
    m_matricePiece[7][1] = Cavalier;
    m_matricePiece[7][2] = Fous;
    m_matricePiece[7][3] = Reine;
    m_matricePiece[7][4] = Rois;
    m_matricePiece[7][5] = Fous;
    m_matricePiece[7][6] = Cavalier;
    m_matricePiece[7][7] = Tour;

    echiquier[0][0].setPiece(Tour,1);
    echiquier[0][1].setPiece(Cavalier,1);
    echiquier[0][2].setPiece(Fous,1);
    echiquier[0][3].setPiece(Reine,1);
    echiquier[0][4].setPiece(Rois,1);

    echiquier[0][5].setPiece(Fous,1);
    echiquier[0][6].setPiece(Cavalier,1);
    echiquier[0][7].setPiece(Tour,1);

    echiquier[7][0].setPiece(Tour,2);
    echiquier[7][1].setPiece(Cavalier,2);
    echiquier[7][2].setPiece(Fous,2);
    echiquier[7][3].setPiece(Reine,2);
    echiquier[7][4].setPiece(Rois,2);

    echiquier[7][5].setPiece(Fous,2);
    echiquier[7][6].setPiece(Cavalier,2);
    echiquier[7][7].setPiece(Tour,2);

    //definition de la position des rois (evite de les chercher plus tard)
    m_Posi_Rois1.setX(0);
    m_Posi_Rois1.setY(4);
    m_Posi_Rois2.setX(7);
    m_Posi_Rois2.setY(4);

    // on met les cases sur lesquelles on peut se deplacer en memoire
    CaseDeplacementPossible =  m_IA->calc_echec_et_mat(m_joueurQuiJoue,QPoint(0,4));


}
/**
 * \brief terrain::getNbTourMax()
 * Permet de recuperer le nombre de tour maximum de la partie d'echec.
 * \return Nombre de tours maximum.
 */
unsigned int terrain::getNbTourMax()
{
    return this->m_nbTourMax;
}
/**
 * \brief terrain::setNbTourMax
 * Permet de definir le nombre de tour maximum de la partie d'echec.
 * \param[in] nb Nombre de tours maximum.
 */
void terrain::setNbTourMax(unsigned int nb)
{
    this->m_nbTourMax = nb;
}
/**
 * \brief terrain::rafraichirCase()
 * Permet de rafraichir la case aux coordonnees spécifier.
 * Elle permet que lors du deplacement d'une piece celui-ci s'affiche sur le terrain.
 * Cette fonction utilise la matrice de Piece et de groupe pour le rafraichisement
 * \param[in] x Coordonner x.
 * \param[in] x Coordonner y.
 */
void terrain::rafraichirCase(int x,int y)
{
    echiquier[x][y].setPiece(m_matricePiece[x][y],m_matriceGroupe[x][y]);
}

/**
 * \brief terrain::getIAActiver()
 * Permet de savoir si l'IA est activee ou pas
 * \return Renvoie true si l'IA  est activee
 */
bool terrain::getIAActiver()
{
    return this->m_joueurIA;
}
/**
 * \brief terrain::getIADifficulter()
 * Permet de savoir quelle est la difficulte de l'IA
 * \return Renvoie le niveau de difficulte 1 facile 2 moyen 3 difficile
 */
int terrain::getIADifficulter()
{
    return m_IA->getDifficulter();
}
/**
 * \brief terrain::setIA()
 * Permet de rendre actif l'IA sur le terrain et de définir son niveau de difficulte
 * Si c'est a l'IA de jouer alors elle jouera
 * \param[in] actif Permet d'activer/desactiver L'IA.
 * \param[in] dificulte Permet de definir la difficultee de l'IA.
 */
void terrain::setIA(bool actif ,int dificulte)
{
    if(actif)
    {
        this->m_joueurIA = true;
        m_IA->setDifficulter(dificulte);
        // CREATION DE L'IA ICI
        if(m_joueurQuiJoue == 1 )
        {
            this->faireJouerIA();
        }
    }
    else
    {
        this->m_joueurIA = false;
    }
}
/**
 * \brief terrain::faireJouerIA()
 * Permet de faire jouer L'IA sur le terrain, elle va simuler le meilleur deplacement
 * en fonction du niveau de difficulte puis elle va choisir parmi les meilleurs solutions
 * une au hasard et va se deplacer sur le terrain.
 */
void terrain::faireJouerIA()
{

    QVector<QPoint> dep = m_IA->jouer(1);
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

    if(m_matricePiece[dep.at(pion_ori).x()][dep.at(pion_ori).y()] == Pion)
    {
        if(dep.at(pion_dest).y() != dep.at(pion_ori).y() && m_matricePiece[dep.at(pion_dest).x()][dep.at(pion_dest).y()] == Rien )
        {
            m_interface->addtoScore(Pion, 1);
            m_matricePiece[dep.at(pion_dest).x()][dep.at(pion_dest).y()-1] = Rien;
            m_matriceGroupe[dep.at(pion_dest).x()][dep.at(pion_dest).y()-1] = 0;
            echiquier[dep.at(pion_dest).x()][dep.at(pion_dest).y()-1].setPiece(Rien,0);
        }
    }
    if(m_matricePiece[dep.at(pion_ori).x()][dep.at(pion_ori).y()] == Rois)
    {
        m_Posi_Rois1.setX(dep.at(pion_dest).x());
        m_Posi_Rois1.setY(dep.at(pion_dest).y());
    }

    m_coupPrecedent[0][0].setX(dep.at(pion_ori).x());
    m_coupPrecedent[0][0].setY(dep.at(pion_ori).y());
    m_coupPrecedent[0][1].setX(dep.at(pion_dest).x());
    m_coupPrecedent[0][1].setY(dep.at(pion_dest).y());

    if(m_matricePiece[dep.at(pion_dest).x()][dep.at(pion_dest).y()] != Rien)
    {
        m_interface->addtoScore(m_matricePiece[dep.at(pion_dest).x()][dep.at(pion_dest).y()], 1);
    }
    m_matriceDeplacement[dep.at(pion_ori).x()][dep.at(pion_ori).y()] = 0;
    m_matricePiece[dep.at(pion_dest).x()][dep.at(pion_dest).y()] = m_matricePiece[dep.at(pion_ori).x()][dep.at(pion_ori).y()];
    m_matricePiece[dep.at(pion_ori).x()][dep.at(pion_ori).y()] = Rien;

    m_matriceGroupe[dep.at(pion_dest).x()][dep.at(pion_dest).y()] = m_matriceGroupe[dep.at(pion_ori).x()][dep.at(pion_ori).y()];
    m_matriceGroupe[dep.at(pion_ori).x()][dep.at(pion_ori).y()] = 0;

    this->deselectAllCaseTerain();
    echiquier[dep.at(pion_dest).x()][dep.at(pion_dest).y()].setPiece(m_matricePiece[dep.at(pion_dest).x()][dep.at(pion_dest).y()],m_matriceGroupe[dep.at(pion_dest).x()][dep.at(pion_dest).y()]);
    echiquier[dep.at(pion_ori).x()][dep.at(pion_ori).y()].setPiece(Rien,0);
    m_pointSelectionner.clear();

    m_joueurQuiJoue = 2;
    CaseDeplacementPossible =  m_IA->calc_echec_et_mat(m_joueurQuiJoue,m_Posi_Rois2);
    if(CaseDeplacementPossible.count() == 0)
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
    }
    // augmentation du nombre de tours jouer
    m_tourno++;

    //Detection de fin de partie par manque de nombre de tours
    if(m_nbTourMax <= m_tourno)
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
    }

}
/**
 * \brief terrain::caseCliquer()
 * Ce Slot est appelle quand une des cases du terrain est cliquee
 * Il fait le traitement relatif a cette case :
 * -si c'est la premiere selection :
 * * Illumination des cases de deplacement possible
 * -si c'est une autre piece qui a rien a voir avec la piece precedemment selectionnee et pas un deplacement :
 * * Deselection de toute les cases deja selectionnees
 * * Illumination des nouvelles cases de deplacement possible
 * -si c'est une des cases ou ma piece peut se deplacer:
 * * Deplacement de la piece
 * * Deselection de toutes les cases selectionees
 * * Test d'echec et mat
 * * Passage au joueur suivant
 * \param[in] x Coordonnee x de la case cliquee.
 * \param[in] y Coordonnee y de la case cliquee.
 */
void terrain::caseCliquer(int x, int y)
{
    // On verifie si la case cliquee fait partie des deplacements possibles de la piece precedement selectionnee
    bool nouvelle_case = true;
    for(int i = 0; i < m_pointSelectionner.count(); i++ )
    {
        if(m_pointSelectionner.at(i).x() == x && m_pointSelectionner.at(i).y() == y)
        {
            nouvelle_case = false;
        }
    }

    if(nouvelle_case) // si on a selectionne une autre piece ou une premiere piece
    {

        if(m_matriceGroupe[x][y] == m_joueurQuiJoue)
        {
            // on efface les points selectionnees precedement
            m_pointSelectionner.clear();
            this->deselectAllCaseTerain();

            //on selectionne le point que l'on vient de cliquer
            echiquier[x][y].select();
            m_origineSelectionner = QPoint(x,y);

            // on charge en memoire les deplacements posssibles pour la piece cliquee
            //et on les illumine (halo jaune)
            for(int i = 0; i < (CaseDeplacementPossible.count()/2); i++ )
            {
                if(CaseDeplacementPossible.at(i*2).x() == x && CaseDeplacementPossible.at(i*2).y() == y)
                {
                    m_pointSelectionner.append(QPoint(CaseDeplacementPossible.at((i*2)+1).x(),CaseDeplacementPossible.at((i*2)+1).y()));
                    echiquier[CaseDeplacementPossible.at((i*2)+1).x()][CaseDeplacementPossible.at((i*2)+1).y()].select();
                }
            }
        }
    }
    else// si on a confirme le choix de la piece selectionne
    {
        if(m_joueurQuiJoue == 1 )
        {
            // si c'est un pion qu'on deplace et que c'est un coup special (on fait un traitement special)
            if(m_matricePiece[m_origineSelectionner.x()][m_origineSelectionner.y()] == Pion)
            {
                if(y != m_origineSelectionner.y() && m_matricePiece[x][y] == Rien )
                {
                    // on efface le pion qui est a l'ancienne case de mon pion
                    m_interface->addtoScore(Pion, 1);
                    m_interface->addtoScore(Pion, 1);
                    m_matricePiece[x-1][y] = Rien;
                    m_matriceGroupe[x-1][y] = 0;
                    echiquier[x-1][y].setPiece(Rien,0);
                }

            }
            if(m_matricePiece[x][y] != Rien)
            {
                 m_interface->addtoScore(m_matricePiece[x][y], 1);
            }

            //Si c'est le roi qui joue on met a jour sa position (ca evite de le chercher tout le temps qu'on veut savoir si il est en echec)
            if(m_matricePiece[m_origineSelectionner.x()][m_origineSelectionner.y()] == Rois)
            {
                m_Posi_Rois1.setX(x);
                m_Posi_Rois1.setY(y);
            }
            // on definit le prochain joueur qui joue
            m_joueurQuiJoue = 2;
        }
        else
        {
             // si c'est un pion qu'on deplace et que c'est un coup special (on fait un traitement special)
            if(m_matricePiece[m_origineSelectionner.x()][m_origineSelectionner.y()] == Pion)
            {
                // on efface l'ancien pion
                if(y != m_origineSelectionner.y() && m_matricePiece[x][y] == Rien )
                {
                    m_interface->addtoScore(Pion, 2);
                    m_matricePiece[x+1][y] = Rien;
                    m_matriceGroupe[x+1][y] = 0;
                    echiquier[x+1][y].setPiece(Rien,0);
                }
            }
            if(m_matricePiece[x][y] != Rien)
            {
                 m_interface->addtoScore(m_matricePiece[x][y], 2);
            }            if(m_matricePiece[m_origineSelectionner.x()][m_origineSelectionner.y()] == Rois)
            {
                m_Posi_Rois2.setX(x);
                m_Posi_Rois2.setY(y);
            }
            // on definit le prochain joueur qui joue
            m_joueurQuiJoue = 1;
        }

        // si le pion a atteint la fin de la carte , Promotion ! (bien jouer soldat !)
        if(m_matricePiece[m_origineSelectionner.x()][m_origineSelectionner.y()] == Pion && ((x == 7 && m_joueurQuiJoue == 2) || (x == 0 && m_joueurQuiJoue == 1)))
        {
            QMessageBox msgBox;
            msgBox.setText("En quelle piece le pion doit-il etre promu ? ");
            QPushButton *dame = msgBox.addButton("Dame", QMessageBox::ActionRole);
            QPushButton *tour = msgBox.addButton("Tour", QMessageBox::ActionRole);
            QPushButton *fou = msgBox.addButton("Fous", QMessageBox::ActionRole);
            QPushButton *cavalier = msgBox.addButton("Cavalier",QMessageBox::ActionRole);

            msgBox.exec();

            if ((QPushButton *)msgBox.clickedButton() == dame) {
                m_matricePiece[m_origineSelectionner.x()][m_origineSelectionner.y()] = Reine;
            } else if ((QPushButton *)msgBox.clickedButton() == tour) {
                m_matricePiece[m_origineSelectionner.x()][m_origineSelectionner.y()] = Tour;
            }
            else if ((QPushButton *)msgBox.clickedButton() == fou) {
                m_matricePiece[m_origineSelectionner.x()][m_origineSelectionner.y()] = Fous;
            }
            else if((QPushButton *)msgBox.clickedButton() == cavalier){
                m_matricePiece[m_origineSelectionner.x()][m_origineSelectionner.y()] = Cavalier;
           }
        }

        // on teste si on joue un rogue
        if(m_matricePiece[m_origineSelectionner.x()][m_origineSelectionner.y()] == Rois)
        {
                            ///////////TEST DU ROGUE//////////////////
            if(m_origineSelectionner.y() - y != 1 && m_origineSelectionner.y() - y != -1 && m_origineSelectionner.y() - y != 0)
            {
                if(m_origineSelectionner.y() < y)
                { // Petit rogue
                    m_matricePiece[x][5] = m_matricePiece[x][7];
                    m_matricePiece[x][7] = Rien;
                    m_matriceGroupe[x][5] = m_matriceGroupe[x][7];
                    m_matriceGroupe[x][7] = 0;
                    echiquier[x][7].setPiece(Rien,0);
                    echiquier[x][5].setPiece(m_matricePiece[x][5],m_matriceGroupe[x][5]);
                }
                else
                {
                    m_matricePiece[x][3] = m_matricePiece[x][0];
                    m_matricePiece[x][0] = Rien;
                    m_matriceGroupe[x][3] = m_matriceGroupe[x][0];
                    m_matriceGroupe[x][0] = 0;
                    echiquier[x][0].setPiece(Rien,0);
                    echiquier[x][3].setPiece(m_matricePiece[x][3],m_matriceGroupe[x][3]);
                }

            }
        }

        //Mise a jour du coup précedent
        m_coupPrecedent[0][0].setX(m_origineSelectionner.x());
        m_coupPrecedent[0][0].setY(m_origineSelectionner.y());
        m_coupPrecedent[0][1].setX(x);
        m_coupPrecedent[0][1].setY(y);


        // on deplace le pion sur la matrice piece et groupe
        m_matriceDeplacement[m_origineSelectionner.x()][m_origineSelectionner.y()] = 0;
        m_matricePiece[x][y] = m_matricePiece[m_origineSelectionner.x()][m_origineSelectionner.y()];
        m_matricePiece[m_origineSelectionner.x()][m_origineSelectionner.y()] = Rien;

        m_matriceGroupe[x][y] = m_matriceGroupe[m_origineSelectionner.x()][m_origineSelectionner.y()];
        m_matriceGroupe[m_origineSelectionner.x()][m_origineSelectionner.y()] = 0;

        //on deselectionne toutes les cases du terrain
        this->deselectAllCaseTerain();

        // on met a jour les deux cases qui sont affectees par le deplacement
        echiquier[x][y].setPiece(m_matricePiece[x][y],m_matriceGroupe[x][y]);
        echiquier[m_origineSelectionner.x()][m_origineSelectionner.y()].setPiece(Rien,0);

        // en fin on efface
        m_pointSelectionner.clear();


        // on va calculer les deplacements qu'il est possible de faire en fonction du joueur qui va jouer maintenant
        if(m_joueurQuiJoue == 1)
        {
            CaseDeplacementPossible =  m_IA->calc_echec_et_mat(m_joueurQuiJoue,m_Posi_Rois1);
        }
        else
        {
            CaseDeplacementPossible =  m_IA->calc_echec_et_mat(m_joueurQuiJoue,m_Posi_Rois2);
        }

        // si aucun deplacement possible ... c'est qu'on est en echec et mat ! la joueur qui joue a perdu
        if(CaseDeplacementPossible.count() == 0)
        {
            int ret = QMessageBox::question(this,"Bravo Partie gagnier","Le joueur "+QString(m_matriceGroupe[x][y])+" a gagnier la partie ! \nVoulez vous rejouer ?",QMessageBox::Yes | QMessageBox::No);
            if(ret == QMessageBox::Yes)
            {
                this->reinitialisation();
            }
            else
            {
                this->destroyed();
            }
        }

        // augmentation du nombre de tour passe
        m_tourno++;

        //Detection de fin de partie par manque de nombre de tour
        if(m_nbTourMax <= m_tourno)
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
        }


        // le joueur a fini : on fait jouer l'IA
        if(this->m_joueurIA)
        {
            this->faireJouerIA();
        }
    }
}

/**
 * \brief terrain::getCaseTerrain()
 * Permet de recuperer un pointeur vers une case du terrain
 * \param[in] x Coordonnee x de la case a récuperer.
 * \param[in] y Coordonnee y de la case a récuperer.
 * \return[in] pointeur vers la case.
 */
case_terrain *terrain::getCaseTerrain(int x,int y)
{
    return &(echiquier[x][y]);
}
/**
 * \brief terrain::deselectAllCaseTerain()
 * Permet de deselectionner toutes les cases du terrain
 */
void terrain::deselectAllCaseTerain()
{
    for(int x = 0; x < 8; x++)
    {
        for(int y = 0; y < 8 ; y++)
        {
            echiquier[x][y].deselect();
        }
    }
}

/**
 * @brief terrain::loadFile
 * Charge une sauvegarde à la place d'une partie en cours
 * @param fichier Nom de la sauvegarde a charger
 */
void terrain::loadFile(QString fichier)
{
    QFile file(fichier);
    if (!file.open(QIODevice::ReadOnly))
        return;

    QDataStream in(&file);
    int piece;
    int nb_pionPrisNoir = 8;
    int nb_tourPrisNoir = 2;
    int nb_fouPrisNoir = 2;
    int nb_cavalierPrisNoir = 2;
    int nb_reinePrisNoir = 1;

    int nb_pionPrisBlanc = 8;
    int nb_tourPrisBlanc = 2;
    int nb_fouPrisBlanc = 2;
    int nb_cavalierPrisBlanc =2;
    int nb_reinePrisBlanc = 1;

    for(int x = 0; x < 8; x++)
    {
        for(int y = 0; y < 8 ; y++)
        {
            in >> m_matriceGroupe[x][y];
            in >> piece;
            switch(piece)
            {
                case 1:
                    m_matricePiece[x][y] = Pion;
                    if(m_matriceGroupe[x][y] == 1){nb_pionPrisNoir--;}
                    else {nb_pionPrisBlanc--;}
                break;
                case 2:
                    m_matricePiece[x][y] =  Rois;
                break;
                case 3:
                    m_matricePiece[x][y] = Reine;
                    if(m_matriceGroupe[x][y] == 1){nb_reinePrisNoir--;}
                    else {nb_reinePrisBlanc--;}
                break;
                case 4:
                    m_matricePiece[x][y] = Fous;
                    if(m_matriceGroupe[x][y] == 1){nb_fouPrisNoir--;}
                    else {nb_fouPrisBlanc--;}
                break;
                case 5:
                    m_matricePiece[x][y] = Tour;
                    if(m_matriceGroupe[x][y] == 1){nb_tourPrisNoir--;}
                    else {nb_tourPrisBlanc--;}
                break;
                case 6:
                    m_matricePiece[x][y] = Cavalier;
                    if(m_matriceGroupe[x][y] == 1){nb_cavalierPrisNoir--;}
                    else {nb_cavalierPrisBlanc--;}
                break;
                case 7:
                    m_matricePiece[x][y] = Rien;
                break;
            }

            in >> m_matriceDeplacement[x][y];

            echiquier[x][y].setPiece(m_matricePiece[x][y],m_matriceGroupe[x][y]);
            if(m_matricePiece[x][y] == Rois)
            {
                if(m_matriceGroupe[x][y] == 1)
                {
                    m_Posi_Rois1.setX(x);
                    m_Posi_Rois1.setY(y);
                }
                else
                {
                    m_Posi_Rois2.setX(x);
                    m_Posi_Rois2.setY(y);
                }
            }

        }
    }

    in >> m_joueurQuiJoue;
    in >> m_nbTourMax;
    in >> m_tourno;
    in >> m_joueurIA;
    int temps = 0;
    in >> temps;
    this->m_interface->setTempsrestant(temps);


    this->m_interface->setScore(Pion,nb_pionPrisNoir, 1);
    this->m_interface->setScore(Tour,nb_tourPrisNoir, 1);
    this->m_interface->setScore(Fous,nb_fouPrisNoir, 1);
    this->m_interface->setScore(Cavalier,nb_cavalierPrisNoir, 1);
    this->m_interface->setScore(Reine,nb_reinePrisNoir, 1);

    this->m_interface->setScore(Pion,nb_pionPrisBlanc, 1);
    this->m_interface->setScore(Tour,nb_tourPrisBlanc, 1);
    this->m_interface->setScore(Fous,nb_fouPrisBlanc, 1);
    this->m_interface->setScore(Cavalier,nb_cavalierPrisBlanc, 1);
    this->m_interface->setScore(Reine,nb_reinePrisBlanc, 1);


    if(m_joueurIA == true && m_joueurQuiJoue == 1)
    {
        file.close();
        this->faireJouerIA();
        return;
    }
    if(m_joueurQuiJoue == 1)
    {
        // on met les cases sur lesquelles on peut se deplacer en memoire
        CaseDeplacementPossible =  m_IA->calc_echec_et_mat(m_joueurQuiJoue,m_Posi_Rois1);
    }
    else
    {
        // on met les cases sur lesquelles on peut se deplacer en memoire
        CaseDeplacementPossible =  m_IA->calc_echec_et_mat(m_joueurQuiJoue,m_Posi_Rois2);
    }
    file.close();
}
/**
 * \brief terrain::saveToFile
 * Permet de sauvegarder la partie en cours dans un fichier
 * \param fichier Nom du fichier sous lequel sera la sauvegarde
 */
void terrain::saveToFile(QString fichier)
{
    QFile file(fichier);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
        return;
    QDataStream out(&file);

    for(int x = 0; x < 8; x++)
    {
        for(int y = 0; y < 8 ; y++)
        {
            out << m_matriceGroupe[x][y];
            switch(m_matricePiece[x][y])
            {
                case Pion:
                    out << 1;
                break;
                case Rois:
                    out << 2;
                break;
                case Reine:
                    out << 3;
                break;
                case Fous:
                    out << 4;
                break;
                case Tour:
                    out << 5;
                break;
                case Cavalier:
                    out << 6;
                break;
                case Rien:
                    out << 7;
                break;
            }
            out << m_matriceDeplacement[x][y];
        }
    }

    out << m_joueurQuiJoue;
    out << m_nbTourMax;
    out << m_tourno;
    out << m_joueurIA;
    out << this->m_interface->getTempsrestant();
    file.close();
}

