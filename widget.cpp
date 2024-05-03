#include "widget.h"
//#include "./ui_widget.h"

#include <QPushButton>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    //, ui(new Ui::Widget)
{
    //ui->setupUi(this);

    resize(800,720);

    m_uiStyle=new UIStyle("Default");
    UIStyle::initStyle(m_uiStyle,UIStyle::Json);

    m_btnWidget=new WheelSlideWidget(this);

    m_showWidget=new QStackedWidget(this);

    m_logWidget=new logWidget(this);
}

Widget::~Widget()
{

}

void Widget::addNewUI(QString uiName)
{
    int uiCount=m_UIDictionary.count();
    QPushButton * btn=new QPushButton(uiName);
    btn->setMinimumSize(50,30);
    btn->adjustSize();
    m_btnWidget->addWidgetInArea(btn,5+uiCount*(btn->width()+10),10);

    QVector<UIWidget*> * vector=new QVector<UIWidget*> ();
    m_UIDictionary.insert(uiName,vector);


    WheelSlideWidget* widget=new WheelSlideWidget();
    //widget->setStyleSheet("background-color:black");
    m_showWidget->addWidget(widget);
    widget->setGeometry(0,0,m_showWidget->width(),m_showWidget->height());
    widget->setWheelDirection(WheelSlideWidget::VDirection);
    connect(btn,&QPushButton::clicked,this,[this,widget](bool flag){

        m_showWidget->setCurrentWidget(widget);
        qDebug()<<"now CurrentWidgetId:"<<m_showWidget->currentIndex();
    });

    m_UIToIndexDictionary.insert(uiName,m_showWidget->indexOf(widget));
    m_UIPosDictionary.insert(uiName,QPair<QPoint,QPoint>{QPoint(40,10),QPoint(10,10)});
}

void Widget::addNewWidgetInUI(QString uiName, UIWidget *w)
{
    auto it=m_UIDictionary.find(uiName);
    if(it== m_UIDictionary.end())
    {
        qDebug()<<"Widget::addNewWidgetInUI | no have this UI:"<<uiName;
        qDebug()<<"Widget::addNewWidgetInUI | UIDictionary:"<<m_UIDictionary;
        return;
    }
    //qDebug()<<"Widget::addNewWidgetInUI | check1 .";
    connect(w,&UIWidget::logSignal,m_logWidget,&logWidget::addLog);
    //qDebug()<<"Widget::addNewWidgetInUI | check2 .";

    QPoint pos;
    QPoint hWidgetPos=m_UIPosDictionary[uiName].first;
    QPoint vWidgetPos=m_UIPosDictionary[uiName].second;
    if(w->uiDirectionFlag()==UIWidget::Horizon)
    {
        w->resize(320,180);

        pos=hWidgetPos;

        hWidgetPos.setY(hWidgetPos.y()+180+10);
        vWidgetPos.setY(hWidgetPos.y());
    }
    else
    {
        w->resize(180,320);
        pos=vWidgetPos;

        if(vWidgetPos.x()>50)
        {
            vWidgetPos.setX(10);
            vWidgetPos.setY(vWidgetPos.y()+320+10);
            hWidgetPos.setY(vWidgetPos.y());
        }
        else
        {
            vWidgetPos.setX(10+180+20);
        }
    }
    m_UIPosDictionary[uiName]=QPair<QPoint,QPoint>(hWidgetPos,vWidgetPos);

    WheelSlideWidget* showUI=static_cast< WheelSlideWidget*>(m_showWidget->widget(m_UIToIndexDictionary.find(uiName).value()));
    showUI->addWidgetInArea(w,pos.x(),pos.y());

    it.value()->append(w);

}

void Widget::init()
{
    m_btnWidget->setGeometry(0,0,400,50);
    m_btnWidget->setBorder(10);
    m_btnWidget->setWheelDirection(WheelSlideWidget::HDirection);

    m_showWidget->setGeometry(0,70,400,650);

    m_logWidget->setGeometry(400,0,400,720);

    //m_logWidget->setReadOnly(true);
    //m_logWidget->setEnabled(false);

    //====================================Widget====================================
    addNewUI("Widget");
    //CarouselMapWidget* w1=new CarouselMapWidget();
    UIWidget * w1=Factory<UIWidget,QWidget*>::GetInstance()->CreateClass("CarouselMapWidget",nullptr);
    w1->initWidget();
    addNewWidgetInUI("Widget",w1);

    UIWidget * w2=Factory<UIWidget,QWidget*>::GetInstance()->CreateClass("SlideWidget",nullptr);
    w2->initWidget();
    addNewWidgetInUI("Widget",w2);


    UIWidget * w3=Factory<UIWidget,int,int,QWidget*>::GetInstance()->CreateClass("PieWidget",5,50,nullptr);
    w3->initWidget();
    addNewWidgetInUI("Widget",w3);
    //====================================Widget====================================end

    //====================================Chart====================================
    addNewUI("Chart");

    UIWidget* chart1=Factory<UIWidget,QWidget*>::GetInstance()->CreateClass("ChartWidget",nullptr);
    chart1->initWidget();
    addNewWidgetInUI("Chart",chart1);

    //====================================Chart====================================end

    //====================================OpenGL====================================
    addNewUI("OpenGL");

    AuraOpenGLWidget* openGLWidget1=new AuraOpenGLWidget();
    UIWidget * enOpenGLWidget1=Factory<UIWidget,QWidget*,QWidget*>::GetInstance()->CreateClass("EncapsulatedWidget",openGLWidget1,nullptr);
    addNewWidgetInUI("OpenGL",enOpenGLWidget1);

    //====================================OpenGL====================================end


}

void Widget::keyPressEvent(QKeyEvent *e)
{
    if(e->key()==Qt::Key_P)
    {
        qDebug()<<"P pressed.";
        //m_testWidget->setUIStyle(*m_uiStyle);
    }
}

