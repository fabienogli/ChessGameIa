#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnWidth(0,20);
    ui->tableWidget->setColumnWidth(1,100);
    ui->tableWidget->setColumnWidth(2,100);
    //QGraphicsScene scene;
  //  ui->graphicsView(&scene);
  //  QGraphicsPixmapItem item(QPixmap("C:\Users\markk\OneDrive\DossiersGit\ChessGameIa\chessicons\King1.bmp"));
   //  scene.addItem(&item);

}

MainWindow::~MainWindow()
{
    delete ui;
}
