#include "Piece.h"
#include "Plateau.h"
#include "Roi.h"
#include "Cavalier.h"
#include "Fou.h"
#include "Tour.h"
#include "Pion.h"
#include <vector>
//Initialise la piece
Piece::Piece()
{
	alive = true;
    couleur = -1;
}

//Retourne les coordonne de la piece
Coordonnee Piece::getCoordonne()
{
	return *coordonnee;
}
int Piece::getCouleur(){
    return couleur;
}
void Piece::setCouleur(int i){
    this->couleur=i;
}

//Modifie les coordonne de la piece
void Piece::setCoordonnee(Coordonnee *coord)
{
	coordonnee = coord;
}
void Piece::setCoordonne(int x,int y){
    coordonnee->setX(x);
    coordonnee->setY(y);
}

//Methode lorsqu une piece mange une autre
void Piece::kill(Piece & piece)
{
	piece.~Piece();
}

virtual QVector<QPoint> Piece::deplacementsPossible(int idJoueur,Plateau plateau){

    QVector<QPoint> listDep;
    return listDep;
}

//Test pour voir si la piece est toujours en vie
bool Piece::isAlive()
{
	return alive;
}

//retourne son abscisse, son ordonnee et le nom de la piece
void Piece::afficher()
{
	std::cout <<"x= "<< getCoordonne().getX() << " et y= " << getCoordonne().getY() << " " << getId()<< std::endl;
}

//Methode pour tester un deplacement
bool Piece::testDeplacement(Coordonnee coord)
{
    bool verif = false;
    return verif;
}

bool Piece::testDiagonal(Coordonnee coord)
{
	int x = coord.getX();
	int y = coord.getY();

    int i = getCoordonne().getX();
    int j = getCoordonne().getY();

	if (x < i)
		i = -i;
	if (y < j)
		j = -j;
	bool moveAble = false;
	while (!moveAble || i < x&&j < y) {
		if (x == i && y == j)
			moveAble = true;
		else {
			i += 1;
			j += 1;
		}
	}
	return moveAble;
}

bool Piece::testVertical(Coordonnee coord)
{
	int y = getCoordonne().getY();
    int j = coord.getY();
	if (j > y)
		j = -j;
	bool moveAble = false;
	while (!moveAble || j < y) {
		if (y == j)
			moveAble = true;
		else
			j++;
	}
	return moveAble;
}

bool Piece::testHorizontal(Coordonnee coord)
{
	int x = getCoordonne().getX();
    int i = coord.getX();

	if (i > x)
		i = -i;
	bool moveAble = false;
	while (!moveAble || i < x) {
		if (x == i)
			moveAble = true;
		else
		{
			i += 1;
		}
	}
	return moveAble;
}

//Methode de deplacement de la piece, si le test retourne vrai, la piece peut se deplacer
bool Piece::move(Coordonnee * coord, Coordonnee origin)
{
    bool verif =false;
    std::cout << "je suis ici";std::cout << std::endl;
   // Coordonnee test(origin.getX() - (*coord).getX(), origin.getY() - (*coord).getY());
    //if (testDeplacement(test)) {
    if (testDeplacement(*coord)==true) {
       // setCoordonnee(new Coordonnee(*coord));
        setCoordonne(coord->getX(),coord->getY());

        afficher();
        std::cout << "j'ai update les coord";std::cout << std::endl;
        verif=true;
	}
    return verif;
}

//Destructeur de la piece
Piece::~Piece()
{
	alive = false;
	delete coordonnee;
}

char Piece::getId()
{
	return typeid(*this).name()[6];
}



