#ifndef DUMMYPROJECT_H
#define DUMMYPROJECT_H

#include <QObject>
#include <QtGui>
#include "QtQml"
#include <QQuickView>
#include <QQuickItem>
#include "PluginBase.h"
#include "DatabaseServiceUserInterface.h"
#include "WebServiceUserInterface.h"

class DummyProject  : public Plugins::PluginBase
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.tepee3d.plugins.dummyproject")

 public:
    DummyProject();
    virtual ~DummyProject();
    int                         getPluginId() const;
    void                        initPlugin();
    void                        clearPluginBeforeRemoval();
    QString			getPluginName() const;
    QString                     getPluginDescription() const;
    QString                     getRoomPluginQmlFile() const;
    QString                     getMenuPluginQmlFile() const;
    QString			getPluginVersion() const;
    PluginBase*                 createNewInstance();

    // DatabaseServiceUserInterface
    void                        receiveResultFromSQLQuery(QList<QSqlRecord> result, int id, void *data);
    // WebServiceUserInterface
    void                        receiveResultFromHttpRequest(QNetworkReply * reply,int id, void *data);

 protected:
    void                onIdleFocusState();
    void                onSelectedFocusState();
    void                onFocusedFocusState();

};

#endif // DUMMYPROJECT_H
