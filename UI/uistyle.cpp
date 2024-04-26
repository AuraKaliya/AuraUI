#include "uistyle.h"

#include <QJsonObject>


QMap<UIStyle::InitFormation,UIStyleInitFunction> UIStyle::s_initFuncDictionary{
{UIStyle::Json,UIStyle::initStyleByJson}
};

QMap<QString,UIStyleInitByJsonFunction> UIStyle::s_initByJsonFuncDictionary
{
{"Widget",UIStyle::initWidgetStyleByJson}
};


void UIStyle::initStyle(UIStyle *styleObj, InitFormation form)
{
    auto it=s_initFuncDictionary.find(form);
    if(it == s_initFuncDictionary.end())
    {
        return;
    }
    bool res=it.value()(styleObj);
    if(!res)
    {
        //出错
        return;
    }
}

bool UIStyle::initStyleByJson(UIStyle *styleObj)
{
    bool res=true;
    QString path=styleObj->m_sourceDir+"/"+styleObj->m_styleName+".json";

    qDebug()<<"UIStyle::initStyleByJson | path:"<<path;
    //=======================check===========================
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug()<<"UIStyle::initStyleByJson | Cannot open file:"<<path;
        res=false;
        return res;
    }

    QByteArray data=file.readAll();
    QJsonParseError parseError;
    QJsonDocument doc=QJsonDocument::fromJson(data,&parseError);
    if(parseError.error!=QJsonParseError::NoError||doc.isNull()||!doc.isObject())
    {
        qDebug()<<"UIStyle::initStyleByJson | Faild to analyze file:"<<path;
        res=false;
        return res;
    }
    //=======================check===========================end

    QJsonObject root=doc.object();
    //=====================init====================
    for(auto it=s_initByJsonFuncDictionary.begin();it!=s_initByJsonFuncDictionary.end();++it)
    {
        if(root.contains(it.key()))
        {
            it.value()(styleObj,root.value(it.key()).toObject());
        }
    }
    //=====================init====================end

    return res;
}

void UIStyle::initWidgetStyleByJson(UIStyle *styleObj, const QJsonObject &obj)
{
    /*========Widget========*/
    styleObj->setStrFirstWidgetStyle(obj.value("strFirstWidget").toString());
    styleObj->setStrSecondWidgetStyle(obj.value("strSecondWidget").toString());
}

UIStyle::UIStyle(QString styleName)
{
    QDir dir(qApp->applicationDirPath()+"/StyleSource");
    m_sourceDir=dir.path();
    m_styleName=styleName;
}



QString UIStyle::strFirstWidgetStyle() const
{
    return m_strFirstWidgetStyle;
}

QString UIStyle::styleName() const
{
    return m_styleName;
}

QString UIStyle::styleWithClass(const QString &className, UIStyleStrFunction func) const
{
    QString style =className+"{"+func()+"}";
    return style;
}

void UIStyle::setStyleName(const QString &newStyleName)
{
    m_styleName = newStyleName;
}

void UIStyle::setStrFirstWidgetStyle(const QString &newStrFirstWidgetStyle)
{
    m_strFirstWidgetStyle = newStrFirstWidgetStyle;
}

QString UIStyle::strSecondWidgetStyle() const
{
    return m_strSecondWidgetStyle;
}

void UIStyle::setStrSecondWidgetStyle(const QString &newStrSecondWidgetStyle)
{
    m_strSecondWidgetStyle = newStrSecondWidgetStyle;
}
