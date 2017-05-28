#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../../Chess/Chess/Plateau.h"
#include "../../Chess/Chess/Coordonnee.h"
#include "../../Chess/Chess/Case.h"
#include "../../Chess/Chess/Grille.h"
#include "../../Chess/Chess/Joueur.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPixmap>
#include <QMessageBox>
#include <QGraphicsPixmapItem>
#include <iostream>
#include <QDirIterator>
#include <QDebug>
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
    //afficher une piece
    QObject::connect(plateau,SIGNAL(affichSuppInit(Piece*,int,int)),this,SLOT(affichSuppInit(Piece*,int,int)));
    //afficher idJoueur
    QObject::connect(plateau,SIGNAL(displayPlayerId(int)),this,SLOT(displayPlayerId(int)),Qt::UniqueConnection);
    //QObject::connect(plateau,SIGNAL(),this,SLOT());

    //initialiser plateau
//    QObject::connect(ui->actionLancer_Partie,SIGNAL(triggered(bool)),plateau,SLOT(displayPlateau()),Qt::UniqueConnection);
//    QObject::connect(ui->actionLancer_Partie,SIGNAL(triggered(bool)),plateau,SLOT(sentDisplayPlayerId()),Qt::UniqueConnection);
    QAction * launch = ui->actionLancer_Partie->addAction("Lancement");
    connect(launch,SIGNAL(triggered(bool)), plateau, SLOT(displayPlateau()),Qt::UniqueConnection);
    connect(launch,SIGNAL(triggered(bool)), plateau, SLOT(sentDisplayPlayerId()),Qt::UniqueConnection);

    //Choix niveau IA
    QObject::connect(ui->actionniveau1_2,SIGNAL(triggered(bool)),plateau,SLOT(setLevel(1)),Qt::UniqueConnection);
    QObject::connect(ui->actionniveau_7,SIGNAL(triggered(bool)),plateau,SLOT(setLevel(3)),Qt::UniqueConnection);
    QObject::connect(ui->actionniveau_8,SIGNAL(triggered(bool)),plateau,SLOT(setLevel(2)),Qt::UniqueConnection);
    QObject::connect(ui->actionPar_d_faut_2,SIGNAL(triggered(bool)),plateau,SLOT(setLevel(2)),Qt::UniqueConnection);

    //deplacer une piece
    QObject::connect(ui->ok_button,SIGNAL(clicked(bool)),this,SLOT(on_ok_button_clicked()),Qt::UniqueConnection);
    QObject::connect(this,SIGNAL(movePiece(int,int,int,int)),plateau,SLOT(movePiece(int,int,int,int)),Qt::UniqueConnection);
    QObject::connect(plateau,SIGNAL(badMove()),this,SLOT(badMove()),Qt::UniqueConnection);
    QObject::connect(plateau,SIGNAL(noPiece()),this,SLOT(noPiece()),Qt::UniqueConnection);

    //QPixmap pixmap;
    // bool loaded= pixmap.load("chessicons/King1.bmp");
    // std::cout << "image loaded = " << loaded << std::endl;
    /* pixmap = pixmap.scaled(45,45);
    QGraphicsScene* scene = new QGraphicsScene;
    scene->addPixmap(pixmap);
    ui->graphicsView->setScene(scene);*/

}
void MainWindow::displayPlayerId(int id){
    ui->label_2->setText(QString::fromStdString(plateau->getJoueurActif()->getNomjoueur()));
}
void MainWindow::badMove(){
    QMessageBox::critical(this, "Mauvais déplacement", "Ce déplacement n'est pas autorisé!");
}

void MainWindow::noPiece(){
        QMessageBox::critical(this, "Mauvaise Case", "Cette case n'a pas de pièce !");
}

