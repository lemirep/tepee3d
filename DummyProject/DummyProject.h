#ifndef DUMMYPROJECT_H
#define DUMMYPROJECT_H

#include <QObject>
#include <PluginBase.h>

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
    QString                     getPluginName() const;
    QString                     getPluginVersion() const;
    QString                     getPluginRepoName() const;
    QString                     getPluginDescription() const;
    QString                     getRoomPluginQmlFile() const;
    QString                     getMenuPluginQmlFile() const;
    PluginBase*                 createNewInstance();

    // DatabaseServiceUserInterface
    void                        receiveResultFromSQLQuery(QList<QSqlRecord> result, int id, QPointer<QObject> data);
    // WebServiceUserInterface
    void                        receiveResultFromHttpRequest(QNetworkReply * reply,int id, QPointer<QObject> data);

 protected:
    void                onIdleFocusState();
    void                onSelectedFocusState();
    void                onFocusedFocusState();

};

#endif // DUMMYPROJECT_H
