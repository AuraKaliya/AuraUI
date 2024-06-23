#include "smallmapwidget.h"

SmallMapWidget::SmallMapWidget(QWidget *parent)
    : UIWidget{parent}
{
    m_view=new AuraTestView01(this);
    QGraphicsScene *scene =new QGraphicsScene();
    m_view->setScene(scene);
}

void SmallMapWidget::initWidget()
{
    QGraphicsScene *scene =m_view->scene();
    AuraTestItem01 *m_item =new AuraTestItem01();
    scene->addItem(m_item);

    AuraTestItem01 *m_item2=new AuraTestItem01();
    scene->addItem(m_item2);

    AuraTestItem01 *m_item3=new AuraTestItem01();
    scene->addItem(m_item3);

    m_view ->addLinkItem(m_item);
    m_view ->addLinkItem(m_item2);
    m_view ->addLinkItem(m_item3);

    adjustSize();
}

void SmallMapWidget::resizeEvent(QResizeEvent *e)
{
    UIWidget::resizeEvent(e);
    if(m_view)
    {
        int w=width()-10;
        int h=height()-10;
        m_view->setGeometry(5,5,width()-10,height()-10);
        if(m_view->scene())
        {
            m_view->scene()->setSceneRect(-w/2,-h/2,w,h);
            m_view->centerOn(0,0);
        }
    }
}
