#ifndef TESTMODELITEM_H
#define TESTMODELITEM_H

#include <SubListedListItem.h>
#include <SubListedListModel.h>

class TestModelItem : public Models::SubListedListItem
{

public :
    enum TestModelEnums
    {
        itemId = Qt::UserRole + 1,
        itemData
    };

public:
    TestModelItem(int id, QObject *parent = 0);
    ~TestModelItem();

    // SubListedListItem interface
public:
    Models::ListModel *submodel() const;

    // ListItem interface
public:
    int id() const;
    QVariant data(int role) const;
    QHash<int, QByteArray> roleNames() const;
    bool operator <(const Models::ListItem &nextElem);
    QString getData() const;
    void    setData(const QString & data);

private :
    Models::SubListedListModel *m_subModel;
    int                         m_id;
    QString                     m_data;
};

#endif // TESTMODELITEM_H
