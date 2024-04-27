#include "carouselmapwidget.h"

void CarouselMapWidget::initWidget()
{
   connect(m_leftBtn,SIGNAL(clicked()),this,SLOT(preLabel()));
   connect(m_rightBtn,SIGNAL(clicked()),this,SLOT(nextLabel()));
}

void CarouselMapWidget::initCardSize(QSize curSize, QSize norSize)
{
    m_currentCardSize=curSize;
    m_normalCardSize=norSize;
    m_cardSizeFlag=true;
}

void CarouselMapWidget::setBtnPix(QString leftPixPath, QString rightPixPath)
{
    m_leftBtn->setText("");
    m_rightBtn->setText("");
    m_leftBtn->setStyleSheet("border-image:url("+leftPixPath+");");
    m_rightBtn->setStyleSheet("border-image:url("+rightPixPath+");");
}

void CarouselMapWidget::initShow()
{
    m_currentIdx=0;
    if(m_cardGroup.size()<m_currentIdx+1)
    {
        qDebug()<<"CarouselMapWidget::initShow | No card.";
        return;
    }

    //先将CurrentCard 放在正中间
    QWidget * currentCard=m_cardGroup[m_currentIdx];
    currentCard->resize(m_currentCardSize);
    currentCard->move((width()-currentCard->width())/2,(height()-currentCard->height())/2);

    //CurrentCard右边的Card
    for(int i=m_currentIdx+1;i<m_cardGroup.size();++i)
    {
        QWidget* rWidget=m_cardGroup[i];
        rWidget->resize(m_normalCardSize);
        rWidget->move(cardPosByIndex(CardPosition::right,i-m_currentIdx));
    }

    //CurrentCard左边的Card
    for(int i=m_currentIdx-1;i>=0;--i)
    {
        QWidget* lWidget=m_cardGroup[i];
        lWidget->resize(m_normalCardSize);
        lWidget->move(cardPosByIndex(CardPosition::left,m_currentIdx-i));
    }

    for(auto it:m_cardGroup)
    {
        it->setVisible(true);
    }

    initZ();

    //==============check=========================
    qDebug()<<"CarouselMapWidget::initShow | check cardCount:"<<m_cardGroup.size();
    qDebug()<<"CarouselMapWidget::initShow | check card Visible";
    for(auto it:m_cardGroup)
    {
        qDebug()<< it->isVisible();
    }

    qDebug()<<"CarouselMapWidget::initShow | check geo";
    for(auto it:m_cardGroup)
    {
        qDebug()<<it->geometry();
    }

    //==============check=========================
}


void CarouselMapWidget::init()
{
    //组件init
    //init btn
    //m_rightBtn->setGeometry(1100,15,50,220);
    //m_leftBtn->setGeometry(0,15,50,220);



    //m_rightBtn->setStyleSheet("border-image:url("+m_rightBtnPixUrl+");");
    //m_leftBtn->setStyleSheet("border-image:url("+m_leftBtnPixUrl+");");



    //内部connect
    //connect(m_rightBtn,SIGNAL(clicked()),this,SLOT(nextLabel()));
    //connect(m_leftBtn,SIGNAL(clicked()),this,SLOT(preLabel()));


    //其他init
    initZ();

}

CarouselMapWidget::CarouselMapWidget(QWidget *parent)
    : UIWidget{parent}
{
    m_cardSizeFlag=false;
    m_margin=10;
    m_ratio=0.9;
    m_animationDuration=1000;
    m_animationLock=false;


    m_leftBtn=new QPushButton("←",this);
    m_rightBtn=new QPushButton("→",this);

    //m_currentSize=QSize(450,240);
    //m_normalSize=QSize(356,190);

}

//void CarouselMapWidget::initCarousel(QVector<ClickLabel *> lbg, QSize curSize, QSize norSize, int margin)
//{
//    //resize(1600,900);

//    for(auto it : m_carsouseLabelGroup)
//    {
//        it->setVisible(false);
//        delete it;
//    }
//    if(lbg.size()==0)
//    {
//        qDebug()<<"没有剧情！";
//        return;
//    }
//    m_carsouseLabelGroup.clear();

