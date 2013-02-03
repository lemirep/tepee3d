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
    emit (PluginBase::executeSQLQuery("CREATE TABLE IF NOT EXISTS `testplugincolor` (`id` text NOT NULL PRIMARY KEY  , `color` text NOT NULL)",this));
    emit (PluginBase::executeSQLQuery("INSERT OR REPLACE INTO data VALUES (1,'grey')",this));
}

int TestPlugin::getPluginId()
{
    return 1;
}

void TestPlugin::initPlugin()
{
    std::cout << " INITIALIZING PLUGINS " << std::endl;
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

void    TestPlugin::receiveResultFromSQLQuery(const QList<QSqlRecord> &q)
{
    qDebug() <<  "----------------------- " + q.first().value("id").toString();
/*    QList<QSqlRecord>::iterator it = q.begin();
           while (it != q.end())
           {

               qDebug() << (*it).value("id").toInt();

               ++it;
           }
    qDebug() << "TestPlugin::Received Result From SQL Query Plugin";
*/
}

void    TestPlugin::receiveResultFromHttpRequest(QNetworkReply *reply)
{
    qDebug() << "TestPlugin::Received Network Reply";
    qDebug() << reply->readAll();
}

void   TestPlugin::exposeContentToQml(QQmlContext *context)
{
    //    QmlFunction *q = new QmlFunction();
    context->setContextProperty("apc",this);
}

void TestPlugin::selectColor(QString color)
{
    emit (PluginBase::executeSQLQuery("CREATE TABLE IF NOT EXISTS `testplugincolor` (`id` text NOT NULL PRIMARY KEY  , `color` text NOT NULL)",this));
    emit (PluginBase::executeSQLQuery("INSERT OR REPLACE INTO data VALUES (1,'grey')",this));

    emit (PluginBase::executeSQLQuery("SELECT *", this));
    std::cout<< "Called the C++ slot " << color.toStdString() << std::endl;

}
