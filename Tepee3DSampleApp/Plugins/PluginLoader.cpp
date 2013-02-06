#include "PluginLoader.h"
// DEBUG
#include <QDebug>

/*!
 * \class Plugins::PluginLoader
 * \brief The Plugins::PluginLoader class is an utility static class
 * aimed at easing the process of loading plugin libraries.
 */

void    Plugins::PluginLoader::loadWidgetPlugins()
{
    QDir    pluginsDir = QApplication::applicationDirPath();

    // GO TO THE PLUGINS DIRECTORY
#if defined(Q_OS_WIN)
    if (pluginsDir.dirName().toLower() == "debug" || pluginsDir.dirName().toLower() == "release")
        pluginsDir.cdUp();
#elif defined(Q_OS_MAC)
    if (pluginsDir.dirName() == "MacOS")
    {
        pluginsDir.cdUp();
        pluginsDir.cdUp();
        pluginsDir.cdUp();
    }
#endif
    pluginsDir.cdUp();
    pluginsDir.cd(WIDGET_PLUGIN_DIRECTORY);

    // LOOP THROUGH EACH FILE OF THE PLUGIN DIR AND LOAD THE PLUGINS
    foreach (QString fileName, pluginsDir.entryList(QDir::Files))
    {
        qDebug() << "NEW PLUGIN FOUND " << fileName << " ABSOLUTE PATH " << pluginsDir.absoluteFilePath(fileName);
        QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
        Plugins::PluginInterface *plugin = qobject_cast<PluginInterface *>(pluginLoader.instance());
        if (plugin)
        {
            qDebug() << "WIDGET PLUGIN LOADED";
            widgetPlugins.append(plugin->getPluginBase());
        }
        else
        {
           // qDebug("WIDGET PLUGIN FAILED TO LxxxxxxxxxxxxxxOAD");
            qDebug() << "FAILED TO LOAD " << fileName;
            qDebug() << pluginLoader.errorString();
        }
    }
}

QList<Plugins::PluginBase*>  Plugins::PluginLoader::getWidgetPlugins()
{
    return widgetPlugins;
}

QList<Plugins::PluginBase *> Plugins::PluginLoader::widgetPlugins = QList<Plugins::PluginBase *>();
