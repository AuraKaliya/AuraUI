#include "auratestitem01.h"

#include <QPainter>

AuraTestItem01::AuraTestItem01(QGraphicsItem *parent)
    : QGraphicsObject{parent}
    ,m_rect(0,0,40,40)
    ,m_color(Qt::red)
{
    setFlags(ItemIsMovable | ItemIsSelectable);
}

QRectF AuraTestItem01::boundingRect() const
{
    return m_rect;
}

void AuraTestItem01::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    painter->setBrush(QBrush(m_color));
    painter->drawEllipse(boundingRect());
    painter->setBrush(Qt::NoBrush);
}
