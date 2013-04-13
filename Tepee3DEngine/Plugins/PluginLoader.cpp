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

Plugins::PluginLoader::PluginLoader(QObject *parent) : QObject(parent)
{
    // CONNECT TO DATABASE SERVICE
    Services::ServicesManager::connectObjectToServices(this);
    qDebug() << "Connection PluginLoader to services";

    // DATABASE CALLBACKS
    this->pFunc[PLUGIN_LOADED] = &Plugins::PluginLoader::loadPluginsCallback;
    this->pFunc[GENERIC_RESULT] = &Plugins::PluginLoader::genericResultCallback;

}


Plugins::PluginLoader::~PluginLoader()
{
    Services::ServicesManager::disconnectObjectFromServices(this);
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

QList<Plugins::PluginBase *> Plugins::PluginLoader::widgetPlugins = QList<Plugins::PluginBase *>();

void    Plugins::PluginLoader::receiveResultFromSQLQuery(QList<QSqlRecord> result, int id, void *data)
{
    (this->*this->pFunc[id])(result);
}

void    Plugins::PluginLoader::genericResultCallback(QList<QSqlRecord> result)
{
    Q_UNUSED(result);
}

void    Plugins::PluginLoader::loadPluginsCallback(QList<QSqlRecord> result)
{
    qDebug() << "restoreRoomsCallback";
    if (result.size() > 1) // FIRST RECORD IS STATUS COUNT OF RECORDINGS
    {
        result.pop_front();
        foreach (QSqlRecord rsecord, result)
        {
            // Create a new plugin and insert in room manager.
        }
    }
}

void                   Plugins::PluginLoader::loadAllPluginForRoom(Room::RoomBase &room)
{
    QString request;

    request = "SELECT widgetImpl.idWidgetImpl, widgetImpl.idRoom, room.name, widgetImpl.idUser, widgetImpl.idWidget, widgetImpl.posX, widgetImpl.posY, widgetImpl.posZ, widgetImpl.scaleX, widgetImpl.scaleY, widgetImpl.scaleZ, widget.name, widget.description, widget.localpath FROM widget, widgetImpl, room WHERE ";
    request += "widgetImpl.idwidget = widget.idWidget";
    request += " AND ";
    request += "widgetImpl.idRoom = room.idRoom AND room.name = \"" + room.getRoomName() + "\""; // TEMPORARY! Should be changed in the future
    request += ";";

    emit executeSQLQuery(request, this, 1, DB_NAME, NULL);
}

void                   Plugins::PluginLoader::loadAllPluginForUser(int &idUser)
{
    QString request;

    request = "SELECT widgetImpl.idWidgetImpl, widgetImpl.idRoom, room.name, widgetImpl.idUser, widgetImpl.idWidget, widgetImpl.posX, widgetImpl.posY, widgetImpl.posZ, widgetImpl.scaleX, widgetImpl.scaleY, widgetImpl.scaleZ, widget.name, widget.description, widget.localpath FROM widget, widgetImpl, room WHERE ";
    request += "widgetImpl.idwidget = widget.idWidget";
    request += " AND ";
    request += " widgetImpl.idUser = " + QString::number(idUser);
    request += ";";

    emit  executeSQLQuery(request, this, 1, DB_NAME, NULL);
}

void                   Plugins::PluginLoader::addPluginImpl(PluginBase &plugin, Room::RoomBase &room, int &idUser, QVector3D &scale, QVector3D &pos)
{
    QString request;

    request = "INSERT INTO widgetImpl (idRoom, idWidget, idUser, posX, posY, posZ, scaleX, scaleY, scaleZ) VALUES (";
    request +=  1 + ", "; // TEMPORARY! Should be changed in the future
    request +=  1 + ", "; // TEMPORARY! Should be changed in the future
    request +=  idUser + ", ";
    request +=  QString::number(pos.x()) + ", ";
    request +=  QString::number(pos.y()) + ", ";
    request +=  QString::number(pos.z()) + ", ";
    request +=  QString::number(scale.x()) + ", ";
    request +=  QString::number(scale.y()) + ", ";
    request +=  QString::number(scale.z()) + ")";
    request += ";";

    emit executeSQLQuery(request, this, 1, DB_NAME, NULL);
}

void                   Plugins::PluginLoader::addNewPlugin(PluginBase &plugin)
{
    QString request;

    request = "INSERT INTO widget (name, description, localpath, minimalage) VALUES (\"";
    request += plugin.getPluginName() + "\", ";
    request += plugin.getPluginDescription() + "\", \"";
    request += plugin.getRoomPluginQmlFile() + "\", \"";
    request += 3 + "\")"; // TEMPORARY! Should be changed in the future
    request += ";";

    emit  executeSQLQuery(request, this, 1, DB_NAME, NULL);
}

