#include "ListModel.h"
// DEBUG
#include <QDebug>

/*!
 * \class ListModel
 * \code
 * #include <ListModel.h>
 * \endcode
 * \brief The ListModel class is a utility model class
 *
 * The ListModel class provides an easy way to create a C++ model
 * and later expose it to the Qml View.
 *
 * \sa SubListedListModel
 */


/*!
 * Instanciates a new ListModel and sets the list row prototype to \a prototype.
 * The \a parent parameter is optional.
 */
Models::ListModel::ListModel(Models::ListItem *prototype, QObject *parent) : QAbstractListModel(parent)
{
    this->prototype = prototype;
}

/*!
 * Destroys a ListModel instance.
 */
Models::ListModel::~ListModel()
{
    delete this->prototype;
    this->clear();
}

/*!
 * \property Models::ListModel::count
 *
 * This property holds the number of rows of the model.
 */

/*!
 * Returns number of rows in the model.
 * \a index is not used but needed to reimplement the method.
 */

int         Models::ListModel::rowCount(const QModelIndex &) const
{
    return this->items.size();
}

/*!
 * Returns a QVariant containing the data associed to \a role for row at \a index.
 */

QVariant    Models::ListModel::data(const QModelIndex &index, int role) const
{
    if (index.row() >= 0 && index.row() < this->items.size())
        return this->items.at(index.row())->data(role);
    return QVariant();
}

/*!
 * Returns a hash containing the roleNames of the Model.
 */

QHash<int, QByteArray>  Models::ListModel::roleNames() const
{
    return this->prototype->roleNames();
}

/*!
 * Appends a single row \a item to the Model.
 */

void        Models::ListModel::appendRow(ListItem *item)
{
    this->appendRows(QList<ListItem *>() << item);
    emit (countChanged(this->rowCount()));
}

/*!
 * Appends several rows \a items to the Model.
 */
void        Models::ListModel::appendRows(QList<ListItem *> &items)
{
    // NEEDED TO UPDATE VIEW
    this->beginInsertRows(QModelIndex(), this->rowCount(), this->rowCount() + items.size() - 1);
    foreach(ListItem *item, items)
    {
        QObject::connect(item, SIGNAL(dataChanged()), this, SLOT(updateItem()));
        this->items.append(item);
        qDebug() << "Row appended";
    }
    // NEEDED TO UPDATE VIEW
    this->endInsertRows();
    emit (countChanged(this->rowCount()));
}

/*!
 * Insert new row described by \a item at position defined by \a row.
 */
void       Models::ListModel::insertRow(int row, ListItem *item)
{
    this->beginInsertRows(QModelIndex(), row, row);
    QObject::connect(item, SIGNAL(dataChanged()), this, SLOT(updateItem()));
    this->items.insert(row, item);
    this->endInsertRows();
    emit (countChanged(this->rowCount()));
}

/*!
 * Removes a single row at position defined by \a row .
 * The \a index argument is optional.
 * Returns true if row was removed, false if row not found or \a row is invalid.
 */
bool        Models::ListModel::removeRow(int row, const QModelIndex &index)
{
    if (row >= 0 && row < this->items.size())
    {
        beginRemoveRows(index, row, row);
        delete this->items.takeAt(row);
        endRemoveRows();
        emit (countChanged(this->rowCount()));
        return true;
    }
    return false;
}

/*!
 * Removes several rows starting at position defined by \a row until either \a count
 * or the model's last row is reached. The \a index argument is optional.
 * Returns true if the rows were removed, false if \a row is invalid.
 */
bool        Models::ListModel::removeRows(int row, int count, const QModelIndex &index)
{
    if (row >= 0 && (row + count) <= this->items.size())
    {
        beginRemoveRows(index, row, row + count - 1);
        for (int i = 0; i < count; i++)
            delete this->items.takeAt(row);
        qDebug() << "REMOVED ROWS";
        endRemoveRows();
        emit (countChanged(this->rowCount()));
        return true;
    }
    return false;
}

/*!
 * Clears the whole model removing all rows.
 */
void        Models::ListModel::clear()
{    
    qDebug() << "Clearing model";
    this->removeRows(0, this->items.size());
    qDebug() << "ListMode size " << this->items.size();
    emit (countChanged(this->rowCount()));
}

/*!
 * Returns the index of the row in the model containing \a item.
 */
QModelIndex     Models::ListModel::indexFromItem(ListItem *item) const
{
    if (item != NULL)
    {
        for (int i = 0; i < this->items.size(); i++)
            if (this->items.at(i) == item)
                return index(i);
    }
    return QModelIndex();
}

/*!
 * Returns the item whose id matches \a itemId.
 */
Models::ListItem *  Models::ListModel::find(int itemId) const
{
    foreach(ListItem *item, this->items)
        if (item->id() == itemId)
            return item;
    return NULL;
}
/*!
 * Returns row index at which \a item can be found in the model.
 */
int         Models::ListModel::getRowFromItem(ListItem *item) const
{
    if (item != NULL)
        for (int i = 0; i < this->items.size(); i++)
            if (this->items.at(i) == item)
                return i;
    return -1;
}

/*!
 * Returns model as a QList.
 */
QList<Models::ListItem *>   Models::ListModel::toList() const
{
    return this->items;
}

/*!
 * Slot triggered when a row item needs to be updated to reflect data changes.
 */
void        Models::ListModel::updateItem()
{
    qDebug() << "Row updated";
    Models::ListItem *item = static_cast<Models::ListItem *>(sender());
    QModelIndex index = this->indexFromItem(item);
    if (index.isValid())
        emit dataChanged(index, index);
}

/*!
 * Returns a QVariant containg the data of the row item at \a index in the model.
 */
QVariant    Models::ListModel::get(int index)
{
    Models::ListItem * item = this->items.at(index);
    QMap<QString, QVariant> itemData;
    QHashIterator<int, QByteArray> hashItr(item->roleNames());

    while(hashItr.hasNext())
    {
        hashItr.next();
        itemData.insert(hashItr.value(),QVariant(item->data(hashItr.key())));
    }
    return QVariant(itemData);
}

/*!
 * Returns the index for item identified by \a id  in the model.
 */
int         Models::ListModel::rowIndexFromId(int id)
{
    Models::ListItem* item = find(id);

    if (item)
        return indexFromItem(item).row();
    return -1;
}