void MainWindow::affichSuppInit(Piece * piece, int id,int i){
    //std::cout << "image loaded";
    QPixmap pixmap;
//    bool verid =pixmap.load(":/chessicons/bKing.png");

//    QDirIterator it(":", QDirIterator::Subdirectories);
//    while (it.hasNext()) {
//        qDebug() << it.next();
//    }
    //pixmap.fill(Qt::transparent);
    /* void MainWindow::afficherInit(){
    QPixmap pixmap;
    bool loaded= pixmap.load("chessicons/King1.bmp");
    std::cout << "image loaded = " << loaded << std::endl;
    pixmap = pixmap.scaled(45,45);
    QGraphicsScene* scene = new QGraphicsScene;
    scene->addPixmap(pixmap);
    ui->graphicsView->setScene(scene);*/
    if(i==0){
        std::cout << "jaffiche"<<id;std::cout << std::endl;
        switch((*piece).getId()){
        case 'R':
            switch (id) {
            case 0:
                std::cout<<"Roi noir"<<std::endl;
                pixmap.load(":/chessicons/bKing.png");
                break;
            case 1:
                pixmap.load(":/chessicons/wKing.png");
                break;
            default:
                break;
            }
            break;
        case 'F':
            switch (id) {
            case 0:
                pixmap.load(":/chessicons/bMad.png");
                break;
            case 1:
                pixmap.load(":/chessicons/wMAd.png");
                break;
            default:
                break;
            }
            break;
        case 'C':
            switch (id) {
            case 0:
                pixmap.load(":/chessicons/bKnight.png");
                break;
            case 1:
                pixmap.load(":/chessicons/wKnight.png");
                break;
            default:
                break;
            }
            break;
        case 'T':
            switch (id) {
            case 0:
                pixmap.load(":/chessicons/bTower.png");
                break;
            case 1:
                pixmap.load(":/chessicons/wTower.png");
                break;
            default:
                break;
            }
            break;
        case 'P':
            switch (id) {
            case 0:
                pixmap.load(":/chessicons/bPawn.png");
                break;
            case 1:
                pixmap.load(":/chessicons/wPawn.png");
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
    }else{
        std::cout << "jefface";std::cout << std::endl;
        pixmap.load("");

    }
    pixmap = pixmap.scaled(45,45);
    QGraphicsScene* scene = new QGraphicsScene;
    scene->addPixmap(pixmap);
    if((*piece).getCoordonne()->getX() == 0 && (*piece).getCoordonne()->getY()==0){
        ui->graphicsView->setScene(scene);
    }else if((*piece).getCoordonne()->getX() == 0 && (*piece).getCoordonne()->getY()==1){
        ui->graphicsView_3->setScene(scene);
    }else if((*piece).getCoordonne()->getX() == 0 && (*piece).getCoordonne()->getY()==2){
        ui->graphicsView_4->setScene(scene);

    }else if((*piece).getCoordonne()->getX() == 0 && (*piece).getCoordonne()->getY()==3){
        ui->graphicsView_5->setScene(scene);

    }else if((*piece).getCoordonne()->getX() == 0 && (*piece).getCoordonne()->getY()==4){
        ui->graphicsView_6->setScene(scene);

    }else if((*piece).getCoordonne()->getX() == 0 && (*piece).getCoordonne()->getY()==5){
        ui->graphicsView_7->setScene(scene);

    }else if((*piece).getCoordonne()->getX() == 0 && (*piece).getCoordonne()->getY()==6){
        ui->graphicsView_8->setScene(scene);

    }else if((*piece).getCoordonne()->getX() == 0 && (*piece).getCoordonne()->getY()==7){
        ui->graphicsView_9->setScene(scene);

    }else if((*piece).getCoordonne()->getX() == 1 && (*piece).getCoordonne()->getY()==0){
        ui->graphicsView_2->setScene(scene);

    }else if((*piece).getCoordonne()->getX() == 1 && (*piece).getCoordonne()->getY()==1){
        ui->graphicsView_21->setScene(scene);

    }else if((*piece).getCoordonne()->getX() == 1 && (*piece).getCoordonne()->getY()==2){
        ui->graphicsView_20->setScene(scene);

    }else if((*piece).getCoordonne()->getX() == 1 && (*piece).getCoordonne()->getY()==3){
        ui->graphicsView_19->setScene(scene);

    }else if((*piece).getCoordonne()->getX() == 1 && (*piece).getCoordonne()->getY()==4){
        ui->graphicsView_18->setScene(scene);

    }else if((*piece).getCoordonne()->getX() == 1 && (*piece).getCoordonne()->getY()==5){
        ui->graphicsView_17->setScene(scene);

    }else if((*piece).getCoordonne()->getX() == 1 && (*piece).getCoordonne()->getY()==6){
        ui->graphicsView_16->setScene(scene);

    }else if((*piece).getCoordonne()->getX() == 1 && (*piece).getCoordonne()->getY()==7){
        ui->graphicsView_31->setScene(scene);

    }else if((*piece).getCoordonne()->getX() == 2 && (*piece).getCoordonne()->getY()==0){
        ui->graphicsView_11->setScene(scene);

    }else if((*piece).getCoordonne()->getX() == 2 && (*piece).getCoordonne()->getY()==1){
        ui->graphicsView_24->setScene(scene);

    }else if((*piece).getCoordonne()->getX() == 2 && (*piece).getCoordonne()->getY()==2){
        ui->graphicsView_25->setScene(scene);

    }else if((*piece).getCoordonne()->getX() == 2 && (*piece).getCoordonne()->getY()==3){
        ui->graphicsView_26->setScene(scene);

    }else if((*piece).getCoordonne()->getX() == 2 && (*piece).getCoordonne()->getY()==4){
        ui->graphicsView_27->setScene(scene);

    }else if((*piece).getCoordonne()->getX() == 2 && (*piece).getCoordonne()->getY()==5){
        ui->graphicsView_28->setScene(scene);

    }else if((*piece).getCoordonne()->getX() == 2 && (*piece).getCoordonne()->getY()==6){
        ui->graphicsView_29->setScene(scene);

    }else if((*piece).getCoordonne()->getX() == 2 && (*piece).getCoordonne()->getY()==7){
        ui->graphicsView_30->setScene(scene);

    }else if((*piece).getCoordonne()->getX() == 3 && (*piece).getCoordonne()->getY()==0){
        ui->graphicsView_12->setScene(scene);

    }else if((*piece).getCoordonne()->getX() == 3 && (*piece).getCoordonne()->getY()==1){
        ui->graphicsView_23->setScene(scene);

    }else if((*piece).getCoordonne()->getX() == 3 && (*piece).getCoordonne()->getY()==2){
        ui->graphicsView_22->setScene(scene);

    }else if((*piece).getCoordonne()->getX() == 3 && (*piece).getCoordonne()->getY()==3){
        ui->graphicsView_61->setScene(scene);

    }else if((*piece).getCoordonne()->getX() == 3 && (*piece).getCoordonne()->getY()==4){
        ui->graphicsView_60->setScene(scene);

    }else if((*piece).getCoordonne()->getX() == 3 && (*piece).getCoordonne()->getY()==5){
        ui->graphicsView_59->setScene(scene);

    }else if((*piece).getCoordonne()->getX() == 3 && (*piece).getCoordonne()->getY()==6){
        ui->graphicsView_58->setScene(scene);

    }else if((*piece).getCoordonne()->getX() == 3 && (*piece).getCoordonne()->getY()==7){
        ui->graphicsView_57->setScene(scene);

    }else if((*piece).getCoordonne()->getX() == 4 && (*piece).getCoordonne()->getY()==0){
        ui->graphicsView_15->setScene(scene);

    }else if((*piece).getCoordonne()->getX() == 4 && (*piece).getCoordonne()->getY()==1){
        ui->graphicsView_51->setScene(scene);

    }else if((*piece).getCoordonne()->getX() == 4 && (*piece).getCoordonne()->getY()==2){
        ui->graphicsView_50->setScene(scene);

    }else if((*piece).getCoordonne()->getX() == 4 && (*piece).getCoordonne()->getY()==3){
        ui->graphicsView_52->setScene(scene);

    }else if((*piece).getCoordonne()->getX() == 4 && (*piece).getCoordonne()->getY()==4){
        ui->graphicsView_53->setScene(scene);

    }else if((*piece).getCoordonne()->getX() == 4 && (*piece).getCoordonne()->getY()==5){
        ui->graphicsView_54->setScene(scene);

    }else if((*piece).getCoordonne()->getX() == 4 && (*piece).getCoordonne()->getY()==6){
        ui->graphicsView_55->setScene(scene);

    }else if((*piece).getCoordonne()->getX() == 4 && (*piece).getCoordonne()->getY()==7){
        ui->graphicsView_56->setScene(scene);

    }else if((*piece).getCoordonne()->getX() == 5 && (*piece).getCoordonne()->getY()==0){
        ui->graphicsView_14->setScene(scene);

    }else if((*piece).getCoordonne()->getX() == 5 && (*piece).getCoordonne()->getY()==1){
        ui->graphicsView_49->setScene(scene);

    }else if((*piece).getCoordonne()->getX() == 5 && (*piece).getCoordonne()->getY()==2){
        ui->graphicsView_48->setScene(scene);

    }else if((*piece).getCoordonne()->getX() == 5 && (*piece).getCoordonne()->getY()==3){
        ui->graphicsView_47->setScene(scene);

    }else if((*piece).getCoordonne()->getX() == 5 && (*piece).getCoordonne()->getY()==4){
        ui->graphicsView_46->setScene(scene);

    }else if((*piece).getCoordonne()->getX() == 5 && (*piece).getCoordonne()->getY()==5){
        ui->graphicsView_45->setScene(scene);

    }else if((*piece).getCoordonne()->getX() == 5 && (*piece).getCoordonne()->getY()==6){
        ui->graphicsView_44->setScene(scene);

    }else if((*piece).getCoordonne()->getX() == 5 && (*piece).getCoordonne()->getY()==7){
        ui->graphicsView_43->setScene(scene);

    }else if((*piece).getCoordonne()->getX() == 6 && (*piece).getCoordonne()->getY()==0){
        ui->graphicsView_13->setScene(scene);

    }else if((*piece).getCoordonne()->getX() == 6 && (*piece).getCoordonne()->getY()==1){
        ui->graphicsView_36->setScene(scene);

    }else if((*piece).getCoordonne()->getX() == 6 && (*piece).getCoordonne()->getY()==2){
        ui->graphicsView_37->setScene(scene);

    }else if((*piece).getCoordonne()->getX() == 6 && (*piece).getCoordonne()->getY()==3){
        ui->graphicsView_38->setScene(scene);

    }else if((*piece).getCoordonne()->getX() == 6 && (*piece).getCoordonne()->getY()==4){
        ui->graphicsView_39->setScene(scene);

    }else if((*piece).getCoordonne()->getX() == 6 && (*piece).getCoordonne()->getY()==5){
        ui->graphicsView_40->setScene(scene);

    }else if((*piece).getCoordonne()->getX() == 6 && (*piece).getCoordonne()->getY()==6){
        ui->graphicsView_41->setScene(scene);

    }else if((*piece).getCoordonne()->getX() == 6 && (*piece).getCoordonne()->getY()==7){
        ui->graphicsView_42->setScene(scene);

    }else if((*piece).getCoordonne()->getX() == 7 && (*piece).getCoordonne()->getY()==0){
        ui->graphicsView_10->setScene(scene);

    }else if((*piece).getCoordonne()->getX() == 7 && (*piece).getCoordonne()->getY()==1){
        ui->graphicsView_35->setScene(scene);

    }else if((*piece).getCoordonne()->getX() == 7 && (*piece).getCoordonne()->getY()==2){
        ui->graphicsView_34->setScene(scene);

    }else if((*piece).getCoordonne()->getX() == 7 && (*piece).getCoordonne()->getY()==3){
        ui->graphicsView_33->setScene(scene);

    }else if((*piece).getCoordonne()->getX() == 7 && (*piece).getCoordonne()->getY()==4){
        ui->graphicsView_32->setScene(scene);

    }else if((*piece).getCoordonne()->getX() == 7 && (*piece).getCoordonne()->getY()==5){
        ui->graphicsView_65->setScene(scene);

    }else if((*piece).getCoordonne()->getX() == 7 && (*piece).getCoordonne()->getY()==6){
        ui->graphicsView_66->setScene(scene);

    }else if((*piece).getCoordonne()->getX() == 7 && (*piece).getCoordonne()->getY()==7){
        ui->graphicsView_67->setScene(scene);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ok_button_clicked()
{
    emit movePiece(ui->comboBox->currentIndex(),ui->comboBox_2->currentIndex(),ui->comboBox_3->currentIndex(),ui->comboBox_4->currentIndex());
}
