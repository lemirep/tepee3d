#include "SongModel.h"

SongModel::SongModel(QObject *parent, int songId) : Models::ListItem(parent)
{
    this->m_songId = songId;
    this->m_artistId = -1;
    this->m_albumId = -1;
}

SongModel::~SongModel()
{
}

int SongModel::id() const
{
    return this->m_songId;
}

QVariant SongModel::data(int role) const
{
    switch (role)
    {
    case songId:
        return this->id();
    case albumId:
        return this->getAlbumId();
    case artistId:
        return this->getArtistId();
    case duration:
        return this->getDuration();
    case rating:
        return this->getRating();
    case track:
        return this->getTrack();
    case file:
        return this->getFile();
    case thumbnail:
        return this->getThumbnail();
    case genre:
        return this->getGenre();
    case title:
        return this->getTitle();
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> SongModel::roleNames() const
{
    QHash<int, QByteArray>  roleNames;

    roleNames[songId] = "songId";
    roleNames[albumId] = "albumId";
    roleNames[artistId] = "artistId";
    roleNames[duration] = "duration";
    roleNames[rating] = "rating";
    roleNames[track] = "track";
    roleNames[file] = "file";
    roleNames[thumbnail] = "thumbnail";
    roleNames[genre] = "genre";
    roleNames[title] = "title";

    return roleNames;
}

QString SongModel::getTitle() const
{
    return this->m_title;
}

void SongModel::setTitle(const QString &title)
{
    this->m_title = title;
}

QString SongModel::getGenre() const
{
    return this->m_genre;
}

void SongModel::setGenre(const QString &genre)
{
    this->m_genre = genre;
}

QString SongModel::getThumbnail() const
{
    return this->m_thumbnail;
}

void SongModel::setThumbnail(const QString &thumbnail)
{
    this->m_thumbnail = thumbnail;
}

QString SongModel::getFile() const
{
    return this->m_file;
}

void SongModel::setFile(const QString &file)
{
    this->m_file = file;
}

int SongModel::getTrack() const
{
    return this->m_track;
}

void SongModel::setTrack(int track)
{
    this->m_track = track;
}

int SongModel::getRating() const
{
    return this->m_rating;
}

void SongModel::setRating(int rating)
{
    this->m_rating = rating;
}

int SongModel::getDuration() const
{
    return this->m_duration;
}

void SongModel::setDuration(int duration)
{
    this->m_duration = duration;
}

int SongModel::getArtistId() const
{
    return this->m_artistId;
}

void SongModel::setArtistId(int artistId)
{
    this->m_artistId = artistId;
}

int SongModel::getAlbumId() const
{
    return this->m_albumId;
}

void SongModel::setAlbumId(int albumId)
{
    this->m_albumId = albumId;
}
