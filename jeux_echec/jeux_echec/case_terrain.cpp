#include "case_terrain.h"
#include "terrain.h"
#include <QDebug>
#include <QPainter>
#include <QMouseEvent>
#include <QResizeEvent>

/**
 * \brief case_terrain::case_terrain()
 * Constructeur d'une Case du terrain
 */
case_terrain::case_terrain(QLabel *parent) : QLabel(parent)
{
    this->setCouleur(0);
    this->m_selected = 0;
    this->m_x = 0;
    this->m_y = 0;
    this->m_pieceSurLaCase = Rien;
    this->resize(40,40);
    this->m_monTerrain = NULL;
}
/**
 * \brief case_terrain::setTerrain()
 * Permet de definir un pointeur vers le terrain ou la case apparait
 * Doit etre OBLIGATOIREMENT appeler apres le constructeur
 * \param[in] mon_terrain Pointeur vers le terrain.
 */
void case_terrain::setTerrain(terrain *mon_terrain)
{
    this->m_monTerrain = mon_terrain;
}
/**
 * \brief case_terrain::resizeEvent()
 * Reecriture du Slot rezizeEvent pour pouvoir gerer le redimentionnement de la fenetre
 * \param[in] event Information sur l'évent.
 */
void case_terrain::resizeEvent ( QResizeEvent * event )
{
    if(this->m_couleurCase == 1)
    {
        QPixmap img("case_noir.png");
        if(m_pieceSurLaCase != Rien)
        {
           img =  superpositionImage(img, m_imagePiece);
        }
        if(m_selected)
        {
           img =  superpositionImage(img, QPixmap("halo.png"));
        }
        this->setPixmap(img.scaled(event->size().width(),event->size().height(),Qt::IgnoreAspectRatio));
    }
    else
    {
        QPixmap img("case_blanche.png");
        if(m_pieceSurLaCase != Rien)
        {
           img =  superpositionImage(img, m_imagePiece);
        }
        if(m_selected)
        {
           img =  superpositionImage(img, QPixmap("halo.png"));
        }
        this->setPixmap(img.scaled(event->size().width(),event->size().height(),Qt::IgnoreAspectRatio));
    }
    setMinimumSize(40,40);
}
/**
 * \brief case_terrain::mousePressEvent()
 * Reecriture du Slot mousePressEvent pour pouvoir gerer le clic sur la case
 * \param[in] event Information sur l'évent.
 */
void case_terrain::mousePressEvent ( QMouseEvent * event )
{
    if(event->button() == Qt::LeftButton)
    {
        emit clicked(this->m_x,this->m_y);
    }
}
/**
 * \brief case_terrain::setPosition()
 * Permet de définir la position de la case dans l'échiquier
 * \param[in] x Coordonnee en x.
 * \param[in] y Coordonnee en y.
 */
void case_terrain::setPosition(int x,int y)
{
    this->m_x = x;
    this->m_y = y;
}

/**
 * \brief case_terrain::deselect()
 * Permet de deselectionner la case : supprime l'entourage jaune autour de la case
 * l'image en dessous est conserve
 */
void case_terrain::deselect()
{
    m_selected = false;
    setCouleur(m_couleurCase);
    if(this->m_pieceSurLaCase != Rien)
    {
        this->setPixmap(superpositionImage(*this->pixmap(), m_imagePiece));
    }
    setMinimumSize(40,40);
}
/**
 * \brief case_terrain::select()
 * Permet de selectionner la case : ajoute un entourage jaune autour de la case
 * l'image en dessous est conserve
 */
void case_terrain::select()
{
    m_selected = true;
    this->setPixmap(superpositionImage(*this->pixmap(), QPixmap("halo.png")));
    setMinimumSize(40,40);
}
/**
 * \brief case_terrain::setCouleur()
 * Permet de définir la couleur de la case Noir/Blanche
 * \param[in] couleur 1 = noir , 2 = blanc.
 */

void case_terrain::setCouleur(int couleur)
{
    this->m_couleurCase = couleur;
    this->m_selected = false;
    if(m_couleurCase == 1)
    {
        QPixmap img("case_noir.png");
        m_imageCouleurCase = img;
        this->setPixmap(img.scaled(this->width(),this->height(),Qt::IgnoreAspectRatio));
    }
    else
    {
        QPixmap img("case_blanche.png");
        m_imageCouleurCase = img;
        this->setPixmap(img.scaled(this->width(),this->height(),Qt::IgnoreAspectRatio));
    }
}

/**
 * \brief case_terrain::setPiece()
 * Permet de definir la Piece sur la case. cette fonction repeint la case avec la piece dessus
 * elle se sert du groupe pour savoir si c'est noir ou blanc
 * \param[in] ma_piece Piece qui va se trouver sur la case
 * \param[in] groupe Couleur de la piece
 */
void case_terrain::setPiece(piece ma_piece,int groupe)
{   // on remet la case d'origine
    m_pieceSurLaCase = ma_piece;

    if(groupe == 1)
    {
        switch(ma_piece)
        {
            case Pion:
                m_imagePiece.load("pieces/noir_pion.png");
            break;
            case Rois:
                m_imagePiece.load("pieces/noir_roi.png");
            break;
            case Reine:
                m_imagePiece.load("pieces/noir_reine.png");
            break;
            case Fous:
                m_imagePiece.load("pieces/noir_fou.png");
            break;
            case Tour:
                m_imagePiece.load("pieces/noir_tour.png");
            break;
            case Cavalier:
                m_imagePiece.load("pieces/noir_cavalier.png");
            break;
            case Rien:
                setCouleur(m_couleurCase);
                return;
            break;
        }
    }
    else
    {
        switch(ma_piece)
        {
            case Pion:
                m_imagePiece.load("pieces/blanc_pion.png");
            break;
            case Rois:
                m_imagePiece.load("pieces/blanc_roi.png");
            break;
            case Reine:
                m_imagePiece.load("pieces/blanc_reine.png");
            break;
            case Fous:
                m_imagePiece.load("pieces/blanc_fou.png");
            break;
            case Tour:
                m_imagePiece.load("pieces/blanc_tour.png");
            break;
            case Cavalier:
                m_imagePiece.load("pieces/blanc_cavalier.png");
            break;
            case Rien:
                setCouleur(m_couleurCase);
                return;
            break;
        }
    }
    QPixmap var = superpositionImage(m_imageCouleurCase, m_imagePiece);
    this->setPixmap(var.scaled(this->width(),this->height(),Qt::IgnoreAspectRatio));
    setMinimumSize(40,40);
}
/**
 * \brief case_terrain::superpositionImage()
 * Fonction utilitaire qui permet de fusionner 2 images ensemble , avec la transparence cela me permet
 * d'afficher la case (blanche/noir) et un pion avec l'illumination de la case
 * \param[in] base Image de base
 * \param[in] overlay Image qui va se placer dessus
 */
QPixmap case_terrain::superpositionImage(QPixmap base, QPixmap overlay)
{
    int width = base.width();
    int height = base.height();
    if(width != 0 && height != 0 )
    {
        overlay = overlay.scaled(width,height);
        QPixmap result(width,height);
        result.fill(Qt::transparent); // force alpha channel
        {
            QPainter painter(&result);
            painter.drawPixmap(QPoint(0, 0), base);
            painter.drawPixmap(QPoint(0, 0), overlay);
            painter.end();
        }
        return result;
    }
    else
    {
        return QPixmap();
    }

}
