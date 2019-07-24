#include "Pipe.h"

#include <QtWidgets/QGraphicsScene>
#include <QtCore/QTimer>
#include <QtCore/QDebug>


Pipe::Pipe(QGraphicsObject* parent): QGraphicsObject(parent)
{
	m_pipe = new QPixmap("images/greenPipe.png");
    
    //Once constructed, the pipe calls its move function every 50 milliseconds
    
	QTimer* timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer -> start(70);
}

Pipe::~Pipe()
{
    //Restores the memory used to store the image for this object once deleted
    
	delete m_pipe;
}


QRectF Pipe::boundingRect() const
{
    //The pipe first gets created at the right end of the screen, with dimensios
    //equal to those of the image used to display it (m_image)
    
	return QRectF(scene() -> width(), y(), m_pipe -> width(), m_pipe -> height());
}


void Pipe::paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
	             QWidget* widget)
{
	Q_UNUSED(option);
	Q_UNUSED(widget);

	painter -> drawPixmap(boundingRect().x(), boundingRect().y(), *m_pipe);
}


void Pipe::rotatePixmap()
{
	m_pipe = new QPixmap("images/upPipe.png");
}


void Pipe::move()
{
    
//    if(x() > -435)
//    {
	this -> setPos(x() - 5, y());
//    }
//    else
//    {
//    this -> setPos(x(), y());
//    }
//    
    //The negative of the scene width is used because m_pipe's 0,0 position is at the
    //far right of the screen, and decreases to the left, the direction in which the 
    //pipes are moviing ---> moving in the negative direction
    
	if(x() + m_pipe -> width() < -scene() -> width())
	{
		scene() -> removeItem(this);
		delete this;
	}
}





