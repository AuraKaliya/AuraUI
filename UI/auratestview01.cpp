#include "auratestview01.h"

AuraTestView01::AuraTestView01(QWidget *parent)
    : QGraphicsView{parent}
{
    m_smallMapSize=QSize(200,200);
    setViewportUpdateMode(QGraphicsView::ViewportUpdateMode::FullViewportUpdate);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void AuraTestView01::addLinkItem(QGraphicsItem *item)
{
    m_linkItemList.append(item);
}

void AuraTestView01::setLinkItem(QGraphicsItem *item)
{
    m_linkItem =item;
}

double AuraTestView01::itemOffset(QGraphicsItem * item)
{
    if(!item) return 0;
    qDebug()<<"SceneRect:"<<scene()->sceneRect();
    qDebug()<<"CenterPos: "<<m_centerPos;
    QPointF center =QPoint(width()/2,height()/2);
    //QPointF center(m_centerPos);
    qDebug()<<"Center in Scene: "<<center;
    QPointF itemBasePos =item->pos();
    QPointF itemPos = mapFromScene(itemBasePos.rx()+item->boundingRect().width()/2,itemBasePos.ry()+item->boundingRect().height()/2);
    qDebug()<<"Item Pos: "<<itemPos;
    QPointF disVector =(center-itemPos);
    double  dis =qSqrt(disVector.rx()*disVector.rx() +disVector.ry()*disVector.ry());
    return dis;
}

void AuraTestView01::paintEvent(QPaintEvent *e)
{
    QGraphicsView::paintEvent(e);

    //画小地图Rect
    int smallMapX = (width()-m_smallMapSize.width())/2;
    int smallMapY = (height()-m_smallMapSize.height())/2;
    m_centerPos.setX(smallMapX);
    m_centerPos.setY(smallMapY);

    QPainter p(this->viewport());
    p.setPen(Qt::blue);
    p.drawEllipse(smallMapX,smallMapY,m_smallMapSize.width(),m_smallMapSize.height());

    for(auto it: m_linkItemList)
    {
        bool drawFlag =itemOffset(it) <=m_smallMapSize.width()/2 ? false : true;
        if(drawFlag)
        {
            double angle =qAtan2(it->pos().ry()+it->boundingRect().height()/2,it->pos().rx()+it->boundingRect().width()/2);
            qDebug()<<angle;
            QPointF center =mapFromScene(0,0);
            QPointF tipPos;
            int length =10;

            tipPos.setX(center.x() +m_smallMapSize.width()/2 *qCos(angle));
            tipPos.setY(center.y() +m_smallMapSize.height()/2 *qSin(angle));

            qDebug()<<tipPos;
            p.setPen(Qt::green);
            p.setBrush(Qt::red);
            p.drawEllipse(tipPos,length,length);
        }
    }



}

void AuraTestView01::resizeEvent(QResizeEvent *e)
{
    QGraphicsView::resizeEvent(e);
    int length = width()>=height()? height()/2:width()/2;

    m_smallMapSize . setHeight(length);
    m_smallMapSize . setWidth(length);
}
