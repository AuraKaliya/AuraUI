#ifndef HOVERLIGHTBTNWIDGET_H
#define HOVERLIGHTBTNWIDGET_H

#include <QWidget>
#include "uiwidget.h"
#include "flowlayout.h"

#include "hoverlightbtn.h"


class HoverLightBtnWidget : public UIWidget
{
    Q_OBJECT
public:
    explicit HoverLightBtnWidget(QWidget *parent = nullptr);
    void initWidget()override;
private:
    FlowLayout * m_mainLayout=nullptr;
    QVector<HoverLightBtn*> m_hoverLightBtnList;



signals:

};
REGISTER_CLASS(HoverLightBtnWidget,UIWidget,QWidget*)
#endif // HOVERLIGHTBTNWIDGET_H
