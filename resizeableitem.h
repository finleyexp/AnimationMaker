#ifndef RESIZEABLEITEM_H
#define RESIZEABLEITEM_H

#include <QGraphicsItem>
#include <QPropertyAnimation>
#include <QAction>
#include <QList>
#include "itemhandle.h"

class ResizeableItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity)
    Q_PROPERTY(qreal left READ left WRITE setLeft)
    Q_PROPERTY(qreal top READ top WRITE setTop)
public:
    ResizeableItem();

    void drawHighlightSelected(QPainter *painter, const QStyleOptionGraphicsItem *option);
    void paint( QPainter *paint, const QStyleOptionGraphicsItem *, QWidget *);
    QRectF boundingRect() const;
    bool sceneEventFilter(QGraphicsItem * watched, QEvent * event);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    virtual void scaleObjects();
    virtual void setScale(qreal x, qreal y);
    qreal xscale();
    qreal yscale();

    QRectF rect() const;
    void setRect(qreal x, qreal y, qreal w, qreal h);

    QPen pen() const;
    void setPen(const QPen &pen);

    QBrush brush() const;
    void setBrush(const QBrush &brush);

    inline qreal left() {return x();}
    inline qreal top() {return y();}
    inline void setLeft(qreal val) {setX(val);}
    inline void setTop(qreal val) {setY(val);}

    void setWidth(qreal value);
    void setHeight(qreal value);

    void addAnimation(QPropertyAnimation *anim);
    int getAnimationCount() const;
    QPropertyAnimation *getAnimation(int row);

private:
    ItemHandle*  m_handles[8];
    bool m_hasHandles;
    QRectF m_rect;
    QPen m_pen;
    QBrush m_brush;
    QMenu *m_contextMenu;
    QAction *delAct;
    QAction *bringToFrontAct;
    QAction *sendToBackAct;
    QAction *lowerAct;
    QAction *raiseAct;
    QMenu *m_animateMenu;
    QAction *m_opacityAct;
    QAction *m_leftAct;
    QAction *m_topAct;
    QList<QPropertyAnimation*> *m_animations;

private slots:
    void deleteItem();
    void bringToFront();
    void sendToBack();
    void lower();
    void raise();
    void addOpacityAnimation();
    void addLeftAnimation();
    void addTopAnimation();

signals:
    void addPropertyAnimation(ResizeableItem *item, const QString propertyName, qreal value);

protected:
    void setHandlePositions();
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) Q_DECL_OVERRIDE;
    qreal m_xscale;
    qreal m_yscale;
};

#endif // RESIZEABLEITEM_H