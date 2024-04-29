#ifndef CHARTWIDGET_H
#define CHARTWIDGET_H

#include <QWidget>
#include "uiwidget.h"

#include "mychart.h"



class ChartWidget : public UIWidget
{
    Q_OBJECT
public:
    explicit ChartWidget(QWidget *parent = nullptr);
    void initWidget()override;
    void setUIStyle(const UIStyle & style)override ;
protected:
    void resizeEvent(QResizeEvent* e)override;
private:
    AuraChart* m_chart;
    bool m_initFlag;
signals:

};

#endif // CHARTWIDGET_H
