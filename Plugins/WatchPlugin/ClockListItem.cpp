#include "ClockListItem.h"

ClockListItem::ClockListItem(QObject *parent) : Models::ListItem(parent)
{
}


ClockListItem::ClockListItem(int clockId, double clockUtc, QString clockCity, QObject *parent) : Models::ListItem(parent)
{
    this->m_clockId = clockId;
    this->m_clockUtc = clockUtc;
    this->m_clockCity = clockCity;
}

ClockListItem::~ClockListItem()
{
}


int ClockListItem::id() const
{
    return this->m_clockId;
}

QVariant ClockListItem::data(int role) const
{
    switch (role)
    {
    case clockId:
        return this->m_clockId;
    case clockUtc:
        return this->m_clockUtc;
    case clockCity:
        return this->m_clockCity;
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> ClockListItem::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[clockId] = "clockId";
    roles[clockUtc] = "clockUtc";
    roles[clockCity] = "clockCity";

    return roles;
}

