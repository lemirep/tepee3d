#include "SeriesPlugin.h"

SeriesPlugin::SeriesPlugin() : PluginBase()
{
    this->initPlugin();
    this->webServicesCallBacks[SEARCH_SHOW_REQUEST] = &SeriesPlugin::searchForShowCallBack;
    this->webServicesCallBacks[SEARCH_EPISODE_REQUEST] = &SeriesPlugin::searchForEpisodeBack;
    this->webServicesCallBacks[GET_SEASONS] = &SeriesPlugin::getSeasonsForShowCallBack;
    this->webServicesCallBacks[GET_EPISODES_FOR_SEASON] = &SeriesPlugin::getEpisodesForSeasonCallBack;
    this->followedSeriesModel = new Models::SubListedListModel(new SerieSubListedItem("", "", ""));
}
// ALL the function should be implemented

int SeriesPlugin::getPluginId()
{
    return PLUGIN_ID;
}

void SeriesPlugin::initPlugin()
{
    //    this->executeHttpGetRequest(QNetworkRequest(QUrl("http://127.0.0.1/RESTphp/index.php")),1);
}

QString SeriesPlugin::getPluginName()
{
    return QString("SeriesPlugin");
}

QString SeriesPlugin::getPluginDescription()
{
    return QString("SeriesPlugin.qml");
}

Plugins::PluginBase* SeriesPlugin::getPluginBase()
{
    return this;
}

QString SeriesPlugin::getRoomPluginQmlFile() const
{
    return QString("SeriesPlugin.qml");
}

QString SeriesPlugin::getMenuPluginQmlFile() const
{
    return QString("Menu.qml");
}

Plugins::PluginBase* SeriesPlugin::createNewInstance()
{
    return new SeriesPlugin();
}

void    SeriesPlugin::receiveResultFromSQLQuery( QList<QSqlRecord> , int )
{
}

void    SeriesPlugin::receiveResultFromHttpRequest(QNetworkReply *reply, int id)
{
    qDebug() << "Received WebService CallBack";
    (this->*this->webServicesCallBacks[id])(reply);
}

QObject    *SeriesPlugin::getFollowedSeriesModel()
{
    if (this->followedSeriesModel->rowCount() == 0)
        this->searchForShow("the walking dead");
    return this->followedSeriesModel;
}

void SeriesPlugin::searchForShow(QString showName)
{
    showName = showName.replace(" ", "-");
    PluginBase::executeHttpGetRequest(QNetworkRequest(QUrl("http://api.trakt.tv/search/shows.json/" + QString(TRAKT_API_KEY) + "/" + showName)),
                                      SEARCH_SHOW_REQUEST);
}

void SeriesPlugin::searchForEpisode(QString episodeName)
{
    episodeName = episodeName.replace(" ", "-");
    PluginBase::executeHttpGetRequest(QNetworkRequest(QUrl("http://api.trakt.tv/search/episodes.json/" + QString(TRAKT_API_KEY) + "/" + episodeName)),
                                      SEARCH_EPISODE_REQUEST);
}

QObject *SeriesPlugin::getSeasonsForShow(QString title)
{
    return NULL;
}

QObject *SeriesPlugin::getEpisodesForShowSeason(QString title, int season)
{
    return NULL;
}

void SeriesPlugin::searchForShowCallBack(QNetworkReply *reply)
{
    if (reply != NULL)
    {
        QJsonDocument jsonDoc = QJsonDocument::fromJson(reply->readAll());
//        qDebug() << "{" << data << "}";
        if (!jsonDoc.isNull() && !jsonDoc.isEmpty())
        {
            qDebug() << "Json is not null";
            if (jsonDoc.isArray())
            {
                QJsonArray showsArray = jsonDoc.array();
                foreach (QJsonValue arrayVal, showsArray)
                {
                    if (arrayVal.isObject())
                    {
                        QJsonObject show = arrayVal.toObject();
                        if (!show.isEmpty())
                        {
                            QJsonObject imageObj = show.take("images").toObject();
                            qDebug() << "New Show Added";
                            qDebug() << show.value("imdb_id").toString() << " " << show.value("title").toString() << "images" << imageObj.value("poster").toString();
                            this->followedSeriesModel->appendRow(new SerieSubListedItem(show.value("imdb_id").toString(),
                                                                                        show.value("title").toString(),
                                                                                        imageObj.value("poster").toString()));
                        }
                    }
                }
            }
        }
        else
            qDebug() << "An error occured when retrieving the JSON";
    }
}

void SeriesPlugin::searchForEpisodeBack(QNetworkReply *reply)
{
}

void SeriesPlugin::getSeasonsForShowCallBack(QNetworkReply *reply)
{
}

void SeriesPlugin::getEpisodesForSeasonCallBack(QNetworkReply *reply)
{
}
