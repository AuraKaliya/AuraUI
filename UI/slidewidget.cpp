#include "slidewidget.h"

SlideWidget::SlideWidget(QWidget *parent)
    : UIWidget{parent}
{
    m_duration=500;
    m_leftWidgetFlag=false;
    m_rightWidgetAnimationLock=false;
    m_slideLabel=new ClickLabel(this);
    m_leftWidget=new QWidget(this);
    m_rightWidget=new QWidget(this);


}

void SlideWidget::initWidget()
{
    connect(m_slideLabel,&ClickLabel::clicked,this,[this](){
        if(!m_leftWidgetFlag)
        {
            showLeftWidget();
        }
        else
        {
            hideLeftWidget();
        }
    });

    m_leftWidget->setStyleSheet("background-color:rgb(140,180,250)");
    m_rightWidget->setStyleSheet("background-color:rgb(170,180,250)");
    m_slideLabel->setStyleSheet("background-color:rgb(220,180,250)");

}

void SlideWidget::setUIStyle(const UIStyle &style)
{

}

void SlideWidget::showRightWidget()
{
    QPropertyAnimation * animation=new QPropertyAnimation(m_rightWidget,"geometry");
    QRect startRect=m_rightWidget->geometry();
    QRect endRect=QRect(width()-m_rightWidget->width(),0,m_rightWidget->width(),m_rightWidget->height());
    animation->setDuration(m_duration);
    animation->setStartValue(startRect);
    animation->setEndValue(endRect);
    QObject::connect(animation,&QPropertyAnimation::valueChanged,[this](){
        update();
    });
    QObject::connect(animation,&QPropertyAnimation::finished,[=](){
        qDebug()<<"SlideWidget::showRightWidget | end.";
        m_rightWidgetAnimationLock=false;
    });
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void SlideWidget::hideRightWidget()
{
    QPropertyAnimation * animation=new QPropertyAnimation(m_rightWidget,"geometry");
    QRect startRect=m_rightWidget->geometry();
    QRect endRect=QRect(width(),0,m_rightWidget->width(),m_rightWidget->height());
    animation->setDuration(m_duration);
    animation->setStartValue(startRect);
    animation->setEndValue(endRect);
    QObject::connect(animation,&QPropertyAnimation::valueChanged,[this](){
        update();
    });
    QObject::connect(animation,&QPropertyAnimation::finished,[=](){
        qDebug()<<"SlideWidget::hideRightWidget | end.";
        m_rightWidgetAnimationLock=false;
    });

    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void SlideWidget::showLeftWidget()
{
    QParallelAnimationGroup *group=new QParallelAnimationGroup();

    QPropertyAnimation * animation=new QPropertyAnimation(m_leftWidget,"geometry");
    QRect startRect=m_leftWidget->geometry();
    QRect endRect=QRect(0,0,m_leftWidget->width(),m_leftWidget->height());
    animation->setDuration(m_duration);
    animation->setStartValue(startRect);
    animation->setEndValue(endRect);
    QObject::connect(animation,&QPropertyAnimation::valueChanged,[this](){
        update();
    });
    QObject::connect(animation,&QPropertyAnimation::finished,[=](){
        qDebug()<<"SlideWidget::showLeftWidget | end.";
    });
    group->addAnimation(animation);

    QPropertyAnimation * animation2=new QPropertyAnimation(m_slideLabel,"geometry");
    QRect startRect2=m_slideLabel->geometry();
    QRect endRect2=QRect(m_leftWidget->width(),0,m_slideLabel->width(),m_slideLabel->height());
    animation2->setDuration(m_duration);
    animation2->setStartValue(startRect2);
    animation2->setEndValue(endRect2);
    QObject::connect(animation2,&QPropertyAnimation::finished,[=](){
        m_slideLabel->setText("←");
        m_leftWidgetFlag=true;
    });
    group->addAnimation(animation2);

    group->start(QAbstractAnimation::DeleteWhenStopped);
}

void SlideWidget::hideLeftWidget()
{
    QParallelAnimationGroup *group=new QParallelAnimationGroup();
    QPropertyAnimation * animation=new QPropertyAnimation(m_leftWidget,"geometry");
    QRect startRect=m_leftWidget->geometry();
    QRect endRect=QRect(-m_leftWidget->width(),0,m_leftWidget->width(),m_leftWidget->height());
    animation->setDuration(m_duration);
    animation->setStartValue(startRect);
    animation->setEndValue(endRect);
    QObject::connect(animation,&QPropertyAnimation::valueChanged,[this](){
        update();
    });
    QObject::connect(animation,&QPropertyAnimation::finished,[=](){
        qDebug()<<"SlideWidget::hideLeftWidget | end.";
        //qDebug()<<"SlideWidget::hideLeftWidget | check:"<<m_leftWidget->geometry();
        //qDebug()<<"SlideWidget::hideLeftWidget | check:"<<m_slideLabel->geometry();
    });
    group->addAnimation(animation);

    QPropertyAnimation * animation2=new QPropertyAnimation(m_slideLabel,"geometry");
    QRect startRect2=m_slideLabel->geometry();
    QRect endRect2=QRect(0,0,m_slideLabel->width(),m_slideLabel->height());
    animation2->setDuration(m_duration);
    animation2->setStartValue(startRect2);
    animation2->setEndValue(endRect2);
    QObject::connect(animation2,&QPropertyAnimation::finished,[=](){
        m_slideLabel->setText("→");
        m_leftWidgetFlag=false;
    });
    group->addAnimation(animation2);

    group->start(QAbstractAnimation::DeleteWhenStopped);
}

void SlideWidget::resetWidgetPos()
{
    m_leftWidget->move(-m_leftWidget->width(),0);
    m_rightWidget->move(width(),0);
    m_slideLabel->move(0,0);
    m_slideLabel->setText("→");
}

void SlideWidget::resizeEvent(QResizeEvent *e)
{
    UIWidget::resizeEvent(e);
    int w=width();
    int h=height();

    m_leftWidget->resize(w*3/10,h);
    m_rightWidget->resize(w*3/10,h);
    m_slideLabel->resize(w/10,h*2/10);
    m_reflectRect=QRect(w*9/10,0,w/10,h);
    resetWidgetPos();
}

void SlideWidget::enterEvent(QEnterEvent *e)
{
    setMouseTracking(true);
}

void SlideWidget::leaveEvent(QEvent *e)
{
    setMouseTracking(false);
}

void SlideWidget::mouseMoveEvent(QMouseEvent *e)
{
    if(!m_rightWidgetAnimationLock && !m_rightWidgetFlag && m_reflectRect.contains(e->pos()))
    {
        m_rightWidgetAnimationLock=true;
        m_rightWidgetFlag=true;
        showRightWidget();
    }

    if(!m_rightWidgetAnimationLock && m_rightWidgetFlag && !m_rightWidget->geometry().contains( e->pos() ) )
    {
        m_rightWidgetAnimationLock=true;
        m_rightWidgetFlag=false;
        hideRightWidget();
    }


}
