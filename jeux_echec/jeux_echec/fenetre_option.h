#ifndef FENETRE_OPTION_H
#define FENETRE_OPTION_H
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>
#include <QButtonGroup>
#include <QSpinBox>
#include "terrain.h"



class Fenetre_Option : public QWidget
{
     Q_OBJECT
public:
    Fenetre_Option(terrain *mon_terrain ,QWidget * parent = 0);
    ~Fenetre_Option();
public slots:
    void validerOption();
private:
    QLabel *texteIADifficulty;
    QLabel *texteNombreTourMax;
    QLabel *texteActiverIA;

    QPushButton *valider;
    QPushButton *annuler;
    QVBoxLayout *layout;
    QHBoxLayout *layoutBoutonValidation;
    QHBoxLayout *layoutBoutonDiffIA;
    QHBoxLayout *layoutBoutonIAActiff;
    QHBoxLayout *layoutNbMax;

    QButtonGroup *groupeDiffIA;
    QRadioButton *buttonDiffIA1;
    QRadioButton *buttonDiffIA2;
    QRadioButton *buttonDiffIA3;

    QSpinBox *nbTourMax;

    QButtonGroup *groupeIAActif;
    QRadioButton *buttonIADisable;
    QRadioButton *buttonIAEnable;

    terrain *m_monTerrain;

};

#endif // FENETRE_OPTION_H
