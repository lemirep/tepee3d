#ifndef TVSHOWEPISODEMODEL_H
#define TVSHOWEPISODEMODEL_H

#include <QUrl>
#include <PlayableItemModel.h>

class TVShowEpisodeModel : public PlayableItemModel
{
    Q_OBJECT
public:
    enum TVShowEpisodeModelItemRoles
    {
        episodeId = PlayableItemModel::thumbnail + 1,
        aired,
        summary,
        tvShowId,
        season,
        episodeNum
    };

    explicit TVShowEpisodeModel(QObject *parent = NULL, int episodeId = -1);
    ~TVShowEpisodeModel();

    int id() const;
    QVariant data(int role) const;
    QHash<int, QByteArray> roleNames() const;

    QString getAired() const;
    QString getSummary() const;
    int getSeason() const;
    int getTVShowId() const;
    int getEpisodeNum() const;

    void setAired(const QString &aired);
    void setSummary(const QString &summary);
    void setSeason(int season);
    void setTVShowId(int tvShowId);
    void setEpisodeNum(int episodeNum);


private:
    QString m_aired;
    QString m_summary;
    int m_tvShowId;
    int m_season;
    int m_episodeId;
    int m_episodeNum;
};

#endif // TVSHOWEPISODEMODEL_H
