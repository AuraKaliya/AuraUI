#include "hoverlightbtninnerwidget.h"

HoverLightBtnInnerWidget::HoverLightBtnInnerWidget(QWidget *parent)
    : QWidget{parent}
{
    m_drawFlag=false;
    m_text="";
}

void HoverLightBtnInnerWidget::paintEvent(QPaintEvent *e)
{
    qreal radius=0.0;
    QPainter p(this);

    //绘制内背景色
    p.setBrush(QBrush(QColor(40,40,40,255)));
    p.drawRoundedRect(rect(),radius,radius);

    p.setBrush(Qt::NoBrush);
    //绘制text
    QPen textPen;

    if(m_drawFlag)
    {
        textPen.setColor(QColorConstants::Svg::pink);
    }
    else
    {
        textPen.setColor(Qt::white);
    }
    p.setPen(textPen);
    p.drawText(rect(),Qt::AlignCenter,m_text);
}

void HoverLightBtnInnerWidget::enterEvent(QEnterEvent *e)
{
    QWidget::enterEvent(e);
    m_drawFlag=true;
}

void HoverLightBtnInnerWidget::leaveEvent(QEvent *e)
{
    QWidget::leaveEvent(e);
    m_drawFlag=false;
}

QString HoverLightBtnInnerWidget::GetText() const
{
    return m_text;
}

void HoverLightBtnInnerWidget::SetText(const QString &newText)
{
    m_text = newText;
}

bool HoverLightBtnInnerWidget::GetDrawFlag() const
{
    return m_drawFlag;
}

void HoverLightBtnInnerWidget::SetDrawFlag(bool newDrawFlag)
{
    m_drawFlag = newDrawFlag;
}
