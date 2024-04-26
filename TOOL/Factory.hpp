#pragma once

#include<QString>
#include <QMap>
#include <QObject>


/*
    提供QObject和QWidget两种原基类的引申类模板，方便构造基于元对象系统的多态族和基于窗体的多态族
*/


template<class T>
class Factory
{
public:

    static Factory<T>* GetInstance()
    {
        if(m_instance==nullptr)
        {
            m_instance=new Factory();
        }
        return m_instance;
    };

    void RegisterClass(const QString &objectName,T* objectClass)
    {
        m_factoryCreator[objectName]=objectClass;
    };
    void RegisterObject(const QString &objectName,std::function<T*(QObject*)> objectClass)
    {
        m_factoryObjectCreator.insert(objectName,objectClass);
    };
    void RegisterWidget(const QString &objectName,std::function<T*(QWidget*)> objectClass)
    {
        m_factoryWidgetCreator.insert(objectName,objectClass);
    };

    T* CreateClass(const QString &objectName)
    {
        auto it=m_factoryCreator.find(objectName);
        if(it!=m_factoryCreator.end())
        {
            return it.value()();
        }
        else
        {
            return nullptr;
        }
    };


    T* CreateObject(const QString &objectName,QObject* parent=nullptr)
    {
        auto it=m_factoryObjectCreator.find(objectName);
        if(it!=m_factoryObjectCreator.end())
        {
            return it.value()(parent);
        }
        else
        {
            return nullptr;
        }
    };


    T* CreateWidget(const QString &objectName,QWidget* parent=nullptr)
    {
        auto it=m_factoryWidgetCreator.find(objectName);
        if(it!=m_factoryWidgetCreator.end())
        {
            return it.value()(parent);
        }
        else
        {
            return nullptr;
        }
    };


private:

    static Factory<T>* m_instance;

    Factory()=default;

    QMap<QString,T*>m_factoryCreator;
    QMap<QString,std::function<T*(QObject*)> >m_factoryObjectCreator;
    QMap<QString,std::function<T*(QWidget*)> >m_factoryWidgetCreator;
};


template<class T>
Factory<T>* Factory<T>::m_instance=nullptr;



template <typename T,typename Base>
std::function<Base*()> createFactoryCreator()
{
    return []() ->Base*
    {
        return new T();
    };
}

//////////////////////////////////////////////

template <typename T,typename Base>
std::function<Base*(QObject*)> createObjectFactoryCreator()
{
    return [](QObject* parent) ->Base*
    {
        return new T(parent);
    };
}

template <typename T,typename Base>
std::function<Base*(QObject*)> createObjectFactoryCreatorSingle()
{
    return [](QObject* parent) ->Base*
    {
        return T::GetInstance();
    };
}


//////////////////////////////////////////////


template <typename T,typename Base>
std::function<Base*(QWidget*)> createWidgetFactoryCreator()
{
    return [](QWidget* parent) ->Base*
    {
        return new T(parent);
    };
}

template <typename T,typename Base>
std::function<Base*(QWidget*)> createWidgetCreatorSingle()
{
    return [](QWidget* parent) ->Base*
    {
        return T::GetInstance();
    };
}




