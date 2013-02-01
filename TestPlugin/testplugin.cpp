#include "testplugin.h"
#include "widgetmodel.h"
#include <iostream>
#include <QDebug>
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
    emit (PluginBase::executeSQLQuery("SELECT *", this));
    this->executeHttpGetRequest(QNetworkRequest(QUrl("http://127.0.0.1/RESTphp/index.php")));

    //Connect qml to c++ first method
    QQmlEngine engine;
    QQmlComponent component(&engine, "../plugins_qml/qmltestplugin/Widget.qml");
    QObject *Instance = component.create();
    if (QObject::connect(Instance, SIGNAL(selectColorSignal(QString color)),this, SLOT(SaveColorDB(QString color))))
         std::cout << "connect signal to slot 1 method  OK " << std::endl;
     else
         std::cout << "connectconnect signal to slot 1 method  not OK " << std::endl;

    //Connect qml to c++ second method
   QQuickView view(QUrl::fromLocalFile("../plugins_qml/qmltestplugin/Widget.qml"));
   QObject *item = view.rootObject();
   if (QObject::connect(item, SIGNAL(selectColorSignal(QString color)),this, SLOT(SaveColorDB(QString color))))
        std::cout << "connect signal to slot 2 method OK " << std::endl;
    else
        std::cout << "connect signal to slot 2 method  not OK " << std::endl;
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

void    TestPlugin::receiveResultFromSQLQuery(const QList<QSqlRecord> &)
{
    qDebug() << "TestPlugin::Received Result From SQL Query Plugin";
}

void    TestPlugin::receiveResultFromHttpRequest(QNetworkReply *reply)
{
    qDebug() << "TestPlugin::Received Network Reply";
    qDebug() << reply->readAll();
}

void TestPlugin::SaveColorDB(QString color)
{
   std::cout<< "Called the C++ slot " << color.toStdString() << std::endl;
}

//void        TestPlugin::resultFromSQL()
//{
//    std::cout << "TEST PLUGIN RESULT FROM SQL" << std::endl;
//}
