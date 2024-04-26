#include "widget.h"
#include "./ui_widget.h"

#include <QPushButton>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    resize(300,720);

    m_uiStyle=new UIStyle("Default");
    UIStyle::initStyle(m_uiStyle,UIStyle::Json);

    m_btnWidget=new WheelSlideWidget(this);

    m_showWidget=new QStackedWidget(this);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::addNewUI(QString uiName)
{
    int uiCount=m_UIDictionary.count();
    QPushButton * btn=new QPushButton(uiName);
    btn->resize(50,30);
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

    w->resize(300,180);

    int widgetCount=it.value()->size();

    WheelSlideWidget* showUI=static_cast< WheelSlideWidget*>(m_showWidget->widget(m_UIToIndexDictionary.find(uiName).value()));
    showUI->addWidgetInArea(w,0,widgetCount*(w->height()+10));

    it.value()->append(w);

}

void Widget::init()
{
    m_btnWidget->setGeometry(0,0,300,50);
    m_btnWidget->setBorder(10);
    m_btnWidget->setWheelDirection(WheelSlideWidget::HDirection);

    m_showWidget->setGeometry(0,70,300,650);



    addNewUI("Widget");


    CarouselMapWidget* w1=new CarouselMapWidget();

    addNewWidgetInUI("Widget",w1);
    w1->addLabel(new ClickLabel("Label1"));
    w1->addLabel(new ClickLabel("Label2"));
    w1->addLabel(new ClickLabel("Label3"));
    w1->initShow();

}

void Widget::keyPressEvent(QKeyEvent *e)
{
    if(e->key()==Qt::Key_P)
    {
        qDebug()<<"P pressed.";
        //m_testWidget->setUIStyle(*m_uiStyle);
    }
}

