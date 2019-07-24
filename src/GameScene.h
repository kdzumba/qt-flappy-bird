#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include <QtWidgets/QGraphicsScene>
#include <QtWidgets/QGraphicsView>
#include <QtCore/QObject>
#include <QtGui/QPainter>
#include <QtCore/QRectF>
#include <QtGui/QPixmap>

class GameScene : public QGraphicsScene
{
    Q_OBJECT
public:
    GameScene();
   ~GameScene();
   
    void drawBackground(QPainter* background, const QRectF& boundingRect) Q_DECL_OVERRIDE;
    QGraphicsView* view() const;
    
public slots:
    void show();
    
private:
    static int s_updateTime;
    QPixmap* m_background;
    QGraphicsView* m_view;
};
#endif //GAME_SCENE_H