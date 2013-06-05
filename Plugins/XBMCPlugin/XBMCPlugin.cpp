#include "XBMCPlugin.h"

// MANDATORY PLUGIN METHODS

XBMCPlugin::XBMCPlugin() : PluginBase()
{
    this->m_audioLibrary = new AudioLibrary();
    this->m_videoLibrary = new VideoLibrary();
    this->m_remoteManager = new RemoteManager();
    this->m_playerManager = new PlayerManager();

    QObject::connect(this->m_audioLibrary, SIGNAL(performJsonRPCRequest(QJsonObject, int, void *)), this, SLOT(performJsonRPCRequest(QJsonObject,int,void*)));
    QObject::connect(this->m_videoLibrary, SIGNAL(performJsonRPCRequest(QJsonObject, int, void *)), this, SLOT(performJsonRPCRequest(QJsonObject,int,void*)));
    QObject::connect(this->m_remoteManager, SIGNAL(performJsonRPCRequest(QJsonObject, int, void *)), this, SLOT(performJsonRPCRequest(QJsonObject,int,void*)));
    QObject::connect(this->m_playerManager, SIGNAL(performJsonRPCRequest(QJsonObject, int, void *)), this, SLOT(performJsonRPCRequest(QJsonObject,int,void*)));

    this->networkRequestResultDispatch[this->m_audioLibrary->getMajorIDRequestHandled()] = this->m_audioLibrary;
    this->networkRequestResultDispatch[this->m_videoLibrary->getMajorIDRequestHandled()] = this->m_videoLibrary;
    this->networkRequestResultDispatch[this->m_remoteManager->getMajorIDRequestHandled()] = this->m_remoteManager;
    this->networkRequestResultDispatch[this->m_playerManager->getMajorIDRequestHandled()] = this->m_playerManager;

    this->databaseCallBacks[RETRIEVE_XBMC_AUTH] = &XBMCPlugin::retrieveXBMCAuthFromDatabaseCallBack;
    this->databaseCallBacks[GENERIC_DATABASE_CALLBACK] = &XBMCPlugin::genericDatabaseCallBack;
}

XBMCPlugin::~XBMCPlugin()
{
    delete this->m_audioLibrary;
    delete this->m_videoLibrary;
}

int XBMCPlugin::getPluginId() const
{
    return PLUGIN_ID;
}

void XBMCPlugin::initPlugin()
{
    this->retrieveXBMCAuthFromDatabase();
}

void XBMCPlugin::clearPluginBeforeRemoval()
{
}

QString XBMCPlugin::getPluginName() const
{
    return QString("XBMCPlugin");
}

QString XBMCPlugin::getPluginVersion() const
{
    return PLUGIN_VERSION;
}

QString XBMCPlugin::getPluginDescription() const
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
    (this->*this->databaseCallBacks[id])(reply, data);
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
    QUrl url;
    url.setScheme("http");
    url.setHost(this->m_xbmcServerUrl.host());
    url.setPort(this->m_xbmcServerPort);
    url.setUserName(this->m_xbmcServerUserName);
    url.setPassword(this->m_xbmcServerPassword);
    url.setPath("/jsonrpc");
    return url;
}

void XBMCPlugin::retrieveXBMCAuthFromDatabase()
{
    QString query = "SELECT url, port, username, password FROM auth;";

    emit executeSQLQuery(query, this, RETRIEVE_XBMC_AUTH, DATABASE_NAME);
}

void XBMCPlugin::retrieveXBMCAuthFromDatabaseCallBack(QList<QSqlRecord> result, void *data)
{
    Q_UNUSED(data)

    if (result.size() == 2)
    {
        result.pop_front();
        this->setXbmcServerUrl(QUrl(result.first().value(0).toString()));
        this->setXbmcServerPort(result.first().value(1).toInt());
        this->setXbmcServerUserName(result.first().value(2).toString());
        this->setXbmcServerPassword(result.first().value(3).toString());
        this->updateDataModels();
    }
}

void XBMCPlugin::saveXBMCAuthToDatabase()
{
    QString removeQuery("DELETE FROM auth;");
    emit executeSQLQuery(removeQuery, this, GENERIC_DATABASE_CALLBACK, DATABASE_NAME);
    QString query = QString("INSERT OR REPLACE INTO auth (url, port, username, password) VALUES ('%1', %2, '%3', '%4');")
            .arg(this->m_xbmcServerUrl.toString(),
                 QString::number(this->m_xbmcServerPort),
                 this->m_xbmcServerUserName,
                 this->m_xbmcServerPassword);
    emit executeSQLQuery(query, this, GENERIC_DATABASE_CALLBACK, DATABASE_NAME);
}

void XBMCPlugin::genericDatabaseCallBack(QList<QSqlRecord> result, void *data)
{
    Q_UNUSED(result)
    Q_UNUSED(data)
}

void XBMCPlugin::updateDataModels()
{
    this->m_audioLibrary->getAlbumsLibraryModel()->clear();
    this->m_audioLibrary->getArtistsLibraryModel()->clear();
    this->m_audioLibrary->getSongsLibraryModel()->clear();
    this->m_videoLibrary->getTVShowsLibraryModel()->clear();
    this->m_videoLibrary->getMoviesLibraryModel()->clear();
    //    // RETRIEVE VIDEO MEDIAS
    this->m_videoLibrary->retrieveTVShows(this->m_videoLibrary->getTVShowsLibraryModel());
    this->m_videoLibrary->retrieveMovies(this->m_videoLibrary->getMoviesLibraryModel());
    //    // RETRIEVE AUDIO MEDIAS
    this->m_audioLibrary->retrieveAudioAlbums(this->m_audioLibrary->getAlbumsLibraryModel());
    this->m_audioLibrary->retrieveAudioArtists(this->m_audioLibrary->getArtistsLibraryModel());
    this->m_audioLibrary->retrieveAllSongs(this->m_audioLibrary->getSongsLibraryModel());
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

QUrl XBMCPlugin::getXBMCImageProviderUrl(const QString& imageUrl) const
{
    QUrl url;
    url.setScheme("http");
    url.setHost(this->m_xbmcServerUrl.host());
    url.setPort(this->m_xbmcServerPort);
    url.setUserName(this->m_xbmcServerUserName);
    url.setPassword(this->m_xbmcServerPassword);
    url.setPath("/image/" + imageUrl);
    return url;
}

// REMOTE CONTROL ACTIONS

void XBMCPlugin::pressNavigationKey(NavigationKeys key)
{
    this->m_remoteManager->moveKey(key);
}

// PLAYER ACTIONS

void XBMCPlugin::playAction()
{
    this->m_playerManager->resumeCurrentPlayer();
}

void XBMCPlugin::pauseAction()
{
    this->m_playerManager->pauseCurrentPlayer();
}

void XBMCPlugin::nextAction()
{
    this->m_playerManager->playNext();
}

void XBMCPlugin::previousAction()
{
    this->m_playerManager->playPrevious();
}

void XBMCPlugin::playFile(const QString &file)
{
    this->m_playerManager->playFile(file);
}

