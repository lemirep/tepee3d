#include "testplugin.h"

#include "widgetmodel.h"
#include <iostream>
//#include "qmlfunction.h"
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
//    QObject::connect(this, SIGNAL(focusStateChanged(QVariant, QVariant)), this, SLOT(onFocusStateChanged()));
//    this->initPlugin();
}

int TestPlugin::getPluginId()
{
    return 1;
}

void TestPlugin::initPlugin()
{
    std::cout << " INITIALIZING PLUGINS " << std::endl;
    this->setColor("yellow");
    this->executeHttpGetRequest(QNetworkRequest(QUrl("http://api.trakt.tv/show/summary.json/9a67e6b3bc1cbd1d92fdc56a03b51267/the-walking-dead")), 1);
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
    if (q.size() < 2)
        return ;
    if (id == ASSIGNCOLOR)
    {
        QList<QSqlRecord>::iterator it = q.begin();
        ++it;
        this->colorSelect = (*it).value("color").toString();
        qDebug() << "RECEIVE ASSIGN COLOR";
        QQmlComponent component(this->context->engine(), "../plugins_qml/qmltestplugin/Widget.qml");
        QObject *object = component.create();
        QVariant returnedValue;
        QVariant msg = this->colorSelect;
        QMetaObject::invokeMethod(object, "setColorAssign",
                Q_RETURN_ARG(QVariant, returnedValue),
                Q_ARG(QVariant, msg));
        delete object;
    }
}

void    TestPlugin::receiveResultFromHttpRequest(QNetworkReply *reply, int requestId)
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

void TestPlugin::onFocusStateChanged()
{
//    if (this->focusState == Plugins::PluginEnums::pluginFocusedState)
}

void TestPlugin::setColor(QString color)
{
    this->colorSelect = color;
}


void TestPlugin::onIdleFocusState()
{
    qDebug() << "Idle focus handler";
}

void TestPlugin::onSelectedFocusState()
{
    qDebug() << "Selected focus handler";
    this->initPlugin();
}

void TestPlugin::onFocusedFocusState()
{
    qDebug() << "Focused focus handler";
}
