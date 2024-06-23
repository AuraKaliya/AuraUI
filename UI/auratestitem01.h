#ifndef AURATESTITEM01_H
#define AURATESTITEM01_H

#include <QObject>
#include <QGraphicsObject>
#include <QColor>

class AuraTestItem01 : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit AuraTestItem01(QGraphicsItem *parent = nullptr);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr)override;
private:
    QRectF m_rect;
    QColor m_color;

signals:
};

#endif // AURATESTITEM01_H
