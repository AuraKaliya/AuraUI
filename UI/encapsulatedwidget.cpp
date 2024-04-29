#include "encapsulatedwidget.h"

EncapsulatedWidget::EncapsulatedWidget(QWidget *parent)
    : UIWidget{parent}
{
    m_initFlag=false;
}

void EncapsulatedWidget::setWidget(QWidget *w)
{
    w->setParent(this);
    m_widget=w;
    m_initFlag=true;
}

void EncapsulatedWidget::resizeEvent(QResizeEvent *e)
{
    UIWidget::resizeEvent(e);
    if(m_initFlag)
    {
        m_widget->setGeometry(0,0,width(),height());
    }
}
