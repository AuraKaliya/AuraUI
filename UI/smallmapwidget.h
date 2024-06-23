#ifndef SMALLMAPWIDGET_H
#define SMALLMAPWIDGET_H

#include <QWidget>

#include "auratestitem01.h"
#include "auratestview01.h"

#include "uiwidget.h"

class SmallMapWidget : public UIWidget
{
    Q_OBJECT
public:
    explicit SmallMapWidget(QWidget *parent = nullptr);

    void initWidget()override;
protected:
    void resizeEvent(QResizeEvent* e)override;
private:
    AuraTestView01 * m_view;
signals:

};
REGISTER_CLASS(SmallMapWidget,UIWidget,QWidget*)
#endif // SMALLMAPWIDGET_H
