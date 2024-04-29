#include "mychart.h"

#include <QPen>
#include <QPixmap>

AuraChart::AuraChart(QWidget *parent)
    : QChartView{parent}
{
    m_chart=new QChart();
    m_curve=new AuraCurve();
    m_toolWidget=new ChartToolWidget(this);
    m_toolWidget->hide();

    //connect=================
    connect(m_curve,&QLineSeries::hovered,this,[](const QPointF& point,bool state)
            {
                // qDebug()<<"hovered! point:"<<point<< state;
            }
            );
    connect(m_toolWidget,&ChartToolWidget::stateChanged,this,&AuraChart::stateChange);
    //connect=================

    setChart(m_chart);
    setRenderHint(QPainter::Antialiasing);
    //resize(400, 300);

}

void AuraChart::stateChange(State state)
{

    if(state& Move)
    {
        //移动
        m_Q_flag=!m_Q_flag;
    }

    if(state& Select)
    {
        //选取
        m_W_flag=!m_W_flag;
    }

    if(state& Save)
    {
        //保存
        saveToImage();
    }



}

void AuraChart::setState(State state)
{
    resetState();
    if(state==None) return;

    if(state& Move)
    {
        //移动
        m_Q_flag=true;
    }

    if(state& Select)
    {
        //选取
        m_W_flag=true;
    }

    if(state& Save)
    {
        //保存
        saveToImage();
    }

}

void AuraChart::resetState()
{
    m_Q_flag=false;
    m_W_flag=false;
}

void AuraChart::sethighlightPointsInRect(const QRectF &selectRect)
{

    for(auto it:m_highlightCurveList)
    {
        m_chart->removeSeries(it);
        delete it;
        it=nullptr;
    }
    m_highlightCurveList.clear();

    bool startFlag=false;
    bool continueFlag=false;
    AuraCurve* tmpCurve;

    const QVector<QPointF> points=m_curve->points();

    for(auto it:points)
    {
        if(selectRect.contains(it))
        {
            if(!startFlag)
            {
                startFlag=true;
                tmpCurve=new AuraCurve();
                tmpCurve->setPen(QPen(Qt::red));
            }

            tmpCurve->append(it);

            if(!continueFlag)
            {
                continueFlag=true;
            }
        }
        else
        {
            continueFlag=false;
        }

        if(startFlag && !continueFlag)
        {
            m_chart->addSeries(tmpCurve);
            m_highlightCurveList.append(tmpCurve);
            startFlag=false;
        }
    }
    if(startFlag)
    {
        m_chart->addSeries(tmpCurve);
        m_highlightCurveList.append(tmpCurve);
    }

    m_chart->createDefaultAxes();
}

void AuraChart::addHighlightPointsInRect(const QRectF &selectRect)
{
    bool startFlag=false;
    bool continueFlag=false;
    AuraCurve* tmpCurve;

    const QVector<QPointF> points=m_curve->points();

    for(auto it:points)
    {
        if(selectRect.contains(it) )
        {
            if(!startFlag)
            {
                startFlag=true;
                tmpCurve=new AuraCurve();
                tmpCurve->setPen(QPen(Qt::red));
            }
            tmpCurve->append(it);

            if(!continueFlag)
            {
                continueFlag=true;
            }
        }
        else
        {
            continueFlag=false;
        }

        if(startFlag && !continueFlag)
        {

            m_chart->addSeries(tmpCurve);
            m_highlightCurveList.append(tmpCurve);
            startFlag=false;
        }
    }
    if(startFlag)
    {
        m_chart->addSeries(tmpCurve);
        m_highlightCurveList.append(tmpCurve);
    }

    m_chart->createDefaultAxes();


}

void AuraChart::init()
{
    m_dragFlag=false;
    m_Q_flag=false;
    m_lineHoverFlag=false;
    m_selectFlag=false;
    m_W_flag=false;
    m_Shift_flag=false;

    m_toolWidget->init();
    m_toolWidget->move(width()-m_toolWidget->width(),0);


    //================curve======================
    m_curve->init();
    m_curve->setPen(QPen(Qt::black));


    m_chart->legend()->hide();
    m_chart->addSeries(m_curve);
    //================curve======================


    m_chart->createDefaultAxes();
    m_chart->setTitle(QStringLiteral("Qt Line Chart Example"));

    m_chart->layout()->setContentsMargins(0,0,0,0);
    m_chart->setBackgroundRoundness(0);


}

