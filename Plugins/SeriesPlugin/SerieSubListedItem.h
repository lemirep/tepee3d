#ifndef SERIESUBLISTEDITEM_H
#define SERIESUBLISTEDITEM_H

#include <SubListedListModel.h>
#include <SubListedListItem.h>
#include "SeasonSubListedItem.h"

class SerieSubListedItem : public Models::SubListedListItem
{
    Q_OBJECT
public:

    enum    SeriesModelItemRoles
    {
        serieId = Qt::UserRole + 1,
        slug,
        imdbId,
        serieName,
        imageUrl
    };

    explicit SerieSubListedItem(QString slug, QString imdbId, QString serieName, QString imageUrl, QObject *parent = 0);
    ~SerieSubListedItem();

    int             id() const;
    QVariant        data(int role) const;
    QHash<int, QByteArray>  roleNames() const;

    Models::ListModel*  submodel()   const;

private :
    int m_serieId;
    QString m_serieName;
    QString m_imdbId;
    QString m_imageUrl;
    QString m_slug;

    Models::SubListedListModel*  seasonModel;
    static int nextSerieId;

};

#endif // SERIESUBLISTEDITEM_H
