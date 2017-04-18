#pragma once
#include "Grille.h"
#include "Joueur.h"
#include "Piece.h"
#include <QObject>
class Plateau : public QObject
{
    Q_OBJECT

public:
	Plateau();
	void initiatePosInGrid();
	void afficher();
    Joueur getJoueurActif();
    Joueur getJoueur1();
    Joueur getJoueur2();
    void setJoueurActif(Joueur joueur);
    Grille getGrille();

	~Plateau();
private:
	Grille *damier;
	Joueur *joueurActif;
	Joueur *joueur1,*joueur2;
    Coordonnee *coordArrivee;
    Coordonnee *coordDepart;
signals:
    void afficherInit(Piece * piece,int id);
    void displayPlayerId(int id);
public slots:
    void sentDisplayPlayerId();
    void displayPlateau();
    void displayPiece(Piece * piece,int id);
    void movePiece(int i1,int i2,int i3,int i4);

};

