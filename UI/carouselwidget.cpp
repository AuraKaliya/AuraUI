#include "carouselwidget.h"

CarouselWidget::CarouselWidget(QWidget *parent)
    : UIWidget{parent}
{
    m_cardSizeFlag=false;
    m_margin=10;
    m_ratio=0.9;
    m_animationDuration=1000;
    m_animationLock=false;

    m_leftBtn=new QPushButton("←",this);
    m_rightBtn=new QPushButton("→",this);
}

void CarouselWidget::initWidget()
{
    connect(m_leftBtn,SIGNAL(clicked()),this,SLOT(preLabel()));
    connect(m_rightBtn,SIGNAL(clicked()),this,SLOT(nextLabel()));

    ClickLabel* lb1=new ClickLabel("Label1");
    lb1->setStyleSheet("background-color:rgb(140,180,250)");
    ClickLabel* lb2=new ClickLabel("Label2");
    lb2->setStyleSheet("background-color:rgb(170,180,250)");
    ClickLabel* lb3=new ClickLabel("Label3");
    lb3->setStyleSheet("background-color:rgb(220,180,250)");
    addLabel(lb1);
    addLabel(lb2);
    addLabel(lb3);
    initShow();
}

void CarouselWidget::initCardSize(QSize norSize)
{
    m_currentCardSize=size();
    m_normalCardSize=norSize;
    m_cardSizeFlag=true;
}

void CarouselWidget::setBtnPix(QString leftPixPath, QString rightPixPath)
{
    m_leftBtn->setText("");
    m_rightBtn->setText("");
    m_leftBtn->setStyleSheet("border-image:url("+leftPixPath+");");
    m_rightBtn->setStyleSheet("border-image:url("+rightPixPath+");");

}

void CarouselWidget::setMargin(int margin)
{
    m_margin=margin;
}

void CarouselWidget::addLabel(ClickLabel *lb)
{
    lb->setParent(this);
    lb->setVisible(true);
    m_cardGroup.append(lb);

}

void CarouselWidget::initShow()
{
    m_currentIdx=0;
    if(m_cardGroup.size()<m_currentIdx+1)
    {
        qDebug()<<"CarouselMapWidgetT::initShow | No card.";
        return;
    }

    //CurrentCard 充满屏幕
    QWidget * currentCard=m_cardGroup[m_currentIdx];
    currentCard->resize(m_currentCardSize);
    currentCard->move(0,0);

    //NormalCard 左上角
    for(int i=0;i<m_cardGroup.size();++i)
    {
        if(i==m_currentIdx) continue;
        QWidget* widget=m_cardGroup[i];
        widget->resize(m_normalCardSize);
        widget->move(m_normalCardPos);
    }

    for(auto it:m_cardGroup)
    {
        it->setVisible(true);
    }

    initZ();

    //==============check=========================
    qDebug()<<"CarouselMapWidgetT::initShow | check cardCount:"<<m_cardGroup.size();
    qDebug()<<"CarouselMapWidgetT::initShow | check card Visible";
    for(auto it:m_cardGroup)
    {
        qDebug()<< it->isVisible();
    }

    qDebug()<<"CarouselMapWidgetT::initShow | check geo";
    for(auto it:m_cardGroup)
    {
        qDebug()<<it->geometry();
    }

    //==============check=========================
}

void CarouselWidget::initZ()
{

    if(m_cardGroup.size()>0 && m_currentIdx>=0 && m_currentIdx<m_cardGroup.size() )
    {
        m_cardGroup[m_currentIdx]->raise();
    }

    m_leftBtn->raise();
    m_rightBtn->raise();

}

