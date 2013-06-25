#include "TestUnit.h"

// MODELS TESTS

void TestUnit::initTestModel()
{
    this->testModel = new Models::SubListedListModel(new TestModelItem(-1, NULL));
}

void TestUnit::appendOnTestModel()
{
    QList<Models::ListItem *> testItems;

    for(int i = 0; i < 10; i++)
    {
        testItems << new TestModelItem(i, NULL);
    }
    this->testModel->appendRow(testItems.takeFirst());
    QCOMPARE(this->testModel->rowCount(), 1);
    this->testModel->appendRows(testItems);
    QCOMPARE(this->testModel->rowCount(), testItems.size() + 1);

    TestModelItem *item = new TestModelItem(10);
    TestModelItem *item2 = new TestModelItem(11);
    this->testModel->insertRow(900, NULL);
    this->testModel->insertRow(900, item);
    QCOMPARE(this->testModel->rowIndexFromId(10), 10);
    this->testModel->insertRow(5, item2);
    QCOMPARE(this->testModel->rowIndexFromId(11), 5);
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
    QCOMPARE(this->testModel->rowCount(), oldCount);

    takenItems.append(this->testModel->takeRow(this->testModel->rowCount() - 1));
    QVERIFY(takenItems.first() == takenItems.last());
    oldCount = this->testModel->rowCount();
    takenItems = this->testModel->takeRows();
    QCOMPARE(takenItems.size(), oldCount);
    QVERIFY(this->testModel->takeRow(300) == NULL);
}

void TestUnit::triggerItemUpdateOnTestModel()
{
    Models::ListItem *item = new TestModelItem(-1, NULL);
    QVERIFY(item != NULL);
    QSignalSpy itemUpdateSigSpy(item, SIGNAL(dataChanged()));
    item->triggerItemUpdate();
    QCOMPARE(itemUpdateSigSpy.count(), 1);
}

void TestUnit::clearItemOnTestModel()
{
    this->testModel->clear();
    QCOMPARE(this->testModel->rowCount(), 0);
}

void TestUnit::testComparisonOnTestModel()
{
    QList<Models::ListItem *> testItems;
    QString charset = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    for(int i = 0; i < 30; i++)
    {
        TestModelItem *item = new TestModelItem(i, NULL);
        QString tmData = QString(charset[qrand() % (charset.size() - 1)]);
        tmData.append(charset[qrand() % (charset.size() - 1)]);
        tmData.append(charset[qrand() % (charset.size() - 1)]);
        tmData.append(charset[qrand() % (charset.size() - 1)]);
        item->setData(tmData);
        testItems.append(item);
    }
    this->testModel->appendRows(testItems);
    this->testModel->setSorting(true);
    QList<Models::ListItem *> resultList = this->testModel->toList();
    QCOMPARE(resultList.size(), 30);
    QString previous = "";
    foreach (Models::ListItem *item, resultList)
    {
        if (!previous.isEmpty())
        {
            qDebug() << reinterpret_cast<TestModelItem *>(item)->getData() << " " << previous << QString::compare(reinterpret_cast<TestModelItem *>(item)->getData(), previous);
            QVERIFY(QString::compare(reinterpret_cast<TestModelItem *>(item)->getData(), previous) >= 0);
        }
        previous = reinterpret_cast<TestModelItem *>(item)->getData();
    }
}

void TestUnit::findItemsInTestModel()
{
    QVERIFY(this->testModel->get(300) != this->testModel->get(10));
    QCOMPARE(this->testModel->rowIndexFromId(-10), -1);
    QVERIFY(this->testModel->indexFromItem(this->testModel->toList().last()) != this->testModel->indexFromItem(NULL));
    QVERIFY(this->testModel->indexFromItem(NULL) == QModelIndex());
}

