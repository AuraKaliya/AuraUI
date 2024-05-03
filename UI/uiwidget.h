#ifndef UIWIDGET_H
#define UIWIDGET_H

#include <QWidget>
#include <QVector>
#include <QPainter>
#include <QJsonObject>
#include <QJsonArray>

#include "uistyle.h"
#include "AuraUIConstValue.h"





//=========================加入反射
#include "../TOOL/Registor.hpp"
//===============================


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
    virtual void initWidget(const QJsonObject& obj);
    virtual void setUIStyle(const UIStyle & style);

    //==================控制位======================
    bool autoInitUIStyleFlag() const;
    UIWidget::UIDirection uiDirectionFlag() const;


protected:
    void setAutoInitUIStyleFlag(bool newAutoInitUIStyleFlag);
    void setUiDirectionFlag(UIWidget::UIDirection newUiDirectionFlag);
    void paintEvent(QPaintEvent*e)override;
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
