#include "chartwidget.h"

ChartWidget::ChartWidget(QWidget *parent)
    : UIWidget{parent}
{
    m_initFlag=false;
}

void ChartWidget::initWidget()
{
    m_chart=new AuraChart(this);
    m_chart->init();
    m_initFlag=true;
}

void ChartWidget::setUIStyle(const UIStyle &style)
{

}

void ChartWidget::resizeEvent(QResizeEvent *e)
{
    UIWidget::resizeEvent(e);
    if(m_initFlag)
    {
        m_chart->setGeometry(0,0,width(),height());
        update();
    }
}
