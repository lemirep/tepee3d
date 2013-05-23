#ifndef ARTISTMODEL_H
#define ARTISTMODEL_H

#include <SubListedListItem.h>
#include <ListModel.h>
#include <QDebug>

class ArtistModel : public Models::SubListedListItem
{
    Q_OBJECT
public:

    enum    ArtistModelItemRoles
    {
        artistId = Qt::UserRole + 1,
        artistName,
        birthDate,
        genre,
        thumbnail,
        mood
    };

    ArtistModel(QObject *parent = 0, int artistId = -1);
    ~ArtistModel();

    int     id() const;
    QHash<int, QByteArray>    roleNames() const;
    QVariant        data(int role) const;
    Models::ListModel*  submodel() const;

    QString getArtistName() const;
    void setArtistName(const QString &artistName);

    QString getBirthDate() const;
    void setBirthDate(const QString &birthDate);

    QString getGenre() const;
    void setGenre(const QString &genre);

    QString getThumbnail() const;
    void setThumbnail(const QString &thumbnail);

    QString getMood() const;
    void setMood(const QString &mood);

private:
    int     m_artistId;
    QString m_artistName;
    QString m_birthDate;
    QString m_genre;
    QString m_thumbnail;
    QString m_mood;

    Models::ListModel   *songModel;
};

#endif // ARTISTMODEL_H