void AuraChart::saveToImage()
{
    toolWidgetHide();
    QPixmap pixmap = grab();
    pixmap.save("chart.png");
    toolWidgetShow();
}

void AuraChart::mousePressEvent(QMouseEvent *e)
{
    if(m_Q_flag)
    {
        m_dragFlag=true;
    }

    if(m_W_flag)
    {
        //qDebug()<<"SELSECT~ pressed~";
        m_selectFlag=true;
    }


    m_dragStartPos=e->pos();
    m_selectStartPos=e->pos();
    m_chartStartPos=m_chart->mapToValue(e->pos());

    //check=================
    //qDebug()<<"StartPos:"<<m_selectStartPos;
    //qDebug()<<"CharStartPos:"<<m_chartStartPos;
    //check=================

    QChartView::mousePressEvent(e);
}

void AuraChart::mouseMoveEvent(QMouseEvent *e)
{

    if(m_dragFlag)
    {
        m_dragEndPos=e->pos();
        auto dx=m_dragEndPos.x()-m_dragStartPos.x();
        auto dy=m_dragEndPos.y()-m_dragStartPos.y();
        m_chart->scroll(-dx,dy);
        m_dragStartPos=e->pos();
    }
    if(m_selectFlag)
    {
        m_selectEndPos=e->pos();
        m_chartEndPos=m_chart->mapToValue(e->pos());
        m_selectRect=QRectF(m_selectStartPos,m_selectEndPos);
        m_chartSelectRect=QRectF(m_chartStartPos,m_chartEndPos);
        viewport()->update();
    }

    QChartView::mouseMoveEvent(e);
}

void AuraChart::mouseReleaseEvent(QMouseEvent *e)
{

    m_dragFlag=false;
    m_selectFlag=false;
    if(m_Shift_flag)
    {
        addHighlightPointsInRect(m_chartSelectRect);
    }
    else
    {
        sethighlightPointsInRect(m_chartSelectRect);
    }

    //check=================
    //qDebug()<<"m_selectEndPos:"<<m_selectEndPos;
    //check=================

    viewport()->repaint();

    QChartView::mouseReleaseEvent(e);
}

void AuraChart::wheelEvent(QWheelEvent *e)
{
    double factor = std::pow(1.1, e->angleDelta().y() / 240.0);
    m_chart->zoom(factor);
    QChartView::wheelEvent(e);
}

void AuraChart::keyPressEvent(QKeyEvent *e)
{
    if(e->key()==Qt::Key_Q)
    {
        m_Q_flag=!m_Q_flag;
    }

    if(e->key()==Qt::Key_W)
    {
        m_W_flag=!m_W_flag;
    }

    if(e->key()==Qt::Key_Shift)
    {
        m_Shift_flag=true;
    }

    if(e->key()==Qt::Key_P)
    {
        saveToImage();
    }
}

void AuraChart::keyReleaseEvent(QKeyEvent *e)
{
    m_Shift_flag=false;
}

void AuraChart::paintEvent(QPaintEvent *e)
{
    QChartView::paintEvent(e);

    QPainter p(viewport());
    if(m_selectFlag)
    {
        p.setPen(QPen(Qt::red));
        p.drawRect(m_selectRect);
    }
    p.end();

}

void AuraChart::enterEvent(QEnterEvent *e)
{
    toolWidgetShow();
}


void AuraChart::leaveEvent(QEvent *e)
{
    toolWidgetHide();
}

void AuraChart::resizeEvent(QResizeEvent *e)
{
    QChartView::resizeEvent(e);
    m_toolWidget->move(width()-m_toolWidget->width(),0);
}

void AuraChart::toolWidgetHide()
{
    m_toolWidget->hide();
}

void AuraChart::toolWidgetShow()
{
    m_toolWidget->show();
}

