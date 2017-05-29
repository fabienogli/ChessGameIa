#include "deplacement.h"
#include <QDebug>
#include <iostream>

/**
 * \brief deplacement::kingMove()
 * Permet de recuperer les coordonnees des cases ou le roi peut se deplacer.
 * Il va prendre a partir de la matrice couleur dans quelle equipe est le roi puis va tester tout les deplacement possibles
 * Si il rencontre une char de son equipe il ne selectionne pas la case
 * Si il rencontre une char adverse il verifie si la case est en echec (des fois qu'un autre pion pourai la prendre) puis selectionne la case
 * Si il rencontre un espace (case vide) il verifie que ca ne le met pas en echec et ajoute la case
 * \param[in] idchar Matrice des chars du idchar.
 * \param[in] couleur Matrice corespondant a la couleur des chars.
 * \param[in] cas Coordonnees du roi a calculer.
 * \return Un tableau de coordonnees
 */
QVector<QPoint> deplacement::kingMove( char idchar[8][8], int couleur[8][8],  QPoint& cas)
{
    QVector<QPoint> resultat;
        for(int x = -1; x < 2 ; x++) // on fait les 3 zones de guauche a droite
        {
            if((cas.x()+x) < 8 && (cas.x()+x) >= 0) // si on depasse le x a droite ou a guauche on regarde pas le y
            {
                for(int y = -1; y < 2; y++) // pour chaque x on fait les 3 valeurs de y possible
                {
                    // si on sort de la carte ou que c'est notre case (notre char) on l'ajoute pas
                    if((cas.y()+y) < 8 && (cas.y()+y) >= 0 && (cas.y() != (cas.y()+y) || cas.x() != (cas.x()+x)))
                    {
                        if(couleur[cas.x()+x][cas.y()+y] != couleur[cas.x()][cas.y()] )
                        {
                            if(x != 0 || y != 0)
                            {
                              if(inCheck(idchar,couleur,couleur[cas.x()][cas.y()],QPoint(cas.x()+x, (cas.y()+y)),&cas) == false)
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
 * \brief deplacement::checkPetitRoque()
 * Permet de savoir si on peut faire le petit rogue
 * \param[in] joueur numero du joueur que l'on veut verifier
 * \param[in] couleur Matrice correspondant a la couleur des chars.
 * \param[in] matriceDeplacement Matrice de deplacement pour savoir si un pion a deja été bouge ou pas.
 * \param[in] idPiece Matrice corespondant au chars sur l'echiquier.
 * \return True si on peut faire le grand rogue, sinon False
 */
bool deplacement::checkPetitRoque(int joueur, int couleur[8][8], int matriceDeplacement[8][8], char idPiece[8][8])
{
    if(joueur == 0) // joueur noir
    {
        // si le roi et la tour n'ont pas bouge
        if(matriceDeplacement[0][4] == 1 && matriceDeplacement[0][7] == 1)
        {
            for(int i = 4 ; i < 6 ; i++)
            {
                // si on a une char sur le chemin
                if(couleur[0][i] != -1 && i != 4)
                {
                    return false;
                }
                if(inCheck(idPiece,couleur,joueur, QPoint(0,i)))
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
                // si on a une char sur le chemin
                if(couleur[7][i] != -1 && i != 4)
                {
                    return false;
                }
                if(inCheck(idPiece,couleur,joueur, QPoint(7,i)))
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
 * \brief deplacement::checkGrandRoque()
 * Permet de savoir si on peut faire le grand rogue
 * \param[in] joueur Numero du joueur que l'on veut verifier
 * \param[in] couleur Matrice corespondant a la couleur des chars.
 * \param[in] matriceDeplacement Matrice de deplacement pour savoir si une char a deja été bouger ou pas.
 * \param[in] idPiece Matrice corespondant au type des chars.
 * \return True si on peut faire le grand rogue, sinon False
 */
bool deplacement::checkGrandRoque(int joueur, int couleur[8][8], int matriceDeplacement[8][8], char idPiece[8][8])
{
    if(joueur == 0) // joueur noir
    {
        // si le roi et la tour n'ont pas bouge
        if(matriceDeplacement[0][4] == 1 && matriceDeplacement[0][0] == 1)
        {
            for(int i = 4 ; i > 2 ; i--)
            {
                // si on a une char sur le chemin
                if(couleur[0][i] != -1 && i != 4)
                {
                    return false;
                }
                if(inCheck(idPiece,couleur,joueur, QPoint(0,i)))
                {
                    return false;
                }
            }
            if(couleur[0][1] != -1)
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
                // si on a une char sur le chemin
                if(couleur[7][i] != -1 && i != 4)
                {
                    return false;
                }
                if(inCheck(idPiece,couleur,joueur, QPoint(7,i)))
                {
                    return false;
                }
            }
            if(couleur[7][1] != -1)
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
 * \brief deplacement::madMove()
 * Permet de recuperer les coordonnees des cases ou le fou peut se deplacer.
 * La fonction va prendre a partir de la matrice couleur dans quelle equipe est le fous puis va tester tous les deplacement possibles
 * Si le fou rencontre une char de son equipe il ne selectionne pas la case et s'arrete
 * Si le fou rencontre une char adverse il ajoute la case et s'arrete
 * Si le fou rencontre un espace (case vide) la fonction ajoute la case et continue a la prochaine case
 * \param[in] couleur Matrice correspondant a la couleur des chars.
 * \param[in] cas Coordonnees du fou a calculer.
 * \return Un tableau de coordonnees
 */
QVector<QPoint> deplacement::madMove( int couleur[8][8],  QPoint cas){

    QVector<QPoint> resultat;

        int x = cas.x();
        int y = cas.y();

        while (x > 0 && y > 0)
        {
            x--;
            y--;
            if(couleur[x][y] != couleur[cas.x()][cas.y()] )
            {
                resultat.append(QPoint(x, y));
            }
            if(couleur[x][y] != -1) // on a rencontre un obstacle ami ou ennemis
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
            if(couleur[x][y] != couleur[cas.x()][cas.y()] )
            {
                resultat.append(QPoint(x, y));
            }
            if(couleur[x][y] != -1) // on a rencontre un obstacle ami ou ennemis
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
            if(couleur[x][y] != couleur[cas.x()][cas.y()] )
            {
                resultat.append(QPoint(x, y));
            }
            if(couleur[x][y] != -1) // on a rencontre un obstacle ami ou ennemi
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
            if(couleur[x][y] != couleur[cas.x()][cas.y()] )
            {
                resultat.append(QPoint(x, y));
            }
            if(couleur[x][y] != -1) // on a rencontre un obstacle ami ou ennemi
            {
                x = 7; // on stoppe la boucle
            }
        }
        return resultat;
}
/*
/**
 * \brief deplacement::knightMove()
 * Permet de recuperer les coordonnees des cases ou le Cavalier peut se deplacer.
 * La fonction va prendre a partir de la matrice couleur dans quelle equipe est le Cavalier puis va tester tous les deplacement possibles
 * Si le Cavalier rencontre une char de son equipe il ne selectionne pas la case
 * Si le Cavalier rencontre une char adverse ou un espace (case vide) il ajoute la case
 * \param[in] couleur Matrice correspondant a la couleur des chars.
 * \param[in] cas Coordonnees du Cavalier a calculer.
 * \return Un tableau de coordonnees
 */
QVector<QPoint> deplacement::knightMove( const int couleur[8][8], const  QPoint cas){
    QVector<QPoint> resultat;
        /////////// HAUT
        if(cas.y()>= 1){

            if(cas.x()>=2)
            {
                if(couleur[cas.x()-2][cas.y()-1] != couleur[cas.x()][cas.y()] )
                    // sinon est pas sur une char aliee mais une char adverse ou un Rien
                {
                    resultat.append(QPoint(cas.x()-2, (cas.y()-1)));
                }
            }
            if(cas.x() <= 5)
            {
                if(couleur[cas.x()+2][cas.y()-1] != couleur[cas.x()][cas.y()] )
                {
                    resultat.append(QPoint(cas.x()+2, (cas.y()-1)));
                }
            }
        }/////////BAS
        if(cas.y()<=6)
        {
            if(cas.x()>=2)
            {
                if(couleur[cas.x()-2][cas.y()+1] != couleur[cas.x()][cas.y()] )
                {
                    resultat.append(QPoint(cas.x()-2, (cas.y()+1)));
                }
            }
            if(cas.x() <= 5)
            {
                if(couleur[cas.x()+2][cas.y()+1] != couleur[cas.x()][cas.y()] )
                {
                    resultat.append(QPoint(cas.x()+2, (cas.y()+1)));
                }
            }
        }/////// GAUCHE
        if(cas.y()>= 2){

            if(cas.x()>=1)
            {
                if(couleur[cas.x()-1][cas.y()-2] != couleur[cas.x()][cas.y()] )
                {
                    resultat.append(QPoint(cas.x()-1, (cas.y()-2)));
                }
            }
            if(cas.x() <= 6)
            {
                if(couleur[cas.x()+1][cas.y()-2] != couleur[cas.x()][cas.y()] )
                {
                    resultat.append(QPoint(cas.x()+1, (cas.y()-2)));
                }
            }
        }/////////DROITE
        if(cas.y()<=5)
        {
            if(cas.x()>=1)
            {
                if(couleur[cas.x()-1][cas.y()+2] != couleur[cas.x()][cas.y()] )
                {
                    resultat.append(QPoint(cas.x()-1, (cas.y()+2)));
                }
            }
            if(cas.x() <= 6)
            {
                if(couleur[cas.x()+1][cas.y()+2] != couleur[cas.x()][cas.y()] )
                {
                    resultat.append(QPoint(cas.x()+1, (cas.y()+2)));
                }
            }
        }
        return resultat;
}

/**
 * \brief deplacement::towerMove()
 * Permet de recuperer les coordonnees des cases ou la Tour peut se deplacer.
 * La fonction va prendre a partir de la matrice couleur dans quelle equipe est la Tour puis va tester tout les deplacement possibles
 * Si La Tour rencontre une char de son equipe il ne selectionne pas la case et s'arrete
 * Si La Tour rencontre une char adverse il ajoute la case et s'arrete
 * Si La Tour recontre un espace (case vide) la fonction ajoute la case et continue a la prochaine case
 * \param[in] couleur Matrice corespondant a la couleur des chars.
 * \param[in] cas Coordonnees de la tour a calculer.
 * \return Un tableau de coordonnees
 */
QVector<QPoint> deplacement::towerMove( int couleur[8][8],  QPoint cas){
    QVector<QPoint> resultat;
        int x = cas.x();
        while(x > 0)
        {
            x--;
            if(couleur[x][cas.y()] != couleur[cas.x()][cas.y()]) // si on rencontre un blanc ou un pion ennemi
            {
                resultat.append(QPoint(x, cas.y()));

            }
            if(couleur[x][cas.y()] != -1) // on a rencontre un obstacle ami ou ennemi
            {
                x = 0; // on stoppe la boucle
            }
        }
        x = cas.x();
        while(x < 7)
        {
            x++;
            if(couleur[x][cas.y()] != couleur[cas.x()][cas.y()]) // si on rencontre un blanc ou une char ennemie
            {
                resultat.append(QPoint(x, cas.y()));
            }
            if(couleur[x][cas.y()] != -1) // on a rencontre un obstacle ami ou ennemi
            {
                x = 7; // on stoppe la boucle
            }
        }
        int y = cas.y();
        while(y > 0)
        {
            y--;
            if(couleur[cas.x()][y] != couleur[cas.x()][cas.y()]) // si on rencontre un blanc ou une piece ennemie
            {
                resultat.append(QPoint(cas.x(), y));
            }
            if(couleur[cas.x()][y] != -1) // on a rencontre un obsacle ami ou ennemi
            {
                y = 0; // on stoppe la boucle
            }
        }
        y = cas.y();
        while(y < 7)
        {
            y++;
            if(couleur[cas.x()][y] != couleur[cas.x()][cas.y()]) // si on rencontre un blanc ou une piece ennemie
            {
                resultat.append(QPoint(cas.x(), y));
            }
            if(couleur[cas.x()][y] != -1) // on a rencontre un obstacle ami ou ennemi
            {
                y = 7; // on stoppe la boucle
            }
        }
        return resultat;
}
/**
 * \brief deplacement::pawnAttackList()
 * Permet de recuperer les coordonnees des cases ou le pion peut attaquer.
 * La fonction va prendre a partir de la matrice couleur dans quelle equipe est le pion puis va tester tout les deplacement possibles
 * Si Le Pion peut attaquer quelqu'un la case est ajouter
 * \param[in] couleur Matrice corespondant a la couleur de chars.
 * \param[in] cas Coordonnees du Pion a calculer.
 * \return Un tableau de coordonnees
 */
QVector<QPoint> deplacement::pawnAttackList( int couleur[8][8], QPoint cas)
{
    QVector<QPoint> resultat;
    bool noir = true;
    if(couleur[cas.x()][cas.y()] != 1)
    {
      noir = false;
    }
    //puis apres on avance toujours de devant et on prend sur les cotes
    if(noir == true)
    {
        if(cas.x() > 0)
        {
            if(couleur[cas.x()-1][cas.y()+1] != couleur[cas.x()][cas.y()])
            {
                resultat.append(QPoint(cas.x()-1,cas.y()+1));
            }
        }
        if(cas.x() < 7)
        {
            if(couleur[cas.x()+1][cas.y()+1] != couleur[cas.x()][cas.y()])
            {
                resultat.append(QPoint(cas.x()+1,cas.y()+1));
            }
        }
    }
    else
    {
        if(cas.x() > 0)
        {
            if( couleur[cas.x()-1][cas.y()-1] != couleur[cas.x()][cas.y()])
            {
                resultat.append(QPoint(cas.x()-1,cas.y()-1));
            }
        }
        if(cas.x() < 7)
        {
            if( couleur[cas.x()+1][cas.y()-1] != couleur[cas.x()][cas.y()])
            {
                resultat.append(QPoint(cas.x()+1,cas.y()-1));
            }
        }
    }

    return resultat;
}
/**
 * \brief deplacement::pawnMove()
 * Permet de recuperer les coordonnees des cases ou le pion peut se deplacer.
 * La fonction va prendre a partir de la matrice couleur dans quelle equipe est le pion puis va tester tout les deplacement possibles
 * Si Le Pion a une char qui le gene pour avancer (amie ou enemie) la case n'est pas ajoute
 * Si Le Pion voit une char enemie sur l'un de ses vecteur d'attaquer alors la case est ajoute
 * Si le pion voit que le coup precedent c'etait une avance de 2 cases d'un pion on verifie la prise en passant
 * \param[in] couleur Matrice corespondant au type de chars sur le idchar.
 * \param[in] idchar Matrice corespondant a la couleur des chars.
 * \param[in] cas Coordonnees du pion a calculer.
 * \return Un tableau de coordonnees
 */
QVector<QPoint> deplacement::pawnMove(int idJoueur, int couleur[8][8], QPoint cas,int matriceDeplacement[8][8])
{
    QVector<QPoint> tabDep;
        switch(idJoueur){
            case 0:
                //black
            //si le pion n'a pas encore bougé
                if(matriceDeplacement[cas.x()][cas.y()]==1){
                if((cas.y() == 1 || cas.y()==2) &&
                        couleur[cas.x()][cas.y()+2]==-1 && couleur[cas.x()][cas.y()+1]==-1)
                {
                    std::cout << "merde"<< std::endl;
                    tabDep.append(QPoint(cas.x(),cas.y()+2));
                }}
                if(cas.y() < 7)
                {
                    if(couleur[cas.x()][cas.y()+1] == -1)
                    {
                        tabDep.append(QPoint(cas.x(),cas.y()+1));
                    }
                }
                if(cas.x() > 0)
                {

                    if(couleur[cas.x()-1][cas.y()+1] != couleur[cas.x()][cas.y()] && couleur[cas.x()-1][cas.y()+1] != -1 )
                    {
                       tabDep.append(QPoint(cas.x()-1,cas.y()+1));
                    }
                }
                if(cas.x() < 7)
                {
                    if(couleur[cas.x()+1][cas.y()+1] != couleur[cas.x()][cas.y()] && couleur[cas.x()+1][cas.y()+1] != -1)
                    {
                       tabDep.append(QPoint(cas.x()+1,cas.y()+1));
                    }
                }

                break;
            case 1:
            if(matriceDeplacement[cas.x()][cas.y()]==1){
                if((cas.y() == 5 || cas.y()==6) && couleur[cas.x()][cas.y()-2]==-1 && couleur[cas.x()][cas.y()-1]==-1 )
                {
                    tabDep.append(QPoint(cas.x(),cas.y()-2));
                }
            }
                if(cas.y() > 0)
                {
                    if(couleur[cas.x()][cas.y()-1]==-1)
                    {
                        tabDep.append(QPoint(cas.x(),cas.y()-1));
                    }
                }
                if(cas.x() > 0)
                {
                    if( couleur[cas.x()-1][cas.y()-1] != couleur[cas.x()][cas.y()] && couleur[cas.x()-1][cas.y()-1] != -1)
                    {
                       tabDep.append(QPoint(cas.x()-1,cas.y()-1));
                    }
                }
                if(cas.x() < 7)
                {
                    if( couleur[cas.x()+1][cas.y()-1] != couleur[cas.x()][cas.y()] && couleur[cas.x()+1][cas.y()-1] != -1)
                    {
                       tabDep.append(QPoint(cas.x()+1,cas.y()-1));
                    }
                }
                break;
            default:
                break;
            }
            return tabDep;
}

/**
 * \brief deplacement::inCheck()
 * Permet de savoir si a une coordonnee indique si une char du couleur adverse peut manger cette case
 * \param[in] idPiece Matrice corespondant au type des chars.
 * \param[in] couleur Matrice corespondant a la couleur de chars.
 * \param[in] couleur Token permetant de definir a quel equipe on appartient (quelle est ma couleur)
 * \param[in] coordcase Coordonnees de la piece a calculer.
 * \param[in] coordpion Un pointeur qui peut etre NULL,permetant d'indiquer la position de la char qu'on compte deplacer (sert pour le roi)
 * \return True si on est en echec, sinon False
 */
bool deplacement::inCheck(char idPiece[8][8], int couleur[8][8],int couleurPiece,  QPoint coordcase,  QPoint* coordpion)
{   // on teste pour toutes les chars qui ne sont pas dans mon couleur si il y en a une qui mene a ma char , si oui elle est en echec
    QVector<QPoint> destination;
    for(int x = 0; x < 8; x++)
    {
        for(int y = 0; y < 8; y++)
        {
            if(couleur[x][y] != couleurPiece )
            {
                switch(idPiece[x][y])
                {
                    case 'P':
                        destination = deplacement::pawnAttackList(couleur,QPoint(x,y));
                        for(int u = 0; u < destination.count(); u++)
                        {
                            if(destination.at(u).x() == coordcase.x() && destination.at(u).y() == coordcase.y() )
                            {
                                return true;
                            }
                        }
                        destination.clear();
                    break;
                    case 'R':
                        if(coordpion != NULL)
                        {
                            if(idPiece[coordpion->x()][coordpion->y()] != 'R') // un roi ne peut pas attaquer un autre roi !
                            {
                                destination = deplacement::kingMove(idPiece,couleur,QPoint(x,y));
                            }
                            else
                            {
                                //on ne peut simplement ignorer l'autre roi, il faut calculer si on peut le mettre en echec
                            }

                        }
                        else
                        {
                            destination = deplacement::kingMove(idPiece,couleur,QPoint(x,y));
                        }

                        for(int u = 0; u < destination.count(); u++)
                        {
                            if(destination.at(u).x() == coordcase.x() && destination.at(u).y() == coordcase.y() )
                            {
                                return true;
                            }
                        }
                        destination.clear();

                    case 'F':
                        destination = deplacement::madMove(couleur,QPoint(x,y));
                        for(int u = 0; u < destination.count(); u++)
                        {
                            if(destination.at(u).x() == coordcase.x() && destination.at(u).y() == coordcase.y() )
                            {
                                return true;
                            }
                        }
                        destination.clear();
                    break;
                    case 'T':
                        destination =  deplacement::towerMove(couleur,QPoint(x,y));
                        for(int u = 0; u < destination.count(); u++)
                        {
                            if(destination.at(u).x() == coordcase.x() && destination.at(u).y() == coordcase.y() )
                            {
                                return true;
                            }
                        }
                        destination.clear();
                    break;
                    case 'C':
                        destination = deplacement::knightMove(couleur,QPoint(x,y));
                        for(int u = 0; u < destination.count(); u++)
                        {
                            if(destination.at(u).x() == coordcase.x() && destination.at(u).y() == coordcase.y() )
                            {
                                return true;
                            }
                        }
                        destination.clear();
                    break;
                    default:
                    break;
                }
            }
        }
    }
    return false;
}

