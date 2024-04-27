#ifndef SLIDEWIDGET_H
#define SLIDEWIDGET_H

#include <QWidget>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>

#include "clicklabel.h"
#include "uiwidget.h"

class SlideWidget : public UIWidget
{
    Q_OBJECT
public:
    explicit SlideWidget(QWidget *parent = nullptr);
    void initWidget()override;
    void setUIStyle(const UIStyle & style)override;

    void showRightWidget();
    void hideRightWidget();

    void showLeftWidget();
    void hideLeftWidget();


    void resetWidgetPos();
protected:
    void resizeEvent(QResizeEvent* e)override;
    void enterEvent(QEnterEvent *e)override;
    void leaveEvent(QEvent *e)override;
    void mouseMoveEvent(QMouseEvent*e)override;

private:
    ClickLabel * m_slideLabel;
    QWidget * m_leftWidget;
    QWidget * m_rightWidget;

    QWidget * m_bottomWidget;

    int m_duration;
    QRect m_reflectRect;

    bool m_leftWidgetFlag;
    bool m_rightWidgetFlag;
    bool m_rightWidgetAnimationLock;

signals:

};

#endif // SLIDEWIDGET_H
