#ifndef SONGMODEL_H
#define SONGMODEL_H

#include <ListModel.h>
#include <ListItem.h>
#include <QDebug>

class SongModel : public Models::ListItem
{
    Q_OBJECT
public:

    enum    SongModelItemRoles
    {
        songId = Qt::UserRole + 1,
        albumId,
        artistId,
        duration,
        rating,
        track,
        file,
        thumbnail,
        genre,
        title
    };

    SongModel(QObject *parent = 0, int songId = -1);
    ~SongModel();

    int             id() const;
    QVariant  data(int role) const;
    QHash<int, QByteArray>  roleNames() const;

    void setAlbumId(int albumId);
    void setArtistId(int artistId);
    void setDuration(int duration);
    void setRating(int rating);
    void setTrack(int track);
    void setFile(const QString &file);
    void setThumbnail(const QString &thumbnail);
    void setGenre(const QString &genre);
    void setTitle(const QString &title);

    int getAlbumId() const;
    int getArtistId() const;
    int getDuration() const;
    int getRating() const;
    int getTrack() const;
    QString getFile() const;
    QString getThumbnail() const;
    QString getGenre() const;
    QString getTitle() const;


private:
    int             m_songId;
    int             m_albumId;
    int             m_artistId;
    int             m_duration;
    int             m_rating;
    int             m_track;
    QString    m_file;
    QString    m_thumbnail;
    QString    m_genre;
    QString    m_title;
};

#endif // SONGMODEL_H
