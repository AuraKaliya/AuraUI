#ifndef HOVERLIGHTBTN_H
#define HOVERLIGHTBTN_H

#include <QWidget>
#include <QPainter>
#include <QBrush>
#include <QColor>
#include <QResizeEvent>
#include <QMouseEvent>

#include <QRadialGradient>

#include "../TOOL/aurapixtool.h"

class HoverLightBtn : public QWidget
{
    Q_OBJECT
public:
    explicit HoverLightBtn(QWidget *parent = nullptr);
    void initColor(QColor lightColor=QColor(Qt::red),QColor outerBackgroundColor=QColor(70,70,70,240),QColor innerbackgroundColor=QColor(70,70,70,250),QColor borderColor=QColor(40,40,40,250),QColor textNormalColor=QColor(Qt::white));
    void paint(QPainter* p,QWidget* w);
    void setText(QString text);

protected:
    void paintEvent(QPaintEvent*e)override;
    void resizeEvent(QResizeEvent*e)override;
    void mouseMoveEvent(QMouseEvent*e)override;
    void enterEvent(QEnterEvent*e)override;
    void leaveEvent(QEvent*e)override;

private:
   // MaskWidget* m_maskWidget;
    QPoint m_mousePos;


    int m_margin;
    int m_border;

    QColor m_lightColor;
    QColor m_outerBackgroundColor;
    QColor m_innerBackgroundColor;
    QColor m_borderColor;
    QColor m_textNormalColor;

    QString m_text;

    bool m_drawPixFlag;
signals:

};



#endif // HOVERLIGHTBTN_H
