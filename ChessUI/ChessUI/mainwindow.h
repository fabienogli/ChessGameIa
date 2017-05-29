#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "../../Chess/Chess/Plateau.h"
#include "../../Chess/Chess/Piece.h"

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


signals:
 //on transmet les coordonnées en paramètres
void movePiece(int i1,int i2,int i3,int i4);

public slots:
 void on_ok_button_clicked();
 void displayPlayerId(int id);
 //affiche ou supprime une pieces au debut
 void affichSuppInit(Piece * piece,int id,int i);
// mauvais deplacement();
 void badMove();
 void loseSignal1(int i);
 void coupJoue(int idjoueur,int xdep,int ydep,int xarr,int yarr);

private:
    Ui::MainWindow *ui;
    Plateau *plateau;
};

#endif // MAINWINDOW_H
