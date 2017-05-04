#pragma once
#include "Grille.h"
#include "Joueur.h"
#include "Piece.h"
#include "ia.h"
#include <QObject>
class Plateau : public QObject
{
    Q_OBJECT

public:
	Plateau();
	void initiatePosInGrid();
	void afficher();
    Joueur getJoueurActif();
    Joueur* getJoueur1();
    Joueur* getJoueur2();
    void setJoueurActif(Joueur joueur);
    Grille* getGrille();
    void initialize();
    void reinitialize();
    void updateCaseStatus(Piece piece,Coordonnee oldCoord);
    QVector<QPoint> getCoupPrec();
    void setCoupPrec(QVector<QPoint> CoupPrec);
    bool est_en_echec(QPoint* coordcase, QPoint* coordpion, int i);
    bool testDestination(QPoint *coordcase, int i_piece, int i_joueur);
    QVector<QPoint> attaquePion(QPoint point);
    bool caseAtOccupy(int x, int y);
	~Plateau();
private:
	Grille *damier;
	Joueur *joueurActif;
	Joueur *joueur1,*joueur2;
    Coordonnee *coordArrivee;
    Coordonnee *coordDepart;
    Piece *aSupprimer;
    QVector<QPoint> *m_coupPrecedent;

    ia *IA;
signals:
    void affichSuppInit(Piece * piece,int id,int i);
    void displayPlayerId(int id);
    void badMove();
public slots:
    void sentDisplayPlayerId();
    void displayPlateau();
    void movePiece(int i1,int i2,int i3,int i4);

};

