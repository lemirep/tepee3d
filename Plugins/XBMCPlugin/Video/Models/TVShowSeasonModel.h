#ifndef TVSHOWSEASONMODEL_H
#define TVSHOWSEASONMODEL_H

#include <SubListedListItem.h>
#include <ListModel.h>
#include "TVShowEpisodeModel.h"

class TVShowSeasonModel : public Models::SubListedListItem
{
    Q_OBJECT
public:
    enum TVShowSeasonModelItemRoles
    {
        season = Qt::UserRole + 1,
        watchedEpisodes, //UNUSED
        tvShowId,
        episode,
        thumbnail
    };

    explicit TVShowSeasonModel(QObject *parent = 0, int seasonId = -1);
    ~TVShowSeasonModel();

    int     id() const;
    QVariant data(int role) const;
    QHash<int, QByteArray> roleNames() const;
    Models::ListModel *submodel() const;

    int getWatchedEpisodes() const;
    int getTVShowId() const;
    int getEpisode() const;
    QString getThumbnail() const;

    void setWatchedEpisodes(int watchedEpisodes);
    void setTVShowId(int tvShowId);
    void setEpisode(int episode);
    void setThumbnail(const QString &thumbnail);



private:
    int     m_season;
    int     m_watchedEpisodes;
    int     m_tvShowId;
    int     m_episode;
    QString m_thumbnail;
    Models::ListModel* episodeModel;
};

#endif // TVSHOWSEASONMODEL_H
