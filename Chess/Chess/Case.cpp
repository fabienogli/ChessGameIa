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
/**
 * @brief Case::setId
 * setter de l'id de la case
 * @param id un entier 0, 1 ou -1
 */
void Case::setId(char id){
    this->id=id;
}

/**
 * @brief Case::getCouleur
 * couleur =0 : la case est occupe par une piece noire
 * couleur =1 : la case est occupe par une piece blanche
 * couleur =-1 : la case est innocupee
 * @return  la couleur
 */
int Case::getCouleur(){
   // std::cout << "dans getcouleur";std::cout << std::endl;
    return couleur;
}
/**
 * @brief Case::setCouleur
 * setter de la couleur de la case
 * @param i
 */
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

/**
 * @brief Case::setPiece
 * met l'attribut occupied à true
 */
void Case::setPiece()
{
	occupied = true;
}
/**
 * @brief Case::setOccupied
 * met l'attribut occupied à t
 * @param t un booleen
 */
void Case::setOccupied(bool t)
{
    occupied = t;
}
/**
 * @brief Case::removePiece
 * met l'attribut occupied à false
 */
void Case::removePiece()
{
	occupied = false;
}

/**
 * @brief Case::setCoord
 * setter des coordonnées
 * @param coord
 */
void Case::setCoord(Coordonnee coord)
{
	*coordonnee = coord;
}


Case::~Case()
{
	delete coordonnee;
}

