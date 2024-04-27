#include "logwidget.h"

logWidget::logWidget(QWidget *parent)
    : QTextEdit{parent}
{

}

void logWidget::addAction(QString str)
{
    QString header="[Act] ";
    QTextCursor cursor(textCursor());
    cursor.movePosition(QTextCursor::End);
    QTextCharFormat fmt;
    fmt.setForeground(QBrush(Qt::blue));
    cursor.setCharFormat(fmt);
    cursor.insertText(header);
    fmt.setForeground(QBrush(Qt::black));
    cursor.setCharFormat(fmt);
    cursor.insertText(str);
    cursor.insertText("\n");
    setTextCursor(cursor);
}

void logWidget::addError(QString str)
{
    QString header="[Ins] ";
    QTextCursor cursor(textCursor());
    cursor.movePosition(QTextCursor::End);
    QTextCharFormat fmt;

    fmt.setForeground(QBrush(Qt::red));

    cursor.setCharFormat(fmt);
    cursor.insertText(header);
    fmt.setForeground(QBrush(Qt::black));
    cursor.setCharFormat(fmt);
    cursor.insertText(str);
    cursor.insertText("\n");
    setTextCursor(cursor);

}

void logWidget::addLog(QString str, AuraUI::LogType type)
{
    //qDebug()<<"logWidget::addLog | begin.";
    switch (type) {
    case AuraUI::Action:
        addAction(str);
        break;
    case AuraUI::Error:
        addError(str);
        break;
    default:
        addError("Log get unknown info:"+str);
        break;
    }
    //qDebug()<<"logWidget::addLog | end.";
}
