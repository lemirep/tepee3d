#ifndef QMLVIEWMANAGER_H
#define QMLVIEWMANAGER_H

#include <Qt/qapplication.h>
#include <Qt/qdesktopwidget.h>
#include <Qt/qglcamera.h>
#include <QtQuick/QQuickView>
#include <QtQuick/QQuickItem>
#include <Qt3DQuick/QQuickViewport>
#include <Qt3DQuick/qquickviewport.h>
#include <Qt/qqmlcontext.h>
#include "QmlContentExposerInterface.h"
#include "PluginManager.h"
#include "RoomManager.h"
#include "ServicesManager.h"


class QmlViewManager : public QObject
{
    Q_OBJECT

private:
    QQuickView                  *viewer;
    QQmlEngine                  *qmlEngine;
    QQmlContext                 *qmlContext;
    QDesktopWidget              *desktopWidget;
    QQuickItem                  *rootQmlObject;
    QQuickItem                  *viewport;
    QQuickItem                  *root3dObject;


    // ROOM MANAGER
    Room::RoomManager           *roomManager;
    // SERVICESMANAGER
    Services::ServicesManager   *servicesManager;
    // PLUGIN MANAGER
    Plugins::PluginManager      *pluginsManager;

private :

    static  QmlViewManager      *instance;
    explicit QmlViewManager(QApplication *app);

public:
    static  QmlViewManager*     getInstance(QApplication *app);
    ~QmlViewManager();
    bool    initView();

    void    registerComponentsToQml();

signals:

};

#endif // QMLVIEWMANAGER_H
