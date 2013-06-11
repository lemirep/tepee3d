#include "TVShowEpisodeModel.h"

TVShowEpisodeModel::TVShowEpisodeModel(QObject *parent, int episodeId) : PlayableItemModel(parent)
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
    case tvShowId:
        return this->getTVShowId();
    case season:
        return this->getSeason();
    default:
        return PlayableItemModel::data(role);
    }
}

QHash<int, QByteArray> TVShowEpisodeModel::roleNames() const
{
    QHash<int, QByteArray> roleNames = PlayableItemModel::roleNames();
    roleNames[episodeId] = "episodeId";
    roleNames[aired] = "aired";
    roleNames[summary] = "summary";
    roleNames[tvShowId] = "tvShowId";
    roleNames[season] = "season";
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


int TVShowEpisodeModel::getTVShowId() const
{
    return this->m_tvShowId;
}

void TVShowEpisodeModel::setTVShowId(int tvShowId)
{
    this->m_tvShowId = tvShowId;
}

int TVShowEpisodeModel::getSeason() const
{
    return this->m_season;
}

void TVShowEpisodeModel::setSeason(int season)
{
    this->m_season = season;
}
