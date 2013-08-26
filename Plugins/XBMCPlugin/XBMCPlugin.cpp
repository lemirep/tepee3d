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
    QObject::connect(this->m_playerManager, SIGNAL(playingChanged()), this, SIGNAL(playingChanged()));
    QObject::connect(this->m_playerManager, SIGNAL(playerAdvanceChanged()), this, SIGNAL(playerAdvanceChanged()));

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
    delete this->m_playerManager;
    delete this->m_remoteManager;
}

int XBMCPlugin::getPluginId() const
{
    return PLUGIN_ID;
}

bool XBMCPlugin::needsUpdating() const
{
    return true;
}

void XBMCPlugin::initPlugin()
{
    this->retrieveXBMCAuthFromDatabase();
}

void XBMCPlugin::clearPluginBeforeRemoval()
{
}

void XBMCPlugin::updatePlugin()
{
    static char i = 0;

    // Update Player State Frequently
    if (this->m_playerManager->getIsPlaying() || i == 15)
        this->m_playerManager->getCurrentPlayerState();
    if (i == 15 && this->m_playerManager->getIsPlaying())
    {
        i = 0;
        this->m_playerManager->getCurrentlyPlayedItem();
    }
    i++;
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

QString XBMCPlugin::getPluginRepoName() const
{
    return QString("xbmc_plugin");
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
    reply->close();
    delete reply;
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
    this->m_playerManager->getActivesPlayers();
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
    QUrl hostUrl(this->m_xbmcServerUrl);
    url.setScheme(hostUrl.scheme());
    url.setHost(hostUrl.host());
    url.setPort(this->m_xbmcServerPort);
    url.setUserName(this->m_xbmcServerUserName);
    url.setPassword(this->m_xbmcServerPassword);
    url.setPath(hostUrl.path() + "/jsonrpc");
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
    this->updateDataModels();
}

void XBMCPlugin::getCurrentlyPlayedItem()
{
    this->m_playerManager->getCurrentlyPlayedItem();
}

void XBMCPlugin::refreshLibraries()
{
    this->m_audioLibrary->refreshAudioLibrary();
    this->m_videoLibrary->refreshVideoLibrary();
}

void XBMCPlugin::addArtistToPlaylist(const int artistId)
{
    this->m_playerManager->addArtistToPlaylist(artistId);
}

void XBMCPlugin::addAlbumToPlaylist(const int albumId)
{
    this->m_playerManager->addAlbumToPlaylist(albumId);
}

void XBMCPlugin::addSongToPlaylist(const int songId)
{
    this->m_playerManager->addSongToPlaylist(songId);
}

void XBMCPlugin::addMovieToPlaylist(const int movieId)
{
    this->m_playerManager->addMovieToPlaylist(movieId);
}

void XBMCPlugin::addEpisodeToPlaylist(const int episodeId)
{
    this->m_playerManager->addEpisodeToPlaylist(episodeId);
}

void XBMCPlugin::clearPlaylist(const int playlistId)
{
    this->m_playerManager->clearPlaylist(playlistId);
}

void XBMCPlugin::genericDatabaseCallBack(QList<QSqlRecord> result, void *data)
{
    Q_UNUSED(result)
    Q_UNUSED(data)
}

bool XBMCPlugin::getPlaying() const
{
    return this->m_playerManager->getIsPlaying();
}

double XBMCPlugin::getPlayerAdvance() const
{
    return this->m_playerManager->getPlayerAdvance();
}

void XBMCPlugin::updateDataModels()
{
    this->m_videoLibrary->reloadDataModels();
    this->m_audioLibrary->reloadDataModels();
    this->m_playerManager->reloadPlaylists();
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

QObject *XBMCPlugin::getCurrentlyPlayedItemModel() const
{
    return this->m_playerManager->getCurrentlyPlayedItemModel();
}

QObject *XBMCPlugin::getPlaylists() const
{
    return this->m_playerManager->getPlaylistsModel();
}

QUrl XBMCPlugin::getXBMCImageProviderUrl(const QString& imageUrl) const
{
    QUrl url;
    QUrl hostUrl(this->m_xbmcServerUrl);
    url.setScheme(hostUrl.scheme());
    url.setHost(hostUrl.host());
    url.setPort(this->m_xbmcServerPort);
    url.setUserName(this->m_xbmcServerUserName);
    url.setPassword(this->m_xbmcServerPassword);
    url.setPath(hostUrl.path() + "/image/" + imageUrl);
    return url;
}

// REMOTE CONTROL ACTIONS

void XBMCPlugin::pressNavigationKey(int keyVal)
{
    RemoteManager::NavigationKeys key;
    switch (keyVal)
    {
    case 0:
        key = RemoteManager::Up;
        break;
    case 1:
        key = RemoteManager::Down;
        break;
    case 2:
        key = RemoteManager::Left;
        break;
    case 3:
        key = RemoteManager::Right;
        break;
    case 4:
        key = RemoteManager::Back;
        break;
    case 5:
        key = RemoteManager::Select;
        break;
    case 6:
        key = RemoteManager::Home;
        break;
    default:
        return ;
    }

    this->m_remoteManager->moveKey(key);
}

// PLAYER ACTIONS

void XBMCPlugin::playAction()
{
    this->m_playerManager->pause_resumeCurrentPlayer();
}

void XBMCPlugin::pauseAction()
{
    this->m_playerManager->pause_resumeCurrentPlayer();
}

void XBMCPlugin::nextAction()
{
    this->m_playerManager->playNext();
}

void XBMCPlugin::previousAction()
{
    this->m_playerManager->playPrevious();
}

void XBMCPlugin::smallForward()
{
    this->m_playerManager->smallForward();
}

void XBMCPlugin::smallBackward()
{
    this->m_playerManager->smallBackward();
}

void XBMCPlugin::bigForward()
{
    this->m_playerManager->bigForward();
}

void XBMCPlugin::bigBackward()
{
    this->m_playerManager->bigBackward();
}

void XBMCPlugin::stopAction()
{
    this->m_playerManager->stopCurrentPlayer();
}

void XBMCPlugin::seekAction(int durationPercent)
{
    this->m_playerManager->seekCurrentPlayer(durationPercent);
}

void XBMCPlugin::playFile(const QString &file)
{
    this->m_playerManager->playFile(file);
}

void XBMCPlugin::playPlaylist(int playlistId, int position)
{
    this->m_playerManager->playPlaylist(playlistId, position);
}

