#include "ia.h"
#include "Plateau.h"
#include "Joueur.h"
#include "Piece.h"

ia::ia()
{


}
int ia::gagnant(int joueur){

}
int ia::max(Joueur *joueur,Plateau *plateau,int profondeur,int alpha,int beta)
{
    int retour=0  ;
    int max = -10000;
    if(profondeur <= 0 || (retour = gagnant(joueur->getIdJoueur())) != 0)
        {
            if(profondeur <= 0)
            {
                return eval(plateau);
            }
            else
            {
                return retour;
            }
        }
         for(int x=0;x<8;x++)
         {
              for(int y=0;y<8;y++)
              {
                  int idPiece=(joueur->isAnyPiece(Coordonnee(x,y)));
                  if(idPiece != (-1)){
                    std::vector<Coordonnee> listeCoup;
                    switch(joueur->getDeck()[idPiece]->getId())
                                      {
                                          case 'P':

                                          break;
                                          case 'R':

                                          break;
                                          case 'F':

                                          break;
                                          case 'C':

                                          break;
                                          case 'T':

                                          break;
                                          default:

                                          break;
                                      }
                  }
              }
         }

    return max;
}
int ia::min(int idJoueur,Plateau *plateau,int profondeur,int alpha,int beta){

}
void ia::setLevel(int i){
    this->level=i;
}
int ia::getLevel(){
    return level;
}

int ia::jouer()
{

}
int ia::eval(Plateau * plateau){

}

