#ifndef LISTMODEL_H
#define LISTMODEL_H

#include <QAbstractListModel>
#include <QVariant>
#include <QList>
#include <QHash>
#include <QByteArray>
#include "ListItem.h"

namespace Models
{

class ListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ rowCount NOTIFY countChanged)
public:
    explicit ListModel(ListItem *prototype, QObject *parent = 0);
    ~ListModel();

    // REIMPLEMENTED METHODS
    int         rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant    data(const QModelIndex &index, int role) const;
    QModelIndex indexFromItem(ListItem *item) const;


    void        appendRow(ListItem *item);
    void        appendRows(QList<ListItem *> &items);
    void        insertRow(int row, ListItem *item);
    QHash<int, QByteArray>        roleNames() const;


    bool        removeRow(int row, const QModelIndex &parent = QModelIndex());
    bool        removeRows(int row, int count, const QModelIndex &parent = QModelIndex());
    void        clear();

    int         getRowFromItem(ListItem *item) const;
    ListItem*   find(int itemId) const;
    QList<ListItem *>   toList() const;

    Q_INVOKABLE QVariant get(int index);
    Q_INVOKABLE int      rowIndexFromId(int id);

protected:
    ListItem *prototype;
    QList<ListItem *> items;

private slots :
    void        updateItem();

signals :
    void        countChanged(int);

};

}

#endif // LISTMODEL_H
