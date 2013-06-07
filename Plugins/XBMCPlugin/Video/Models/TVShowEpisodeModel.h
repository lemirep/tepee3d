#ifndef TVSHOWEPISODEMODEL_H
#define TVSHOWEPISODEMODEL_H

#include <ListItem.h>
#include <QUrl>

class TVShowEpisodeModel : public Models::ListItem
{
    Q_OBJECT
public:
    enum TVShowEpisodeModelItemRoles
    {
        episodeId = Qt::UserRole + 1,
        aired,
        summary,
        title,
        thumbnail,
        tvShowId,
        season,
        rating,
        file
    };

    explicit TVShowEpisodeModel(QObject *parent = NULL, int episodeId = -1);
    ~TVShowEpisodeModel();

    int id() const;
    QVariant data(int role) const;
    QHash<int, QByteArray> roleNames() const;

    QString getAired() const;
    QString getSummary() const;
    QString getTitle() const;
    QString getThumbnail() const;
    QString getFile() const;
    int getSeason() const;
    int getRating() const;
    int getTVShowId() const;

    void setAired(const QString &aired);
    void setSummary(const QString &summary);
    void setTitle(const QString &title);
    void setSeason(int season);
    void setRating(int rating);
    void setTVShowId(int tvShowId);
    void setThumbnail(const QString &thumbnail);
    void setFile(const QString &file);

private:
    QString m_aired;
    QString m_summary;
    QString m_thumbnail;
    QString m_title;
    QString m_file;
    int m_tvShowId;
    int m_season;
    int m_rating;
    int m_episodeId;
};

#endif // TVSHOWEPISODEMODEL_H
