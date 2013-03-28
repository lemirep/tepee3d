#ifndef SEASONSUBLISTEDITEM_H
#define SEASONSUBLISTEDITEM_H

#include <SubListedListItem.h>
#include "EpisodeListItem.h"

class SeasonSubListedItem : public Models::SubListedListItem
{
    Q_OBJECT
public:
    enum    SeasonSubListedItemRoles
    {
        seasonId = Qt::UserRole + 1,
        episodeCount,
        imageUrl
    };

    explicit SeasonSubListedItem(int seasonId, int episodeCount, QString imageUrl, QObject *parent = 0);
    ~SeasonSubListedItem();

    int         id() const;
    QVariant    data(int role)  const;
    QHash<int, QByteArray> roleNames() const;

    Models::ListModel* submodel()   const;

private:
    int m_seasonId;
    int m_episodeCount;
    QString m_imageUrl;

    Models::ListModel*  episodesModel;
};

#endif // SEASONSUBLISTEDITEM_H
