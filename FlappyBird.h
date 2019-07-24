#ifndef FLAPPY_H
#define FLAPPY_H

#include <QtWidgets/QStyleOptionGraphicsItem>
#include <QtWidgets/QGraphicsItem>
#include <QtCore/QRectF>
#include <QtGui/QPainter>
#include <QtGui/QPixmap>
#include <QtGui/QKeyEvent>
#include <QtCore/QObject>
#include <QtWidgets/QGraphicsObject>


class Flappy : public QGraphicsObject
{
    Q_OBJECT
public:
   
    Flappy();
   ~Flappy();
    
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter* paint, const QStyleOptionGraphicsItem* option, QWidget* widget = Q_NULLPTR) Q_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent* event) Q_DECL_OVERRIDE;
    void advance(int phase) Q_DECL_OVERRIDE;
    void collisionsDetection();
    void outOfSceneDetection();
    void move();
    void currentScore();
    
signals:
    void outOfScene();
    void inCollision();
    void scoreIncreased();
    
private:
    static int s_gravity;
    int m_dy;
    QPixmap* m_image;
};
#endif //FLAPPY_H