#include "AlbumModel.h"

AlbumModel::AlbumModel(QObject *parent, int albumId) : Models::SubListedListItem(parent)
{
    this->m_albumId = albumId;
    this->songModel = new Models::ListModel(NULL);
}

AlbumModel::~AlbumModel()
{
    delete this->songModel;
}

int AlbumModel::id() const
{
    return this->m_albumId;
}

QVariant AlbumModel::data(int role) const
{
    switch (role)
    {
    case albumYear :
        return this->getAlbumYear();
    case rating:
        return this->getRating();
    case artistId:
        return this->getArtistId();
    case albumTitle:
        return this->getAlbumTitle();
    case genre:
        return this->getGenre();
    case mood:
        return this->getMood();
    case thumbnail:
        return this->getThumbnail();
    case description:
        return this->getDescription();
    case albumId:
        return this->id();
    default :
        return QVariant();
    }
}

QHash<int, QByteArray> AlbumModel::roleNames() const
{
    QHash<int, QByteArray>  roleNames;

    roleNames[albumId] = "albumId";
    roleNames[albumYear] = "albumYear";
    roleNames[rating] = "rating";
    roleNames[artistId] = "artistId";
    roleNames[albumTitle] = "albumTitle";
    roleNames[genre] = "genre";
    roleNames[mood] = "mood";
    roleNames[thumbnail] = "thumbnail";
    roleNames[description] = "description";

    return roleNames;
}

Models::ListModel *AlbumModel::submodel() const
{
    return this->songModel;
}

int AlbumModel::getAlbumYear() const
{
    return this->m_albumYear;
}

void AlbumModel::setAlbumYear(int albumYear)
{
    this->m_albumYear = albumYear;
}

int AlbumModel::getRating() const
{
    return this->m_rating;
}

void AlbumModel::setRating(int rating)
{
    this->m_rating = rating;
}

int AlbumModel::getArtistId() const
{
    return this->m_artistId;
}

void AlbumModel::setArtistId(int artistId)
{
    this->m_artistId = artistId;
}

QString AlbumModel::getAlbumTitle() const
{
    return this->m_albumTitle;
}

void AlbumModel::setAlbumTitle(const QString &albumTitle)
{
    this->m_albumTitle = albumTitle;
}

QString AlbumModel::getGenre() const
{
    return this->m_genre;
}

void AlbumModel::setGenre(const QString &genre)
{
    this->m_genre = genre;
}

QString AlbumModel::getMood() const
{
    return this->m_mood;
}

void AlbumModel::setMood(const QString &mood)
{
    this->m_mood = mood;
}

QString AlbumModel::getThumbnail() const
{
    return this->m_thumbnail;
}

void AlbumModel::setThumbnail(const QString &thumbnail)
{
    this->m_thumbnail = thumbnail;
}

QString AlbumModel::getDescription() const
{
    return this->m_description;
}

void AlbumModel::setDescription(const QString &description)
{
    this->m_description = description;
}
