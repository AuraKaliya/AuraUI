#ifndef HOVERLIGHTBTNBACKGROUNDWIDGET_H
#define HOVERLIGHTBTNBACKGROUNDWIDGET_H

#include <QWidget>
#include "../TOOL/aurapixtool.h"
#include <QPainter>


class HoverLightBtnBackgroundWidget : public QWidget
{
    Q_OBJECT
public:
    explicit HoverLightBtnBackgroundWidget(QWidget *parent = nullptr);
    bool GetDrawFlag() const;
    void SetDrawFlag(bool newDrawFlag);

    void SetMousePos(QPoint newMousePos);

protected:
    void paintEvent(QPaintEvent* e) override;

    void enterEvent(QEnterEvent*e)override;
    void leaveEvent(QEvent*e)override;
private:
    QPoint m_mousePos;
    bool m_drawFlag;
signals:

};

#endif // HOVERLIGHTBTNBACKGROUNDWIDGET_H
