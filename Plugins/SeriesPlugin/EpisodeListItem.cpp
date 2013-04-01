#include "EpisodeListItem.h"

EpisodeListItem::EpisodeListItem(QObject *parent) : Models::ListItem(parent)
{
}

EpisodeListItem::EpisodeListItem(int episodeId, int episodeNumber, int episodeSeason,
                                 QString episodeTitle, QString episodeSummary, QString imageUrl,
                                 QDateTime episodeAiring, bool episodeSeen, QObject *parent) : Models::ListItem(parent)
{
    this->m_episodeId = episodeId;
    this->m_episodeNumber = episodeNumber;
    this->m_episodeSeason = episodeSeason;
    this->m_episodeTitle = episodeTitle;
    this->m_episodeSummary = episodeSummary;
    this->m_imageUrl = imageUrl;
    this->m_episodeAiring = episodeAiring;
    this->m_episodeSeen = episodeSeen;
}

EpisodeListItem::~EpisodeListItem()
{
}

int EpisodeListItem::id() const
{
    return this->m_episodeId;
}

QVariant EpisodeListItem::data(int role) const
{
    switch (role)
    {
    case episodeId:
        return this->m_episodeId;
    case episodeNumber:
        return this->m_episodeNumber;
    case episodeSeason:
        return this->m_episodeSeason;
    case episodeTitle:
        return this->m_episodeTitle;
    case episodeSummary:
        return this->m_episodeSummary;
    case episodeAiring:
        return this->m_episodeAiring;
    case imageUrl:
        return this->m_imageUrl;
    case episodeSeen:
        return this->m_episodeSeen;
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> EpisodeListItem::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[episodeId] = "episodeId";
    roles[episodeNumber] = "episodeNumber";
    roles[episodeSeason] = "episodeSeason";
    roles[episodeTitle] = "episodeTitle";
    roles[episodeSummary] = "episodeSummary";
    roles[episodeAiring] = "episodeAiring";
    roles[imageUrl] = "imageUrl";
    roles[episodeSeen] = "episodeSeen";

    return roles;
}
