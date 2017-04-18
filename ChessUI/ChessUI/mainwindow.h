#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "C:\Users\markk\OneDrive\DossiersGit\ChessGameIa\Chess\Chess\Plateau.h"
#include "C:\Users\markk\OneDrive\DossiersGit\ChessGameIa\Chess\Chess\Piece.h"

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


public slots:
    //affiche toutes les pieces au debut
    void afficherInit(Piece * piece,int id);
   // void afficherInit();

signals:
 //on transmet les coordonnées en paramètres
void movePiece(int idJoueur,int i1,int i2,int i3,int i4);

private slots:
 void on_ok_button_clicked();
 void displayPlayerId(int id);

private:
    Ui::MainWindow *ui;
    Plateau *plateau;
};

#endif // MAINWINDOW_H
