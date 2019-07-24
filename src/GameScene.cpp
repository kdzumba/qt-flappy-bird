#include "GameScene.h"

#include <iostream>

#include <QtCore/QTimer>

//The scene gets to be advanced every s_updateTime milliseconds --> 100ms
int GameScene::s_updateTime = 65;


GameScene::GameScene()
{
    m_background = new QPixmap("images/nightbg.png");
    m_view = new QGraphicsView(this);
    
    setSceneRect(0, 0, 500, 700);
    m_view -> setFixedSize(width(), height());
    m_view -> setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_view -> setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    
    QTimer* timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(advance()));
    timer -> start(s_updateTime);
}



GameScene::~GameScene()
{
    delete m_background;
    delete m_view;
}


void GameScene::drawBackground(QPainter* paint, const QRectF& boundingRect)
{
    paint -> drawPixmap(QRect(0, 0, width(), height()), *m_background);
    Q_UNUSED(boundingRect);
    
}


//Returns the view that is used to display this scene
QGraphicsView* GameScene::view() const
{
    return m_view;
}


//Displays the scene through the m_view QGraphicsView
void GameScene::show()
{
    m_view -> show();
}