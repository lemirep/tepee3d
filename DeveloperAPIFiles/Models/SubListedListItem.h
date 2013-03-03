#ifndef SUBLISTEDLISTITEM_H
#define SUBLISTEDLISTITEM_H

#include "ListItem.h"

namespace Models
{

class ListModel;

class SubListedListItem : public ListItem
{
    Q_OBJECT
public :
    SubListedListItem(QObject *parent = 0) : ListItem(parent) {}
    virtual ~SubListedListItem() {}
    virtual ListModel*  submodel()  const = 0;
};
}

#endif // SUBLISTEDLISTITEM_H
