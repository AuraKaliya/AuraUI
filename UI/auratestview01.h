#ifndef AURATESTVIEW01_H
#define AURATESTVIEW01_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsitem>
#include <QVector>

class AuraTestView01 : public QGraphicsView
{
    Q_OBJECT
public:
    explicit AuraTestView01(QWidget *parent = nullptr);
    void addLinkItem(QGraphicsItem* item);
    void setLinkItem(QGraphicsItem* item);
    double itemOffset(QGraphicsItem *item);
protected:
    void paintEvent(QPaintEvent* e)override;
    void resizeEvent(QResizeEvent* e)override;


private:
    QSize m_smallMapSize;
    QPoint m_centerPos;
    QVector<QGraphicsItem* >m_linkItemList;
    QGraphicsItem * m_linkItem=nullptr;

signals:
};

#endif // AURATESTVIEW01_H
