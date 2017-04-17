#include "fenetre_option.h"

/**
 * \brief Fenetre_Option::Fenetre_Option()
 * Constructeur de la fenetre des options
 * \param[in] mon_terrain Prend un pointeur sur le terrain de la partie en cours
 */
Fenetre_Option::Fenetre_Option(terrain *mon_terrain ,QWidget * parent) : QWidget(parent)
{
    this->setWindowTitle("Option");
    this->m_monTerrain = mon_terrain;
    layout = new QVBoxLayout();
    layoutNbMax = new QHBoxLayout();
    layoutBoutonValidation = new QHBoxLayout();
    layoutBoutonDiffIA = new QHBoxLayout();
    layoutBoutonIAActiff = new QHBoxLayout();
    texteIADifficulty = new QLabel("Choisisez la difficulter de l'IA :",this);

    groupeDiffIA = new QButtonGroup(this);
    buttonDiffIA1 = new QRadioButton("Facile");
    buttonDiffIA2 = new QRadioButton("Moyen");
    buttonDiffIA3 = new QRadioButton("Difficile");

    switch(m_monTerrain->getIADifficulter())
    {
    case 1:
        buttonDiffIA1->setChecked(true);
        break;
    case 2:
        buttonDiffIA2->setChecked(true);
        break;
    case 3:
        buttonDiffIA3->setChecked(true);
        break;
    }

    groupeDiffIA->addButton(buttonDiffIA1,1);
    groupeDiffIA->addButton(buttonDiffIA2,2);
    groupeDiffIA->addButton(buttonDiffIA3,3);

    layoutBoutonDiffIA->addWidget(buttonDiffIA1);
    layoutBoutonDiffIA->addWidget(buttonDiffIA2);
    layoutBoutonDiffIA->addWidget(buttonDiffIA3);

    texteNombreTourMax = new QLabel("Entrer le nombre de tour maximum :",this);
    nbTourMax = new QSpinBox(this);
    nbTourMax->setRange(1,1000);
    nbTourMax->setValue(mon_terrain->getNbTourMax());
    layoutNbMax->addWidget(texteNombreTourMax);
    layoutNbMax->addWidget(nbTourMax);

    texteActiverIA = new QLabel("Activation / desactivation de l'IA' :",this);
    groupeIAActif = new QButtonGroup(this);
    buttonIAEnable = new QRadioButton("Activer",this);
    buttonIADisable = new QRadioButton("Desactiver",this);

    if(m_monTerrain->getIAActiver())
    {
        buttonIAEnable->setChecked(true);
    }
    else
    {
        buttonIADisable->setChecked(true);
    }

    groupeIAActif->addButton(buttonIAEnable,1);
    groupeIAActif->addButton(buttonIADisable,2);

    layoutBoutonIAActiff->addWidget(buttonIAEnable);
    layoutBoutonIAActiff->addWidget(buttonIADisable);

    valider = new QPushButton("Valider",this);
    connect(valider,SIGNAL(clicked()),this,SLOT(validerOption()));
    annuler = new QPushButton("Annuler",this);
    connect(annuler,SIGNAL(clicked()),this,SLOT(close()));
    layoutBoutonValidation->addWidget(annuler);
    layoutBoutonValidation->addWidget(valider);

    layout->addWidget(texteIADifficulty);
    layout->addLayout(layoutBoutonDiffIA);
    layout->addLayout(layoutNbMax);
    layout->addWidget(texteActiverIA);
    layout->addLayout(layoutBoutonIAActiff);

    layout->addLayout(layoutBoutonValidation);
    this->setLayout(layout);
}
/**
 * \brief Fenetre_Option::~Fenetre_Option()
 * Destructeur de la fenetre des options
 */
Fenetre_Option::~Fenetre_Option()
{
    delete texteIADifficulty;
    delete texteNombreTourMax;
    delete texteActiverIA;
    delete valider;
    delete annuler;
    delete layout;
    delete layoutBoutonValidation;
    delete layoutBoutonDiffIA;
    delete layoutBoutonIAActiff;
    delete layoutNbMax;
    delete groupeDiffIA;
    delete buttonDiffIA1;
    delete buttonDiffIA2;
    delete buttonDiffIA3;
    delete nbTourMax;
    delete groupeIAActif;
    delete buttonIADisable;
    delete buttonIAEnable;
}
/**
 * \brief Fenetre_Option::validerOption()
 * Fonction appele lors de la validation des options du jeux avec le bouton
 * Modifie les parametres du terrain pour coller a la nouvelle configuration
 */
void Fenetre_Option::validerOption()
{
    if(groupeIAActif->checkedId() == 1)
    {
        m_monTerrain->setIA(true,groupeDiffIA->checkedId());
    }
    else
    {
        m_monTerrain->setIA(false,groupeDiffIA->checkedId());
    }
    m_monTerrain->setNbTourMax(nbTourMax->value());
    this->close();

}

