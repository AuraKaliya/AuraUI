#ifndef UIWIDGET_H
#define UIWIDGET_H

#include <QWidget>
#include <QVector>


#include "uistyle.h"
#include "AuraUIConstValue.h"

class UIWidget : public QWidget
{
    Q_OBJECT
public:
public:
    enum UIDirection{
        Horizon=1,Vertical=2
    };
public:
    explicit UIWidget(QWidget *parent = nullptr);
    virtual void initWidget();
    virtual void setUIStyle(const UIStyle & style);

    //==================控制位======================
    bool autoInitUIStyleFlag() const;
    UIWidget::UIDirection uiDirectionFlag() const;


protected:
    void setAutoInitUIStyleFlag(bool newAutoInitUIStyleFlag);
    void setUiDirectionFlag(UIWidget::UIDirection newUiDirectionFlag);
private:
    //专门用于管理UIStyle的容器
    QVector<UIWidget*> m_widgetList;
    //自动设置UIStyle的控制位
    bool m_autoInitUIStyleFlag;
    //  横向UI/纵向UI；
    UIDirection m_uiDirectionFlag;
signals:
    void setUIStyleFinished();

    void actionSignal(QString);
    void errorSignal(QString);
    void logSignal(QString,AuraUI::LogType);
};

#endif // UIWIDGET_H
