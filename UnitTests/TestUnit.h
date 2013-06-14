#ifndef QTEST_UNIT_H
#define QTEST_UNIT_H


#ifndef TESTING
#define TESTING
#endif

#include <QtTest/QtTest>
#include <QList>
#include <ListModel.h>
#include <PluginModelItem.h>
#include <ServicesManager.h>
#include <RoomManager.h>
#include <PluginManager.h>
#include <QmlViewProperties.h>
#include <PlatformFactory.h>

class TestUnit : public QObject
{
    Q_OBJECT

private:
    Models::ListModel           *testModel;
    Services::ServicesManager   *servicesManager;
    Room::RoomManager           *roomManager;
    Plugins::PluginManager      *pluginManager;
    View::QmlViewProperties     *viewManager;

private slots:

    //    MODELS
    void    initTestModel();
    void    appendOnTestModel();
    void    removeOnTestModel();
    void    takeItemsOnTestModel();
    void    clearItemOnTestModel();
    void    releaseTestModel();

    //    SERVICES
    void    initServicesManager();
    void    loadServicesLibraries();
    void    connectObjectToServices();
    void    disconnectObjectFromServices();

    //    ROOM MANAGER
    void    initRoomManager();
    void    addNewRooms();
    void    removeRooms();
    void    editRoom();
    void    setCurrentRoom();

    //    PLUGIN MANAGER
    void    initPluginManager();
    void    requestNewPluginInstance();
    void    initNewPlugin();

    //    RELEASE METHODS
    void    releaseRoomManager();
    void    releasePluginManager();
    void    releaseServiceManager();

    //    FULL ENGINE TEST
    void    initCoreManager();
    void    initManagers();
    void    launchViewTesting();
    void    launchRoomViewTesting();
    void    launchPluginsViewTesting();
    void    releaseCoreManager();

};

#endif // QTEST_H
