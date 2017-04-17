#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QGridLayout>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QTimer>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QMediaPlaylist>
class terrain;
#include "terrain.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void addtoScore(enum piece type, int joueur);
    void updateaffichageall();
    void setScore(enum piece type,int nb, int joueur);
    int getTempsrestant();
    void setTempsrestant(int temps);
    void resetScore();
private slots:

    void lancerNouvellePartie();
    void afficherOption();
    void update_temp_jeux();
    void SavPartieFichier();
    void RestaurerPartieFichier();
    void stopStartSong();

private:
    void initialisation();

    int temps_restant_partie;
    QWidget *m_centre;
    QTimer *m_timer;
    QLabel *m_label_temps;
    QLabel *m_afficheur_temps;

    QLabel *m_label_pionPrisNoir;
    QLabel *m_label_tourPrisNoir;
    QLabel *m_label_fouPrisNoir;
    QLabel *m_label_cavalierPrisNoir;
    QLabel *m_label_reinePrisNoir;

    QLabel *m_label_pionPrisBlanc;
    QLabel *m_label_tourPrisBlanc;
    QLabel *m_label_fouPrisBlanc;
    QLabel *m_label_cavalierPrisBlanc;
    QLabel *m_label_reinePrisBlanc;

    int m_nb_pionPrisNoir;
    int m_nb_tourPrisNoir;
    int m_nb_fouPrisNoir;
    int m_nb_cavalierPrisNoir;
    int m_nb_reinePrisNoir;

    int m_nb_pionPrisBlanc;
    int m_nb_tourPrisBlanc;
    int m_nb_fouPrisBlanc;
    int m_nb_cavalierPrisBlanc;
    int m_nb_reinePrisBlanc;

    QHBoxLayout *m_layoutPrincipale;
    QVBoxLayout *m_layoutScore;

    QAction *m_menuQuiter;
    QAction *m_menuNouvellePartie;
    QAction *m_menuRecommencer;
    QAction *m_menuOption;
    QAction *m_sauvegarderPartie;
    QAction *m_chargerPartie;
    QAction *m_aboutMenu;
    QAction *m_stopstartSong;
    terrain *m_monTerrain;
    QMediaPlayer *m_player;
    QMediaPlaylist *m_playlist;
};

#endif // MAINWINDOW_H
