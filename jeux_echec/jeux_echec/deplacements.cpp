#include "deplacements.h"
#include <QDebug>

/**
 * \brief deplacements::deplacementRoi()
 * Permet de recuperer les coordonnees des cases ou le roi peut se deplacer.
 * Il va prendre a partir de la matrice groupe dans quelle equipe est le roi puis va tester tout les deplacements possibles
 * Si il rencontre une piece de son equipe il ne selectionne pas la case
 * Si il rencontre une piece adverse il verifie si la case est en echec (des fois qu'un autre pion pourai la prendre) puis selectionne la case
 * Si il rencontre un espace (case vide) il verifie que ca ne le met pas en echec et ajoute la case
 * \param[in] terrain Matrice des pieces du terrain.
 * \param[in] matriceGroupe Matrice corespondant a la couleur des pieces.
 * \param[in] cas Coordonnees du roi a calculer.
 * \return Un tableau de coordonnees
 */
QVector<QPoint> deplacements::deplacementRoi(const piece terrain[8][8],const int matriceGroupe[8][8], const QPoint& cas)
{
    QVector<QPoint> resultat;
    for(int x = -1; x < 2 ; x++) // on fait les 3 zones de guauche a droite
    {
        if((cas.x()+x) < 8 && (cas.x()+x) >= 0) // si on depasse le x a droite ou a guauche on regarde pas le y
        {
            for(int y = -1; y < 2; y++) // pour chaque x on fait les 3 valeurs de y possible
            {
                // si on sort de la carte ou que c'est notre case (notre piece) on l'ajoute pas
                if((cas.y()+y) < 8 && (cas.y()+y) >= 0 && (cas.y() != (cas.y()+y) || cas.x() != (cas.x()+x)))
                {
                    if(matriceGroupe[cas.x()+x][cas.y()+y] != matriceGroupe[cas.x()][cas.y()] )
                    {
                        if(x != 0 || y != 0)
                        {
                          if(estEnEchec(terrain,matriceGroupe,matriceGroupe[cas.x()][cas.y()], QPoint(cas.x()+x, (cas.y()+y)),&cas) == false)
                          {
                                resultat.append(QPoint(cas.x()+x, (cas.y()+y)));
                          }
                        }
                    }
                }
            }
        }
    }
    return resultat;
}

/**
 * \brief deplacements::petitRoguePossible()
 * Permet de savoir si on peut faire le petit rogue
 * \param[in] joueur numero du joueur que l'on veut verifier
 * \param[in] matriceGroupe Matrice correspondant a la couleur des pieces.
 * \param[in] matriceDeplacement Matrice de deplacement pour savoir si un pion a deja été bouge ou pas.
 * \param[in] matricePiece Matrice corespondant au pieces sur l'echiquier.
 * \return True si on peut faire le grand rogue, sinon False
 */
