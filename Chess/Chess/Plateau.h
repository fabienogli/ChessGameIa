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
    Piece *aSupprimer;
signals:
    void affichSuppInit(Piece * piece,int id,int i);
    void displayPlayerId(int id);
public slots:
    void sentDisplayPlayerId();
    void displayPlateau();
    void movePiece(int i1,int i2,int i3,int i4);

};

