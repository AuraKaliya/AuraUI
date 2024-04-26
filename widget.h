#ifndef WIDGET_H
#define WIDGET_H

#include <QKeyEvent>
#include <QWidget>
#include <QStackedWidget>
#include <QMap>
#include <QVector>

#include <QDir>
#include <QApplication>




#include "UI/uistyle.h"

#include "UI/testwidget.h"
#include "UI/wheelslidewidget.h"
#include "UI/carouselmapwidget.h"



QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void addNewUI(QString uiName );
    void addNewWidgetInUI(QString uiName,UIWidget* w);
    void init();

protected:
    void keyPressEvent(QKeyEvent*e)override;
private:
    Ui::Widget *ui;

    UIStyle* m_uiStyle;

    WheelSlideWidget* m_btnWidget;

    QStackedWidget* m_showWidget;

    QMap<QString,QVector<UIWidget*> *> m_UIDictionary;
    QMap<QString,int>m_UIToIndexDictionary;

    QDir * m_dir;

};
#endif // WIDGET_H
