#include "ListModel.h"
// DEBUG
#include <QDebug>

ListModel::ListModel(ListItem *prototype, QObject *parent) : QAbstractListModel(parent)
{
    this->prototype = prototype;
}

ListModel::~ListModel()
{
    delete this->prototype;
    this->clear();
}

int         ListModel::rowCount(const QModelIndex &) const
{
    return this->items.size();
}

QVariant    ListModel::data(const QModelIndex &index, int role) const
{
    if (index.row() >= 0 && index.row() < this->items.size())
        return this->items.at(index.row())->data(role);
    return QVariant();
}

QHash<int, QByteArray>  ListModel::roleNames() const
{
    return this->prototype->roleNames();
}

void        ListModel::appendRow(ListItem *item)
{
    this->appendRows(QList<ListItem *>() << item);
    emit (countChanged(this->rowCount()));
}

void        ListModel::appendRows(QList<ListItem *> &items)
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

void        ListModel::insertRow(int row, ListItem *item)
{
    this->beginInsertRows(QModelIndex(), row, row);
    QObject::connect(item, SIGNAL(dataChanged()), this, SLOT(updateItem()));
    this->items.insert(row, item);
    this->endInsertRows();
    emit (countChanged(this->rowCount()));
}

bool        ListModel::removeRow(int row, const QModelIndex &index)
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

bool        ListModel::removeRows(int row, int count, const QModelIndex &index)
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

void        ListModel::clear()
{    
    qDebug() << "Clearing model";
    this->removeRows(0, this->items.size());
    qDebug() << "ListMode size " << this->items.size();
    emit (countChanged(this->rowCount()));
}

QModelIndex ListModel::indexFromItem(ListItem *item) const
{
    if (item != NULL)
    {
        for (int i = 0; i < this->items.size(); i++)
            if (this->items.at(i) == item)
                return index(i);
    }
    return QModelIndex();
}

ListItem *  ListModel::find(int itemId) const
{
    foreach(ListItem *item, this->items)
        if (item->id() == itemId)
            return item;
    return NULL;
}

int         ListModel::getRowFromItem(ListItem *item) const
{
    if (item != NULL)
        for (int i = 0; i < this->items.size(); i++)
            if (this->items.at(i) == item)
                return i;
    return -1;
}

QList<ListItem *>   ListModel::toList() const
{
    return this->items;
}

void        ListModel::updateItem()
{
    qDebug() << "Row updated";
    ListItem *item = static_cast<ListItem *>(sender());
    QModelIndex index = this->indexFromItem(item);
    if (index.isValid())
        emit dataChanged(index, index);
}

QVariant    ListModel::get(int index)
{
    ListItem * item = this->items.at(index);
    QMap<QString, QVariant> itemData;
    QHashIterator<int, QByteArray> hashItr(item->roleNames());

    while(hashItr.hasNext())
    {
        hashItr.next();
        itemData.insert(hashItr.value(),QVariant(item->data(hashItr.key())));
    }
    return QVariant(itemData);
}

int         ListModel::rowIndexFromId(int id)
{
    ListItem* item = find(id);

    if (item)
        return indexFromItem(item).row();
    return -1;
}
