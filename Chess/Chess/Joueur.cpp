#include "Joueur.h"

int Joueur::wayToMove =0;

/**
 * @brief Joueur::Joueur
 * Methode constructeur de la classe joueur
 * @param nom le nom du joueur
 * @param i un int qui determine la position du joueur sur le plateau
 */
Joueur::Joueur(std::string nom, int i)
{
    //deck=new std::vector<Piece*>;
    wayToMove+=1;
    if(wayToMove==2)
        wayToMove=-1;
	nomJoueur = nom;
	setOrigin(i); 
    id = i ;
	generateDeck();
}
/**
 * @brief Joueur::Joueur
 * constructeur sans paramètre du joueur
 */
Joueur::Joueur(){}
//Retourne le nom du joueur
std::string Joueur::getNomjoueur()
{
	return nomJoueur;
}

/**
 * @brief Joueur::getIdJoueur
 *  id= 1 ce qui correspond au joueur noir
 *  id= 0 ce qui correspond au joueur blanc
 * @return id
 */
int Joueur::getIdJoueur(){
    return id;
}

/**
 * @brief Joueur::getOrigin
 * @return Coordonnee d origine du joueur
 */
Coordonnee Joueur::getOrigin(){
    return *origin;
}

/**
 * @brief Joueur::isAnyPiece
 * Methode qui permet de savoir si le joueur dispose d une piece
 * au coordonne coord
 * @param coord Coordonnee recherchee
 * @return indice de la piece dans le vecteur deck ou -1 si aucune piece
 * n est trouvee
 */
int Joueur::isAnyPiece(Coordonnee coord)
{

    std::cout<<"je suis dans anypiece"<<std::endl;
	bool found = false;
	int i = 0;
    while (found==false && i < deck.size())
	{

        if (coord.getX() == getDeck()[i]->getCoordonne()->getX() && coord.getY() == getDeck()[i]->getCoordonne()->getY())
		{
			found = true;
		}
        else{
            i++;
        }
	}
    if (found==true){
        return i;
    }
	else {
        std::cout<<"je sors de anypiece"<<std::endl;
		return -1;

	}
}

int Joueur::isAnyPiece2(Coordonnee coord)
{

    std::cout<<"je suis dans anypiece"<<std::endl;
    //bool found = false;
    int i = 0;
    for(i =0;i<deck.size();i++)
   // while (found==false && i < deck.size())
    {


        if (coord.getX() == getDeck()[i]->getCoordonne()->getX() && coord.getY() == getDeck()[i]->getCoordonne()->getY())
        {
            std::cout<<"t3"<<std::endl;
            return i;
            //found = true;
        }
        std::cout<<"t4"<<std::endl;
    }
    std::cout<<"t5"<<std::endl;

    return -1;
}

/**
 * @brief Joueur::generateDeck
 * Genere les differentes pieces des joueurs dans le vecteur deck
 */
void Joueur::generateDeck()
{
	for (int i = 0; i < 8; i++)
	{
        Pion *pion = new Pion(wayToMove);
		int j = int(abs((*origin).getY() - (2 - i % 2)));
		(*pion).setCoordonnee(new Coordonnee(i,j));
        pion->setCouleur(id);
        deck.push_back(pion);
        //delete pion;
	}
	Tour *tour = new Tour();
	int y = (*origin).getY();
	(*tour).setCoordonnee(new Coordonnee(0, y));
    tour->setCouleur(id);
    deck.push_back(tour);

	Fou *fou = new Fou();
	(*fou).setCoordonnee(new Coordonnee(2, y));
    fou->setCouleur(id);
    deck.push_back(fou);

	Roi *roi = new Roi();
	(*roi).setCoordonnee(new Coordonnee(4, y));
    roi->setCouleur(id);
    deck.push_back(roi);

	Cavalier *cavalier = new Cavalier();
	(*cavalier).setCoordonnee(new Coordonnee(6, y));
    cavalier->setCouleur(id);
    deck.push_back(cavalier);

}


/**
 * @brief Joueur::afficherPiece
 * Affiche pour chaque piece ses coordonne et le nom de la piece
 */
void Joueur::afficherPiece()
{
    for (int i = 0; i < deck.size(); i++)
	{
		(*deck[i]).afficher();
	}
}

//Destructeur du joueur 
Joueur::~Joueur()
{
    for (int i =0; i < deck.size(); i++)
	{
        delete deck[i];
		std::cout << i << std::endl;
	}
	delete origin;
}

/**
 * @brief Joueur::setOrigin
 * Definie la position du joueur dans le plateau
 * @param i entier qui définit la position du joueur
 */
void Joueur::setOrigin(int i)
{
	switch (i)
	{
    case 0:
		origin = new Coordonnee(0, 0);
		break;
    case 1:
		origin = new Coordonnee(7, 7);
		break;
	default:
		break;
	}
}

/**
 * @brief Joueur::getDeck
 * @return le vecteur deck 
 */
std::vector<Piece*> Joueur::getDeck()
{
    return deck;
}

/**
 * @brief Joueur::getPiece
 * @param i indice de la piece
 * @return piece du deck a la position i
 */
Piece Joueur::getPiece(int i)
{
    return *deck[i];
}

Piece* Joueur::getPiece2(int i)
{
    return deck[i];
}

/**
 * @brief Joueur::getDeckSize
 * @return taille du deck 
 */
int Joueur::getDeckSize()
{
    return deck.size();
}


