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


// DYNAMIC QML COMPONENT WILL BE LOADED USING QML LOADERS INSTEAD OF C++ CREATION
namespace View
{
class QmlViewManager : public QObject
{
    Q_OBJECT

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
    explicit QmlViewManager();
    static   QmlViewManager      *instance;

public:
    static  QmlViewManager*     getInstance();
    ~QmlViewManager();
public slots:
    bool                        initView();

signals:
    void                        quit();

};
}
#endif // QMLVIEWMANAGER_H
