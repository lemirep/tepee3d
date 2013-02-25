#ifndef LISTITEM_H
#define LISTITEM_H

#include <QObject>
#include <QVariant>
#include <QHash>


class ListItem : public QObject
{
    Q_OBJECT
public :
    ListItem(QObject *parent = 0) : QObject(parent) {}
    virtual ~ListItem() {}
    virtual int id() const = 0;
    virtual QVariant data(int role) const = 0;
    virtual QHash<int, QByteArray> roleNames() const = 0;
    virtual void triggerItemUpdate() {emit dataChanged();}
signals:
    void dataChanged();
};

#endif // LISTITEM_H
