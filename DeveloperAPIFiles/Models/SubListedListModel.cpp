#include "SubListedListModel.h"

/*!
 * \class SubListedListModel
 *
 * \brief The SubListedListModel class provides an easy way to create C++ n-depth models
 * and expose them for Qml. This is useful in cases where you need to retrieve a sub model from
 * a given element in a model.
 *
 * \sa ListModel
 */

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
