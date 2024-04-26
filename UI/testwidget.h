#ifndef TESTWIDGET_H
#define TESTWIDGET_H

#include <QWidget>
#include "uiwidget.h"

class TestWidget : public UIWidget
{
    Q_OBJECT
public:
    explicit TestWidget(QWidget *parent = nullptr);
    void setUIStyle(const UIStyle &style)override;
signals:

};

#endif // TESTWIDGET_H
