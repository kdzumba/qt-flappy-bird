#include "Menu.h"

#include <QtWidgets/QGraphicsTextItem>
#include <QtWidgets/QGraphicsScene>
#include <QtGui/QFont>
#include <QtGui/QBrush>
#include <QtCore/QDebug>


Menu::Menu(const QString& title, MENU_TYPE type, QGraphicsItem* parent):QGraphicsItem(parent),     
 m_title{title}, m_type{type}
{
    if(m_type == MENU_TYPE::MainMenu)
    {
        Button* play = new Button("Play");
        play -> setParentItem(this);
        m_buttons.push_front(play);
    }
    else
    {
        Button* playAgain = new Button("play Again");
        //playAgain -> setParentItem(this);
        m_buttons.push_front(playAgain);
    }
    
    Button* quit = new Button("Quit");
    quit  -> setParentItem(this);
    m_buttons.push_front(quit);
    
    Button* instructions = new Button("Instructions");
    instructions -> setParentItem(this);
    m_buttons.push_front(instructions);
}


QRectF Menu::boundingRect() const
{
    return QRectF(25, 25, 350, 550);
}


void Menu::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    Q_UNUSED(painter);
    
    QGraphicsTextItem* title = new QGraphicsTextItem(m_title, this);
    QFont titleFont("consolas", 40);
    title -> setFont(titleFont);
    int xPos = scene() -> width() / 2 - title -> boundingRect().width() / 2;
    int yPos =  scene() -> height() / 7;
    title -> setPos(xPos, yPos);
    
    //Play button
    int pXPos = scene() -> width() / 2 - m_buttons.at(2) -> boundingRect().width() / 2;
    int pYPos = 250;
    m_buttons.at(2) -> setPos(pXPos, pYPos);
    
    //Quit button
    int qXPos = scene() -> width() / 2 - m_buttons.at(1) -> boundingRect().width() / 2;
    int qYPos = 325;
    m_buttons.at(1) -> setPos(qXPos, qYPos);
    
    //Instructions button
    int iXPos = scene() -> width() / 2 - m_buttons.at(0) -> boundingRect().width() / 2;
    int iYPos = 400;
    m_buttons.at(0) -> setPos(iXPos, iYPos);
    
}


const QList<Button* > Menu::buttons() const
{
    return m_buttons;
}
