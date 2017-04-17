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

private:
    Ui::MainWindow *ui;
    Plateau *plateau;
};

#endif // MAINWINDOW_H
