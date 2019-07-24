#include "Button.h"
#include <QtGui/QBrush>
#include <QtWidgets/QGraphicsTextItem>


Button::Button(QString name, QGraphicsRectItem* parent): QGraphicsRectItem(parent)
{
    //Drawing the rectangle
    setRect(0, 0, 200, 50);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::yellow);
    setBrush(brush);
    
    //Drawing the text
    m_text =  new QGraphicsTextItem(name, this);
    int xPos = rect().width() / 2 - m_text -> boundingRect().width() / 2;
    int yPos = rect().height() / 2 - m_text -> boundingRect().height() / 2;
    
    m_text -> setPos(xPos, yPos);
    
    //Allow button to respond to hover events
    setAcceptHoverEvents(true);
    
}


void Button::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    Q_UNUSED(event);
    emit clicked();
}


void Button::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
    Q_UNUSED(event);
    //Change the color of the button to yellow
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkYellow);
    setBrush(brush);
}

void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
    Q_UNUSED(event);
    
    //Change the color of the button to dark yellow
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::yellow);
    setBrush(brush);
}