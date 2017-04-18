 #include "Plateau.h"
#include "mainwindow.h"
#include "Piece.h"
#include "Coordonnee.h"
#include <stddef.h>
//Constructeur du plateau
Plateau::Plateau() :QObject()
{
	damier = new Grille();
	joueur1 = new Joueur("joueur 1",0);
	joueur2 = new Joueur("joueur 2",1);
    joueurActif = new Joueur();
    coordDepart = new Coordonnee(0,0);
    coordArrivee= new Coordonnee(0,0);
	initiatePosInGrid();
    //setJoueurActif(*joueur1);
    }

//Positionne les pieces des differentes piece des joueurs dans le plateau
void Plateau::initiatePosInGrid()
{

	for (int i=0; i < (*joueur1).getDeckSize(); i++)
	{
		(*damier).putPiece((*joueur1).getDeck()[i]);
		(*damier).putPiece((*joueur2).getDeck()[i]);

	}
}
//deplacer une piece
void Plateau::movePiece(int i1, int i2, int i3, int i4){
    std::cout << i1;std::cout << std::endl;
    std::cout << i2;std::cout << std::endl;
    std::cout << i3;std::cout << std::endl;
    std::cout << i4;std::cout << std::endl;
    //prendre la piece en i1,i2 et l'envoyer en i3,i4
    std::cout << "je suis 3";
    coordDepart->setX(i2);
    coordDepart->setY(i1);
    coordArrivee->setX(i4);
    coordArrivee->setY(i3);
    std::cout << coordDepart->getX();std::cout << std::endl;
    std::cout << coordDepart->getY();std::cout << std::endl;
    //on recherche dans le deck du premier joueur
    double tmp1 = (*joueur1).isAnyPiece(*coordDepart);
    //on recherche dans le deck du deuxieme joueur
    double tmp2 = (*joueur2).isAnyPiece(*coordDepart);
        if (tmp1 != -1)
        {  std::cout << "je suis 1-1";std::cout << std::endl;
            std::cout << tmp1;std::cout << std::endl;
            (*joueur1).getDeck()[tmp1]->afficher();
            //(*joueur1).getPiece(int(tmp1)).move(coordArrivee,(*joueur1).getOrigin());
            (*joueur1).getDeck()[tmp1]->move(coordArrivee,(*joueur1).getOrigin());
            (*joueur1).getDeck()[tmp1]->afficher();
            std::cout << "je suis 1-2";std::cout << std::endl;
            emit afficherInit((*joueur1).getDeck()[tmp1],(*joueur1).getIdJoueur());
            std::cout << "je suis 1-3";std::cout << std::endl;
        }
        //sinon c'est forcement occupe par une piece du joueur 2
        else if(tmp2 != -1)
        {
           /* (*joueur2).getPiece(tmp2). setCoordonnee(new Coordonnee(i3,i4));
            emit afficherInit((*joueur2).getDeck()[tmp2],(*joueur2).getIdJoueur());
            std::cout << "je suis 2";*/
            std::cout << "je suis 2-1";
                        std::cout << tmp2;
                        //(*joueur2).getPiece(tmp2).afficher();
                        (*joueur2).getDeck()[tmp2]->move(coordArrivee,(*joueur2).getOrigin());
                        (*joueur2).getDeck()[tmp2]->afficher();
                        //(*joueur2).getPiece(tmp2).afficher();
                        std::cout << "je suis 2-2";
                        emit afficherInit((*joueur2).getDeck()[tmp2],(*joueur2).getIdJoueur());
                        std::cout << "je suis 2-3";
        }
       // coordOrigin.~Coordonnee();
        //coordArrivee.~Coordonnee();
}
//slot pour affichage gui des pieces
void Plateau::displayPlateau(){

    for (int i=0; i < (*joueur1).getDeckSize(); i++)
    {
        emit afficherInit((*joueur1).getDeck()[i],(*joueur1).getIdJoueur());
        emit afficherInit((*joueur2).getDeck()[i],(*joueur2).getIdJoueur());
    }

}
void Plateau::sentDisplayPlayerId(){
   emit displayPlayerId((*joueurActif).getIdJoueur());
}

/**
 * @brief Plateau::displayPiece affiche une piece dans le GUI
 */
void Plateau::displayPiece(Piece * piece, int id){


}

//Affichage du plateau dans la console
void Plateau::afficher()
{
	for (int j = 0; j<(*damier).getHauteur(); j++) {
		for (int i = 0; i<(*damier).getLargeur(); i++) {
			//on teste si la case est occupee
			if ((*damier).getCase(i, j).isOccupied()) {
				Coordonnee coord(i, j);
				//on recherche dans le deck du premier joueur
				double i1 = (*joueur1).isAnyPiece(coord);
				//on recherche dans le deck du deuxieme joueur
				double i2 = (*joueur2).isAnyPiece(coord);
				// on verifie si la case est occupee par une piece du joueur
					if (i1 != -1)
					{
						std::cout << (*joueur1).getPiece(i1).getId();
					}
					//sinon c'est forcement occupe par une piece du joueur 2
					else
					{
						std::cout << (*joueur2).getPiece(i2).getId();
					}
					coord.~Coordonnee();
			}
			else
			{
				std::cout << 0;
			}
			std::cout << "|";
		}
		std::cout << std::endl;
		std::cout << "-------------" << std::endl;
	}
}

//Retourne le pointeur du joueur actif
Joueur Plateau::getJoueurActif()
{
    return *joueurActif;
}

Joueur Plateau::getJoueur1(){
    return *joueur1;
}
Joueur Plateau::getJoueur2(){
    return *joueur2;
}
void Plateau::setJoueurActif(Joueur  joueur){
    *joueurActif=joueur;
}

Grille Plateau::getGrille(){
    return *damier;
}

//Destructeur du plateau
Plateau::~Plateau()
{
	delete damier;
	delete joueur1;
	delete joueur2;
    delete joueurActif;
    delete coordArrivee;
    delete coordDepart;
}
