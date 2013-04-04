#ifndef PLUGINLOADER_H
#define PLUGINLOADER_H

#include <QList>
#include <QCoreApplication>
#include <QPluginLoader>
#include <QQmlExtensionPlugin>
#include <QDir>
#include "PluginInterface.h"
#include "PluginBase.h"

#define WIDGET_PLUGIN_DIRECTORY "libraries/widget_libraries"

namespace Plugins
{

class PluginLoader
{
private :
    PluginLoader(); // PRIVATE SO THAT IT CANNOT  BE CALLED
    static QList<PluginBase *>     widgetPlugins; //LIST CONTAINING ALL THE PLUGINS
public :
    static void                loadWidgetPlugins(); //TRIES TO LOAD EVERY PLUGIN IN DIR AND RETURN FALSE IF ERROR OCCURS
    static QList<PluginBase *> getWidgetPlugins(); // RETURN LIST CONTAINING ALL THE LOADED PLUGINS
};

}
#endif // PLUGINLOADER_H
