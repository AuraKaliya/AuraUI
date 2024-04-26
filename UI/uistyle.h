#ifndef UISTYLE_H
#define UISTYLE_H

#include <QString>
#include <QMap>
#include <QDir>
#include <QApplication>

#include <QFile>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonParseError>

#include <functional>
//
#include <QDebug>
//

class UIStyle;
using UIStyleInitFunction=bool(*)(UIStyle*);
using UIStyleInitByJsonFunction=void(*)(UIStyle*,const QJsonObject&);
using UIStyleStrFunction=std::function<QString()>;
class UIStyle
{
public:
    enum InitFormation{
        Json=1
    };

public:
    static void initStyle(UIStyle* styleObj,InitFormation form);
    static bool initStyleByJson(UIStyle* styleObj);
    static void initWidgetStyleByJson(UIStyle* styleObj,const QJsonObject& obj);


public:
    UIStyle(QString styleName="Default");


    //=============WidgetStyle==================
    QString strFirstWidgetStyle() const;
    QString strSecondWidgetStyle() const;



    //=============Others==================
    QString styleName() const;
    QString styleWithClass(const QString & className,UIStyleStrFunction  func)const;
    void setStyleName(const QString &newStyleName);

    void setStrFirstWidgetStyle(const QString &newStrFirstWidgetStyle);
    void setStrSecondWidgetStyle(const QString &newStrSecondWidgetStyle);


private:
    QString m_styleName;
    QString m_sourceDir;
    QString m_strFirstWidgetStyle;
    QString m_strSecondWidgetStyle;

private:
    static QMap<InitFormation,UIStyleInitFunction> s_initFuncDictionary;
    static QMap<QString,UIStyleInitByJsonFunction> s_initByJsonFuncDictionary;
};

#endif // UISTYLE_H
