#include "mainwindow.h"
#include "fenetre_option.h"
#include <QFileDialog>
#include <QDebug>
#include <time.h>

/**
 * \brief MainWindow::MainWindow()
 * Constructeur de la fenetre principale
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    m_monTerrain = new terrain(this);
    m_layoutPrincipale = new QHBoxLayout;
    m_layoutScore = new QVBoxLayout;
    m_centre = new QWidget();
    temps_restant_partie = 2400;
    m_layoutPrincipale->addWidget(m_monTerrain,4);
    m_layoutPrincipale->addLayout(m_layoutScore);



    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(update_temp_jeux()));
    m_timer->start(1000);

    m_label_temps = new QLabel("Temps avant fin de Partie :");
    m_afficheur_temps = new QLabel("40:00");
    
    
    QVBoxLayout *layoutNoir = new QVBoxLayout();

    m_label_pionPrisNoir = new QLabel("Pion Pris : 0");
    m_label_tourPrisNoir = new QLabel("Tour Prise : 0");
    m_label_fouPrisNoir = new QLabel("Fou Pris : 0");
    m_label_cavalierPrisNoir = new QLabel("Cavalier Pris : 0");
    m_label_reinePrisNoir = new QLabel("Reine Prise : 0");


    QVBoxLayout *layoutBlanc = new QVBoxLayout();

    m_label_pionPrisBlanc = new QLabel("Pion Pris : 0");
    m_label_tourPrisBlanc = new QLabel("Tour Prise : 0");
    m_label_fouPrisBlanc = new QLabel("Fou Pris : 0");
    m_label_cavalierPrisBlanc = new QLabel("Cavalier Pris : 0");
    m_label_reinePrisBlanc = new QLabel("Reine Prise : 0");
    
    
    m_layoutScore->addWidget(m_label_temps);
    m_layoutScore->addWidget(m_afficheur_temps);
    m_layoutScore->addLayout(layoutNoir);
    m_layoutScore->addStretch(8);
    m_layoutScore->addLayout(layoutBlanc);

    layoutNoir->addWidget(m_label_pionPrisNoir);
    layoutNoir->addWidget(m_label_tourPrisNoir);
    layoutNoir->addWidget(m_label_fouPrisNoir);
    layoutNoir->addWidget(m_label_cavalierPrisNoir);
    layoutNoir->addWidget(m_label_reinePrisNoir);


    layoutBlanc->addWidget(m_label_pionPrisBlanc);
    layoutBlanc->addWidget(m_label_tourPrisBlanc);
    layoutBlanc->addWidget(m_label_fouPrisBlanc);
    layoutBlanc->addWidget(m_label_cavalierPrisBlanc);
    layoutBlanc->addWidget(m_label_reinePrisBlanc);

    this->resetScore();
    m_centre->setLayout(m_layoutPrincipale);
    this->setCentralWidget(m_centre);

    qsrand(time(NULL));
    connect(m_monTerrain,SIGNAL(destroyed()),this,SLOT(close()));
    this->initialisation();
}
/**
 * \brief MainWindow::stopStartSong
 * Permet de mettre en pause ou lancer le son
 */
void MainWindow::stopStartSong()
{
    if(m_player->state() == QMediaPlayer::PausedState)
    {
        m_player->play();
    }
    else
    {
        m_player->pause();
    }
}
/**
 * \brief MainWindow::SavPartieFichier
 * Enregistre la partie dans un fichier
 */
void MainWindow::SavPartieFichier()
{
    QString nom_fichier = QFileDialog::getSaveFileName(this);
    m_monTerrain->saveToFile(nom_fichier);
}
/**
 * \brief MainWindow::RestaurerPartieFichier
 * Demande quel partie vous voulez restaurer
 */
void MainWindow::RestaurerPartieFichier()
{
    QString nom_fichier = QFileDialog::getOpenFileName(this);
    m_monTerrain->loadFile(nom_fichier);
}
/**
 * \brief MainWindow::resetScore
 * Remet les valeurs des pièces prises a 0 et le temps de la partie a une valeur par defaut
 * Elles seront mises a jour plus tard
 */
