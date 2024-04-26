#ifndef CAROUSELMAPWIDGET_H
#define CAROUSELMAPWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVector>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QParallelAnimationGroup>
#include <QString>
#include <QSize>
#include <QRect>


#include <QDir>
#include <QApplication>





#include "clicklabel.h"
#include "uiwidget.h"

/*

用于轮播效果的窗体
需要做到：轮播部件的深度切换、部件的缩放和平移
需要有一个Vector


*/


/*
另一种实现方案：
列表直接排列设置当前scale和正常scale，

*/


class CarouselMapWidget : public UIWidget
{
    Q_OBJECT
public:

    void initWidget()override;

    void initCardSize(QSize curSize,QSize norSize);

    void setBtnPix(QString leftPixPath,QString rightPixPath);

    void initShow();



    void init();


    explicit CarouselMapWidget(QWidget *parent = nullptr);


    //void initCarousel(QVector<ClickLabel*> lbg,QSize curSize,QSize norSize,int margin);
    //void initCarousel(QVector<ClickLabel*> lbg);

    //void initChangeBtn(QString btn1N,QString btn2N);
    //void initMask(QMap<QLabel*,QRect>mask);

    //void initMaskTest();

    void initZ();

   // void initTest();

    void addLabel(ClickLabel* lb);


    void setMargin(int margin)             ;


    QSize currentCardSize() const;
    void setCurrentCardSize(const QSize &newCurrentCardSize);

    QSize normalCardSize() const;
    void setNormalCardSize(const QSize &newNormalCardSize);


public slots:
    void preLabel();
    void preLabel(int);
    void nextLabel(int);
    void nextLabel();



protected:
    void resizeEvent(QResizeEvent*e) override;

signals:
    void nowStory(int);

private:
    QSize m_currentCardSize;
    QSize m_normalCardSize;

    int m_margin;


    // QMap<QLabel*,QRect>m_maskGroup;
    QVector<ClickLabel*>m_cardGroup;

    QPushButton * m_leftBtn;
    QPushButton * m_rightBtn;
    int m_preIdx;
    int m_currentIdx;
    int m_nextIdx;

    bool animationLock;

    QPropertyAnimation* m_animation;

    QString m_baseSourcePath;

    bool m_cardSizeFlag;

};

#endif // CAROUSELMAPWIDGET_H
