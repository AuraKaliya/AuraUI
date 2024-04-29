#ifndef ENCAPSULATEDWIDGET_H
#define ENCAPSULATEDWIDGET_H

#include <QWidget>
#include "uiwidget.h"
class EncapsulatedWidget : public UIWidget
{
    Q_OBJECT
public:
    explicit EncapsulatedWidget(QWidget *parent = nullptr);

    void setWidget(QWidget* w);
protected:
    void resizeEvent(QResizeEvent*e)override;
private:
    QWidget* m_widget;
    bool m_initFlag;
signals:

};

#endif // ENCAPSULATEDWIDGET_H