void CarouselWidget::preLabel()
{
    //检查触发条件： 当前序列号>0  动画准备就绪
    //向前移动（左）
    if((m_currentIdx>0)&&!m_animationLock)
    {
        m_animationLock=true;

        QParallelAnimationGroup *group1=new QParallelAnimationGroup();
        QSequentialAnimationGroup * group2=new QSequentialAnimationGroup();

        QPropertyAnimation *animationCurToNor =new QPropertyAnimation(m_cardGroup[m_currentIdx],"geometry");
        QRect startRectCurToNor(m_cardGroup[m_currentIdx]->geometry());
        QRect endRectCurToNor(m_normalCardPos,m_normalCardSize);
        animationCurToNor->setDuration(m_animationDuration);
        animationCurToNor->setStartValue(startRectCurToNor);
        animationCurToNor->setEndValue(endRectCurToNor);
        QObject::connect(animationCurToNor,&QPropertyAnimation::finished,[=](){
            //qDebug()<<"otherSize"<<m_carsouseLabelGroup[i]->geometry();
        });
        QObject::connect(animationCurToNor,&QPropertyAnimation::valueChanged,[this](){
            update();
        });
        group1->addAnimation(animationCurToNor);

        --m_currentIdx;
        QPropertyAnimation *animationNorToCur =new QPropertyAnimation(m_cardGroup[m_currentIdx],"geometry");
        QRect startRectNorToCur(m_cardGroup[m_currentIdx]->geometry());
        QRect endRectNorToCur((width()-m_normalCardSize.width())/2,(height()-m_normalCardSize.height())/2,m_normalCardSize.width(),m_normalCardSize.height());
        animationNorToCur->setDuration(m_animationDuration);
        animationNorToCur->setStartValue(startRectNorToCur);
        animationNorToCur->setEndValue(endRectNorToCur);
        QObject::connect(animationNorToCur,&QPropertyAnimation::finished,[=](){
        });
        QObject::connect(animationNorToCur,&QPropertyAnimation::valueChanged,[this](){
            update();
        });
        group1->addAnimation(animationNorToCur);

        connect(group1,&QParallelAnimationGroup::finished,[this](){
            m_animationLock=false;
            update();
            initZ();
        });

        group2->addAnimation(group1);

        QPropertyAnimation *animationNorToCur2 =new QPropertyAnimation(m_cardGroup[m_currentIdx],"geometry");
        QRect startRectNorToCur2((width()-m_normalCardSize.width())/2,(height()-m_normalCardSize.height())/2,m_normalCardSize.width(),m_normalCardSize.height());
        QRect endRectNorToCur2(0,0,width(),height());
        animationNorToCur2->setDuration(m_animationDuration);
        animationNorToCur2->setStartValue(startRectNorToCur2);
        animationNorToCur2->setEndValue(endRectNorToCur2);
        QObject::connect(animationNorToCur2,&QPropertyAnimation::finished,[=](){

        });
        QObject::connect(animationNorToCur2,&QPropertyAnimation::valueChanged,[this](){
            update();
        });
        group2->addAnimation(animationNorToCur2);

        connect(group2,&QParallelAnimationGroup::finished,[this](){
            m_animationLock=false;
            update();
        });

        group2->start(QAbstractAnimation::DeleteWhenStopped);

    }
    else
    {
        QString logInfo="CarouselMapWidgetT::preLabel | ignore. Current Index:"+QString::number(m_currentIdx);
        //qDebug()<<"CarouselMapWidgetT::preLabel | ignore.";
        emit logSignal(logInfo,AuraUI::Action);
        return;
    }
}