//    update();
//    m_carsouseLabelGroup=lbg;
//    m_currentSize=curSize;
//    m_normalSize=norSize;
//    m_margin=margin;
//    int i=0;
//    // m_currentIdx=m_carsouseLabelGroup.size()-1;
//    m_currentIdx=0;
//    for (auto it:m_carsouseLabelGroup)
//    {
//        it->setParent(this);
//        if(i==m_currentIdx)
//        {
//            it->resize(m_currentSize);
//            it->move((width()-m_currentSize.width())/2,(height()-m_currentSize.height())/2);
//        }
//        else
//        {

//            it->resize(m_normalSize);
//            it->move(((width()-m_normalSize.width())/2)+(i-m_currentIdx)*(m_normalSize.width()+m_margin),(height()-m_normalSize.height())/2);
//        }
//        //qDebug()<<QPoint((width()-m_currentSize.width())/2,(height()-m_currentSize.height())/2));
//        ++i;

//    }

//    m_carsouseLabelGroup[m_currentIdx]->raise();

//initZ();


//}

//void CarouselMapWidget::initCarousel(QVector<ClickLabel *> lbg)
//{
////resize(1600,900);


////qDebug()<<"哈哈哈哈哈！";
//for(auto it : m_carsouseLabelGroup)
//{
//        it->setVisible(false);
//        delete it;
//}
//m_carsouseLabelGroup.clear();
//if(lbg.size()==0)
//{
//        //qDebug()<<"没有剧情！2";
//        return;
//}
////qDebug()<<"哈哈哈哈哈！";


//update();
//m_carsouseLabelGroup=lbg;
//int i=0;
//// m_currentIdx=m_carsouseLabelGroup.size()-1;
//m_currentIdx=0;
//for (auto it:m_carsouseLabelGroup)
//{
//        it->setParent(this);
//        if(i==m_currentIdx)
//        {
//            it->resize(m_currentSize);
//            it->move((width()-m_currentSize.width())/2,(height()-m_currentSize.height())/2);
//        }
//        else
//        {

//            it->resize(m_normalSize);
//            it->move(((width()-m_normalSize.width())/2)+(i-m_currentIdx)*(m_normalSize.width()+m_margin),(height()-m_normalSize.height())/2);
//        }
//        //qDebug()<<QPoint((width()-m_currentSize.width())/2,(height()-m_currentSize.height())/2));
//        ++i;
//}

//    if(m_carsouseLabelGroup.size()!=0)
//        m_carsouseLabelGroup[m_currentIdx]->raise();

//initZ();
//}

//void CarouselMapWidget::initChangeBtn(QString btn1N, QString btn2N)
//{
//    m_rightBtn->setGeometry(1100,15,50,220);
//    m_leftBtn->setGeometry(0,15,50,220);

//    m_rightBtn->setStyleSheet("border-image:url(:/UI/RESOURCE/test_rightBtn.png);");
//    m_leftBtn->setStyleSheet("border-image:url(:/UI/RESOURCE/test_leftBtn.png);");
//    connect(m_rightBtn,SIGNAL(clicked()),this,SLOT(nextLabel()));
//    connect(m_leftBtn,SIGNAL(clicked()),this,SLOT(preLabel()));
//    initZ();
//}

//void CarouselMapWidget::initMask(QMap<QLabel *, QRect> mask)
//{
//    m_maskGroup=mask;
//    for(auto it=mask.begin();it!=mask.end();it++)
//    {
//        it.key()->setParent(this);
//        it.key()->setVisible(true);
//        it.key()->setGeometry(it.value());
//        it.key()->raise();
//    }
//}

//void CarouselMapWidget::initMaskTest()
//{
//    QLabel* lb1=new QLabel(this);
//   QRect rect1=QRect(0,0,500,900);
//   lb1->setStyleSheet("border-image:url(:/UI/RESOURCE/test_Background_mask1.png);");