bool deplacements::petitRoguePossible(int joueur,const int matriceGroupe[8][8],const int matriceDeplacement[8][8],const piece matricePiece[8][8])
{
    if(joueur == 1) // joueur noir
    {
        // si le roi et la tour n'ont pas bouge
        if(matriceDeplacement[0][4] == 1 && matriceDeplacement[0][7] == 1)
        {
            for(int i = 4 ; i < 6 ; i++)
            {
                // si on a une piece sur le chemin
                if(matriceGroupe[0][i] != 0 && i != 4)
                {
                    return false;
                }
                if(estEnEchec(matricePiece,matriceGroupe,joueur, QPoint(0,i)))
                {
                    return false;
                }
            }
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        // si le roi et la tour n'ont pas bouge
        if(matriceDeplacement[7][4] == 1 && matriceDeplacement[7][7] == 1)
        {
            for(int i = 4 ; i < 6 ; i++)
            {
                // si on a une piece sur le chemin
                if(matriceGroupe[7][i] != 0 && i != 4)
                {
                    return false;
                }
                if(estEnEchec(matricePiece,matriceGroupe,joueur, QPoint(7,i)))
                {
                    return false;
                }
            }
            return true;
        }
        else
        {
            return false;
        }
    }
}
/**
 * \brief deplacements::grandRoguePossible()
 * Permet de savoir si on peut faire le grand rogue
 * \param[in] joueur Numero du joueur que l'on veut verifier
 * \param[in] matriceGroupe Matrice corespondant a la couleur des pieces.
 * \param[in] matriceDeplacement Matrice de deplacement pour savoir si une piece a deja été bouger ou pas.
 * \param[in] matricePiece Matrice corespondant au type des pieces.
 * \return True si on peut faire le grand rogue, sinon False
 */
bool deplacements::grandRoguePossible(int joueur,const int matriceGroupe[8][8],const int matriceDeplacement[8][8],const piece matricePiece[8][8])
{
    if(joueur == 1) // joueur noir
    {
        // si le roi et la tour n'ont pas bouge
        if(matriceDeplacement[0][4] == 1 && matriceDeplacement[0][0] == 1)
        {
            for(int i = 4 ; i > 2 ; i--)
            {
                // si on a une piece sur le chemin
                if(matriceGroupe[0][i] != 0 && i != 4)
                {
                    return false;
                }
                if(estEnEchec(matricePiece,matriceGroupe,joueur, QPoint(0,i)))
                {
                    return false;
                }
            }
            if(matriceGroupe[0][1] != 0)
            {
                return false;
            }
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        // si le roi et la tour n'ont pas bouge
        if(matriceDeplacement[7][4] == 1 && matriceDeplacement[7][0] == 1)
        {
            for(int i = 4 ; i > 2 ; i--)
            {
                // si on a une piece sur le chemin
                if(matriceGroupe[7][i] != 0 && i != 4)
                {
                    return false;
                }
                if(estEnEchec(matricePiece,matriceGroupe,joueur, QPoint(7,i)))
                {
                    return false;
                }
            }
            if(matriceGroupe[7][1] != 0)
            {
                return false;
            }
            return true;
        }
        else
        {
            return false;
        }
    }
}

/**
 * \brief deplacements::deplacementReine()
 * Permet de recuperer les coordonnees des cases ou la reine peut se deplacer.
 * La fonction va prendre a partir de la matrice groupe dans quelle equipe est la reine puis va tester tous les deplacements possibles
 * Si la reine rencontre une piece de son equipe il ne selectionne pas la case et s'arrete
 * Si la reine rencontre une piece adverse il ajoute la case mais ne continue pas apres
 * Si la reine rencontre un espace (case vide) la fonction ajoute la case et continue a la prochaine case
 * \param[in] matriceGroupe Matrice correspondant a la couleur des pieces.
 * \param[in] cas Coordonnees de la reine a calculer.
 * \return Un tableau de coordonnees
 */
QVector<QPoint> deplacements::deplacementReine(const int matriceGroupe[8][8], const QPoint& cas)
{
    QVector<QPoint> resultat = deplacements::deplacementFou(matriceGroupe, cas);
    QVector<QPoint> var = deplacements::deplacementTour(matriceGroupe, cas);

    for(int i = 0; i < var.count(); i++)
    {
        resultat.append(var.at(i));
    }
    return resultat;
}

/**
 * \brief deplacements::deplacementFou()
 * Permet de recuperer les coordonnees des cases ou le fou peut se deplacer.
 * La fonction va prendre a partir de la matrice groupe dans quelle equipe est le fous puis va tester tous les deplacement possibles
 * Si le fou rencontre une piece de son equipe il ne selectionne pas la case et s'arrete
 * Si le fou rencontre une piece adverse il ajoute la case et s'arrete
 * Si le fou rencontre un espace (case vide) la fonction ajoute la case et continue a la prochaine case
 * \param[in] matriceGroupe Matrice correspondant a la couleur des pieces.
 * \param[in] cas Coordonnees du fou a calculer.
 * \return Un tableau de coordonnees
 */
QVector<QPoint> deplacements::deplacementFou(const int matriceGroupe[8][8], const QPoint& cas){
    /* peut se deplacer en diagonale tant que !fin de terrain ou !piece */
    QVector<QPoint> resultat;

    int x = cas.x();
    int y = cas.y();

    while (x > 0 && y > 0)
    {
        x--;
        y--;
        if(matriceGroupe[x][y] != matriceGroupe[cas.x()][cas.y()] )
        {
            resultat.append(QPoint(x, y));
        }
        if(matriceGroupe[x][y] != 0) // on a rencontre un obstacle ami ou ennemis
        {
            x = 0; // on stoppe la boucle
        }
    }
    x = cas.x();
    y = cas.y();
    while (x != 7 && y != 7)
    {
        x++;
        y++;
        if(matriceGroupe[x][y] != matriceGroupe[cas.x()][cas.y()] )
        {
            resultat.append(QPoint(x, y));
        }
        if(matriceGroupe[x][y] != 0) // on a rencontre un obstacle ami ou ennemis
        {
            x = 7; // on stoppe la boucle
        }
    }
    x = cas.x();
    y = cas.y();
    while (x > 0 && y < 7)
    {
        x--;
        y++;
        if(matriceGroupe[x][y] != matriceGroupe[cas.x()][cas.y()] )
        {
            resultat.append(QPoint(x, y));
        }
        if(matriceGroupe[x][y] != 0) // on a rencontre un obstacle ami ou ennemi
        {
            x = 0; // on stoppe la boucle
        }
    }
    x = cas.x();
    y = cas.y();
    while (x < 7 && y > 0)
    {
        x++;
        y--;
        if(matriceGroupe[x][y] != matriceGroupe[cas.x()][cas.y()] )
        {
            resultat.append(QPoint(x, y));
        }
        if(matriceGroupe[x][y] != 0) // on a rencontre un obstacle ami ou ennemi
        {
            x = 7; // on stoppe la boucle
        }
    }
    return resultat;
}
/**
 * \brief deplacements::deplacementCavalier()
 * Permet de recuperer les coordonnees des cases ou le Cavalier peut se deplacer.
 * La fonction va prendre a partir de la matrice groupe dans quelle equipe est le Cavalier puis va tester tous les deplacements possibles
 * Si le Cavalier rencontre une piece de son equipe il ne selectionne pas la case
 * Si le Cavalier rencontre une piece adverse ou un espace (case vide) il ajoute la case
 * \param[in] matriceGroupe Matrice correspondant a la couleur des pieces.
 * \param[in] cas Coordonnees du Cavalier a calculer.
 * \return Un tableau de coordonnees
 */
QVector<QPoint> deplacements::deplacementCavalier(const int matriceGroupe[8][8], const QPoint& cas){
    QVector<QPoint> resultat;
    /////////// HAUT
    if(cas.y()>= 1){

        if(cas.x()>=2)
        {
            if(matriceGroupe[cas.x()-2][cas.y()-1] != matriceGroupe[cas.x()][cas.y()] )
                // sinon est pas sur une piece aliee mais une piece adverse ou un Rien
            {
                resultat.append(QPoint(cas.x()-2, (cas.y()-1)));
            }
        }
        if(cas.x() <= 5)
        {
            if(matriceGroupe[cas.x()+2][cas.y()-1] != matriceGroupe[cas.x()][cas.y()] )
            {
                resultat.append(QPoint(cas.x()+2, (cas.y()-1)));
            }
        }
    }/////////BAS
    if(cas.y()<=6)
    {
        if(cas.x()>=2)
        {
            if(matriceGroupe[cas.x()-2][cas.y()+1] != matriceGroupe[cas.x()][cas.y()] )
            {
                resultat.append(QPoint(cas.x()-2, (cas.y()+1)));
            }
        }
        if(cas.x() <= 5)
        {
            if(matriceGroupe[cas.x()+2][cas.y()+1] != matriceGroupe[cas.x()][cas.y()] )
            {
                resultat.append(QPoint(cas.x()+2, (cas.y()+1)));
            }
        }
    }/////// GUAUCHE
    if(cas.y()>= 2){

        if(cas.x()>=1)
        {
            if(matriceGroupe[cas.x()-1][cas.y()-2] != matriceGroupe[cas.x()][cas.y()] )
            {
                resultat.append(QPoint(cas.x()-1, (cas.y()-2)));
            }
        }
        if(cas.x() <= 6)
        {
            if(matriceGroupe[cas.x()+1][cas.y()-2] != matriceGroupe[cas.x()][cas.y()] )
            {
                resultat.append(QPoint(cas.x()+1, (cas.y()-2)));
            }
        }
    }/////////DROITE
    if(cas.y()<=5)
    {
        if(cas.x()>=1)
        {
            if(matriceGroupe[cas.x()-1][cas.y()+2] != matriceGroupe[cas.x()][cas.y()] )
            {
                resultat.append(QPoint(cas.x()-1, (cas.y()+2)));
            }
        }
        if(cas.x() <= 6)
        {
            if(matriceGroupe[cas.x()+1][cas.y()+2] != matriceGroupe[cas.x()][cas.y()] )
            {
                resultat.append(QPoint(cas.x()+1, (cas.y()+2)));
            }
        }
    }
    return resultat;
}

/**
 * \brief deplacements::deplacementTour()
 * Permet de recuperer les coordonnees des cases ou la Tour peut se deplacer.
 * La fonction va prendre a partir de la matrice groupe dans quelle equipe est la Tour puis va tester tout les deplacements possibles
 * Si La Tour rencontre une piece de son equipe il ne selectionne pas la case et s'arrete
 * Si La Tour rencontre une piece adverse il ajoute la case et s'arrete
 * Si La Tour recontre un espace (case vide) la fonction ajoute la case et continue a la prochaine case
 * \param[in] matriceGroupe Matrice corespondant a la couleur des pieces.
 * \param[in] cas Coordonnees de la tour a calculer.
 * \return Un tableau de coordonnees
 */
QVector<QPoint> deplacements::deplacementTour(const int matricegroupe[8][8], const QPoint& cas){
    QVector<QPoint> resultat;
    int x = cas.x();
    while(x > 0)
    {
        x--;
        if(matricegroupe[x][cas.y()] != matricegroupe[cas.x()][cas.y()]) // si on rencontre un blanc ou un pion ennemi
        {
            resultat.append(QPoint(x, cas.y()));
        }
        if(matricegroupe[x][cas.y()] != 0) // on a rencontre un obstacle ami ou ennemi
        {
            x = 0; // on stoppe la boucle
        }
    }
    x = cas.x();
    while(x < 7)
    {
        x++;
        if(matricegroupe[x][cas.y()] != matricegroupe[cas.x()][cas.y()]) // si on rencontre un blanc ou une piece ennemie
        {
            resultat.append(QPoint(x, cas.y()));
        }
        if(matricegroupe[x][cas.y()] != 0) // on a rencontre un obstacle ami ou ennemi
        {
            x = 7; // on stoppe la boucle
        }
    }
    int y = cas.y();
    while(y > 0)
    {
        y--;
        if(matricegroupe[cas.x()][y] != matricegroupe[cas.x()][cas.y()]) // si on rencontre un blanc ou une piece ennemie
        {
            resultat.append(QPoint(cas.x(), y));
        }
        if(matricegroupe[cas.x()][y] != 0) // on a rencontre un obsacle ami ou ennemi
        {
            y = 0; // on stoppe la boucle
        }
    }
    y = cas.y();
    while(y < 7)
    {
        y++;
        if(matricegroupe[cas.x()][y] != matricegroupe[cas.x()][cas.y()]) // si on rencontre un blanc ou une piece ennemie
        {
            resultat.append(QPoint(cas.x(), y));
        }
        if(matricegroupe[cas.x()][y] != 0) // on a rencontre un obstacle ami ou ennemi
        {
            y = 7; // on stoppe la boucle
        }
    }
    return resultat;
}
/**
 * \brief deplacements::attaquePion()
 * Permet de recuperer les coordonnees des cases ou le pion peut attaquer.
 * La fonction va prendre a partir de la matrice groupe dans quelle equipe est le pion puis va tester tout les deplacements possibles
 * Si Le Pion peut attaquer quelqu'un la case est ajouter
 * \param[in] matriceGroupe Matrice corespondant a la couleur de pieces.
 * \param[in] cas Coordonnees du Pion a calculer.
 * \return Un tableau de coordonnees
 */
QVector<QPoint> deplacements::attaquePion(const int groupe[8][8],const QPoint& cas)
{
    QVector<QPoint> resultat;
    bool noir = true;
    if(groupe[cas.x()][cas.y()] != 1)
    {
      noir = false;
    }
    //puis apres on avance toujours de devant et on prend sur les cotes
    if(noir == true)
    {
        if(cas.y() > 0)
        {
            if(groupe[cas.x()+1][cas.y()-1] != groupe[cas.x()][cas.y()])
            {
                resultat.append(QPoint(cas.x()+1,cas.y()-1));
            }
        }
        if(cas.y() < 8)
        {
            if(groupe[cas.x()+1][cas.y()+1] != groupe[cas.x()][cas.y()])
            {
                resultat.append(QPoint(cas.x()+1,cas.y()+1));
            }
        }
    }
    else
    {
        if(cas.y() > 0)
        {
            if( groupe[cas.x()-1][cas.y()-1] != groupe[cas.x()][cas.y()])
            {
                resultat.append(QPoint(cas.x()-1,cas.y()-1));
            }
        }
        if(cas.y() < 8)
        {
            if( groupe[cas.x()-1][cas.y()+1] != groupe[cas.x()][cas.y()])
            {
                resultat.append(QPoint(cas.x()-1,cas.y()+1));
            }
        }
    }

    return resultat;
}
/**
 * \brief deplacements::deplacementPion()
 * Permet de recuperer les coordonnees des cases ou le pion peut se deplacer.
 * La fonction va prendre a partir de la matrice groupe dans quelle equipe est le pion puis va tester tout les deplacements possibles
 * Si Le Pion a une piece qui le gene pour avancer (amie ou enemie) la case n'est pas ajoute
 * Si Le Pion voit une piece enemie sur l'un de ses vecteur d'attaquer alors la case est ajoute
 * Si le pion voit que le coup precedent c'etait une avance de 2 cases d'un pion on verifie la prise en passant
 * \param[in] groupe Matrice corespondant au type de pieces sur le terrain.
 * \param[in] terrain Matrice corespondant a la couleur des pieces.
 * \param[in] cas Coordonnees du pion a calculer.
 * \param[in] coup_precedent Tableau du coup precedemment joue [0] = depart [1] = arriver.
 * \return Un tableau de coordonnees
 */
QVector<QPoint> deplacements::deplacementPion(const int groupe[8][8],const piece terrain[8][8],const QPoint& cas,QVector<QPoint> *coup_precedent)
{
    QVector<QPoint> resultat;
    bool noir = true;
    QPoint dest_precedent = coup_precedent->at(1);
    QPoint origin_precedent = coup_precedent->at(0);
    if(groupe[cas.x()][cas.y()] != 1)
    {
      noir = false;
    }

    // on peut éventuellement avancer de deux cases au debut
    if(noir == true && cas.x() == 1 && groupe[cas.x()+2][cas.y()] == 0 && groupe[cas.x()+1][cas.y()] == 0)
    {
        resultat.append(QPoint(cas.x()+2,cas.y()));
    }
    else if(noir == false && cas.x() == 6 && groupe[cas.x()-2][cas.y()] == 0 && groupe[cas.x()-1][cas.y()] == 0)
    {
        resultat.append(QPoint(cas.x()-2,cas.y() ));
    }

    //puis apres on avance toujours devant et on prend sur les cotes
    if(noir == true)
    {
        if(cas.x() < 7)
        {
            if(groupe[cas.x()+1][cas.y()] == 0)
            {
                resultat.append(QPoint(cas.x()+1,cas.y() ));
            }
        }
        if(cas.y() > 0)
        {

            if(groupe[cas.x()+1][cas.y()-1] != groupe[cas.x()][cas.y()] && groupe[cas.x()+1][cas.y()-1] != 0 )
            {
                resultat.append(QPoint(cas.x()+1,cas.y()-1));
            }
        }
        if(cas.y() < 8)
        {
            if(groupe[cas.x()+1][cas.y()+1] != groupe[cas.x()][cas.y()] && groupe[cas.x()+1][cas.y()+1] != 0)
            {
                resultat.append(QPoint(cas.x()+1,cas.y()+1));
            }
        }
        //si c'est un pion qui c'est deplace : l'attaque est possible
        if(terrain[dest_precedent.x()][dest_precedent.y()] == Pion  && origin_precedent.x() == 6)
		{
            // si le pion fait pas parti de mon groupe
			if(groupe[dest_precedent.x()][dest_precedent.y()] != groupe[cas.x()][cas.y()])
			{
                //si il a fait le deplacement qui m'interesse
				if ((dest_precedent.x() - origin_precedent.x()) == -2)
				{
                    //je verifie qu'il est dans mon champs d'attaque
					if (dest_precedent.x() == cas.x() && (cas.y()+1) == dest_precedent.y())
					{
						resultat.append(QPoint(cas.x()+1,cas.y()+1));
					}
					else if(dest_precedent.x() == cas.x() && (cas.y()-1) == dest_precedent.y())
					{
                        resultat.append(QPoint(cas.x()+1,cas.y()-1));
					}
				}
			}
		}
    }
    else
    {
        if(cas.x() > 0)
        {
            if(groupe[cas.x()-1][cas.y()] == 0)
            {
                resultat.append(QPoint(cas.x()-1,cas.y() ));
            }
        }
        if(cas.y() > 0)
        {
            if( groupe[cas.x()-1][cas.y()-1] != groupe[cas.x()][cas.y()] && groupe[cas.x()-1][cas.y()-1] != 0)
            {
                resultat.append(QPoint(cas.x()-1,cas.y()-1));
            }
        }
        if(cas.y() < 8)
        {
            if( groupe[cas.x()-1][cas.y()+1] != groupe[cas.x()][cas.y()] && groupe[cas.x()-1][cas.y()+1] != 0)
            {
                resultat.append(QPoint(cas.x()-1,cas.y()+1));
            }
        }
        //si c'est un pion celui qui cest deplace : attaque est possible
        if(terrain[dest_precedent.x()][dest_precedent.y()] == Pion  && origin_precedent.x() == 1)
		{
            // si le pion fait pas parti de mon groupe
			if(groupe[dest_precedent.x()][dest_precedent.y()] != groupe[cas.x()][cas.y()])
			{
                //si il a fait le deplacement qui m'interesse
				if ((dest_precedent.x() - origin_precedent.x()) == 2)
				{
                    //je verifie qui est dans mon champs d'attaque
					if (dest_precedent.x() == cas.x() && (cas.y()+1) == dest_precedent.y())
					{
						resultat.append(QPoint(cas.x()-1,cas.y()+1));
					}
					else if(dest_precedent.x() == cas.x() && (cas.y()-1) == dest_precedent.y())
					{
                        resultat.append(QPoint(cas.x()-1,cas.y()-1));
					}
				}
			}
		}
    }
    return resultat;
}

/**
 * \brief deplacements::estEnEchec()
 * Permet de savoir si a une coordonnee indique si une piece du groupe adverse peut manger cette case
 * \param[in] matricePiece Matrice corespondant au type des pieces.
 * \param[in] matriceGroupe Matrice corespondant a la couleur de pieces.
 * \param[in] groupe Token permetant de definir a quel equipe on appartient (quelle est ma couleur)
 * \param[in] coordcase Coordonnees de la piece a calculer.
 * \param[in] coordpion Un pointeur qui peut etre NULL,permetant d'indiquer la position de la piece qu'on compte deplacer (sert pour le roi)
 * \return True si on est en echec, sinon False
 */
bool deplacements::estEnEchec(const piece matricePiece[8][8],const int matriceGroupe[8][8],int groupe, const QPoint& coordcase, const QPoint* coordpion)
{   // on teste pour toutes les pieces qui ne sont pas dans mon groupe si il y en a une qui mene a ma piece , si oui elle est en echec
    QVector<QPoint> destination;
    for(int x = 0; x < 8; x++)
    {
        for(int y = 0; y < 8; y++)
        {
            if(matriceGroupe[x][y] != groupe )
            {
                switch(matricePiece[x][y])
                {
                    case Pion:
                        destination = deplacements::attaquePion(matriceGroupe,QPoint(x,y));
                        for(int u = 0; u < destination.count(); u++)
                        {
                            if(destination.at(u).x() == coordcase.x() && destination.at(u).y() == coordcase.y() )
                            {
                                return true;
                            }
                        }
                        destination.clear();
                    break;
                    case Rois:
                        if(coordpion != NULL)
                        {
                            if(matricePiece[coordpion->x()][coordpion->y()] != Rois) // on rois ne peu pas attaquer un autre rois !
                            {
                                destination = deplacements::deplacementRoi(matricePiece,matriceGroupe,QPoint(x,y));
                            }
                            else
                            {
                                //on ne peut simplement ignorer l'autre roi, il faut calculer si on peut etre sur la piece
                            }

                        }
                        else
                        {
                            destination = deplacements::deplacementRoi(matricePiece,matriceGroupe,QPoint(x,y));
                        }

                        for(int u = 0; u < destination.count(); u++)
                        {
                            if(destination.at(u).x() == coordcase.x() && destination.at(u).y() == coordcase.y() )
                            {
                                return true;
                            }
                        }
                        destination.clear();
                    break;
                    case Reine:
                        destination = deplacements::deplacementReine(matriceGroupe,QPoint(x,y));
                        for(int u = 0; u < destination.count(); u++)
                        {
                            if(destination.at(u).x() == coordcase.x() && destination.at(u).y() == coordcase.y() )
                            {
                                return true;
                            }
                        }
                        destination.clear();
                    break;
                    case Fous:
                        destination = deplacements::deplacementFou(matriceGroupe,QPoint(x,y));
                        for(int u = 0; u < destination.count(); u++)
                        {
                            if(destination.at(u).x() == coordcase.x() && destination.at(u).y() == coordcase.y() )
                            {
                                return true;
                            }
                        }
                        destination.clear();
                    break;
                    case Tour:
                        destination =  deplacements::deplacementTour(matriceGroupe,QPoint(x,y));
                        for(int u = 0; u < destination.count(); u++)
                        {
                            if(destination.at(u).x() == coordcase.x() && destination.at(u).y() == coordcase.y() )
                            {
                                return true;
                            }
                        }
                        destination.clear();
                    break;
                    case Cavalier:
                        destination = deplacements::deplacementCavalier(matriceGroupe,QPoint(x,y));
                        for(int u = 0; u < destination.count(); u++)
                        {
                            if(destination.at(u).x() == coordcase.x() && destination.at(u).y() == coordcase.y() )
                            {
                                return true;
                            }
                        }
                        destination.clear();
                    break;
                    case Rien:
                    break;
                }
            }
        }
    }
    return false;
}

