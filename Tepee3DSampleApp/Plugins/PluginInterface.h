#ifndef PLUGININTERFACE_H
#define PLUGININTERFACE_H
#include <Qt/qobject.h>
#include <Qt/qstring.h>
#include <Qt/qqmlextensionplugin.h>
#include <Qt/qqmlengine.h>


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
