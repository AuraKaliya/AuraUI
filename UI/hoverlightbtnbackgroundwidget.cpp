#include "hoverlightbtnbackgroundwidget.h"

HoverLightBtnBackgroundWidget::HoverLightBtnBackgroundWidget(QWidget *parent)
    : QWidget{parent}
{
    m_drawFlag=false;
}

void HoverLightBtnBackgroundWidget::paintEvent(QPaintEvent *e)
{
    QWidget::paintEvent(e);


    qreal radius=0.0;
    QPainter p(this);
    //绘制外边框背景
    QPen borderPen;

    if(m_drawFlag)
    {
        borderPen.setWidth(1);
        borderPen.setColor(QColor(140,140,140,240));
    }
    else
    {
        borderPen.setWidth(4);
        borderPen.setColor(QColor(40,40,40,240));
    }

    p.setPen(borderPen);
    if(m_drawFlag)
    {
        p.setBrush(QBrush(QColor(170,170,170,240)));
    }
    else
    {
        p.setBrush(QBrush(QColor(70,70,70,240)));
    }

    p.drawRoundedRect(rect(),radius,radius);

    p.setPen(Qt::NoPen);



    //绘制光源
    if(m_drawFlag)
    {
        QImage img("D:/QTF/HoverLightBtnTest/round.png");
        QRect imgRect(m_mousePos.x()-20,m_mousePos.y()-20,40,40);
        QRect newImgRect=imgRect.adjusted(-20,-20,20,20);

        AuraPixTool::burlImage(img,40,false,false);
        p.drawImage(newImgRect,img);
    }


}

void HoverLightBtnBackgroundWidget::enterEvent(QEnterEvent *e)
{
    QWidget::enterEvent(e);
    m_drawFlag=true;
}

void HoverLightBtnBackgroundWidget::leaveEvent(QEvent *e)
{
    QWidget::leaveEvent(e);
    m_drawFlag=false;
}

void HoverLightBtnBackgroundWidget::SetMousePos(QPoint newMousePos)
{
    m_mousePos = QPoint(newMousePos.x()-x(),newMousePos.y()-y());
}

bool HoverLightBtnBackgroundWidget::GetDrawFlag() const
{
    return m_drawFlag;
}

void HoverLightBtnBackgroundWidget::SetDrawFlag(bool newDrawFlag)
{
    m_drawFlag = newDrawFlag;
}