void TestUnit::retrieveSubModelInTestModel()
{
    QVERIFY(this->testModel->subModelFromId(-5) == NULL);
    TestModelItem *item = reinterpret_cast<TestModelItem *>(this->testModel->find(10));
    QVERIFY(item != NULL);
    QVERIFY(item->submodel() != NULL);
    QVERIFY(item->submodel() == this->testModel->subModelFromId(item->id()));
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
    QCOMPARE(this->pluginManager->getLocallyAvailablePlugins()->rowCount(), Plugins::PluginLoader::getWidgetPlugins().size());
    int previousSize = this->pluginManager->getLocallyAvailablePlugins()->rowCount();
    this->pluginManager->loadLocalPlugins();
    qDebug() << "Loaded " << previousSize;
    QCOMPARE(this->pluginManager->getLocallyAvailablePlugins()->rowCount(), Plugins::PluginLoader::getWidgetPlugins().size());
    QCOMPARE(this->pluginManager->getLocallyAvailablePlugins()->rowCount(), previousSize);
}


void TestUnit::requestNewPluginInstance()
{
    QVERIFY(this->pluginManager->getNewInstanceOfPlugin(reinterpret_cast<Plugins::PluginBase*>(NULL)) == NULL);
    QVERIFY(this->pluginManager->getNewInstanceOfPlugin(Plugins::PluginLoader::getWidgetPlugins().first()) != NULL);
    QVERIFY(this->pluginManager->getNewInstanceOfPlugin(Plugins::PluginLoader::getWidgetPlugins().last()) != NULL);
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
    this->viewManager = View::QmlViewProperties::getInstance(this);
    QSignalSpy initializedSignalSpy(this->servicesManager, SIGNAL(librariesInitialized()));
    this->servicesManager->loadServicesLibraries();
    while (true)
    {
        if (initializedSignalSpy.count() > 0)
            break;
        qApp->processEvents();
    }
}

void TestUnit::testRoomLoadingDestroying()
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
        testRoom->addWidgetToRoom(widget->createNewInstance());
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

void TestUnit::testAdditionOfPluginsToRooms()
{
    this->roomManager->addNewRoom("RoomTest1");
    this->roomManager->addNewRoom("RoomTest2");
    this->roomManager->addNewRoom("RoomTest3");
    this->roomManager->addNewRoom("RoomTest4");
    QCOMPARE(this->roomManager->getRoomModel()->rowCount(), 4);

    // TEST THAT PLUGINS ARE PROPERLY ADDED TO THE ROOMS
    foreach (Models::ListItem *roomItem, this->roomManager->getRoomModel()->toList())
    {
        Room::RoomBase *room = reinterpret_cast<Models::RoomModelItem *>(roomItem)->getRoom();
        QVERIFY(room != NULL);
        this->roomManager->setCurrentRoom(room);
        QCOMPARE(this->roomManager->getCurrentRoom(), room);
        this->roomManager->setCurrentRoom(roomItem->id());
        QCOMPARE(this->roomManager->getCurrentRoom(), room);

        foreach (Models::ListItem *pluginItem, this->pluginManager->getLocallyAvailablePlugins()->toList())
            this->roomManager->addNewPluginToCurrentRoom(pluginItem->id());

        QCOMPARE(this->roomManager->getCurrentRoom()->getRoomPluginsModel()->rowCount(), this->pluginManager->getLocallyAvailablePlugins()->rowCount());
    }
}

