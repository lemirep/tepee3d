#ifndef QTEST_UNIT_H
#define QTEST_UNIT_H

#include <QtTest/QtTest>

class TestUnit : public QObject
{
    Q_OBJECT

private slots:
    void toUpper();
};

#endif // QTEST_H