void MainWindow::resetScore()
{
    m_nb_pionPrisNoir = 0;
    m_nb_tourPrisNoir = 0;
    m_nb_fouPrisNoir = 0;
    m_nb_cavalierPrisNoir = 0;
    m_nb_reinePrisNoir = 0;

    m_nb_pionPrisBlanc = 0;
    m_nb_tourPrisBlanc = 0;
    m_nb_fouPrisBlanc = 0;
    m_nb_cavalierPrisBlanc = 0;
    m_nb_reinePrisBlanc = 0;
    temps_restant_partie = 2400;
    this->updateaffichageall();
}
/**
 * \brief MainWindow::setScore
 *Permet de savoir combien de pièce il reste au joueur dans la partie sauvegarder
 * \param type Type de la pièce
 * \param nb Nombre de pièce du type donnee
 * \param joueur Numero du joueur
 */
void MainWindow::setScore(enum piece type,int nb, int joueur)
{
    if(joueur == 1)
    {
        switch(type)
        {
            case Pion:
                m_nb_pionPrisNoir = nb;
            break;
            case Rois:
            break;
            case Reine:
                m_nb_reinePrisNoir = nb;
            break;
            case Fous:
                m_nb_fouPrisNoir = nb;
            break;
            case Tour:
                m_nb_tourPrisNoir = nb;
            break;
            case Cavalier:
                m_nb_cavalierPrisNoir = nb;
            break;
            case Rien:
            break;
        }
    }
    else
    {
        switch(type)
        {
            case Pion:
                m_nb_pionPrisBlanc = nb;
            break;
            case Rois:
            break;
            case Reine:
                m_nb_reinePrisBlanc = nb;
            break;
            case Fous:
                m_nb_fouPrisNoir = nb;
            break;
            case Tour:
                m_nb_tourPrisBlanc = nb;
            break;
            case Cavalier:
                m_nb_cavalierPrisBlanc = nb;
            break;
            case Rien:
            break;
        }
    }
    this->updateaffichageall();

}
/**
 * \brief MainWindow::addtoScore
 * Ajoute le nombre de piece prise par le joueur
 * \param type Type de piece
 * \param joueur Numero du joueur
 */
void MainWindow::addtoScore(enum piece type, int joueur)
{
    if(joueur == 1)
    {
        switch(type)
        {
            case Pion:
                m_nb_pionPrisNoir++;
            break;
            case Rois:
            break;
            case Reine:
                m_nb_reinePrisNoir++;
            break;
            case Fous:
                m_nb_fouPrisNoir++;
            break;
            case Tour:
                m_nb_tourPrisNoir++;
            break;
            case Cavalier:
                m_nb_cavalierPrisNoir++;
            break;
            case Rien:
            break;
        }
    }
    else
    {
        switch(type)
        {
            case Pion:
                m_nb_pionPrisBlanc++;
            break;
            case Rois:
            break;
            case Reine:
                m_nb_reinePrisBlanc++;
            break;
            case Fous:
                m_nb_fouPrisNoir++;
            break;
            case Tour:
                m_nb_tourPrisBlanc++;
            break;
            case Cavalier:
                m_nb_cavalierPrisBlanc++;
            break;
            case Rien:
            break;
        }
    }
    this->updateaffichageall();

}
/**
 * \brief MainWindow::updateaffichageall
 * Met a jour l'affichage liste pieces prises
 */