//    QLabel * lb2=new QLabel(this);
//  QRect rect2=QRect(1100,0,500,900);
//  lb2->setStyleSheet("border-image:url(:/UI/RESOURCE/test_Background_mask2.png);");
//    QMap<QLabel *, QRect> tmpMap;

//    tmpMap.insert(lb1,rect1);
//    tmpMap.insert(lb2,rect2);
//    initMask(tmpMap);

//}

void CarouselMapWidget::initZ()
{
    if(m_cardGroup.size()>0 && m_currentIdx>=0 && m_currentIdx<m_cardGroup.size() )
    {
        for(int i=0;i<m_currentIdx;++i)
        {
            m_cardGroup[i]->raise();
        }

        for(int i=m_cardGroup.size()-1;i>m_currentIdx;--i)
        {
            m_cardGroup[i]->raise();
        }

        m_cardGroup[m_currentIdx]->raise();
    }

    m_leftBtn->raise();
    m_rightBtn->raise();
}

void CarouselMapWidget::addLabel(ClickLabel *lb)
{
    lb->setParent(this);
    lb->setVisible(true);
    m_cardGroup.append(lb);
    //initShow();
}

void CarouselMapWidget::setMargin(int margin)
{
    m_margin=margin;
}

void CarouselMapWidget::preLabel()
{
    //检查触发条件： 当前序列号>0  动画准备就绪
    //向前移动（左）
    if((m_currentIdx>0)&&!m_animationLock)
    {
        m_animationLock=true;

        QParallelAnimationGroup *group=new QParallelAnimationGroup();
        --m_currentIdx;

        QVector<QPropertyAnimation *>animationPosList;

        for (int i=0;i<m_cardGroup.size();++i)
        {
            QPropertyAnimation *animation =new QPropertyAnimation(m_cardGroup[i],"geometry");
            QRect startRect;
            QRect endRect;
            animation->setDuration(m_animationDuration);
            QObject::connect(animation,&QPropertyAnimation::finished,[=](){
                //qDebug()<<"otherSize"<<m_carsouseLabelGroup[i]->geometry();
            });
            QObject::connect(animation,&QPropertyAnimation::valueChanged,[this](){
                update();
            });

            startRect=m_cardGroup[i]->geometry();
            animation->setStartValue(startRect);

            if(i==m_currentIdx)
            {
                m_cardGroup[i]->raise();
                endRect=QRect((width()-m_currentCardSize.width())/2,(height()-m_currentCardSize.height())/2,m_currentCardSize.width(),m_currentCardSize.height());
            }
            else
            {
                CardPosition tmpFlag=CardPosition::left;
                if(m_currentIdx>i)
                {
                    tmpFlag=CardPosition::left;
                }
                else
                {
                    tmpFlag=CardPosition::right;
                }
                endRect=QRect(cardPosByIndex(tmpFlag,abs(m_currentIdx-i)),m_normalCardSize);
            }
            animation->setEndValue(endRect);
            animationPosList<<animation;
            group->addAnimation(animation);
        }

        connect(group,&QParallelAnimationGroup::finished,[this](){
            m_animationLock=false;
            update();
        });
        initZ();
        group->start(QAbstractAnimation::DeleteWhenStopped);

    }
    else
    {
        QString logInfo="CarouselMapWidget::preLabel | ignore. Current Index:"+QString::number(m_currentIdx);
        //qDebug()<<"CarouselMapWidget::preLabel | ignore.";
        emit logSignal(logInfo,AuraUI::Action);
        return;
    }

}

void CarouselMapWidget::preLabel(int cx)
{

}

