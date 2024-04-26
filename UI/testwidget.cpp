#include "testwidget.h"

TestWidget::TestWidget(QWidget *parent)
    : UIWidget{parent}
{
    setAutoInitUIStyleFlag(true);
    setWindowTitle("TestWidget");
}

void TestWidget::setUIStyle(const UIStyle &style)
{
    qDebug()<<"TestWidget::setUIStyle | check 1:"<<style.strFirstWidgetStyle();
    setStyleSheet(style.strFirstWidgetStyle());

    UIWidget::setUIStyle(style);
}
