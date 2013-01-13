#include "SubListedListModel.h"

SubListedListModel::SubListedListModel(SubListedListItem *prototype, QObject *parent) : ListModel(prototype, parent)
{
}

QObject*        SubListedListModel::subModelFromId(int id)
{
    SubListedListItem* item = (SubListedListItem *)this->find(id);
    if (item != NULL)
        return item->submodel();
    return NULL;
}
