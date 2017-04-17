#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "C:\Users\markk\OneDrive\DossiersGit\ChessGameIa\Chess\Chess\Plateau.h"
#include "C:\Users\markk\OneDrive\DossiersGit\ChessGameIa\Chess\Chess\Coordonnee.h"
#include "C:\Users\markk\OneDrive\DossiersGit\ChessGameIa\Chess\Chess\Case.h"
#include "C:\Users\markk\OneDrive\DossiersGit\ChessGameIa\Chess\Chess\Grille.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <iostream>
using namespace std;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    plateau = new Plateau();
    ui->setupUi(this);
    ui->tableWidget->setColumnWidth(0,20);
    ui->tableWidget->setColumnWidth(1,100);
    ui->tableWidget->setColumnWidth(2,100);
    QObject::connect(plateau,SIGNAL(afficherInit(Piece*,int)),this,SLOT(afficherInit(Piece*,int)));
    QObject::connect(ui->pushButton,SIGNAL(clicked(bool)),plateau,SLOT(displayPlateau()));

    //QPixmap pixmap;
    // bool loaded= pixmap.load("chessicons/King1.bmp");
    // std::cout << "image loaded = " << loaded << std::endl;
    /* pixmap = pixmap.scaled(45,45);
    QGraphicsScene* scene = new QGraphicsScene;
    scene->addPixmap(pixmap);
    ui->graphicsView->setScene(scene);*/

}
void MainWindow::afficherInit(Piece * piece, int id){
    QPixmap pixmap;
    //pixmap.fill(Qt::transparent);
    /* void MainWindow::afficherInit(){
    QPixmap pixmap;
    bool loaded= pixmap.load("chessicons/King1.bmp");
    std::cout << "image loaded = " << loaded << std::endl;
    pixmap = pixmap.scaled(45,45);
    QGraphicsScene* scene = new QGraphicsScene;
    scene->addPixmap(pixmap);
    ui->graphicsView->setScene(scene);*/

    switch((*piece).getId()){
    case 'R':
        switch (id) {
        case 0:
            pixmap.load("chessicons/bking.svg");
            break;
        case 1:
            pixmap.load("chessicons/wking.svg");
            break;
        default:
            break;
        }
        break;
    case 'F':
        switch (id) {
        case 0:
            pixmap.load("chessicons/bbishop.svg");
            break;
        case 1:
            pixmap.load("chessicons/wbishop.svg");
            break;
        default:
            break;
        }
        break;
    case 'C':
        switch (id) {
        case 0:
            pixmap.load("chessicons/bknight.svg");
            break;
        case 1:
            pixmap.load("chessicons/wknight.svg");
            break;
        default:
            break;
        }
        break;
    case 'T':
        switch (id) {
        case 0:
            pixmap.load("chessicons/brook.svg");
            break;
        case 1:
            pixmap.load("chessicons/wrook.svg");
            break;
        default:
            break;
        }
        break;
    case 'P':
        switch (id) {
        case 0:
            pixmap.load("chessicons/bpawn.svg");
            break;
        case 1:
            pixmap.load("chessicons/wpawn.svg");
            break;
        default:
            break;
        }
        break;
    default: break;
    }

    pixmap = pixmap.scaled(45,45);
    QGraphicsScene* scene = new QGraphicsScene;
    scene->addPixmap(pixmap);
    if((*piece).getCoordonne().getX() == 0 && (*piece).getCoordonne().getY()==0){
        ui->graphicsView->setScene(scene);
    }else if((*piece).getCoordonne().getX() == 0 && (*piece).getCoordonne().getY()==1){
        ui->graphicsView_3->setScene(scene);
    }else if((*piece).getCoordonne().getX() == 0 && (*piece).getCoordonne().getY()==2){
        ui->graphicsView_4->setScene(scene);

    }else if((*piece).getCoordonne().getX() == 0 && (*piece).getCoordonne().getY()==3){
        ui->graphicsView_5->setScene(scene);

    }else if((*piece).getCoordonne().getX() == 0 && (*piece).getCoordonne().getY()==4){
        ui->graphicsView_6->setScene(scene);

    }else if((*piece).getCoordonne().getX() == 0 && (*piece).getCoordonne().getY()==5){
        ui->graphicsView_7->setScene(scene);

    }else if((*piece).getCoordonne().getX() == 0 && (*piece).getCoordonne().getY()==6){
        ui->graphicsView_8->setScene(scene);

    }else if((*piece).getCoordonne().getX() == 0 && (*piece).getCoordonne().getY()==7){
        ui->graphicsView_9->setScene(scene);

    }else if((*piece).getCoordonne().getX() == 1 && (*piece).getCoordonne().getY()==0){
        ui->graphicsView_2->setScene(scene);

    }else if((*piece).getCoordonne().getX() == 1 && (*piece).getCoordonne().getY()==1){
        ui->graphicsView_21->setScene(scene);

    }else if((*piece).getCoordonne().getX() == 1 && (*piece).getCoordonne().getY()==2){
        ui->graphicsView_20->setScene(scene);

    }else if((*piece).getCoordonne().getX() == 1 && (*piece).getCoordonne().getY()==3){
        ui->graphicsView_19->setScene(scene);

    }else if((*piece).getCoordonne().getX() == 1 && (*piece).getCoordonne().getY()==4){
        ui->graphicsView_18->setScene(scene);

    }else if((*piece).getCoordonne().getX() == 1 && (*piece).getCoordonne().getY()==5){
        ui->graphicsView_17->setScene(scene);

    }else if((*piece).getCoordonne().getX() == 1 && (*piece).getCoordonne().getY()==6){
        ui->graphicsView_16->setScene(scene);

    }else if((*piece).getCoordonne().getX() == 1 && (*piece).getCoordonne().getY()==7){
        ui->graphicsView_31->setScene(scene);

    }else if((*piece).getCoordonne().getX() == 2 && (*piece).getCoordonne().getY()==0){
        ui->graphicsView_11->setScene(scene);

    }else if((*piece).getCoordonne().getX() == 2 && (*piece).getCoordonne().getY()==1){
        ui->graphicsView_24->setScene(scene);

    }else if((*piece).getCoordonne().getX() == 2 && (*piece).getCoordonne().getY()==2){
        ui->graphicsView_25->setScene(scene);

    }else if((*piece).getCoordonne().getX() == 2 && (*piece).getCoordonne().getY()==3){
        ui->graphicsView_26->setScene(scene);

    }else if((*piece).getCoordonne().getX() == 2 && (*piece).getCoordonne().getY()==4){
        ui->graphicsView_27->setScene(scene);

    }else if((*piece).getCoordonne().getX() == 2 && (*piece).getCoordonne().getY()==5){
        ui->graphicsView_28->setScene(scene);

    }else if((*piece).getCoordonne().getX() == 2 && (*piece).getCoordonne().getY()==6){
        ui->graphicsView_29->setScene(scene);

    }else if((*piece).getCoordonne().getX() == 2 && (*piece).getCoordonne().getY()==7){
        ui->graphicsView_30->setScene(scene);

    }else if((*piece).getCoordonne().getX() == 3 && (*piece).getCoordonne().getY()==0){
        ui->graphicsView_12->setScene(scene);

    }else if((*piece).getCoordonne().getX() == 3 && (*piece).getCoordonne().getY()==1){
        ui->graphicsView_23->setScene(scene);

    }else if((*piece).getCoordonne().getX() == 3 && (*piece).getCoordonne().getY()==2){
        ui->graphicsView_22->setScene(scene);

    }else if((*piece).getCoordonne().getX() == 3 && (*piece).getCoordonne().getY()==3){
        ui->graphicsView_61->setScene(scene);

    }else if((*piece).getCoordonne().getX() == 3 && (*piece).getCoordonne().getY()==4){
        ui->graphicsView_60->setScene(scene);

    }else if((*piece).getCoordonne().getX() == 3 && (*piece).getCoordonne().getY()==5){
        ui->graphicsView_59->setScene(scene);

    }else if((*piece).getCoordonne().getX() == 3 && (*piece).getCoordonne().getY()==6){
        ui->graphicsView_58->setScene(scene);

    }else if((*piece).getCoordonne().getX() == 3 && (*piece).getCoordonne().getY()==7){
        ui->graphicsView_57->setScene(scene);

    }else if((*piece).getCoordonne().getX() == 4 && (*piece).getCoordonne().getY()==0){
        ui->graphicsView_15->setScene(scene);

    }else if((*piece).getCoordonne().getX() == 4 && (*piece).getCoordonne().getY()==1){
        ui->graphicsView_51->setScene(scene);

    }else if((*piece).getCoordonne().getX() == 4 && (*piece).getCoordonne().getY()==2){
        ui->graphicsView_50->setScene(scene);

    }else if((*piece).getCoordonne().getX() == 4 && (*piece).getCoordonne().getY()==3){
        ui->graphicsView_52->setScene(scene);

    }else if((*piece).getCoordonne().getX() == 4 && (*piece).getCoordonne().getY()==4){
        ui->graphicsView_53->setScene(scene);

    }else if((*piece).getCoordonne().getX() == 4 && (*piece).getCoordonne().getY()==5){
        ui->graphicsView_54->setScene(scene);

    }else if((*piece).getCoordonne().getX() == 4 && (*piece).getCoordonne().getY()==6){
        ui->graphicsView_55->setScene(scene);

    }else if((*piece).getCoordonne().getX() == 4 && (*piece).getCoordonne().getY()==7){
        ui->graphicsView_56->setScene(scene);

    }else if((*piece).getCoordonne().getX() == 5 && (*piece).getCoordonne().getY()==0){
        ui->graphicsView_14->setScene(scene);

    }else if((*piece).getCoordonne().getX() == 5 && (*piece).getCoordonne().getY()==1){
        ui->graphicsView_49->setScene(scene);

    }else if((*piece).getCoordonne().getX() == 5 && (*piece).getCoordonne().getY()==2){
        ui->graphicsView_48->setScene(scene);

    }else if((*piece).getCoordonne().getX() == 5 && (*piece).getCoordonne().getY()==3){
        ui->graphicsView_47->setScene(scene);

    }else if((*piece).getCoordonne().getX() == 5 && (*piece).getCoordonne().getY()==4){
        ui->graphicsView_46->setScene(scene);

    }else if((*piece).getCoordonne().getX() == 5 && (*piece).getCoordonne().getY()==5){
        ui->graphicsView_45->setScene(scene);

    }else if((*piece).getCoordonne().getX() == 5 && (*piece).getCoordonne().getY()==6){
        ui->graphicsView_44->setScene(scene);

    }else if((*piece).getCoordonne().getX() == 5 && (*piece).getCoordonne().getY()==7){
        ui->graphicsView_43->setScene(scene);

    }else if((*piece).getCoordonne().getX() == 6 && (*piece).getCoordonne().getY()==0){
        ui->graphicsView_13->setScene(scene);

    }else if((*piece).getCoordonne().getX() == 6 && (*piece).getCoordonne().getY()==1){
        ui->graphicsView_36->setScene(scene);

    }else if((*piece).getCoordonne().getX() == 6 && (*piece).getCoordonne().getY()==2){
        ui->graphicsView_37->setScene(scene);

    }else if((*piece).getCoordonne().getX() == 6 && (*piece).getCoordonne().getY()==3){
        ui->graphicsView_38->setScene(scene);

    }else if((*piece).getCoordonne().getX() == 6 && (*piece).getCoordonne().getY()==4){
        ui->graphicsView_39->setScene(scene);

    }else if((*piece).getCoordonne().getX() == 6 && (*piece).getCoordonne().getY()==5){
        ui->graphicsView_40->setScene(scene);

    }else if((*piece).getCoordonne().getX() == 6 && (*piece).getCoordonne().getY()==6){
        ui->graphicsView_41->setScene(scene);

    }else if((*piece).getCoordonne().getX() == 6 && (*piece).getCoordonne().getY()==7){
        ui->graphicsView_42->setScene(scene);

    }else if((*piece).getCoordonne().getX() == 7 && (*piece).getCoordonne().getY()==0){
        ui->graphicsView_10->setScene(scene);

    }else if((*piece).getCoordonne().getX() == 7 && (*piece).getCoordonne().getY()==1){
        ui->graphicsView_35->setScene(scene);

    }else if((*piece).getCoordonne().getX() == 7 && (*piece).getCoordonne().getY()==2){
        ui->graphicsView_34->setScene(scene);

    }else if((*piece).getCoordonne().getX() == 7 && (*piece).getCoordonne().getY()==3){
        ui->graphicsView_33->setScene(scene);

    }else if((*piece).getCoordonne().getX() == 7 && (*piece).getCoordonne().getY()==4){
        ui->graphicsView_32->setScene(scene);

    }else if((*piece).getCoordonne().getX() == 7 && (*piece).getCoordonne().getY()==5){
        ui->graphicsView_65->setScene(scene);

    }else if((*piece).getCoordonne().getX() == 7 && (*piece).getCoordonne().getY()==6){
        ui->graphicsView_66->setScene(scene);

    }else if((*piece).getCoordonne().getX() == 7 && (*piece).getCoordonne().getY()==7){
        ui->graphicsView_67->setScene(scene);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}



