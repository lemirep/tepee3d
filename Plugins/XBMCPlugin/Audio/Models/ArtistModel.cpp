#include "ArtistModel.h"

ArtistModel::ArtistModel(QObject *parent, int artistId) : Models::SubListedListItem(parent)
{
    this->m_artistId = artistId;
    this->songModel = new Models::ListModel(NULL);
}

QString ArtistModel::getArtistName() const
{
    return this->m_artistName;
}

void ArtistModel::setArtistName(const QString &artistName)
{
    this->m_artistName = artistName;
}

ArtistModel::~ArtistModel()
{
    delete this->songModel;
}

int ArtistModel::id() const
{
    return this->m_artistId;
}

QHash<int, QByteArray> ArtistModel::roleNames() const
{
    QHash<int, QByteArray>  roleNames;

    roleNames[artistId] = "artistId";
    roleNames[artistName] = "artistName";
    roleNames[birthDate] = "birthDate";
    roleNames[thumbnail] = "thumbnail";
    roleNames[genre] = "genre";
    roleNames[mood] = "mood";
    return roleNames;
}

QVariant ArtistModel::data(int role) const
{
    switch (role)
    {
    case artistId:
        return this->id();
    case artistName:
        return this->getArtistName();
    case birthDate:
        return this->getBirthDate();
    case thumbnail:
        return this->getThumbnail();
    case genre:
        return this->getGenre();
    case mood:
        return this->getMood();
    default:
        return QVariant();
    }
}

Models::ListModel *ArtistModel::submodel() const
{
    return this->songModel;
}

QString ArtistModel::getMood() const
{
    return m_mood;
}

void ArtistModel::setMood(const QString &mood)
{
    m_mood = mood;
}

QString ArtistModel::getThumbnail() const
{
    return this->m_thumbnail;
}

void ArtistModel::setThumbnail(const QString &thumbnail)
{
    this->m_thumbnail = thumbnail;
}

QString ArtistModel::getGenre() const
{
    return this->m_genre;
}

void ArtistModel::setGenre(const QString &genre)
{
    this->m_genre = genre;
}

QString ArtistModel::getBirthDate() const
{
    return this->m_birthDate;
}

void ArtistModel::setBirthDate(const QString &birthDate)
{
    this->m_birthDate = birthDate;
}
