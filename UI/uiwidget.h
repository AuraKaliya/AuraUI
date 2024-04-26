#ifndef UIWIDGET_H
#define UIWIDGET_H

#include <QWidget>
#include <QVector>


#include "uistyle.h"


class UIWidget : public QWidget
{
    Q_OBJECT
public:
    explicit UIWidget(QWidget *parent = nullptr);
    virtual void initWidget();
    virtual void setUIStyle(const UIStyle & style);

    //==================控制位======================
    bool autoInitUIStyleFlag() const;



protected:
    void setAutoInitUIStyleFlag(bool newAutoInitUIStyleFlag);

private:
    //专门用于管理UIStyle的容器
    QVector<UIWidget*> m_widgetList;
    //自动设置UIStyle的控制位
    bool m_autoInitUIStyleFlag;
signals:
    void setUIStyleFinished();

};

#endif // UIWIDGET_H
