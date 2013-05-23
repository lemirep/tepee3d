#include "XBMCPlugin.h"

XBMCPlugin::XBMCPlugin() : PluginBase()
{
    this->setXbmcServerPassword("0000");
    this->setXbmcServerPort(8033);
    this->setXbmcServerUserName("xbmc");
    this->setXbmcServerUrl(QUrl("192.168.1.14"));

    this->m_audioLibrary = new AudioLibrary();
    QObject::connect(this->m_audioLibrary, SIGNAL(performJsonRPCRequest(QJsonObject, int, void *)), this, SLOT(performJsonRPCRequest(QJsonObject,int,void*)));
    this->networkRequestResultDispatch[this->m_audioLibrary->getMajorIDRequestHandled()] = this->m_audioLibrary;

    this->initPlugin();
}
// ALL the function should be implemented

int XBMCPlugin::getPluginId()
{
    return PLUGIN_ID;
}

void XBMCPlugin::initPlugin()
{
    qDebug() << ">>>>>>>>>>>>>>>>>>> " << this->getXbmcServerRequestUrl().toString();
    // PluginBase::executeHttpGetRequest(QNetworkRequest(this->getXbmcServerRequestUrl()), 1);
//    this->m_audioLibrary->retrieveAudioAlbums();
    this->m_audioLibrary->retrieveAudioArtists(this->m_audioLibrary->getSongsLibraryModel());
//    this->m_audioLibrary->retrieveAllSongs();
}

void XBMCPlugin::clearPluginBeforeRemoval()
{
}

QString XBMCPlugin::getPluginName()
{
    return QString("XBMCPlugin");
}

QString XBMCPlugin::getPluginDescription()
{
    return QString("XBMCPlugin.qml");
}

Plugins::PluginBase* XBMCPlugin::getPluginBase()
{
    return this;
}

QString XBMCPlugin::getRoomPluginQmlFile() const
{
    return QString("XBMCPlugin.qml");
}

QString XBMCPlugin::getMenuPluginQmlFile() const
{
    return QString("Menu.qml");
}

Plugins::PluginBase* XBMCPlugin::createNewInstance()
{
    return new XBMCPlugin();
}

void    XBMCPlugin::receiveResultFromSQLQuery(QList<QSqlRecord> reply, int id, void *data)
{
}

void    XBMCPlugin::receiveResultFromHttpRequest(QNetworkReply *reply, int id, void *data)
{
    qDebug() << "Result FROM XBMC PLUGIN REQUEST *************** Dispatching";
    this->networkRequestResultDispatch[id / 10]->receiveResultFromHttpRequest(reply, id % 10, data);
}

void XBMCPlugin::setXbmcServerPort(int port)
{
    this->m_xbmcServerPort = port;
    emit xbmcServerPortChanged();
}

void XBMCPlugin::setXbmcServerUrl(const QUrl &url)
{
    this->m_xbmcServerUrl = url;
    emit xbmcServerUrlChanged();
}

void XBMCPlugin::setXbmcServerUserName(const QString &username)
{
    this->m_xbmcServerUserName = username;
    emit xbmcServerUserNameChanged();
}

void XBMCPlugin::setXbmcServerPassword(const QString &password)
{
    this->m_xbmcServerPassword = password;
    emit xbmcServerPasswordChanged();
}

int XBMCPlugin::xbmcServerPort() const
{
    return this->m_xbmcServerPort;
}

QUrl XBMCPlugin::xbmcServerUrl() const
{
    return this->m_xbmcServerUrl;
}

QString XBMCPlugin::xbmcServerUserName() const
{
    return this->m_xbmcServerUserName;
}

QString XBMCPlugin::xbmcServerPassword() const
{
    return this->m_xbmcServerPassword;
}

QUrl XBMCPlugin::getXbmcServerRequestUrl() const
{
    return QUrl("http://" + this->m_xbmcServerUserName + ":" + this->m_xbmcServerPassword + "@" + this->m_xbmcServerUrl.toString() + ":" + QString::number(this->m_xbmcServerPort) + "/jsonrpc");
}

void XBMCPlugin::performJsonRPCRequest(const QJsonObject& request, int requestId, void *data)
{
    qDebug() << QUrl(this->getXbmcServerRequestUrl().toString() + "?request=" + QJsonDocument(request).toJson()).toString();

    PluginBase::executeHttpGetRequest(QNetworkRequest(QUrl(this->getXbmcServerRequestUrl().toString() + "?request=" + QJsonDocument(request).toJson())),
                                       requestId,
                                       data);
}
