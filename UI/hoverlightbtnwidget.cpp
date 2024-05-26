#include "hoverlightbtnwidget.h"

HoverLightBtnWidget::HoverLightBtnWidget(QWidget *parent)
    : UIWidget{parent}
{
    m_mainLayout=new FlowLayout();
}

void HoverLightBtnWidget::initWidget()
{
    setLayout(m_mainLayout);

    HoverLightBtn * btn1 =new HoverLightBtn(this);
    btn1->setFixedSize(180,50);
    m_mainLayout->addWdiget(btn1);
    btn1->setVisible(true);


    HoverLightBtn * btn2 =new HoverLightBtn(this);
    btn2->setFixedSize(180,50);
    btn2->initColor(QColor(Qt::green));
    m_mainLayout->addWdiget(btn2);
    btn2->setVisible(true);

    HoverLightBtn * btn3 =new HoverLightBtn(this);
    btn3->setFixedSize(180,50);
    btn3->initColor(QColor(Qt::yellow));
    m_mainLayout->addWdiget(btn3);
    btn3->setVisible(true);

}