void TestUnit::testPluginFocusStates()
{
    // CHECK THAT PLUGIN ARE PROPERLY LOADED IN THE ROOM AND CAN ASK FOR FOCUS STATES
    qRegisterMetaType<Plugins::PluginEnums::PluginState>("Plugins::PluginEnums::PluginState");
    foreach (Models::ListItem *pluginItem, this->roomManager->getCurrentRoom()->getRoomPluginsModel()->toList())
    {
        Plugins::PluginBase *plugin = reinterpret_cast<Models::PluginModelItem *>(pluginItem)->getPlugin();
        QVERIFY(plugin != NULL);
        qDebug() << "ID {" << plugin->getPluginId() << "}";
        qDebug() << "Name {" << plugin->getPluginName() << "}";
        qDebug() << "Description  {" << plugin->getPluginDescription() << "}";

        QSignalSpy spy(plugin, SIGNAL(askForFocusState(Plugins::PluginEnums::PluginState,QObject*)));
        plugin->askForFocusState(Plugins::PluginEnums::pluginIdleState);
        plugin->askForFocusState(Plugins::PluginEnums::pluginSelectedState);
        plugin->askForFocusState(Plugins::PluginEnums::pluginFocusedState);
        plugin->askForFocusState(Plugins::PluginEnums::pluginSelectedState);
        plugin->askForFocusState(Plugins::PluginEnums::pluginIdleState);
        QCOMPARE(spy.count(), 5);
    }

    Plugins::PluginBase *plugin1 = reinterpret_cast<Models::PluginModelItem *>(this->roomManager->getCurrentRoom()->getRoomPluginsModel()->toList().first())->getPlugin();
    Plugins::PluginBase *plugin2 = reinterpret_cast<Models::PluginModelItem *>(this->roomManager->getCurrentRoom()->getRoomPluginsModel()->toList().last())->getPlugin();

    QCOMPARE(plugin1->getFocusState(), Plugins::PluginEnums::pluginIdleState);
    QCOMPARE(plugin2->getFocusState(), Plugins::PluginEnums::pluginIdleState);

    // CHECK THAT IF A PLUGIN IS IN SELECTED AND ANOTHER ASKS IT, THE ASKER GETS THE SELECTED STATE
    plugin1->askForFocusState(Plugins::PluginEnums::pluginSelectedState);
    QCOMPARE(plugin1->getFocusState(), Plugins::PluginEnums::pluginSelectedState);

    plugin2->askForFocusState(Plugins::PluginEnums::pluginSelectedState);
    QCOMPARE(plugin2->getFocusState(), Plugins::PluginEnums::pluginSelectedState);
    QCOMPARE(plugin1->getFocusState(), Plugins::PluginEnums::pluginIdleState);

    // CHECK THAT IF A PLUGIN IS FOCUSED, NO OTHER PLUGIN CAN BECOME FOCUSED
    plugin2->askForFocusState(Plugins::PluginEnums::pluginFocusedState);
    QCOMPARE(plugin2->getFocusState(), Plugins::PluginEnums::pluginFocusedState);
    plugin1->askForFocusState(Plugins::PluginEnums::pluginFocusedState);
    QCOMPARE(plugin2->getFocusState(), Plugins::PluginEnums::pluginIdleState);
    QCOMPARE(plugin1->getFocusState(), Plugins::PluginEnums::pluginFocusedState);
}

void TestUnit::testRoomEnteringLeavingSignals()
{
    // THE CURRENT ROOM IS THE LAST, CHECK THAT IF THE ROOM CHANGES THE roomLeft SIGNAL IS TRIGGERED FOR THE ROOM AND ITS PLUGINS
    Room::RoomBase *lastRoom = this->roomManager->getCurrentRoom();
    QSignalSpy roomLeftSigSpy(lastRoom, SIGNAL(roomLeft()));
    this->roomManager->setCurrentRoom(this->roomManager->getRoomModel()->toList().first()->id());
    QCOMPARE(roomLeftSigSpy.count(), 1);
    QSignalSpy roomEnteredSpy(lastRoom, SIGNAL(roomEntered()));
    this->roomManager->setCurrentRoom(lastRoom);
    QCOMPARE(roomEnteredSpy.count(), 1);
}

void TestUnit::testPluginBehaviorOnRoomEnteringLeaving()
{
    Plugins::PluginBase *roomPlugin = reinterpret_cast<Models::PluginModelItem *>(this->roomManager->
                                                                                  getCurrentRoom()->
                                                                                  getRoomPluginsModel()->
                                                                                  toList().first())->getPlugin();
    QVERIFY(roomPlugin != NULL);
    QSignalSpy pluginEntered(roomPlugin, SIGNAL(roomEntered()));
    roomPlugin->onRoomEntered();
    QCOMPARE(pluginEntered.count(), 1);

    QSignalSpy pluginLeft(roomPlugin, SIGNAL(roomLeft()));
    roomPlugin->onRoomLeft();
    QCOMPARE(pluginLeft.count(), 1);
}

void TestUnit::launchViewTesting()
{
//    this->viewManager->showView();
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
