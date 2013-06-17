#include "TVShowSeasonModel.h"

TVShowSeasonModel::TVShowSeasonModel(QObject *parent, int seasonId) : Models::SubListedListItem(parent)
{
    this->m_season = seasonId;
    this->episodeModel = new Models::ListModel(new TVShowEpisodeModel());
}

TVShowSeasonModel::~TVShowSeasonModel()
{
    delete this->episodeModel;
    this->episodeModel = NULL;
}

int TVShowSeasonModel::id() const
{
    return this->m_season;
}

QVariant TVShowSeasonModel::data(int role) const
{
    switch (role)
    {
    case season:
        return this->id();
    case watchedEpisodes:
        return this->watchedEpisodes;
    case tvShowId:
        return this->getTVShowId();
    case episode:
        return this->getEpisode();
    case thumbnail:
        return this->getThumbnail();
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> TVShowSeasonModel::roleNames() const
{
    QHash<int, QByteArray> roleNames;
    roleNames[season] = "season";
    roleNames[watchedEpisodes] = "watchedEpisodes";
    roleNames[tvShowId] = "tvShowId";
    roleNames[episode] = "episode";
    roleNames[thumbnail] = "thumbnail";
    return roleNames;
}

Models::ListModel *TVShowSeasonModel::submodel() const
{
    return this->episodeModel;
}

QString TVShowSeasonModel::getThumbnail() const
{
    return this->m_thumbnail;
}

void TVShowSeasonModel::setThumbnail(const QString &thumbnail)
{
    this->m_thumbnail = QUrl::toPercentEncoding(thumbnail);
}

int TVShowSeasonModel::getEpisode() const
{
    return this->m_episode;
}

void TVShowSeasonModel::setEpisode(int episode)
{
    this->m_episode = episode;
}

int TVShowSeasonModel::getTVShowId() const
{
    return this->m_tvShowId;
}

void TVShowSeasonModel::setTVShowId(int tvShowId)
{
    this->m_tvShowId = tvShowId;
}

int TVShowSeasonModel::getWatchedEpisodes() const
{
    return this->m_watchedEpisodes;
}

void TVShowSeasonModel::setWatchedEpisodes(int watchedEpisodes)
{
    this->m_watchedEpisodes = watchedEpisodes;
}
