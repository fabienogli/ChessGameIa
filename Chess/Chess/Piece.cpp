#include "Piece.h"
#include "Plateau.h"

//Initialise la piece
Piece::Piece()
{
	alive = true;
    couleur = -1;
}

//Retourne les coordonne de la piece
Coordonnee Piece::getCoordonne()
{
	return *coordonnee;
}
int Piece::getCouleur(){
    return couleur;
}
void Piece::setCouleur(int i){
    this->couleur=i;
}

//Modifie les coordonne de la piece
void Piece::setCoordonnee(Coordonnee *coord)
{
	coordonnee = coord;
}
void Piece::setCoordonne(int x,int y){
    coordonnee->setX(x);
    coordonnee->setY(y);
}

//Methode lorsqu une piece mange une autre
void Piece::kill(Piece * piece)
{
    piece->~Piece();
}

QVector<QPoint> Piece::deplacementsPossible(int idJoueur,Plateau * plateau){

    QVector<QPoint> listDep;
    return listDep;
}

//Test pour voir si la piece est toujours en vie
bool Piece::isAlive()
{
	return alive;
}

//retourne son abscisse, son ordonnee et le nom de la piece
void Piece::afficher()
{
	std::cout <<"x= "<< getCoordonne().getX() << " et y= " << getCoordonne().getY() << " " << getId()<< std::endl;
}

//Methode pour tester un deplacement
bool Piece::testDeplacement(Coordonnee coord, Plateau * plateau)
{
    bool verif = false;
    return verif;
}

bool Piece::testDiagonal(Coordonnee coord, Plateau * plateau)
{
    int nbIter = 0;
    int x = coord.getX();
    int y = coord.getY();

    int i = getCoordonne().getX();
    int j = getCoordonne().getY();

    int operationX, operationY;

    if (x < i)
        operationX = -1;
    else
        operationX = 1;
    if (y < j)
        operationY = -1;
    else
        operationY = 1;
    bool moveAble = false;
    while (!moveAble && (i != x+operationX && j!= y+operationY )) {
        if (x == i && y == j)
            moveAble = true;
        else if(nbIter!=0 && plateau->caseAtOccupy(i,j))
            break;
        else {
            i += operationX;
            j += operationY;
            if(nbIter==0)
                nbIter =1;
        }
    }
    nbIter =0;
    return moveAble;
}

bool Piece::testVertical(Coordonnee coord, Plateau * plateau)
{
    int nbIter = 0;
	int y = getCoordonne().getY();
    int i = coord.getX();
    int j = coord.getY();
    int operation;
	if (j > y)
        operation = -1;
    else
        operation = 1;
	bool moveAble = false;
    if(i==coordonnee->getX())
    {
        while (!moveAble && j != y+operation ) {
            std::cout<<"I = "<<i<<" ET J ="<<j<<std::endl;
            if (y == j)
                moveAble = true;
            else if(nbIter !=0&&plateau->caseAtOccupy(i,j)){
                    break;
            }
            else{
                if(nbIter==0){
                        nbIter =1;
                }
                j+=operation;
            }

        }
    }
    nbIter =0;
	return moveAble;
}

bool Piece::testHorizontal(Coordonnee coord, Plateau * plateau)
{
    int nbIter = 0;
	int x = getCoordonne().getX();
    int i = coord.getX();
    int j = coord.getY();
    int operation;
    if (i > x)
        operation = -1;
    else
        operation = 1;
	bool moveAble = false;
    if(j==coordonnee->getY())
    {
        while (!moveAble && i != x+operation ) {
            if (x == i)
                moveAble = true;
            else if(nbIter!=0&&plateau->caseAtOccupy(i,j)){
                        break;
            }
            else
            {
                if(nbIter==0)
                    nbIter =1;
                i += operation;
            }
        }
    }
    nbIter =0;
	return moveAble;
}

//Methode de deplacement de la piece, si le test retourne vrai, la piece peut se deplacer
bool Piece::move(Coordonnee * coord, Coordonnee origin, Plateau* plateau)
{
    bool verif =false;
    std::cout << "je suis ici";std::cout << std::endl;
   // Coordonnee test(origin.getX() - (*coord).getX(), origin.getY() - (*coord).getY());
    //if (testDeplacement(test)) {
    if (testDeplacement(*coord, plateau)==true) {
       // setCoordonnee(new Coordonnee(*coord));
        //on test si il y a une autre piece sur la case
        if(plateau->caseAtOccupy(coord->getX(),coord->getY()))
        {
            if(couleur!=plateau->getGrille()->getCase(coord->getX(),coord->getY())->getCouleur())
                kill(plateau->getPiece(coord));
            else return false;
        }
        setCoordonne(coord->getX(),coord->getY());
        afficher();
        std::cout << "j'ai update les coord"<< std::endl;
        verif=true;
	}
    return verif;
}

//Destructeur de la piece
Piece::~Piece()
{
	alive = false;
	delete coordonnee;
}

char Piece::getId()
{
    return id_piece;
}




