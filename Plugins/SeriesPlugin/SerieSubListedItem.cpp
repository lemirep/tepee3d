#include "SerieSubListedItem.h"

int SerieSubListedItem::nextSerieId = 0;

SerieSubListedItem::SerieSubListedItem(QString imdbId, QString serieName, QString imageUrl, QObject *parent) : Models::SubListedListItem(parent)
{
    this->m_serieId = nextSerieId++;
    this->m_imdbId = imdbId;
    this->m_serieName = serieName;
    this->m_imageUrl = imageUrl;

    // INIT SEASON MODELS HERE
    this->seasonModel = new Models::SubListedListModel(new SeasonSubListedItem(-1, -1, ""));
}

SerieSubListedItem::~SerieSubListedItem()
{
    delete this->seasonModel;
}

int SerieSubListedItem::id() const
{
    return this->serieId;
}

QVariant SerieSubListedItem::data(int role) const
{
    switch (role)
    {
    case serieId:
        return this->m_serieId;
    case serieName:
        return this->m_serieName;
    case imdbId:
        return this->m_imdbId;
    case imageUrl:
        return this->m_imageUrl;
    default :
        return QVariant();
    }
}

QHash<int, QByteArray> SerieSubListedItem::roleNames() const
{
    QHash<int, QByteArray> hashRoles;

    hashRoles[serieId] = "serieId";
    hashRoles[imdbId] = "imdbId";
    hashRoles[serieName] = "serieName";
    hashRoles[imageUrl] = "imageUrl";

    return hashRoles;
}

Models::ListModel *SerieSubListedItem::submodel() const
{
    // RETURN SEASONS MODEL FOR SHOW
    return (Models::ListModel*)this->seasonModel;
}