void CarouselMapWidget::nextLabel()
{
    if((m_currentIdx<m_cardGroup.size()-1)&&!m_animationLock)
    {
        m_animationLock=true;

        QParallelAnimationGroup *group=new QParallelAnimationGroup();
        ++m_currentIdx;

        QVector<QPropertyAnimation *>animationPosList;

        for (int i=0;i<m_cardGroup.size();++i)
        {
            QPropertyAnimation *animation =new QPropertyAnimation(m_cardGroup[i],"geometry");
            QRect startRect;
            QRect endRect;
            animation->setDuration(m_animationDuration);
            QObject::connect(animation,&QPropertyAnimation::finished,[=](){
                //qDebug()<<"otherSize"<<m_carsouseLabelGroup[i]->geometry();
            });
            QObject::connect(animation,&QPropertyAnimation::valueChanged,[this](){
                update();
            });

            startRect=m_cardGroup[i]->geometry();
            animation->setStartValue(startRect);

            if(i==m_currentIdx)
            {
                m_cardGroup[i]->raise();
                endRect=QRect((width()-m_currentCardSize.width())/2,(height()-m_currentCardSize.height())/2,m_currentCardSize.width(),m_currentCardSize.height());
            }
            else
            {
                CardPosition tmpFlag=CardPosition::left;
                if(m_currentIdx>i)
                {
                    tmpFlag=CardPosition::left;
                }
                else
                {
                    tmpFlag=CardPosition::right;
                }
                endRect=QRect(cardPosByIndex(tmpFlag,abs(m_currentIdx-i)),m_normalCardSize);
            }
            animation->setEndValue(endRect);

            animationPosList<<animation;
            group->addAnimation(animation);
        }

        connect(group,&QParallelAnimationGroup::finished,[this](){
            m_animationLock=false;
            update();
        });
        initZ();
        group->start(QAbstractAnimation::DeleteWhenStopped);
    }
    else
    {
        QString logInfo="CarouselMapWidget::nextLabel | ignore. Current Index:"+QString::number(m_currentIdx);
        //qDebug()<<"CarouselMapWidget::nextLabel | ignore.";
        emit logSignal(logInfo,AuraUI::Action);
        return;
    }
}

void CarouselMapWidget::nextLabel(int cx)
{

}

void CarouselMapWidget::resizeEvent(QResizeEvent *e)
{
    qDebug()<<"CarouselMapWidget::resizeEvent | begin";
    UIWidget::resizeEvent(e);

    int sumRatio=20;
    int btnRatio=3;

    m_leftBtn->resize((width()*btnRatio)/sumRatio,height());
    m_leftBtn->move(0,0);
    m_rightBtn->resize((width()*btnRatio)/sumRatio,height());
    m_rightBtn->move(width()-m_rightBtn->width(),0);

    if(!m_cardSizeFlag)
    {
        qDebug()<<"CarouselMapWidget::resizeEvent | autoSize";
        int curW=width()/2;
        int curH=height()/2;
        int norW=width()/3;
        int norH=height()/3;
        m_currentCardSize=QSize(curW,curH);
        m_normalCardSize=QSize(norW,norH);
        initShow();
    }

    qDebug()<<"CarouselMapWidget::resizeEvent | check CurrentSize:"<<m_currentCardSize;
    qDebug()<<"CarouselMapWidget::resizeEvent | check NormalSize:"<<m_normalCardSize;
}

int CarouselMapWidget::animationDuration() const
{
    return m_animationDuration;
}

void CarouselMapWidget::setAnimationDuration(int newAnimationDuration)
{
    m_animationDuration = newAnimationDuration;
}

QPoint CarouselMapWidget::cardPosByIndex(CardPosition posFlag, int index)
{
    QPoint res;
    int x=0;
    int y=0;
    if(posFlag==CardPosition::left)
    {
        x=width()/2-index*m_margin-m_normalCardSize.width();
        y=(height()-m_normalCardSize.height())/2;
            res.setX(x);
            res.setY(y);
    }
    else
    {
            x=width()/2+index*m_margin;
            y=(height()-m_normalCardSize.height())/2;
            res.setX(x);
            res.setY(y);
    }



    return res;
}

QSize CarouselMapWidget::normalCardSize() const
{
    return m_normalCardSize;
}

void CarouselMapWidget::setNormalCardSize(const QSize &newNormalCardSize)
{
    m_normalCardSize = newNormalCardSize;
}

QSize CarouselMapWidget::currentCardSize() const
{
    return m_currentCardSize;
}

void CarouselMapWidget::setCurrentCardSize(const QSize &newCurrentCardSize)
{
    m_currentCardSize = newCurrentCardSize;
}
