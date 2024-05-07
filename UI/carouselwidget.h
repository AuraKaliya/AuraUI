#ifndef CAROUSELWIDGET_H
#define CAROUSELWIDGET_H

#include <QWidget>

#include <QLabel>
#include <QPushButton>
#include <QVector>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QParallelAnimationGroup>

#include <QString>
#include <QSize>
#include <QRect>

#include <QDir>
#include <QApplication>

#include "clicklabel.h"
#include "uiwidget.h"


class CarouselWidget : public UIWidget
{
    Q_OBJECT
public:
    explicit CarouselWidget(QWidget *parent = nullptr);
    void initWidget()override;
    void initCardSize(QSize norSize);
    void setBtnPix(QString leftPixPath,QString rightPixPath);
    void setMargin(int margin);

    void addLabel(ClickLabel* lb);
    void initShow();

    void initZ();

    int animationDuration() const;
    void setAnimationDuration(int newAnimationDuration);

    QSize normalCardSize() const;
    void setNormalCardSize(const QSize &newNormalCardSize);

    QPoint normalCardPos() const;
    void setNormalCardPos(QPoint newNormalCardPos);

    QSize currentCardSize() const;

public slots:
    void preLabel();
    void nextLabel();
protected:
    void resizeEvent(QResizeEvent*e) override;
private:
    QSize m_currentCardSize;
    double m_ratio;
    QSize m_normalCardSize;
    QPoint m_normalCardPos;

    int m_margin;
    int m_animationDuration;

    // QMap<QLabel*,QRect>m_maskGroup;
    QVector<ClickLabel*>m_cardGroup;

    QPushButton * m_leftBtn;
    QPushButton * m_rightBtn;
    int m_currentIdx;

    bool m_animationLock;

    QString m_baseSourcePath;

    bool m_cardSizeFlag;
signals:

};
REGISTER_CLASS(CarouselWidget,UIWidget,QWidget*)
#endif // CAROUSELWIDGET_H
