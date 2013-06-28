#ifndef XBMCPLUGIN_H
#define XBMCPLUGIN_H

#include <QObject>
#include <QQuickView>
#include <QQuickItem>
#include <QHash>
#include "PluginBase.h"
#include "DatabaseServiceUserInterface.h"
#include "WebServiceUserInterface.h"
#include "IWebRequestDispatcher.h"
#include <QDebug>
#include "AudioLibrary.h"
#include "VideoLibrary.h"
#include "RemoteManager.h"
#include "PlayerManager.h"

#define PLUGIN_ID 12
#define PLUGIN_VERSION "1.0.0"

#define DATABASE_NAME "XBMCPlugin.sql"
#define GENERIC_DATABASE_CALLBACK 0
#define RETRIEVE_XBMC_AUTH 1

//class RemoteManager;

class XBMCPlugin  : public Plugins::PluginBase
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.tepee3d.plugins.xbmcplugin")
    Q_ENUMS(NavigationKeys)

    Q_PROPERTY(int xbmcServerPort WRITE setXbmcServerPort READ xbmcServerPort NOTIFY xbmcServerPortChanged)
    Q_PROPERTY(QUrl xbmcServerUrl WRITE setXbmcServerUrl READ xbmcServerUrl NOTIFY xbmcServerUrlChanged)
    Q_PROPERTY(QString xbmcServerUserName WRITE setXbmcServerUserName READ xbmcServerUserName NOTIFY xbmcServerUserNameChanged)
    Q_PROPERTY(QString xbmcServerPassword WRITE setXbmcServerPassword READ xbmcServerPassword NOTIFY xbmcServerPasswordChanged)
    Q_PROPERTY(bool playing READ getPlaying NOTIFY playingChanged)
    Q_PROPERTY(double playerAdvance READ getPlayerAdvance NOTIFY playerAdvanceChanged)

public:
    XBMCPlugin();
    virtual ~XBMCPlugin();

    int                         getPluginId() const;
    bool                        needsUpdating() const;
    void                        initPlugin();
    void                        clearPluginBeforeRemoval();
    void                        updatePlugin();

    PluginBase*                 getPluginBase();
    PluginBase*                 createNewInstance();

    QString                     getRoomPluginQmlFile() const;
    QString                     getMenuPluginQmlFile() const;

    Q_INVOKABLE QString         getPluginName() const;
    Q_INVOKABLE QString         getPluginVersion() const;
    Q_INVOKABLE QString         getPluginDescription() const;

    // REMOTE CONTROL ACTIONS
    enum NavigationKeys
    {
        Up = 0,
        Down,
        Left,
        Right,
        Back,
        Select,
        Home
    };

    Q_INVOKABLE void               pressNavigationKey(NavigationKeys key);

    // PLAYER ACTIONS
    Q_INVOKABLE void               playAction();
    Q_INVOKABLE void               pauseAction();
    Q_INVOKABLE void               nextAction();
    Q_INVOKABLE void               previousAction();
    Q_INVOKABLE void               stopAction();
    Q_INVOKABLE void               seekAction(int durationPercent);
    Q_INVOKABLE void               playFile(const QString &file);
    Q_INVOKABLE void               playPlaylist(int playlistId, int position);

    // MEDIA LIBRARIES
    Q_INVOKABLE QObject*           getMoviesLibrary() const;
    Q_INVOKABLE QObject*           getTVShowsLibrary() const;
    Q_INVOKABLE QObject*           getAlbumsLibrary() const;
    Q_INVOKABLE QObject*           getArtistsLibrary() const;
    Q_INVOKABLE QObject*           getSongsLibrary() const;
    Q_INVOKABLE QObject*           getCurrentlyPlayedItemModel() const;
    Q_INVOKABLE QObject*           getPlaylists() const;
    Q_INVOKABLE QUrl               getXBMCImageProviderUrl(const QString &imageUrl) const;
    Q_INVOKABLE void               saveXBMCAuthToDatabase();
    Q_INVOKABLE void               getCurrentlyPlayedItem();
    Q_INVOKABLE void               refreshLibraries();
    Q_INVOKABLE void               addArtistToPlaylist(const int artistId);
    Q_INVOKABLE void               addAlbumToPlaylist(const int albumId);
    Q_INVOKABLE void               addMovieToPlaylist(const int movieId);
    Q_INVOKABLE void               addEpisodeToPlaylist(const int episodeId);

    // FOCUS STATE HANDLERS
    void                        onIdleFocusState();
    void                        onSelectedFocusState();
    void                        onFocusedFocusState();

    // DatabaseServiceUserInterface
    void                        receiveResultFromSQLQuery(QList<QSqlRecord> result, int id, void *data);
    // WebServiceUserInterface
    void                        receiveResultFromHttpRequest(QNetworkReply * reply,int id, void *data);

    void                        setXbmcServerPort(int port);
    void                        setXbmcServerUrl(const QUrl &url);
    void                        setXbmcServerUserName(const QString &username);
    void                        setXbmcServerPassword(const QString &password);

    int                         xbmcServerPort()  const;
    QUrl                        xbmcServerUrl()    const;
    QString                     xbmcServerUserName() const;
    QString                     xbmcServerPassword()   const;

private:
    QHash<int, IWebRequestDispatcher*>                                      networkRequestResultDispatch;
    QHash<int, void (XBMCPlugin::*)(QList<QSqlRecord> result, void *data)>  databaseCallBacks;

    AudioLibrary    *m_audioLibrary;
    VideoLibrary    *m_videoLibrary;
    PlayerManager   *m_playerManager;
    RemoteManager   *m_remoteManager;

    bool            m_playing;
    int             m_xbmcServerPort;
    QUrl            m_xbmcServerUrl;
    QString         m_xbmcServerUserName;
    QString         m_xbmcServerPassword;

    QUrl                       getXbmcServerRequestUrl() const;
    void                       retrieveXBMCAuthFromDatabase();
    void                       retrieveXBMCAuthFromDatabaseCallBack(QList<QSqlRecord> result, void *data);
    void                       genericDatabaseCallBack(QList<QSqlRecord> result, void *data);
    bool                       getPlaying() const;
    double                     getPlayerAdvance() const;

    void                       updateDataModels();


private slots:
    void                        performJsonRPCRequest(const QJsonObject& request, int requestId, void *data = NULL);

signals:
    void                        xbmcServerUrlChanged();
    void                        xbmcServerPortChanged();
    void                        xbmcServerUserNameChanged();
    void                        xbmcServerPasswordChanged();
    void                        playingChanged();
    void                        playerAdvanceChanged();

};

#endif // XBMCPLUGIN_H
