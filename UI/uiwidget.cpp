#include "uiwidget.h"

UIWidget::UIWidget(QWidget *parent)
    : QWidget{parent}
{
    m_autoInitUIStyleFlag=false;
    m_uiDirectionFlag=UIWidget::Horizon;
}

void UIWidget::initWidget()
{

}

void UIWidget::initWidget(const QJsonObject &obj)
{

}

void UIWidget::setUIStyle(const UIStyle &style)
{
    if(m_autoInitUIStyleFlag)
    {
        for(auto it:m_widgetList)
        {
            it->setUIStyle(style);
        }
    }
    emit setUIStyleFinished();
}

bool UIWidget::autoInitUIStyleFlag() const
{
    return m_autoInitUIStyleFlag;
}

void UIWidget::setAutoInitUIStyleFlag(bool newAutoInitUIStyleFlag)
{
    m_autoInitUIStyleFlag = newAutoInitUIStyleFlag;
}

UIWidget::UIDirection UIWidget::uiDirectionFlag() const
{
    return m_uiDirectionFlag;
}

void UIWidget::setUiDirectionFlag(UIWidget::UIDirection newUiDirectionFlag)
{
    m_uiDirectionFlag = newUiDirectionFlag;
}

void UIWidget::paintEvent(QPaintEvent *e)
{
    QWidget::paintEvent(e);
    QPainter p(this);
    p.setPen(QPen(Qt::red));
    p.drawRect(QRect(rect().x(),rect().y(),rect().width()-1,rect().height()-1));
}