void MainWindow::updateaffichageall()
{
    m_label_pionPrisNoir->setText("Pion Pris : "+QString::number(this->m_nb_pionPrisNoir));
    m_label_tourPrisNoir->setText("Tour Prise : "+QString::number(this->m_nb_tourPrisNoir));
    m_label_fouPrisNoir->setText("Fou Pris : "+QString::number(this->m_nb_fouPrisNoir));
    m_label_cavalierPrisNoir->setText("Cavalier Pris : "+QString::number(this->m_nb_cavalierPrisNoir));
    m_label_reinePrisNoir->setText("Reine Prise : "+QString::number(this->m_nb_reinePrisNoir));


    m_label_pionPrisBlanc->setText("Pion Pris : "+QString::number(this->m_nb_pionPrisBlanc));
    m_label_tourPrisBlanc->setText("Tour Prise : "+QString::number(this->m_nb_tourPrisBlanc));
    m_label_fouPrisBlanc->setText("Fou Pris : "+QString::number(this->m_nb_fouPrisBlanc));
    m_label_cavalierPrisBlanc->setText("Cavalier Pris : "+QString::number(this->m_nb_cavalierPrisBlanc));
    m_label_reinePrisBlanc->setText("Reine Prise : "+QString::number(this->m_nb_reinePrisBlanc));

}
/**
 * \brief MainWindow::getTempsrestant
 * Recupere le temps impartie pour la partie en cours et le retourne
 * \return Temps restant pour la partie en cours
 */
int MainWindow::getTempsrestant()
{
    return this->temps_restant_partie;
}
/**
 * \brief MainWindow::setTempsrestant
 * Mets a jour le compteur de temps de la partie en cours (utiliser lors du chargement d'une partie)
 * \param temps Nouveau temps impartie a la partie
 */
void MainWindow::setTempsrestant(int temps)
{
    this->temps_restant_partie = temps;
}
/**
 * \brief MainWindow::update_temp_jeux
 * Met a jour l'affichage du compteur de temps de la partie
 * Si temps ecoule, affiche une boite de dialogue pour redemarrer une nouvelle partie²
 */
void MainWindow::update_temp_jeux()
{

    if(temps_restant_partie == 0)
    {
        m_timer->stop();
        int ret = QMessageBox::question(this,"Match Nul","Temps impartie ecouler Math nul \nVoulez vous rejouez  ?",QMessageBox::Yes | QMessageBox::No);
        if(ret == QMessageBox::Yes)
        {
            m_monTerrain->reinitialisation();
        }
        else
        {
            exit(0);
        }
        temps_restant_partie=2400;
    }
    else
    {
        int minute  = temps_restant_partie / 60;
        int seconde = temps_restant_partie % 60;
        QString seconde_text;
        QString minute_text;
        if(seconde == 0)
        {
            seconde_text = QString::number(seconde) + "0";
        }
        else
        {
            seconde_text = QString::number(seconde);
        }
        if(minute == 0)
        {
            minute_text = QString::number(minute) + "0";
        }
        else
        {
            minute_text = QString::number(minute);
        }

        m_afficheur_temps->setText(minute_text+ ":" + seconde_text );
        temps_restant_partie--;
    }
}

/**
 * \brief MainWindow::~MainWindow()
 * Destructeur de la fenetre principale
 */
MainWindow::~MainWindow()
{
    delete m_monTerrain;
    delete m_menuQuiter;
    delete m_menuNouvellePartie;
    delete m_menuRecommencer;
    delete m_menuOption;
    delete m_aboutMenu;
    
    delete m_label_temps;
    delete m_afficheur_temps;

    delete m_label_pionPrisNoir;
    delete m_label_tourPrisNoir;
    delete m_label_fouPrisNoir;
    delete m_label_cavalierPrisNoir;
    delete m_label_reinePrisNoir;

    delete m_label_pionPrisBlanc;
    delete m_label_tourPrisBlanc;
    delete m_label_fouPrisBlanc;
    delete m_label_cavalierPrisBlanc;
    delete m_label_reinePrisBlanc;
    delete m_sauvegarderPartie;
    delete m_chargerPartie;
}
/**
 * \brief MainWindow::initialisation()
 * Initialise la fenetre principale
 */
