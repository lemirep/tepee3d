#include "testplugin.h"
<<<<<<< HEAD
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

=======
>>>>>>> 79f3df03274d66b07efe1845e744f5d881c3dc68

TestPlugin::TestPlugin() : PluginBase()
{
    std::cout << "CREATION OF TEST PLUGIN" << std::endl;
<<<<<<< HEAD
=======

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


>>>>>>> 79f3df03274d66b07efe1845e744f5d881c3dc68
    this->initPlugin();
}

int TestPlugin::getPluginId()
{
    return 1;
}

void TestPlugin::initPlugin()
{
<<<<<<< HEAD
    std::cout << " INITIALIZING PLUGINS " << std::endl;
=======
    std::cout << "INITIALIZING PLUGINS " << std::endl;
    emit (PluginBase::executeSQLQuery("SELECT *", this));
>>>>>>> 79f3df03274d66b07efe1845e744f5d881c3dc68
    this->executeHttpGetRequest(QNetworkRequest(QUrl("http://127.0.0.1/RESTphp/index.php")));
}

void TestPlugin::cppSlot()
{
   std::cout<< "Called the C++ slot with value:" <<std::endl;
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
<<<<<<< HEAD
    qDebug() << " CALLING getRoomPluginQmlFile";
    return QString("Widget.qml");
=======
    return QString("WidgetRoom.qml");
>>>>>>> 79f3df03274d66b07efe1845e744f5d881c3dc68
}

QString TestPlugin::getMenuPluginQmlFile() const
{
    return QString("Menu.qml");
}

Plugins::PluginBase* TestPlugin::createNewInstance()
{
    qDebug() << "BLABLABLABLBALALALALA";
    return new TestPlugin();
}

void    TestPlugin::receiveResultFromSQLQuery(const QList<QSqlRecord> &q, int id)
{
    if (id == ASSIGNCOLOR)
        qDebug() <<  "----------------------- " + q.first().value("color").toString();
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
<<<<<<< HEAD

void   TestPlugin::exposeContentToQml(QQmlContext *context)
{
    context->setContextProperty("apc",this);
    emit (PluginBase::executeSQLQuery("CREATE TABLE IF NOT EXISTS `testplugincolor` (`id` text NOT NULL PRIMARY KEY  , `color` text NOT NULL)",this,1));
    emit (PluginBase::executeSQLQuery("INSERT INTO testplugincolor(id, color) VALUES (1, 'grey')",this,1));
    emit (PluginBase::executeSQLQuery("SELECT color from testplugincolor",this,ASSIGNCOLOR));

}

void TestPlugin::selectColor(QString color)
{
    QString query = "INSERT OR REPLACE INTO testplugincolor VALUES (1,'"+ color +"')";
    emit (PluginBase::executeSQLQuery(query,this,1));
}
=======
>>>>>>> 79f3df03274d66b07efe1845e744f5d881c3dc68
