#include "XBMCPlugin.h"

// MANDATORY PLUGIN METHODS

XBMCPlugin::XBMCPlugin() : PluginBase()
{
    this->setXbmcServerPassword("0000");
    this->setXbmcServerPort(8033);
    this->setXbmcServerUserName("xbmc");
    this->setXbmcServerUrl(QUrl("192.168.1.14"));

    this->m_audioLibrary = new AudioLibrary();
    this->m_videoLibrary = new VideoLibrary();
    this->m_remoteManager = new RemoteManager();

    QObject::connect(this->m_audioLibrary, SIGNAL(performJsonRPCRequest(QJsonObject, int, void *)), this, SLOT(performJsonRPCRequest(QJsonObject,int,void*)));
    QObject::connect(this->m_videoLibrary, SIGNAL(performJsonRPCRequest(QJsonObject, int, void *)), this, SLOT(performJsonRPCRequest(QJsonObject,int,void*)));
    QObject::connect(this->m_remoteManager, SIGNAL(performJsonRPCRequest(QJsonObject, int, void *)), this, SLOT(performJsonRPCRequest(QJsonObject,int,void*)));

    this->networkRequestResultDispatch[this->m_audioLibrary->getMajorIDRequestHandled()] = this->m_audioLibrary;
    this->networkRequestResultDispatch[this->m_videoLibrary->getMajorIDRequestHandled()] = this->m_videoLibrary;
    this->networkRequestResultDispatch[this->m_remoteManager->getMajorIDRequestHandled()] = this->m_remoteManager;
    this->initPlugin();
}

XBMCPlugin::~XBMCPlugin()
{
    delete this->m_audioLibrary;
    delete this->m_videoLibrary;
}

int XBMCPlugin::getPluginId()
{
    return PLUGIN_ID;
}

void XBMCPlugin::initPlugin()
{
//    // RETRIEVE AUDIO MEDIAS
//    this->m_audioLibrary->retrieveAudioAlbums(this->m_audioLibrary->getAlbumsLibraryModel());
//    this->m_audioLibrary->retrieveAudioArtists(this->m_audioLibrary->getSongsLibraryModel());
//    this->m_audioLibrary->retrieveAllSongs(this->m_audioLibrary->getSongsLibraryModel());
//    // RETRIEVE VIDEO MEDIAS
//    this->m_videoLibrary->retrieveTVShows(this->m_videoLibrary->getTVShowsLibraryModel());
//    this->m_videoLibrary->retrieveMovies(this->m_videoLibrary->getMoviesLibraryModel());
    this->pressNavigationKey(Left);
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
    this->networkRequestResultDispatch[id / 10]->receiveResultFromHttpRequest(reply, id % 10, data);
}

// FOCUS STATE HANDLERS

void XBMCPlugin::onIdleFocusState()
{
}

void XBMCPlugin::onSelectedFocusState()
{
}

void XBMCPlugin::onFocusedFocusState()
{
}

// XBMC CREDENTIALS MANIPULATION

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
    PluginBase::executeHttpGetRequest(QNetworkRequest(QUrl(this->getXbmcServerRequestUrl().toString() + "?request=" + QJsonDocument(request).toJson())),
                                       requestId,
                                       data);
}


// MEDIA LIBRARY

QObject *XBMCPlugin::getMoviesLibrary() const
{
    return this->m_videoLibrary->getMoviesLibraryModel();
}

QObject *XBMCPlugin::getTVShowsLibrary() const
{
    return this->m_videoLibrary->getTVShowsLibraryModel();
}

QObject *XBMCPlugin::getAlbumsLibrary() const
{
    return this->m_audioLibrary->getAlbumsLibraryModel();
}

QObject *XBMCPlugin::getArtistsLibrary() const
{
    return this->m_audioLibrary->getArtistsLibraryModel();
}

QObject *XBMCPlugin::getSongsLibrary() const
{
    return this->m_audioLibrary->getSongsLibraryModel();
}

// REMOTE CONTROL ACTIONS

void XBMCPlugin::pressNavigationKey(NavigationKeys key)
{
    this->m_remoteManager->moveKey(key);
}

// PLAYER ACTIONS

void XBMCPlugin::playAction()
{
}

void XBMCPlugin::pauseAction()
{
}

void XBMCPlugin::nextAction()
{
}

void XBMCPlugin::previousAction()
{
}

