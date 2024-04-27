#ifndef LOGWIDGET_H
#define LOGWIDGET_H

#include <QWidget>
#include <QTextEdit>

#include "AuraUIConstValue.h"

class logWidget : public QTextEdit
{
    Q_OBJECT
public:

public:
    explicit logWidget(QWidget *parent = nullptr);

signals:
public slots:
    void addAction(QString str);
    void addError(QString str);
    void addLog(QString str , AuraUI::LogType type);
};

#endif // LOGWIDGET_H
