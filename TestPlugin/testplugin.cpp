#include "testplugin.h"
#include "widgetmodel.h"
#include <iostream>
#include <QDebug>
TestPlugin::TestPlugin() : PluginBase()
{
    std::cout << "CREATION OF TEST PLUGIN" << std::endl;
}

int TestPlugin::getPluginId()
{
    return 1;
}

void TestPlugin::initPlugin()
{
    std::cout << " INITIALIZING PLUGINS " << std::endl;
    emit (PluginBase::executeSQLQuery("SELECT *", this));
    this->executeHttpGetRequest(QNetworkRequest(QUrl("http://127.0.0.1/RESTphp/index.php")));
}

QString TestPlugin::getPluginName()
{
    emit toto(QString("YOUHOU"));
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
    return QString("WidgetRoom.qml");
}

QString TestPlugin::getFocusedPluginQmlFile() const
{
    return QString("WidgetFocused.qml");
}

Plugins::PluginBase* TestPlugin::createNewInstance()
{
    return new TestPlugin();
}

void    TestPlugin::receiveResultFromSQLQuery(const QList<QSqlRecord> &)
{
    qDebug() << "TestPlugin::Received Result From SQL Query Plugin";
}

void    TestPlugin::receiveResultFromHttpRequest(QNetworkReply *reply)
{
    qDebug() << "TestPlugin::Received Network Reply";
    qDebug() << reply->readAll();
}

//void        TestPlugin::resultFromSQL()
//{
//    std::cout << "TEST PLUGIN RESULT FROM SQL" << std::endl;
//}
