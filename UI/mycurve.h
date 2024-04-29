#ifndef MYCURVE_H
#define MYCURVE_H

#include <QObject>
#include <QtCharts>
#include <QLineSeries>

class AuraCurve : public QLineSeries
{
    Q_OBJECT
public:
    explicit AuraCurve(QObject *parent = nullptr);
    void init();
signals:
    void mousehovered(const QPointF& point,bool state);
};

#endif // MYCURVE_H
