#include "PluginLoader.h"
// DEBUG
#include <QDebug>

/*!
 * \class Plugins::PluginLoader
 * \brief The Plugins::PluginLoader class is an utility static class
 * aimed at easing the process of loading plugin libraries. It loads all
 * the local plugin libraries in a list. That list can later be used to
 * instantiate new plugin instances.
 *
 * \since 1.0
 *
 * \inmodule Tepee3D
 */


/*!
 * This methods loads all the local libraries found in the Tepee3D plugin forlder.
 * Each library is checked to see whether it is a valid plugin or not, if it´s the
 * case an instance of the given plugin is saved in a list.
 */

Plugins::PluginLoader*   Plugins::PluginLoader::instance = NULL;
QList<Plugins::PluginBase *> Plugins::PluginLoader::widgetPlugins = QList<Plugins::PluginBase *>();

Plugins::PluginLoader::PluginLoader(QObject *parent) : QObject(parent)
{
}


Plugins::PluginLoader::~PluginLoader()
{
}


Plugins::PluginLoader*   Plugins::PluginLoader::getInstance(QObject *parent)
{
    if (Plugins::PluginLoader::instance == NULL)
        Plugins::PluginLoader::instance = new Plugins::PluginLoader(parent);
    return Plugins::PluginLoader::instance;
}

void    Plugins::PluginLoader::loadWidgetPlugins()
{
    QDir    pluginsDir = QCoreApplication::applicationDirPath();

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

/*!
 * Returns a QList containing PluginBases plugins that could be loaded locally.
 */
QList<Plugins::PluginBase*>  Plugins::PluginLoader::getWidgetPlugins()
{
    return widgetPlugins;
}

QString     Plugins::PluginLoader::loadAllPluginForRoom(Room::RoomBase *room)
{
    return QString("SELECT widgetImpl.idWidgetImpl, widgetImpl.idRoom, room.name, widgetImpl.idUser,"
                              "widgetImpl.idWidget, widgetImpl.posX, widgetImpl.posY, widgetImpl.posZ, "
                              "widgetImpl.scaleX, widgetImpl.scaleY, widgetImpl.scaleZ, widget.name, "
                              "widget.description, widget.localpath FROM widget, widgetImpl, room WHERE "
                              "widgetImpl.idwidget = widget.idWidget AND widgetImpl.idRoom = room.idRoom AND "
                              "room.name = '%1';") // TEMPORARY! Should be changed in the future
                            .arg(room->getRoomName());
}

QString     Plugins::PluginLoader::loadAllPluginForUser(int idUser)
{
    return QString("SELECT widgetImpl.idWidgetImpl, widgetImpl.idRoom, room.name, widgetImpl.idUser,"
                              "widgetImpl.idWidget, widgetImpl.posX, widgetImpl.posY, widgetImpl.posZ, "
                              "widgetImpl.scaleX, widgetImpl.scaleY, widgetImpl.scaleZ, widget.name, "
                              "widget.description, widget.localpath FROM widget, widgetImpl, room WHERE "
                              "widgetImpl.idwidget = widget.idWidget AND widgetImpl.idUser = %1;")
                              .arg(QString::number(idUser));
}

QString     Plugins::PluginLoader::addPluginImpl(PluginBase *plugin, Room::RoomBase *room, int idUser, const QVector3D &scale, const QVector3D &pos)
{
    return QString("INSERT INTO widgetImpl (idRoom, idWidget, idUser, posX, posY, posZ, scaleX, scaleY, scaleZ) VALUES"
            " (%1, %2, %3, %4, %5, %6, %7, %8, %9);")
            .arg(QString::number(1),// TEMPORARY! Should be changed in the future
                 QString::number(1),// TEMPORARY! Should be changed in the future
                 QString::number(idUser),
                 QString::number(pos.x()),
                 QString::number(pos.y()),
                 QString::number(pos.z()),
                 QString::number(scale.x()),
                 QString::number(scale.y()),
                 QString::number(scale.z()));
}

QString     Plugins::PluginLoader::addNewPlugin(PluginBase *plugin)
{
    return QString("INSERT INTO widget (name, description, localpath, minimalage) VALUES "
            "('%1', '%2', '%3', %4);")
            .arg(plugin->getPluginName(),
                 plugin->getPluginDescription(),
                 plugin->getRoomPluginQmlFile(),
                 QString::number(3)); // TEMPORARY! Should be changed in the future
}

