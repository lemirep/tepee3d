/****************************************************************************
**
** Copyright (C) Paul Lemire, Tepee3DTeam and/or its subsidiary(-ies).
** Contact: paul.lemire@epitech.eu
** Contact: tepee3d_2014@labeip.epitech.eu
**
** This file is part of the Tepee3D project
**
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
****************************************************************************/

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
