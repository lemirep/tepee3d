#include "TVShowModel.h"

TVShowModel::TVShowModel(QObject *parent, int tvShowId) : Models::SubListedListItem(parent)
{
    this->m_tvShowId = tvShowId;
    this->seasonModels = new Models::SubListedListModel(new TVShowSeasonModel());
}

TVShowModel::~TVShowModel()
{
    delete this->seasonModels;
    this->seasonModels = NULL;
}

int TVShowModel::id() const
{
    return this->m_tvShowId;
}

QVariant TVShowModel::data(int role) const
{
    switch (role)
    {
    case tvShowId:
        return this->id();
    case title:
        return this->getTitle();
    case year:
        return this->getYear();
    case rating:
        return this->getRating();
    case playcount:
        return this->getPlaycount();
    case episode:
        return this->getEpisode();
    case season:
        return this->getSeason();
    case watchedepisodes:
        return this->getWatchedEpisodes();
    case file:
        return this->getFile();
    case thumbnail:
        return this->getThumbnail();
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> TVShowModel::roleNames() const
{
    QHash<int, QByteArray> roleNames;

    roleNames[tvShowId] = "tvShowId";
    roleNames[title] = "title";
    roleNames[year] = "year";
    roleNames[rating] = "rating";
    roleNames[playcount] = "playcount";
    roleNames[episode] = "episode";
    roleNames[season] = "season";
    roleNames[watchedepisodes] = "watchedepisodes";
    roleNames[file] = "file";
    roleNames[thumbnail] = "thumbnail";

    return roleNames;
}

Models::ListModel *TVShowModel::submodel() const
{
    return this->seasonModels;
}

QString TVShowModel::getThumbnail() const
{
    return this->m_thumbnail;
}

void TVShowModel::setThumbnail(const QString &thumbnail)
{
    this->m_thumbnail = QUrl::toPercentEncoding(thumbnail);
}

QString TVShowModel::getTitle() const
{
    return this->m_title;
}

void TVShowModel::setTitle(const QString &title)
{
    this->m_title = title;
}

QString TVShowModel::getFile() const
{
    return this->m_file;
}

void TVShowModel::setFile(const QString &file)
{
    this->m_file = file;
}

int TVShowModel::getWatchedEpisodes() const
{
    return this->m_watchedEpisodes;
}

void TVShowModel::setWatchedEpisodes(int watchedEpisodes)
{
    this->m_watchedEpisodes = watchedEpisodes;
}

int TVShowModel::getPlaycount() const
{
    return this->m_playcount;
}

void TVShowModel::setPlaycount(int playcount)
{
    this->m_playcount = playcount;
}

int TVShowModel::getEpisode() const
{
    return this->m_episode;
}

void TVShowModel::setEpisode(int episode)
{
    this->m_episode = episode;
}

int TVShowModel::getSeason() const
{
    return this->m_season;
}

void TVShowModel::setSeason(int season)
{
    this->m_season = season;
}

int TVShowModel::getRating() const
{
    return this->m_rating;
}

void TVShowModel::setRating(int rating)
{
    this->m_rating = rating;
}

int TVShowModel::getYear() const
{
    return this->m_year;
}

void TVShowModel::setYear(int year)
{
    this->m_year = year;
}

int TVShowModel::getTVShowId() const
{
    return this->m_tvShowId;
}

void TVShowModel::setTvShowId(int tvShowId)
{
    this->m_tvShowId = tvShowId;
}
