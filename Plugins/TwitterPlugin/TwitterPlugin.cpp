#include "TwitterPlugin.h"

TwitterPlugin::TwitterPlugin() : PluginBase()
{
    qDebug() << "CREATION OF TwitterPlugin";
    this->initPlugin();
}

int TwitterPlugin::getPluginId()
{
    return 60;
}

void TwitterPlugin::initPlugin()
{
    qDebug() << " INITIALIZING PLUGINS ";
    //m_oauthTwitter = new OAuthTwitter(this);
    //m_oauthTwitter->setNetworkAccessManager(new QNetworkAccessManager(this));
    //connect(m_oauthTwitter, SIGNAL(authorizeXAuthFinished()), this, SLOT(xauthFinished()));
    //connect(m_oauthTwitter, SIGNAL(authorizeXAuthError()), this, SLOT(xauthError()));
}

QString TwitterPlugin::getPluginName()
{
    return QString("TwitterPlugin");
}

QString TwitterPlugin::getPluginDescription()
{
    return QString("TwitterPlugin Description");
}

Plugins::PluginBase* TwitterPlugin::getPluginBase()
{
    return this;
}

QString TwitterPlugin::getRoomPluginQmlFile() const
{
    return QString("TwitterPlugin.qml");
}

QString TwitterPlugin::getMenuPluginQmlFile() const
{
    return QString("Menu.qml");
}

Plugins::PluginBase* TwitterPlugin::createNewInstance()
{
    return new TwitterPlugin();
}

void    TwitterPlugin::receiveResultFromSQLQuery( QList<QSqlRecord> q, int , void *)
{
    if (q.size() < 2)
        return ;
}

void    TwitterPlugin::receiveResultFromHttpRequest(QNetworkReply *reply, int requestId, void *)
{
    qDebug() << "TwitterPlugin::Received Network Reply with id : " + requestId;
    qDebug() << reply->readAll();
}

void TwitterPlugin::onFocusStateChanged()
{

    //    if (this->focusState == Plugins::PluginEnums::pluginFocusedState)
}


void TwitterPlugin::onIdleFocusState()
{
    qDebug() << "Idle focus handler";
}

void TwitterPlugin::onSelectedFocusState()
{
    qDebug() << "Selected focus handler";
    this->initPlugin();
}

void TwitterPlugin::onFocusedFocusState()
{
    qDebug() << "Focused focus handler";
}

void TwitterPlugin::xauthFinished()
{
    qDebug() << "xauth successfull";
}

void TwitterPlugin::xauthError()
{
    qDebug() << "xauth fail";
}
