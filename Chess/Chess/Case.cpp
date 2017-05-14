#include "Case.h"

Case::Case(int x, int y)
{
	occupied = false;
    couleur=-1;
    id='N';
	coordonnee = new Coordonnee(x, y);
}

/**
 * @brief Case::getId
 * getteur de l id d une case
 * soit l id de la piece qui l occupe
 * soit 'N' s il n y a rien
 * @return 
 */
char Case::getId(){
    return id;
}
void Case::setId(char id){
    this->id=id;
}

/**
 * @brief Case::getCouleur
 * couleur =0 : la case est occupe par une piece noire
 * couleur =1 : la case est occupe par une piece blanche
 * couleur =-1 : la case est innocupee
 * @return 
 */
int Case::getCouleur(){
   // std::cout << "dans getcouleur";std::cout << std::endl;
    return couleur;
}
void Case::setCouleur(int i){
    this->couleur=i;
}
Coordonnee Case::getCoordonee()
{
	return *coordonnee;
}
/**
 * @brief Case::isOccupied
 * @return true si case occupee
 */
bool Case::isOccupied()
{
	return occupied;
}

void Case::setPiece()
{
	occupied = true;
}

void Case::removePiece()
{
	occupied = false;
}

void Case::setCoord(Coordonnee coord)
{
	*coordonnee = coord;
}


Case::~Case()
{
	delete coordonnee;
}

