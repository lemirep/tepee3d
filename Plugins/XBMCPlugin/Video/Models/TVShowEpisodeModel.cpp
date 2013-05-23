#include "TVShowEpisodeModel.h"

TVShowEpisodeModel::TVShowEpisodeModel(QObject *parent, int episodeId) : Models::ListItem(parent)
{
    this->m_episodeId = episodeId;
}



TVShowEpisodeModel::~TVShowEpisodeModel()
{
}

int TVShowEpisodeModel::id() const
{
    return this->m_episodeId;
}

QVariant TVShowEpisodeModel::data(int role) const
{
    switch (role)
    {
    case episodeId:
        return this->id();
    case aired:
        return this->getAired();
    case summary:
        return this->getSummary();
    case title:
        return this->getTitle();
    case thumbnail:
        return this->getThumbnail();
    case tvShowId:
        return this->getTVShowId();
    case season:
        return this->getSeason();
    case rating:
        return this->getRating();
    case file:
        return this->getFile();
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> TVShowEpisodeModel::roleNames() const
{
    QHash<int, QByteArray> roleNames;
    roleNames[episodeId] = "episodeId";
    roleNames[aired] = "aired";
    roleNames[summary] = "summary";
    roleNames[title] = "title";
    roleNames[thumbnail] = "thumbnail";
    roleNames[tvShowId] = "tvShowId";
    roleNames[season] = "season";
    roleNames[rating] = "rating";
    roleNames[file] = "file";
    return roleNames;
}

QString TVShowEpisodeModel::getSummary() const
{
    return this->m_summary;
}

void TVShowEpisodeModel::setSummary(const QString &summary)
{
    this->m_summary = summary;
}

QString TVShowEpisodeModel::getAired() const
{
    return this->m_aired;
}

void TVShowEpisodeModel::setAired(const QString &aired)
{
    this->m_aired = aired;
}

QString TVShowEpisodeModel::getThumbnail() const
{
    return this->m_thumbnail;
}

void TVShowEpisodeModel::setThumbnail(const QString &thumbnail)
{
    this->m_thumbnail = thumbnail;
}

int TVShowEpisodeModel::getTVShowId() const
{
    return this->m_tvShowId;
}

void TVShowEpisodeModel::setTVShowId(int tvShowId)
{
    this->m_tvShowId = tvShowId;
}

int TVShowEpisodeModel::getRating() const
{
    return this->m_rating;
}

void TVShowEpisodeModel::setRating(int rating)
{
    this->m_rating = rating;
}

int TVShowEpisodeModel::getSeason() const
{
    return this->m_season;
}

void TVShowEpisodeModel::setSeason(int season)
{
    this->m_season = season;
}

QString TVShowEpisodeModel::getTitle() const
{
    return this->m_title;
}

void TVShowEpisodeModel::setTitle(const QString &title)
{
    this->m_title = title;
}

QString TVShowEpisodeModel::getFile() const
{
    return this->m_file;
}

void TVShowEpisodeModel::setFile(const QString &file)
{
    this->m_file = file;
}
