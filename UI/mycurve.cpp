#include "mycurve.h"

AuraCurve::AuraCurve(QObject *parent)
    : QLineSeries{parent}
{

}

void AuraCurve::init()
{
    append(0, 2);
    append(1, 4);
    append(2, 6);
    append(3, 8);
    append(4, 6);
    append(5, 4);
    append(6, 2);
}
