#include "wheelslidewidget.h"

#include <QCoreApplication>
#include <QWheelEvent>

QWidget *WheelSlideWidget::getArea() const
{
    return m_area;
}

QWidget *WheelSlideWidget::getLastWidget()
{
    QWidget* w=nullptr;
    if(m_widgetList.size()>0)
    {
        w=m_widgetList[m_widgetList.size()-1];
    }
    return w;
}

void WheelSlideWidget::setArea(QWidget *newArea)
{
    m_area = newArea;
}

void WheelSlideWidget::setArea(int width, int height)
{
    if(m_area!=nullptr)
    {
        m_area->setMinimumSize(width,height);
    }
}

void WheelSlideWidget::addWidgetInArea(QWidget *w, int x, int y)
{
    w->setParent(m_area);
    w->move(x,y);
    m_widgetList.append(w);
    //m_area->resize(x+w->width(),y+w->height());
    m_area->adjustSize();

}

void WheelSlideWidget::clearWidgetList()
{
    for(auto it:m_widgetList)
    {
        it->setParent(nullptr);
        it->deleteLater();
    }
    QCoreApplication::processEvents();
}

int WheelSlideWidget::getBorder() const
{
    return m_border;
}

void WheelSlideWidget::setBorder(int newBorder)
{
    m_border = newBorder;
    redoMove();
}

void WheelSlideWidget::updateArea()
{
    m_area->adjustSize();
}

void WheelSlideWidget::setUIStyle(const UIStyle &style)
{
    setStyleSheet(style.styleWithClass("WheelSlideWidget", std::bind(&UIStyle::strFirstWidgetStyle,style)));
    setStyleSheet(style.styleWithClass("QWidget", std::bind(&UIStyle::strSecondWidgetStyle,style)));
    UIWidget::setUIStyle(style);
}

void WheelSlideWidget::initWidget()
{
//    m_border=20;
//    setWheelDirection(HDirection);
//    qDebug()<<"WheelSlideWidget::initWidget | check 1:"<<m_area->geometry();
}

WheelSlideWidget::WheelSlideWidget(QWidget *parent)
    : UIWidget{parent}
{
    m_border=0;
    m_area=new QWidget(this);
    m_area->move(0,0);
}

void WheelSlideWidget::setWheelDirection(wheelDirection direction)
{
    m_wheelDirection=direction;
    m_area->setMinimumSize(width(),height());
    redoMove();
}

void WheelSlideWidget::wheelEvent(QWheelEvent *e)
{
    if(m_wheelDirection&NoDirection)
    {
        qDebug()<<"NoDirection";
    }
    else if(m_wheelDirection&VDirection)
    {
        int delta=e->angleDelta().y();
        m_area->move(m_area->x(),m_area->y()+delta);
    }
    else if(m_wheelDirection&HDirection)
    {
        int delta=e->angleDelta().y();
        m_area->move(m_area->x()+delta,m_area->y());
    }
    redoMove();
}

void WheelSlideWidget::resizeEvent(QResizeEvent *e)
{
    UIWidget::resizeEvent(e);
    m_area->setMinimumSize(width(),height());
}

void WheelSlideWidget::redoMove()
{
    int nowY=m_area->y();
    int heightLimit=this->height();

    int nowX=m_area->x();
    int widthLimit=this->width();

    int hBorder=0;
    int wBorder=0;

    if(m_wheelDirection&VDirection)
    {
        hBorder=m_border;
    }

    if(m_wheelDirection&HDirection)
    {
        wBorder=m_border;
    }

    if(nowY+m_area->height()+hBorder<heightLimit)
    {
        m_area->move(m_area->x(),heightLimit-m_area->height()-hBorder);
    }
    else if(nowY>hBorder)
    {
        m_area->move(m_area->x(),hBorder);
    }

    if(nowX+m_area->width()+wBorder<widthLimit)
    {
        m_area->move(widthLimit-m_area->width()-wBorder,m_area->y());
    }
    else if(nowX>wBorder)
    {
        m_area->move(wBorder,m_area->y());
    }
}
