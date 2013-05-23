#ifndef ALBUMMODEL_H
#define ALBUMMODEL_H

#include <ListModel.h>
#include <SubListedListItem.h>
#include <QDebug>

class AlbumModel : public Models::SubListedListItem
{
    Q_OBJECT
public:

    enum    AlbumModelItemRoles
    {
        albumYear = Qt::UserRole + 1,
        rating,
        artistId,
        albumTitle,
        genre,
        mood,
        thumbnail,
        description,
        albumId
    };

    explicit AlbumModel(QObject *parent = 0, int albumId = -1);
    ~AlbumModel();

    int                 id() const;
    QVariant      data(int role) const;
    QHash<int, QByteArray>  roleNames() const;
    Models::ListModel*  submodel() const;

    QString getDescription() const;
    QString getThumbnail() const;
    QString getMood() const;
    QString getGenre() const;
    QString getAlbumTitle() const;
    int getArtistId() const;
    int getRating() const;
    int getAlbumYear() const;

    void setDescription(const QString &description);
    void setThumbnail(const QString &thumbnail);
    void setMood(const QString &mood);
    void setGenre(const QString &genre);
    void setAlbumTitle(const QString &albumTitle);
    void setArtistId(int artistId);
    void setRating(int rating);
    void setAlbumYear(int albumYear);

private :
    int          m_albumId;
    int          m_albumYear;
    int          m_rating;
    int          m_artistId;
    QString m_albumTitle;
    QString m_genre;
    QString m_mood;
    QString m_thumbnail;
    QString m_description;

    Models::ListModel *songModel;
};

#endif // ALBUMMODEL_H
