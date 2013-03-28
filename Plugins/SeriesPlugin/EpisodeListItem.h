#ifndef EPISODELISTITEM_H
#define EPISODELISTITEM_H

#include <ListItem.h>
#include <QDateTime>

class EpisodeListItem : public Models::ListItem
{
public:
    enum    EpisodeListItemRoles
    {
        episodeId = Qt::UserRole + 1,
        episodeNumber,
        episodeSeason,
        episodeTitle,
        episodeSummary,
        episodeAiring,
        imageUrl
    };

    explicit EpisodeListItem(int episodeId, int episodeNumber, int episodeSeason,
                             QString episodeTitle, QString episodeSummary, QString imageUrl,
                             QDateTime episodeAiring, QObject *parent = 0);
    ~EpisodeListItem();
    int             id() const;
    QVariant        data(int role) const;
    QHash<int, QByteArray>  roleNames() const;

private :
    int m_episodeId;
    int m_episodeNumber;
    int m_episodeSeason;

    QString m_episodeTitle;
    QString m_episodeSummary;
    QString m_imageUrl;

    QDateTime m_episodeAiring;
};

#endif // EPISODELISTITEM_H
