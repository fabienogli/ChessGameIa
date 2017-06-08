#ifndef CASE_TERRAIN_H
#define CASE_TERRAIN_H

#include <QLabel>
#include "Definement.h"
class terrain;


class case_terrain : public QLabel
{
    int m_couleurCase; // si la case est noir ou blanche
    bool m_selected;
    int m_x,m_y;
    piece m_pieceSurLaCase;
    terrain *m_monTerrain;
    QPixmap m_imageCouleurCase;
    QPixmap m_imagePiece;
    Q_OBJECT

public:
    case_terrain(QLabel *parent = 0);
    void setTerrain(terrain * mon_terrain);
    void mousePressEvent ( QMouseEvent * event );
    void resizeEvent ( QResizeEvent * event );
    void setCouleur(int couleur);
    void deselect();
    void select();
    void setPosition(int x,int y);
    void setPiece(piece ma_piece,int groupe);
    QPixmap superpositionImage(QPixmap base, QPixmap overlay);

signals:
    void clicked(int x,int y);

};

#endif // CASE_TERRAIN_H
