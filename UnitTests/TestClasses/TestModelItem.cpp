#include "TestModelItem.h"

TestModelItem::TestModelItem(int id, QObject *parent) : Models::SubListedListItem(parent)
{
    this->m_id = id;
    this->m_subModel = new Models::SubListedListModel(NULL, NULL);
    this->m_data = "";
}

TestModelItem::~TestModelItem()
{
    delete this->m_subModel;
}

Models::ListModel *TestModelItem::submodel() const
{
    return this->m_subModel;
}

int TestModelItem::id() const
{
    return this->m_id;
}

QVariant TestModelItem::data(int role) const
{
    switch (role)
    {
    case itemId:
        return this->id();
    case itemData:
        return this->getData();
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> TestModelItem::roleNames() const
{
    QHash<int, QByteArray> roleNames;

    roleNames[itemId] = "itemId";
    roleNames[itemData] = "itemData";

    return roleNames;
}

bool TestModelItem::operator <(const Models::ListItem &nextElem)
{
    return (this->m_data.compare(nextElem.data(TestModelItem::itemData).toString()) < 0);
}

QString TestModelItem::getData() const
{
    return this->m_data;
}

void TestModelItem::setData(const QString &data)
{
    this->m_data = data;
    this->triggerItemUpdate();
}
