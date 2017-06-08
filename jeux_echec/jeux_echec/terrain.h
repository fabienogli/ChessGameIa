#ifndef TERRAIN_H
#define TERRAIN_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QPixmap>
#include <QFile>
#include "Definement.h"
#include "deplacements.h"

class MainWindow;
#include "mainwindow.h"
class IA;
#include "ia.h"

class case_terrain;
#include "case_terrain.h"



class terrain : public QWidget
{
    Q_OBJECT
public:
    explicit terrain(QWidget *parent = 0);
    ~terrain();
    void initialisation();


    void setIA(bool actif ,int dificulter = 2);
    case_terrain * getCaseTerrain(int x,int y);
    void faireJouerIA();
    void deselectAllCaseTerain();
    void rafraichirCase(int x,int y);
    unsigned int getNbTourMax();
    void setNbTourMax(unsigned int nb);
    bool getIAActiver();
    int getIADifficulter();
    void loadFile(QString fichier);
    void saveToFile(QString fichier);


public slots:
    void reinitialisation();
    void caseCliquer(int x, int y);

private:
    MainWindow *m_interface;
    unsigned int m_nbTourMax;
    unsigned int m_tourno;
    bool m_joueurIA;
    piece m_matricePiece[8][8]; // matrice du terrain permet de savoir ou sont les pions facilement
    int m_matriceGroupe[8][8]; // permet de connaitre le groupe d'une piece soit 1 pour noir, 2 pour blanc
    int m_matriceDeplacement[8][8]; // permet de savoir si une piece a bouger ou pas, toute les pieces a 1 n'ont pas ete bouger sinon 0
    int m_joueurQuiJoue;

    QVector<QPoint> m_pointSelectionner; // permet de donner les coordonees des futurs cibles
    QPoint m_origineSelectionner; // permet de stocker case selectionner
    QVector<QPoint> *m_coupPrecedent;

    case_terrain echiquier[8][8]; // cases effectives du terrain sur lequel appliquer le chargement d'image
    IA *m_IA;

    // token permetant a l'utilisateur de selectionner que les pieces qui permetent de sortir de l'echec
    QVector<QPoint> CaseDeplacementPossible;

    QPoint m_Posi_Rois1;
    QPoint m_Posi_Rois2;



    QGridLayout *m_layout;
};

#endif // TERRAIN_H
