#ifndef PLUGIN_H
#define PLUGIN_H

#include <Qt/qobject.h>
#include <Qt/qplugin.h>
#include "PluginBase.h"

class TestPlugin : public Plugins::PluginBase
{
    Q_OBJECT                        // NECESSARY FOR QOBJECT INHERITANCE
    Q_PLUGIN_METADATA(IID "com.tepee3d.plugins.testplugin")

signals :
    void toto(QString);

public:
    TestPlugin();
    int                             getPluginId();
    void                            initPlugin();
    void                            registerTypes(const char *uri); // NECESSARY FOR QEXTENSION PLUGIN
    QString                         getPluginName();
    QString                         getPluginDescription();
    PluginBase*                     getPluginBase();
    PluginBase*                     createNewInstance();

public slots:
//    void                    resultFromSQL();

};

#endif // PLUGIN_H