void CarouselWidget::nextLabel()
{
    if((m_currentIdx<m_cardGroup.size()-1)&&!m_animationLock)
    {
        m_animationLock=true;

        QParallelAnimationGroup *group1=new QParallelAnimationGroup();
        QSequentialAnimationGroup * group2=new QSequentialAnimationGroup();

        QPropertyAnimation *animationCurToNor =new QPropertyAnimation(m_cardGroup[m_currentIdx],"geometry");
        QRect startRectCurToNor(m_cardGroup[m_currentIdx]->geometry());
        QRect endRectCurToNor(m_normalCardPos,m_normalCardSize);
        animationCurToNor->setDuration(m_animationDuration);
        animationCurToNor->setStartValue(startRectCurToNor);
        animationCurToNor->setEndValue(endRectCurToNor);
        QObject::connect(animationCurToNor,&QPropertyAnimation::finished,[=](){
            //qDebug()<<"otherSize"<<m_carsouseLabelGroup[i]->geometry();
        });
        QObject::connect(animationCurToNor,&QPropertyAnimation::valueChanged,[this](){
            update();
        });
        group1->addAnimation(animationCurToNor);

        ++m_currentIdx;
        QPropertyAnimation *animationNorToCur =new QPropertyAnimation(m_cardGroup[m_currentIdx],"geometry");
        QRect startRectNorToCur(m_cardGroup[m_currentIdx]->geometry());
        QRect endRectNorToCur((width()-m_normalCardSize.width())/2,(height()-m_normalCardSize.height())/2,m_normalCardSize.width(),m_normalCardSize.height());
        animationNorToCur->setDuration(m_animationDuration);
        animationNorToCur->setStartValue(startRectNorToCur);
        animationNorToCur->setEndValue(endRectNorToCur);
        QObject::connect(animationNorToCur,&QPropertyAnimation::finished,[=](){
        });
        QObject::connect(animationNorToCur,&QPropertyAnimation::valueChanged,[this](){
            update();
        });
        group1->addAnimation(animationNorToCur);

        connect(group1,&QParallelAnimationGroup::finished,[this](){
            m_animationLock=false;
            update();
            initZ();
        });

        group2->addAnimation(group1);

        QPropertyAnimation *animationNorToCur2 =new QPropertyAnimation(m_cardGroup[m_currentIdx],"geometry");
        QRect startRectNorToCur2((width()-m_normalCardSize.width())/2,(height()-m_normalCardSize.height())/2,m_normalCardSize.width(),m_normalCardSize.height());
        QRect endRectNorToCur2(0,0,width(),height());
        animationNorToCur2->setDuration(m_animationDuration);
        animationNorToCur2->setStartValue(startRectNorToCur2);
        animationNorToCur2->setEndValue(endRectNorToCur2);
        QObject::connect(animationNorToCur2,&QPropertyAnimation::finished,[=](){

        });
        QObject::connect(animationNorToCur2,&QPropertyAnimation::valueChanged,[this](){
            update();
        });
        group2->addAnimation(animationNorToCur2);

        connect(group2,&QParallelAnimationGroup::finished,[this](){
            m_animationLock=false;
            update();
        });

        group2->start(QAbstractAnimation::DeleteWhenStopped);

    }
    else
    {
        QString logInfo="CarouselMapWidgetT::nextLabel | ignore. Current Index:"+QString::number(m_currentIdx);
        //qDebug()<<"CarouselMapWidgetT::nextLabel | ignore.";
        emit logSignal(logInfo,AuraUI::Action);
        return;
    }
}

void CarouselWidget::resizeEvent(QResizeEvent *e)
{
    qDebug()<<"CarouselMapWidgetT::resizeEvent | begin";
    UIWidget::resizeEvent(e);

    int sumRatio=20;
    int btnRatio=3;

    m_leftBtn->resize((width()*btnRatio)/sumRatio,height());
    m_leftBtn->move(0,0);
    m_rightBtn->resize((width()*btnRatio)/sumRatio,height());
    m_rightBtn->move(width()-m_rightBtn->width(),0);

    if(!m_cardSizeFlag)
    {
        qDebug()<<"CarouselMapWidgetT::resizeEvent | autoSize";
        int norW=width()/5;
        int norH=height()/5;
        m_currentCardSize=size();
        m_normalCardSize=QSize(norW,norH);
        m_normalCardPos=QPoint(m_margin,m_margin);
        initShow();
    }

    qDebug()<<"CarouselMapWidgetT::resizeEvent | check CurrentSize:"<<m_currentCardSize;
    qDebug()<<"CarouselMapWidgetT::resizeEvent | check NormalSize:"<<m_normalCardSize;
}

QSize CarouselWidget::currentCardSize() const
{
    return m_currentCardSize;
}

QPoint CarouselWidget::normalCardPos() const
{
    return m_normalCardPos;
}

void CarouselWidget::setNormalCardPos(QPoint newNormalCardPos)
{
    m_normalCardPos = newNormalCardPos;
}

QSize CarouselWidget::normalCardSize() const
{
    return m_normalCardSize;
}

void CarouselWidget::setNormalCardSize(const QSize &newNormalCardSize)
{
    m_normalCardSize = newNormalCardSize;
}

int CarouselWidget::animationDuration() const
{
    return m_animationDuration;
}

void CarouselWidget::setAnimationDuration(int newAnimationDuration)
{
    m_animationDuration = newAnimationDuration;
}
