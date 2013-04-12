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
        imageUrl,
        episodeSeen,
        episodeSickbeardStatus
    };

    explicit EpisodeListItem(QObject *parent = 0);
    explicit EpisodeListItem(int episodeId, int episodeNumber, int episodeSeason,
                             const QString& episodeTitle, const QString& episodeSummary, const QString& imageUrl,
                             QDateTime episodeAiring, bool episodeSeen = false,
                             const QString& episodeSickbeardStatus = "", QObject *parent = 0);
    ~EpisodeListItem();
    int             id() const;
    QVariant        data(int role) const;
    QHash<int, QByteArray>  roleNames() const;

    void    setSickbeardStatus(const QString& status);
    void    setEpisodeSeen(bool value);

private :
    int m_episodeId;
    int m_episodeNumber;
    int m_episodeSeason;
    bool m_episodeSeen;

    QString m_episodeTitle;
    QString m_episodeSummary;
    QString m_imageUrl;
    QString m_episodeSickbeardStatus;

    QDateTime m_episodeAiring;
};

#endif // EPISODELISTITEM_H
