#ifndef BUTTON_H
#define BUTTON_H

#include <QtWidgets/QGraphicsRectItem>
#include <QtWidgets/QGraphicsTextItem>
#include <QtWidgets/QGraphicsSceneMouseEvent>
#include <QtWidgets/QGraphicsSceneHoverEvent>
#include <QtCore/QString>
#include <QtCore/QObject>


class Button :public QObject,  public QGraphicsRectItem
{
    Q_OBJECT
public:
    Button(QString name, QGraphicsRectItem* parent = NULL);
    
    void mousePressEvent(QGraphicsSceneMouseEvent* event)  Q_DECL_OVERRIDE;
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event)  Q_DECL_OVERRIDE;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event)  Q_DECL_OVERRIDE;
    
signals:
    void clicked();
    
private:
    QGraphicsTextItem* m_text;
};

#endif //BUTTON_H