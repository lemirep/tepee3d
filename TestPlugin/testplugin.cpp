#include "testplugin.h"
#include "widgetmodel.h"
#include <iostream>
#include "qmlfunction.h"
#include <QDebug>
#include <QtQml>
#include <QtCore/QDir>
#include <QtCore/QFileInfo>
#include <QtQml/QQmlComponent>
#include <QtQml/QQmlEngine>
#include <QtQml/QQmlContext>
#include <QtGui/QGuiApplication>


TestPlugin::TestPlugin() : PluginBase()
{
    std::cout << "CREATION OF TEST PLUGIN" << std::endl;
    this->initPlugin();
}

int TestPlugin::getPluginId()
{
    return 1;
}

void TestPlugin::initPlugin()
{
    std::cout << " INITIALIZING PLUGINS " << std::endl;
    this->setColor("yellow");
    this->executeHttpGetRequest(QNetworkRequest(QUrl("http://127.0.0.1/RESTphp/index.php")));
}

QString TestPlugin::getPluginName()
{
    return QString("qmltestplugin");
}

QString TestPlugin::getPluginDescription()
{
    return QString("Widget.qml");
}

Plugins::PluginBase* TestPlugin::getPluginBase()
{
    return this;
}

QString TestPlugin::getRoomPluginQmlFile() const
{
    qDebug() << " CALLING getRoomPluginQmlFile";
    return QString("Widget.qml");
}

QString TestPlugin::getMenuPluginQmlFile() const
{
    return QString("Menu.qml");
}

Plugins::PluginBase* TestPlugin::createNewInstance()
{
    return new TestPlugin();
}

void    TestPlugin::receiveResultFromSQLQuery( QList<QSqlRecord> q, int id)
{
    if (id == ASSIGNCOLOR)
    {
        QList<QSqlRecord>::iterator it = q.begin();
        ++it;
        this->colorSelect = (*it).value("color").toString();
        qDebug() << "RECEIVE ASSIGN COLOR";
        QQmlEngine engine;
        QQmlComponent component(&engine, "../plugins_qml/qmltestplugin/Widget.qml");
        QObject *object = component.create();
        QVariant returnedValue;
        QVariant msg = this->colorSelect;
        QMetaObject::invokeMethod(object, "setColorAssign",
                Q_RETURN_ARG(QVariant, returnedValue),
                Q_ARG(QVariant, msg));
        delete object;
    }
}

void    TestPlugin::receiveResultFromHttpRequest(QNetworkReply *reply)
{
    qDebug() << "TestPlugin::Received Network Reply";
    qDebug() << reply->readAll();
}

void   TestPlugin::exposeContentToQml(QQmlContext *context)
{
    this->context = context;
    this->context->setContextProperty("apc",this);
    emit (PluginBase::executeSQLQuery("CREATE TABLE IF NOT EXISTS `testplugincolor` (`id` text NOT NULL PRIMARY KEY  , `color` text NOT NULL)",this,1));
    emit (PluginBase::executeSQLQuery("INSERT INTO testplugincolor(id, color) VALUES (1, 'grey')",this,1));
    emit (PluginBase::executeSQLQuery("SELECT color from testplugincolor", this, ASSIGNCOLOR));
}

void TestPlugin::selectColor(QString color)
{
    QString query = "INSERT OR REPLACE INTO testplugincolor VALUES (1,'"+ color +"')";
    emit (PluginBase::executeSQLQuery(query,this,1));
}

QString TestPlugin::getColor()
{
    return this->colorSelect;
}

void TestPlugin::setColor(QString color)
{
    this->colorSelect = color;
}
