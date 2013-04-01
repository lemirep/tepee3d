#include "SerieSubListedItem.h"
#include <QDebug>

int SerieSubListedItem::nextSerieId = 0;

SerieSubListedItem::SerieSubListedItem(QString slug, QString serieName, QString imageUrl, QObject *parent) : Models::SubListedListItem(parent)
{
    this->m_serieId = nextSerieId++;
    this->m_serieName = serieName;
    this->m_imageUrl = imageUrl;
    this->m_slug = slug;

    // INIT SEASON MODELS HERE
    this->seasonModel = new Models::SubListedListModel(new SeasonSubListedItem(-1, -1, ""));
}

SerieSubListedItem::~SerieSubListedItem()
{
    delete this->seasonModel;
}

int SerieSubListedItem::id() const
{
    return this->m_serieId;
}

QVariant SerieSubListedItem::data(int role) const
{
    switch (role)
    {
    case serieId:
        return this->id();
    case slug:
        return this->m_slug;
    case serieName:
        return this->m_serieName;
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
    hashRoles[serieName] = "serieName";
    hashRoles[imageUrl] = "imageUrl";
    hashRoles[slug] = "slug";

    return hashRoles;
}

Models::ListModel *SerieSubListedItem::submodel() const
{
    // RETURN SEASONS MODEL FOR SHOW
    qDebug() << "Season Model Size " << this->seasonModel->rowCount();

    return (Models::ListModel*)this->seasonModel;
}
