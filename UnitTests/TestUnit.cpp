#include "TestUnit.h"

void TestUnit::initTestModel()
{
    this->testModel = new Models::ListModel(new Models::PluginModelItem(NULL, NULL));
}

void TestUnit::appendOnTestModel()
{
    QList<Models::ListItem *> testItems;

    for(int i = 0; i < 10; i++)
    {
        testItems << new Models::PluginModelItem(NULL, NULL);
    }
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

void TestUnit::takeItemsOnTestModel()
{
    QList<Models::ListItem *> takenItems;
    int oldCount = this->testModel->rowCount();

    takenItems = this->testModel->takeRows(0, 1);
    QCOMPARE(this->testModel->rowCount(), oldCount - takenItems.size());
    QCOMPARE(takenItems.size(), 1);

    this->testModel->appendRows(takenItems);

    takenItems.append(this->testModel->takeRow(this->testModel->rowCount() - 1));
    QVERIFY(takenItems.first() == takenItems.last());


    oldCount = this->testModel->rowCount();

    takenItems = this->testModel->takeRows();
    QCOMPARE(takenItems.size(), oldCount);

}

void TestUnit::clearItemOnTestModel()
{
    QBENCHMARK_ONCE
    {
        this->testModel->clear();
        QCOMPARE(this->testModel->rowCount(), 0);
    }
}

void TestUnit::releaseTestModel()
{
    delete this->testModel;
}

// TEST SERVICES MANAGER

void TestUnit::initServicesManager()
{
    this->servicesManager = Services::ServicesManager::getInstance();
    QVERIFY(this->servicesManager != NULL);
}

void TestUnit::loadServicesLibraries()
{
    QSignalSpy initializedSignalSpy(this->servicesManager, SIGNAL(librariesInitialized()));
    QEventLoop waitingLoop;
    QObject::connect(this->servicesManager, SIGNAL(librariesInitialized()), &waitingLoop, SLOT(quit()));
    this->servicesManager->loadServicesLibraries();
    waitingLoop.exec();
    QObject::disconnect(this->servicesManager, SIGNAL(librariesInitialized()), &waitingLoop, SLOT(quit()));
    QCOMPARE(initializedSignalSpy.count(), 1);
}

void TestUnit::connectObjectToServices()
{
    QBENCHMARK_ONCE
    {
        QObject * test = new QObject();
        this->servicesManager->connectObjectToServices(test);
    }
}

void TestUnit::disconnectObjectFromServices()
{
    QBENCHMARK_ONCE
    {
        QObject * test = new QObject();
        this->servicesManager->disconnectObjectFromServices(test);
    }
}


// TEST ROOM MANAGER

void TestUnit::initRoomManager()
{
    this->roomManager = Room::RoomManager::getInstance();
    QVERIFY(this->roomManager != NULL);
}

void TestUnit::addNewRooms()
{
    QCOMPARE(this->roomManager->getRoomModel()->rowCount(), 0);
    this->roomManager->getRoomModel()->appendRow(new Models::RoomModelItem(this->roomManager->getNewRoomInstance()));
    this->roomManager->getRoomModel()->appendRow(new Models::RoomModelItem(this->roomManager->getNewRoomInstance()));
    this->roomManager->getRoomModel()->appendRow(new Models::RoomModelItem(this->roomManager->getNewRoomInstance()));
    QCOMPARE(this->roomManager->getRoomModel()->rowCount(), 3);
}

void TestUnit::removeRooms()
{
    int oldCount = this->roomManager->getRoomModel()->rowCount();
    this->roomManager->deleteRoom(1);
    QCOMPARE(this->roomManager->getRoomModel()->rowCount(), oldCount - 1);
}

void TestUnit::editRoom()
{
    this->roomManager->editRoom(88, "New Name", QVector3D(0, 0, 0), QVector3D(1, 1, 1));
    this->roomManager->editRoom(2, "New Name", QVector3D(0, 0, 0), QVector3D(1, 1, 1));
}

void TestUnit::setCurrentRoom()
{
    this->roomManager->setCurrentRoom(99);
    QVERIFY(this->roomManager->getCurrentRoom() == NULL);
    this->roomManager->setCurrentRoom(2);
    QVERIFY(this->roomManager->getCurrentRoom() != NULL);
}

// TEST PLUGIN LOADER

void TestUnit::initPluginManager()
{
    this->pluginManager = Plugins::PluginManager::getInstance();
    QVERIFY(this->pluginManager != NULL);
    QVERIFY(Plugins::PluginLoader::getWidgetPlugins().size() > 0);
    QVERIFY(this->pluginManager->getLocallyAvailablePlugins()->rowCount() > 0);
}


void TestUnit::requestNewPluginInstance()
{
    QVERIFY(this->pluginManager->getNewInstanceOfPlugin(reinterpret_cast<Plugins::PluginBase*>(NULL)) == NULL);
    QVERIFY(this->pluginManager->getNewInstanceOfPlugin(Plugins::PluginLoader::getWidgetPlugins().first()) != NULL);
}

void TestUnit::initNewPlugin()
{
    this->pluginManager->initRoomPlugin(NULL);
    Plugins::PluginBase *plugin = this->pluginManager->getNewInstanceOfPlugin(Plugins::PluginLoader::getWidgetPlugins().last());
    QVERIFY(plugin != NULL);
    this->pluginManager->initRoomPlugin(plugin);
}

// RELEASE METHODS

void TestUnit::releaseRoomManager()
{
    delete this->roomManager;
}

void TestUnit::releasePluginManager()
{
    delete this->pluginManager;
}

void TestUnit::releaseServiceManager()
{
    delete this->servicesManager;
}


// FULL ENGINE TEST

void TestUnit::initCoreManager()
{
    // INIT PLATFORM
    QVERIFY(PlatformFactory::getPlatformInitializer()->initPlatform() == true);
    this->servicesManager = Services::ServicesManager::getInstance(this);
    QVERIFY(this->servicesManager != NULL);
    this->pluginManager = Plugins::PluginManager::getInstance(this);
    QVERIFY(this->pluginManager != NULL);
    this->roomManager = Room::RoomManager::getInstance(this);
    QVERIFY(this->roomManager != NULL);
    QSignalSpy initializedSignalSpy(this->servicesManager, SIGNAL(librariesInitialized()));
//    this->servicesManager->loadServicesLibraries();
//    while (true)
//    {
//        if (initializedSignalSpy.count() > 0)
//            break;
//    }
}

void TestUnit::initDataModels()
{
    Room::RoomBase *testRoom = Room::RoomManager::getNewRoomInstance();
    QVERIFY(testRoom != NULL);
    Models::SubListedListModel *roomsModel = new Models::SubListedListModel(new Models::RoomModelItem(NULL));
    QVERIFY(roomsModel != NULL);
    roomsModel->appendRow(new Models::RoomModelItem(testRoom));

    foreach (Models::ListItem *pluginItem, this->pluginManager->getLocallyAvailablePlugins()->toList())
    {
        Plugins::PluginBase *widget = reinterpret_cast<Models::PluginModelItem *>(pluginItem)->getPlugin();
        QVERIFY(widget != NULL);
        testRoom->addWidgetToRoom(widget);
    }
    QCOMPARE(testRoom->getRoomPluginsModel()->rowCount(), this->pluginManager->getLocallyAvailablePlugins()->rowCount());
    testRoom->removeWidgetFromRoom(reinterpret_cast<Models::PluginModelItem *>(testRoom->getRoomPluginsModel()->takeRow()));
    QCOMPARE(testRoom->getRoomPluginsModel()->rowCount(), this->pluginManager->getLocallyAvailablePlugins()->rowCount() - 1);
    delete testRoom;
}

void TestUnit::initManagers()
{
    // CONNECT THE SERVICE MANAGER TO THE SERVICES
    Services::ServicesManager::connectObjectToServices(this->servicesManager);
    // CONNECT THE ROOM MANAGER TO THE SERVICE MANAGER
    Services::ServicesManager::connectObjectToServices(this->roomManager);
    // CONNECT THE PLUGIN MANAGER TO THE SERVICE MANAGER
    Services::ServicesManager::connectObjectToServices(this->pluginManager);

    // SET QML PROPERTIES THAT CAN BE ACCESSED DIRECTLY FROM QML
    View::QmlViewProperties::exposeContentToQml(this->roomManager);
    View::QmlViewProperties::exposeContentToQml(this->servicesManager);
    View::QmlViewProperties::exposeContentToQml(this->pluginManager);
}

void TestUnit::launchViewTesting()
{

}

void TestUnit::launchRoomViewTesting()
{

}

void TestUnit::launchPluginsViewTesting()
{

}

void TestUnit::releaseCoreManager()
{
    delete this->roomManager;
    delete this->pluginManager;
    delete this->servicesManager;
    //    delete this->viewManager;
}

// TEST ROOM DataBase Saving

// TEST ROOM DataBase Restoring

QTEST_MAIN(TestUnit)
