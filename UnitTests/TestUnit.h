#ifndef QTEST_UNIT_H
#define QTEST_UNIT_H

#include <QtTest/QtTest>
#include <QList>
#include <ListModel.h>
#include <PluginModelItem.h>

class TestUnit : public QObject
{
    Q_OBJECT

private:
    Models::ListModel   *testModel;

private slots:

//    MODELS
    void    initTestModel();
    void    appendOnTestModel();
    void    removeOnTestModel();
    void    clearItemOnTestModel();
    void    releaseTestModel();



};

#endif // QTEST_H
