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

    //Connect qml to c++ first method
    QQmlEngine engine;
    QQmlComponent component(&engine, "../plugins_qml/qmltestplugin/WidgetRoom.qml");
    QObject *Instance = component.create();
    QObject::connect(Instance, SIGNAL(qmlSignal()),this, SLOT(cppSlot()));

    //Connect qml to c++ second method
   QQuickView view(QUrl::fromLocalFile("../plugins_qml/qmltestplugin/WidgetRoom.qml"));
   QObject *item = view.rootObject();
   if (QObject::connect(item, SIGNAL(qmlSignal()),this, SLOT(cppSlot())))
        std::cout << "connect OK " << std::endl;
    else
        std::cout << "connect not OK " << std::endl;
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

void    TestPlugin::receiveResultFromSQLQuery(const QList<QSqlRecord> &)
{
    qDebug() << "TestPlugin::Received Result From SQL Query Plugin";
}

void    TestPlugin::receiveResultFromHttpRequest(QNetworkReply *reply)
{
    qDebug() << "TestPlugin::Received Network Reply";
    qDebug() << reply->readAll();
}

void TestPlugin::cppSlot()
{
   std::cout<< "Called the C++ slot" <<std::endl;
}

//void        TestPlugin::resultFromSQL()
//{
//    std::cout << "TEST PLUGIN RESULT FROM SQL" << std::endl;
//}