void MainWindow::initialisation()
{   
    m_menuQuiter = new QAction("Quitter",this);
    connect(m_menuQuiter,SIGNAL(triggered()),this,SLOT(close()));

    m_menuNouvellePartie = new QAction("Nouvelle Partie",this);
    connect(m_menuNouvellePartie,SIGNAL(triggered()),this,SLOT(lancerNouvellePartie()));

    m_menuRecommencer = new QAction("Recommencer Partie",this);
    connect(m_menuRecommencer,SIGNAL(triggered()),m_monTerrain,SLOT(reinitialisation()));

    m_sauvegarderPartie = new QAction("Sauvegarder la partie",this);
    connect(m_sauvegarderPartie,SIGNAL(triggered()),this,SLOT(SavPartieFichier()));

    m_chargerPartie = new QAction("Charger la partie",this);
    connect(m_chargerPartie,SIGNAL(triggered()),this,SLOT(RestaurerPartieFichier()));

    m_stopstartSong = new QAction("Stop/Start",this);
    connect(m_stopstartSong,SIGNAL(triggered()),this,SLOT(stopStartSong()));

    m_menuOption = new QAction("Option",this);
    connect(m_menuOption,SIGNAL(triggered()),this,SLOT(afficherOption()));

   m_player = new QMediaPlayer;
   QDir var;
   m_playlist = new QMediaPlaylist;
   if(QFile::exists(var.absoluteFilePath("son/1.mp3")))
        m_playlist->addMedia(QUrl::fromLocalFile(var.absoluteFilePath("1.mp3")));/*
   if(QFile::exists(var.absoluteFilePath("2.mp3")))
        m_playlist->addMedia(QUrl::fromLocalFile(var.absoluteFilePath("2.mp3")));
   if(QFile::exists(var.absoluteFilePath("3.mp3")))
        m_playlist->addMedia(QUrl::fromLocalFile(var.absoluteFilePath("3.mp3")));
   if(QFile::exists(var.absoluteFilePath("4.mp3")))
        m_playlist->addMedia(QUrl::fromLocalFile(var.absoluteFilePath("4.mp3")));
   if(QFile::exists(var.absoluteFilePath("5.mp3")))
        m_playlist->addMedia(QUrl::fromLocalFile(var.absoluteFilePath("5.mp3")));
   if(QFile::exists(var.absoluteFilePath("6.mp3")))
        m_playlist->addMedia(QUrl::fromLocalFile(var.absoluteFilePath("6.mp3")));
   if(QFile::exists(var.absoluteFilePath("7.mp3")))
        m_playlist->addMedia(QUrl::fromLocalFile(var.absoluteFilePath("7.mp3")));
   if(QFile::exists(var.absoluteFilePath("8.mp3")))
        m_playlist->addMedia(QUrl::fromLocalFile(var.absoluteFilePath("8.mp3")));*/


   m_playlist->setPlaybackMode(QMediaPlaylist::Random);

   m_player->setPlaylist(m_playlist);
   m_player->setVolume(50);
   m_player->play();

    m_aboutMenu = new QAction("?",this);
    QMenu *me_fichier = menuBar()->addMenu("Fichier");
    me_fichier->addAction(m_menuNouvellePartie);
    me_fichier->addAction(m_menuRecommencer);
    me_fichier->addAction(m_sauvegarderPartie);
    me_fichier->addAction(m_chargerPartie);
    me_fichier->addAction(m_menuOption);
    me_fichier->addAction(m_menuQuiter);

    QMenu *me_son = menuBar()->addMenu("Son");
    me_son->addAction(m_stopstartSong);

    QMenu *me_about = menuBar()->addMenu("?");
    me_about->addAction(m_aboutMenu);
}

/**
 * \brief MainWindow::lancerNouvellePartie()
 * Permet que lorsque l'on clique sur nouvelle partie la partie se recharge correctement
 */
void MainWindow::lancerNouvellePartie()
{
    int ret = QMessageBox::question(this,"Question","VOulez vous jouez contre une IA ?",QMessageBox::Yes | QMessageBox::No);
    if(ret == QMessageBox::Yes)
    {
       m_monTerrain->setIA(true);
    }
    else
    {
        m_monTerrain->setIA(false);
    }
    m_monTerrain->setIA(false);
    m_monTerrain->reinitialisation();
}

/**
 * \brief MainWindow::afficherOption()
 * Affiche la fenetre d'option du jeux
 */
void MainWindow::afficherOption()
{
    Fenetre_Option *test = new Fenetre_Option(m_monTerrain);
    test->setWindowModality (Qt::ApplicationModal);
    test->show();
}
