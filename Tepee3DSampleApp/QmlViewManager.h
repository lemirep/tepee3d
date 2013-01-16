#ifndef QMLVIEWMANAGER_H
#define QMLVIEWMANAGER_H

#include <QApplication>
#include <QDesktopWidget>
#include <QtQuick/QQuickView>
#include <QtQuick/QQuickItem>
#include <QQmlContext>
#include "QmlContentExposerInterface.h"
#include "PluginManager.h"
#include "RoomManager.h"
#include "ServicesManager.h"


// DYNAMIC QML COMPONENT WILL BE LOADED USING QML LOADERS INSTEAD OF C++ CREATION

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
    explicit QmlViewManager();
    static   QmlViewManager      *instance;

public:
    static  QmlViewManager*     getInstance();
    ~QmlViewManager();
    bool                        initView();
private slots :
    void                        exposeContentToQml(QObject* exposer);
signals:

};

#endif // QMLVIEWMANAGER_H
