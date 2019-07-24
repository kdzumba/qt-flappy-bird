#ifndef PIPE_H
#define PIPE_H

#include <QtGui/QPixmap>
#include <QtWidgets/QGraphicsItem>
#include <QtWidgets/QStyleOptionGraphicsItem>
#include <QtGui/QPainter>
#include <QtCore/QRectF>
#include <QtCore/QObject>
#include <QtWidgets/QGraphicsObject>

class Pipe : public QGraphicsObject
{
	Q_OBJECT
public:
	Pipe(QGraphicsObject* parent = Q_NULLPTR);
   ~Pipe();
   
    QRectF boundingRect() const Q_DECL_OVERRIDE;
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = Q_NULLPTR) Q_DECL_OVERRIDE;
	void rotatePixmap();

public slots:
	void move();

private:
	QPixmap* m_pipe;
};

#endif //PIPE_H