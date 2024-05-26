#ifndef HOVERLIGHTBTNINNERWIDGET_H
#define HOVERLIGHTBTNINNERWIDGET_H

#include <QWidget>
#include "../TOOL/aurapixtool.h"
#include <QPainter>

class HoverLightBtnInnerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit HoverLightBtnInnerWidget(QWidget *parent = nullptr);
    bool GetDrawFlag() const;
    void SetDrawFlag(bool newDrawFlag);

    QString GetText() const;
    void SetText(const QString &newText);

protected:
    void paintEvent(QPaintEvent*e)override;

    void enterEvent(QEnterEvent*e)override;
    void leaveEvent(QEvent*e)override;
private:
    bool m_drawFlag;
    QString m_text;
signals:

};

#endif // HOVERLIGHTBTNINNERWIDGET_H
