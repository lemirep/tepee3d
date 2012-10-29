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

Plugins::PluginBase* TestPlugin::createNewInstance()
{
    return new TestPlugin();
}

void   TestPlugin::receiveResultFromSQLQuery(const QList<QSqlRecord> &result)
{
    qDebug() << "Received Result From SQL Query Plugin";
}

//void        TestPlugin::resultFromSQL()
//{
//    std::cout << "TEST PLUGIN RESULT FROM SQL" << std::endl;
//}
