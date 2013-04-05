#include "SubListedListModel.h"

/*!
 * \class Models::SubListedListModel
 * \code
 * #include <SubListedListModel.h>
 * \endcode
 * \brief The Models::SubListedListModel class provides an easy way to create C++ n-depth models
 * and expose them for Qml. This is useful in cases where you need to retrieve a sub model from
 * a given element in a model.
 *
 * \inmodule Tepee3D
 *
 * \sa Models::ListModel
 */

/*!
 * \class Models::SubListedListItem
 * \code
 * #include <SubListedListItem.h>
 * \endcode
 *
 * \brief The basic element Models::SubListedListModel are composed of.
 *
 * The basic element Models::SubListedListModel are composed of. It gives a representation
 * of the data it contains throught the use of data retrieved by matching role names.
 * Your model items should inherit from this class and implement the various methods to reflect
 * what your item contains.
 *
 * The difference with the Models::ListItem element is that a Models::SubListedListModel can contain a
 * submodel. This is particularly interesting when you want to have a model containing another model for
 * each of its row.
 *
 * \sa Models::ListModel
 * \sa Models::SubListedListModel
 * \sa Models::ListItem
 *
 * \inmodule Tepee3D
 */

/*!
 * \fn  Models::SubListedListItem::SubListedListItem(QObject *parent)
 *
 * Constructs a new Models::SubListedListItem instance given the optionnal \a parent paremeter.
 */

/*!
 * \fn Models::SubListedListItem::~SubListedListItem()
 *
 * Destroys a Models::SubListedListItem instance.
 */

/*!
 * \fn Models::ListModel* Models::SubListedListItem::submodel() const
 *
 * Returns a Modles::ListModel* instance.
 */



/*!
 * Construcst a new Models::SubListedListModel instance with the provided \a prototype item template.
 */

Models::SubListedListModel::SubListedListModel(Models::SubListedListItem *prototype, QObject *parent) : Models::ListModel(prototype, parent)
{
}

/*!
 * Returns the model contained by row Item identified by \a id.
 */
QObject*        Models::SubListedListModel::subModelFromId(int id)
{
    Models::SubListedListItem* item = (Models::SubListedListItem *)this->find(id);
    if (item != NULL)
        return item->submodel();
    return NULL;
}
