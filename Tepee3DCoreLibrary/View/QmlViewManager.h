#ifndef QMLVIEWMANAGER_H
#define QMLVIEWMANAGER_H

#include <QCoreApplication>
#include <QtQuick/QQuickView>
#include <QtQuick/QQuickItem>
#include <QQmlContext>
#include "QmlViewProperties.h"
#include "QmlContentExposerInterface.h"
#include "PluginManager.h"
#include "RoomManager.h"
#include "ServicesManager.h"
#include "QmlAsTexture.h"
#include <CoreLibraryInterface.h>
#include "PlatformFactory.h"

// DYNAMIC QML COMPONENT WILL BE LOADED USING QML LOADERS INSTEAD OF C++ CREATION
namespace View
{
class QmlViewManager : public QObject, public CoreLibraryInterface
{
    Q_OBJECT
    Q_INTERFACES(CoreLibraryInterface)
    Q_PLUGIN_METADATA(IID "com.tepee3d.Core")

private:
    // QML VIEW PROPERTIES
    QmlViewProperties           *viewProperties;
    // ROOM MANAGER
    Room::RoomManager           *roomManager;
    // SERVICESMANAGER
    Services::ServicesManager   *servicesManager;
    // PLUGIN MANAGER
    Plugins::PluginManager      *pluginsManager;

private :
//    static   QmlViewManager      *instance;

public:
//    static  QmlViewManager*     getInstance();
    explicit QmlViewManager();
    ~QmlViewManager();
    void                        initCoreEngine();
    QObject*                    getObject();
public slots:
    bool                        initView();
    void                        cleanBeforeClosing();
signals:
    void                        quit();

};
}
#endif // QMLVIEWMANAGER_H
