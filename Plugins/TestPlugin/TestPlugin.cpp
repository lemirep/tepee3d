#include "TestPlugin.h"
#include <QAudioOutput>
TestPlugin::TestPlugin() : PluginBase()
{
    qDebug() << "CREATION OF TEST PLUGIN";
    //    QObject::connect(this, SIGNAL(focusStateChanged(QVariant, QVariant)), this, SLOT(onFocusStateChanged()));
    //    this->initPlugin();
}

int TestPlugin::getPluginId()
{
    return 1;
}

void TestPlugin::initPlugin()
{
    qDebug() << " INITIALIZING PLUGINS ";
    this->setColor("yellow");
    //   this->executeHttpGetRequest(QNetworkRequest(QUrl("http://api.trakt.tv/show/summary.json/9a67e6b3bc1cbd1d92fdc56a03b51267/the-walking-dead")), 1);
}

QString TestPlugin::getPluginName()
{
    return QString("TestPlugin");
}

QString TestPlugin::getPluginDescription()
{
    return QString("TestPlugin Description");
}

Plugins::PluginBase* TestPlugin::getPluginBase()
{
    return this;
}

QString TestPlugin::getRoomPluginQmlFile() const
{
    return QString("TestPlugin.qml");
}

QString TestPlugin::getMenuPluginQmlFile() const
{
    return QString("Menu.qml");
}

Plugins::PluginBase* TestPlugin::createNewInstance()
{
    return new TestPlugin();
}

void    TestPlugin::receiveResultFromSQLQuery( QList<QSqlRecord> q, int id, void *)
{
    if (q.size() < 2)
        return ;
    if (id == ASSIGNCOLOR)
    {
        //        QList<QSqlRecord>::iterator it = q.begin();
        //        ++it;
        //        this->colorSelect = (*it).value("color").toString();
        //        qDebug() << "RECEIVE ASSIGN COLOR";
        //        QQmlComponent component(this->context->engine(), "../plugins_qml/qmlTestPlugin/Widget.qml");
        //        QObject *object = component.create();
        //        QVariant returnedValue;
        //        QVariant msg = this->colorSelect;
        //        QMetaObject::invokeMethod(object, "setColorAssign",
        //                Q_RETURN_ARG(QVariant, returnedValue),
        //                Q_ARG(QVariant, msg));
        //        delete object;
    }
}

void    TestPlugin::receiveResultFromHttpRequest(QNetworkReply *reply, int requestId, void *)
{
    qDebug() << "TestPlugin::Received Network Reply with id : " + requestId;
    qDebug() << reply->readAll();
}

void TestPlugin::selectColor(QString color)
{
    QString query = "INSERT OR REPLACE INTO TestPlugincolor VALUES (1,'"+ color +"')";
    emit (PluginBase::executeSQLQuery(query,this,1, "", NULL));
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
    QMediaPlayer *player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile("HS.mp3"));
    player->setVolume(100);
    player->play();
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

