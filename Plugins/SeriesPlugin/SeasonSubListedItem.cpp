#include "SeasonSubListedItem.h"

SeasonSubListedItem::SeasonSubListedItem(int seasonId, int episodeCount, QString imageUrl, QObject *parent) : Models::SubListedListItem(parent)
{
    this->m_seasonId = seasonId;
    this->m_episodeCount = episodeCount;
    this->m_imageUrl = imageUrl;
    this->episodesModel = new Models::ListModel(new EpisodeListItem());
}

SeasonSubListedItem::~SeasonSubListedItem()
{
    delete this->episodesModel;
}

int SeasonSubListedItem::id() const
{
    return this->m_seasonId;
}

QVariant SeasonSubListedItem::data(int role) const
{
    switch (role)
    {
    case seasonId:
        return this->m_seasonId;
    case episodeCount:
        return this->m_episodeCount;
    case imageUrl:
        return this->m_imageUrl;
    default :
        return QVariant();
    }
}

QHash<int, QByteArray> SeasonSubListedItem::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[seasonId] = "seasonId";
    roles[episodeCount] = "episodeCount";
    roles[imageUrl] = "imageUrl";

    return roles;
}

Models::ListModel *SeasonSubListedItem::submodel() const
{
    return (Models::ListModel*)this->episodesModel;
}

