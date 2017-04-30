#include "Fou.h"
#include <QVector>
#include "Plateau.h"


Fou::Fou()
{
}


Fou::~Fou()
{
}
QVector<QPoint> Fou::deplacementsPossible(int idJoueur,Plateau * plateau){
    /*
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
*/
}

bool Fou::testDeplacement(Coordonnee coord)
{
	return Piece::testDiagonal(coord);
}
