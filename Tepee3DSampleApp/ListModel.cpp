#include "ListModel.h"

// DEBUG
#include <iostream>

ListModel::ListModel(ListItem *prototype, QObject *parent) : QAbstractListModel(parent)
{
    this->prototype = prototype;
    std::cout << "prototype set" << std::endl;
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
    std::cout << "Row appended" << std::endl;
    QObject::connect(item, SIGNAL(dataChanged()), this, SLOT(updateItem()));
    this->items.append(item);
}

void        ListModel::appendRows(QList<ListItem *> &items)
{
    foreach(ListItem *item, items)
        this->appendRow(item);
}

void        ListModel::insertRow(int row, ListItem *item)
{
    this->beginInsertRows(QModelIndex(), row, row);
    QObject::connect(item, SIGNAL(dataChanged()), this, SLOT(updateItem()));
    this->items.insert(row, item);
    this->endInsertRows();
}

bool        ListModel::removeRow(int row, const QModelIndex &)
{
    if (row >= 0 && row < this->items.size())
    {
        beginRemoveRows(QModelIndex(), row, row);
        delete this->items.takeAt(row);
        endRemoveRows();
        return true;
    }
    return false;
}

bool        ListModel::removeRows(int row, int count, const QModelIndex &)
{
    if (row >= 0 && (row + count) < this->items.size())
    {
        beginRemoveRows(QModelIndex(), row, row);
        for (int i = 0; i < count; i++)
            delete this->items.takeAt(row + i);
        endRemoveRows();
        return true;
    }
    return false;
}

void        ListModel::clear()
{
    qDeleteAll(this->items);
    this->items.clear();
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
    std::cout << "row updated" << std::endl;
    ListItem *item = static_cast<ListItem *>(sender());
    QModelIndex index = this->indexFromItem(item);
    if (index.isValid())
        emit dataChanged(index, index);
}
