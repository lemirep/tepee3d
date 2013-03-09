#include "TestUnit.h"

void TestUnit::initTestModel()
{
    this->testModel = new Models::ListModel(new Models::PluginModelItem(NULL, NULL));
}

void TestUnit::appendOnTestModel()
{
    QList<Models::ListItem *> testItems;

    for(int i = 0; i < 10; i++)
        testItems << new Models::PluginModelItem(NULL, NULL);
    this->testModel->appendRow(testItems.takeFirst());
    QCOMPARE(this->testModel->rowCount(), 1);
    this->testModel->appendRows(testItems);
    QCOMPARE(this->testModel->rowCount(), testItems.size() + 1);
}

void TestUnit::removeOnTestModel()
{
    int oldsize = this->testModel->rowCount();
    this->testModel->removeRow(2);
    QCOMPARE(this->testModel->rowCount(), oldsize - 1);
}

void TestUnit::clearItemOnTestModel()
{
    this->testModel->clear();
    QCOMPARE(this->testModel->rowCount(), 0);
}

void TestUnit::releaseTestModel()
{
    delete this->testModel;
}


QTEST_MAIN(TestUnit)
