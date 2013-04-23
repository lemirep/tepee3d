#ifndef ClockListItem_H
#define ClockListItem_H

#include <ListItem.h>

class ClockListItem  : public Models::ListItem
{
public:
    enum    ClockListItemRoles
    {
        clockId = Qt::UserRole + 1,
        clockUtc,
        clockCity
    };

    explicit ClockListItem(QObject *parent = 0);
    explicit ClockListItem(int clockId, double clockUtc, QString clockCity, QObject *parent = 0);

    ~ClockListItem();

    int             id() const;
    QVariant        data(int role) const;
    QHash<int, QByteArray>  roleNames() const;
    QString getClockCity() const;
    double getClockUtc() const;
private:
    int m_clockId;
    double m_clockUtc;
    QString m_clockCity;
};

#endif // ClockListItem_H
