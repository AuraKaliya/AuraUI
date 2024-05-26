#include "hoverlightbtn.h"

HoverLightBtn::HoverLightBtn(QWidget *parent)
    : QWidget{parent}
{
    setWindowTitle("HoverLightBtn");

    m_text="DefaultText";
    m_drawPixFlag=false;
    m_margin=1;
    m_border=3;

    initColor();
}

void HoverLightBtn::initColor(QColor lightColor, QColor outerBackgroundColor, QColor innerbackgroundColor, QColor borderColor, QColor textNormalColor)
{
    m_lightColor=lightColor;
    m_outerBackgroundColor=outerBackgroundColor;
    m_innerBackgroundColor=innerbackgroundColor;
    m_borderColor=borderColor;
    m_textNormalColor=textNormalColor;
}

void HoverLightBtn::paint(QPainter *p, QWidget *w)
{
    qreal radius=0.0;
    QRect outerRect(m_margin,m_margin,width()-2*m_margin,height()-2*m_margin);
    QRect innerRect(m_margin+m_border,m_margin+m_border,width()-2*(m_margin+m_border),height()-2*(m_margin+m_border));

    p->setRenderHints(QPainter::Antialiasing|QPainter::SmoothPixmapTransform |QPainter::TextAntialiasing);

    //绘制外背景
//    if(m_drawPixFlag)
//    {
//        p->setBrush(QBrush(QColor(170,170,170,220)));
//    }
//    else
//    {
//        p->setBrush(QBrush(m_outerBackgroundColor));
//    }
    p->setPen(Qt::NoPen);
    p->setBrush(QBrush(m_outerBackgroundColor));

    p->drawRoundedRect(outerRect,radius,radius);

    p->setPen(Qt::NoPen);
    p->setBrush(Qt::NoBrush);


    //绘制light
    if(m_drawPixFlag)
    {
        auto blurPix=AuraPixTool::applyGaussianBlur(AuraPixTool::createColoredCircle(m_lightColor,300,50),30);
        p->drawPixmap(QRect(m_mousePos.x()-blurPix.width()/2,m_mousePos.y()-blurPix.height()/2,blurPix.width(),blurPix.height()),blurPix);
    }

    //绘制border
   QPen borderPen;

    borderPen.setColor(m_borderColor);
    if(m_drawPixFlag)
    {
        borderPen.setWidth(1);
    }
    else
    {
        borderPen.setWidth(2);
    }

    p->setPen(borderPen);
    p->setBrush(Qt::NoBrush);
    p->drawRoundedRect(outerRect,radius,radius);


    //绘制内背景色
    p->setBrush(QBrush(m_innerBackgroundColor));
    p->drawRoundedRect(innerRect,radius,radius);


    //绘制Text
    QPen textPen;
    if(m_drawPixFlag)
    {
        textPen.setColor(m_lightColor);
    }
    else
    {
        textPen.setColor(Qt::white);
    }
    p->setPen(textPen);
    p->drawText(rect(),Qt::AlignCenter,m_text);

}

void HoverLightBtn::setText(QString text)
{

}


void HoverLightBtn::paintEvent(QPaintEvent *e)
{
    QWidget::paintEvent(e);

    QPainter painter(this);
    paint(&painter,this);
}

void HoverLightBtn::resizeEvent(QResizeEvent *e)
{
    QWidget::resizeEvent(e);
}

void HoverLightBtn::mouseMoveEvent(QMouseEvent *e)
{
    m_mousePos=e->pos();
    update();
}

void HoverLightBtn::enterEvent(QEnterEvent *e)
{
    QWidget::enterEvent(e);
    setMouseTracking(true);
    m_drawPixFlag=true;
    update();
}

void HoverLightBtn::leaveEvent(QEvent *e)
{
    QWidget::leaveEvent(e);
    setMouseTracking(false);
    m_drawPixFlag = false;

    update();
}
