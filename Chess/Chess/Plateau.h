#pragma once
#include "Grille.h"

class ia;
class Joueur;
class Plateau : public QObject
{
    Q_OBJECT

public:
	Plateau();
	void initiatePosInGrid();
	void afficher();
    Joueur* getJoueurActif();
    Joueur* getJoueur1();
    Joueur* getJoueur2();
    void setJoueurActif(Joueur joueur);
    Grille* getGrille();
    void initialize();
    bool checkPetitRoque(Joueur *joueur);
    bool checkGrandRoque(Joueur *joueur);
    void reinitialize();
    void updateCaseStatus(Piece piece,Coordonnee oldCoord);
    QVector<QPoint> getCoupPrec();
    void setCoupPrec(QVector<QPoint> CoupPrec);
    static bool est_en_echec(Joueur * joueur,QPoint coordcase, QPoint* coordpion, int i,const int couleur[8][8],const char idPiece[8][8]);
    bool testDestination(Joueur * joueur,QPoint coordcase, int i_piece,const int couleur[8][8],const char idPiece[8][8]);
    QVector<QPoint> listeAttaquePion(QPoint point,const int couleur[8][8]);
    bool caseAtOccupy(int x, int y);
    Piece* getPiece(Coordonnee* coord);
    void jouerIA();
	~Plateau();
private:
	Grille *damier;
    Joueur *joueurActif;
    int idJoueurActif;
	Joueur *joueur1,*joueur2;
    Coordonnee *coordArrivee;
    Coordonnee *coordDepart;
    Piece *aSupprimer;
    QVector<QPoint> *m_coupPrecedent;
    QVector<QPoint> CaseDeplacementPossible;
    QPoint m_Posi_Rois1;
    QPoint m_Posi_Rois2;
    int m_matriceDeplacement[8][8]; // permet de savoir si une piece a bouger ou pas, toute les pieces a 1 n'ont pas ete bouger sinon 0
    ia *IA;
signals:
    void affichSuppInit(Piece * piece,int id,int i);
    void displayPlayerId(int id);
    void badMove();
    void loseSignal();
public slots:
    void setLevel(int level);
    void sentDisplayPlayerId();
    void displayPlateau();
    void movePiece(int i1,int i2,int i3,int i4);

};

