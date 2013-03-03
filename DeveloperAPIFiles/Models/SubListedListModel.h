#ifndef SUBLISTEDLISTMODEL_H
#define SUBLISTEDLISTMODEL_H

#include "ListModel.h"
#include "SubListedListItem.h"


namespace Models
{

class SubListedListModel : public ListModel
{
    Q_OBJECT

public:
    explicit SubListedListModel(SubListedListItem *prototype, QObject *parent = 0);

    Q_INVOKABLE QObject*    subModelFromId(int id);
};

}

#endif // SUBLISTEDLISTMODEL_H
