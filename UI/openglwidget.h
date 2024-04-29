#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QWidget>
#include "uiwidget.h"
class OpenGLWidget : public UIWidget
{
    Q_OBJECT
public:
    explicit OpenGLWidget(QWidget *parent = nullptr);

signals:

};

#endif // OPENGLWIDGET_H
