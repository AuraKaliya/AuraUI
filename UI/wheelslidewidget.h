#ifndef WHEELSLIDEWIDGET_H
#define WHEELSLIDEWIDGET_H

#include <QWidget>
#include "uiwidget.h"

class WheelSlideWidget : public UIWidget
{
    Q_OBJECT

public:
enum wheelDirection
    {
        NoDirection=0,
        HDirection=1,
        VDirection=2
    };

public:

    explicit WheelSlideWidget(QWidget *parent = nullptr);
    void setWheelDirection(wheelDirection direction);
    QWidget *getArea() const;
    QWidget* getLastWidget();
    void setArea(QWidget *newArea);
    void setArea(int width,int height);
    void addWidgetInArea(QWidget*w,int x,int y);
    void clearWidgetList();
    int getBorder() const;
    void setBorder(int newBorder);
    void updateArea();
    void setUIStyle(const UIStyle & style)override;
    void initWidget()override;
protected:
    void wheelEvent(QWheelEvent* e)override;
    void resizeEvent(QResizeEvent *e)override;
    virtual void redoMove();

private:
    wheelDirection m_wheelDirection=NoDirection;
    QWidget* m_area;
    QVector<QWidget*>m_widgetList;
    int m_border;
signals:

};

#endif // WHEELSLIDEWIDGET_H
