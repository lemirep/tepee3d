#ifndef SUBLISTEDLISTITEM_H
#define SUBLISTEDLISTITEM_H

#include "ListItem.h"


namespace Models
{
class ListModel;

class SubListedListItem : public Models::ListItem
{
    Q_OBJECT
public :
    SubListedListItem(QObject *parent = 0) : Models::ListItem(parent) {}
    virtual ~SubListedListItem() {}
    virtual Models::ListModel*  submodel()  const = 0;
};
}

#endif // SUBLISTEDLISTITEM_H
