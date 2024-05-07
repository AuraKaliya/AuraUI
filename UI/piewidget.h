#ifndef PIEWIDGET_H
#define PIEWIDGET_H

#include <QWidget>
#include <QVector>
#include <QRect>
#include <QSize>

#include "uiwidget.h"


class PieWidget : public UIWidget
{
    Q_OBJECT

public:
    enum class LabelState{
        Hover,Unhover
    };
public:
    explicit PieWidget(QWidget *parent = nullptr);
    explicit PieWidget(int labelCount,int innerR,QWidget*parent=nullptr);
    int labelCount() const;
    void setLabelCount(int newLabelCount);

    QPoint getRotatePoint(QPoint O,int r,double angel);


    int innerLength() const;
    void setInnerLength(int newInnerLength);
    int sectorContains(QPoint p,QRect roundRect,int labelCount,int offsetAngel=0);

protected:
    void paintEvent(QPaintEvent*e)override;
    void resizeEvent(QResizeEvent* e)override;
    void enterEvent(QEnterEvent*e)override;
    void leaveEvent(QEvent*e)override;
    void mousePressEvent(QMouseEvent* e)override;
    void mouseMoveEvent(QMouseEvent*e)override;

private:
    const double Pi=3.1415926535;
    int m_nowIndex;
    QVector<PieWidget::LabelState> m_labelStateList;
    QVector<QPoint> m_labelCenterPointList;
    int m_labelCount;

    QSize m_labelSize;
    QRect m_centerRect;
    QRect m_innerRect;
    int m_innerLength;


signals:

};
REGISTER_CLASS(PieWidget,UIWidget,QWidget*)
REGISTER_CLASS(PieWidget,UIWidget,int,int,QWidget*)
#endif // PIEWIDGET_H
