#ifndef PLUGININTERFACE_H
#define PLUGININTERFACE_H
#include <QObject>
#include <QString>
#include <QQmlExtensionPlugin>
#include <QQmlEngine>


namespace Plugins
{

class PluginBase;

class PluginInterface
{
public :
    virtual PluginBase*             getPluginBase()             = 0;
};

}
// REGISTER THE CLASS AS A QT INTERFACE
Q_DECLARE_INTERFACE(Plugins::PluginInterface, "com.tepee3d.Plugin.PluginInterface/1.0")

#endif // PLUGININTERFACE_H
