#include "FlappyBird.h"
#include "Pipe.h"

#include <typeinfo>

#include <QtCore/QDebug>
#include <QtWidgets/QGraphicsScene>
#include <QtCore/QObject>
#include <QtGui/QPen>
#include <QtGui/QBrush>
#include <QtCore/QList>

//The acceleration due to gravity --> decreases the bird's up velocity by 2 every phase
int Flappy::s_gravity = 2;


//m_dy is the velocity of the bird --> initially going up when the game starts then dec-
//reasing by s_gravity every phase
Flappy::Flappy(): m_dy{-25}
{
    m_image = new QPixmap("images/yellow1.png");
    setFlag(QGraphicsItem::ItemIsFocusable);
}


Flappy::~Flappy()
{
    delete m_image;
}


QRectF Flappy::boundingRect() const
{
    return QRectF(scene() -> width() / 4, scene() -> height() / 2, m_image -> width(), 
                  m_image -> height());
}


void Flappy::paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    
    painter -> translate(scene() -> width() / 4, scene() -> height() / 2);
    
    //translate the painter to the center of the boundingbox
    painter -> translate(boundingRect().width() / 2, boundingRect().height() / 2);
    
    //this part has a lot of magic numbers --> not good
    
    if(m_dy >= -25 && m_dy <= -10)
    {
        painter -> save();
        painter -> rotate(-20);
        painter -> translate(-1*boundingRect().width() / 2, -1*boundingRect().height() / 2);
        painter -> drawPixmap(QPoint(0, 0), *m_image);
        painter -> restore();
    }
    else if(m_dy > -10 && m_dy <= 0)
    {
        painter -> save();
        painter -> rotate(-10);
        painter -> translate(-1*boundingRect().width() / 2, -1*boundingRect().height() / 2);
        painter -> drawPixmap(QPoint(0, 0), *m_image);
        painter -> restore();
    }
    else if(m_dy > 0 && m_dy <= 10)
    {
        painter -> save();
        painter -> rotate(10);
        painter -> translate(-1*boundingRect().width() / 2, -1*boundingRect().height() / 2);
        painter -> drawPixmap(QPoint(0, 0), *m_image);
        painter -> restore();
    }
    else
    {
        painter -> save();
        painter -> rotate(20);
        painter -> translate(-1*boundingRect().width() / 2, -1*boundingRect().height() / 2);
        painter -> drawPixmap(QPoint(0, 0), *m_image);
        painter -> restore();
    }
}


void Flappy::keyPressEvent(QKeyEvent* event)
{
    if(event -> key() == Qt::Key_Space)
    {
        m_dy = -15; //magic number -15
    }
}


void Flappy::collisionsDetection()
{
    //Collision detection between this player and pipes
    //TODO: investigate why you're getting a memory error when one 
    //function emits two signals due to different conditions
    
    QList<QGraphicsItem* > colliding_items = collidingItems();
    
    for(int i = 0; i < colliding_items.size(); i++)
    {
        if(typeid(*colliding_items[i]) == typeid(Pipe))
        {
            emit inCollision();
        }
    }
}


void Flappy::outOfSceneDetection()
{
     //Collision detection with scene boundary
    if(y() + boundingRect().height() > scene() -> height() / 2)
    {
        emit outOfScene();
    }
}


void Flappy::move()
{
    //TODO: make the bird to stay within the confines of the scene
    setPos(x(), y() + m_dy);
    m_dy += s_gravity;
}


void Flappy::advance(int phase)
{
    
    //TODO: really getting chowed on this part, don't know where the 
    //memory leak is coming from, maybe this is the part where a person
    //has to start joining a forum to understand what is happening
    //Q_UNUSED(phase);
    //GOT THE PART TO WORK BUT STILL NEED AN UNDERSTANDING OF WHY IT WAS
    //NOT WORKING IN THE FIRST 1000 TRIALS THAT I DID
    
    move();
    
    if(phase == 0)
    {
        outOfSceneDetection();
    }
    else
    {
        collisionsDetection();
    }
}

void Flappy::currentScore()
{
    QList<QGraphicsItem* > gameItems = scene() -> items();
    
    for(int i = 0u; i < gameItems.size(); i++)
    {
        if(typeid(*gameItems[i]) == typeid(Pipe) && gameItems[i] -> x() < -430)
        {
            //qDebug() << gameItems[i] -> x();
            emit scoreIncreased();
        }
    }
}


