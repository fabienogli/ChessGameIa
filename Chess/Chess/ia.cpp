#include "ia.h"
#include "Plateau.h"
#include "Joueur.h"
#include "Piece.h"

ia::ia()
{


}
int ia::gagnant(int idJoueur){
    int tmp=0;
    return tmp;

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
int ia::min(Joueur *joueur,Plateau *plateau,int profondeur,int alpha,int beta){
    int tmp=0;
    return tmp;
}
void ia::setLevel(int i){
    this->level=i;
}
int ia::getLevel(){
    return level;
}

int ia::jouer()
{
    int tmp=0;
    return tmp;

}
int ia::eval(Plateau * plateau){
    int tmp=0;
    return tmp;
}

