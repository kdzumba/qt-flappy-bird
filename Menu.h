#ifndef MENU_H
#define MENU_H

#include <QtWidgets/QGraphicsItem>
#include <QtCore/QString>
#include <QtCore/QList>
#include <QtGui/QPainter>
#include <QtWidgets/QStyleOptionGraphicsItem>

#include "Button.h"

enum class MENU_TYPE{
    MainMenu,
    GameOver
};

class Menu : public QGraphicsItem
{
public:
    Menu(const QString& title, MENU_TYPE type, QGraphicsItem* parent = Q_NULLPTR);
    
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = Q_NULLPTR);
    const QList<Button* > buttons() const;
    
private:
    QString m_title;
    MENU_TYPE m_type;
    QList<Button* > m_buttons;
};
#endif //MENU_H