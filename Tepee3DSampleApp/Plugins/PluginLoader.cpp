#include "PluginLoader.h"
// DEBUG
#include <iostream>

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
        std::cout << "NEW PLUGIN FOUND " << fileName.toStdString() << " ABSOLUTE PATH " << pluginsDir.absoluteFilePath(fileName).toStdString() << std::endl;
        QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
        Plugins::PluginInterface *plugin = qobject_cast<PluginInterface *>(pluginLoader.instance());
        if (plugin)
        {
            std::cout << "WIDGET PLUGIN LOADED" << std::endl;
            widgetPlugins.append(plugin->getPluginBase());
            plugin->getPluginBase()->resultFromSQL();
        }
        else
        {
           // qDebug("WIDGET PLUGIN FAILED TO LxxxxxxxxxxxxxxOAD");
            std::cout << "FAILED TO LOADE " << fileName.toStdString() << std::endl;
            std::cout << pluginLoader.errorString().toStdString() << std::endl;
        }
    }
}

QList<Plugins::PluginBase*>  Plugins::PluginLoader::getWidgetPlugins()
{
    return widgetPlugins;
}

QList<Plugins::PluginBase *> Plugins::PluginLoader::widgetPlugins = QList<Plugins::PluginBase *>();
