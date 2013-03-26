#include "RoomLoader.h"

/*!
 * \class Room::RoomLoader
 * \brief The RoomLoader class is a group a static functions aimed
 * to load or save room in databases and files format.
 *
 * \inmodule Tepee3D
 */

Room::RoomLoader*   Room::RoomLoader::instance = NULL;

Room::RoomLoader::RoomLoader(QObject *parent) : QObject(parent)
{
    this->pFunc[SEARCH_FOR_ROOM] = &Room::RoomLoader::searchForRoomEditUpdateCallback;
    this->pFunc[GENERIC_RESULT] = &Room::RoomLoader::genericResultCallback;
    this->pFunc[RESTORE_ROOMS] = &Room::RoomLoader::restoreRoomsCallback;
    // CONNECT TO DATABASE SERVICE
    qDebug() << "Connection RoomLoader to services";
    Services::ServicesManager::connectObjectToServices(this);
}

Room::RoomLoader::~RoomLoader()
{
    Services::ServicesManager::disconnectObjectFromServices(this);
}

Room::RoomLoader*   Room::RoomLoader::getInstance(QObject *parent)
{
    if (Room::RoomLoader::instance == NULL)
        Room::RoomLoader::instance = new Room::RoomLoader(parent);
    return Room::RoomLoader::instance;
}

void Room::RoomLoader::addParamToRoom(Room::RoomBase *room, QString attr, QString value)
{
    QVector3D vec;

    if (attr == "Name")
        room->setRoomName(value);
    if (attr == "Qml")
        room->setRoomQmlFile(value);
    if (attr == "PosX")
    {
        vec = room->getPosition();
        vec.setX(value.toDouble());
        room->setPosition(vec);
    }
    if (attr == "PosY")
    {
        vec = room->getPosition();
        vec.setY(value.toDouble());
        room->setPosition(vec);
    }
    if (attr == "PosZ")
    {
        vec = room->getPosition();
        vec.setZ(value.toDouble());
        room->setPosition(vec);
    }
    if (attr == "ScaleX")
    {
        vec = room->getScale();
        vec.setX(value.toDouble());
        room->setScale(vec);
    }
    if (attr == "ScaleY")
    {
        vec = room->getScale();
        vec.setY(value.toDouble());
        room->setScale(vec);
    }
    if (attr == "ScaleZ")
    {
        vec = room->getScale();
        vec.setZ(value.toDouble());
        room->setScale(vec);
    }
}

void Room::RoomLoader::addParamToRoom(Room::RoomBase *room, int id, QString value)
{
    QVector3D vec;

    if (id == 1)
        room->setRoomName(value);
    if (id == 2)
        room->setRoomQmlFile(value);
    if (id == 3)
    {
        vec = room->getPosition();
        vec.setX(value.toDouble());
        room->setPosition(vec);
    }
    if (id == 4)
    {
        vec = room->getPosition();
        vec.setY(value.toDouble());
        room->setPosition(vec);
    }
    if (id == 5)
    {
        vec = room->getPosition();
        vec.setZ(value.toDouble());
        room->setPosition(vec);
    }
    if (id == 6)
    {
        vec = room->getScale();
        vec.setX(value.toDouble());
        room->setScale(vec);
    }
    if (id == 7)
    {
        vec = room->getScale();
        vec.setY(value.toDouble());
        room->setScale(vec);
    }
    if (id == 8)
    {
        vec = room->getScale();
        vec.setZ(value.toDouble());
        room->setScale(vec);
    }
}

bool Room::RoomLoader::parseLine(std::string line, bool &header, Room::RoomBase *newroom)
{
    if (line == FILEHEADER)
    {
        if (header == true)
        {
            return false;
        }
        header = true;
    }
    else
    {
        std::string attr;
        std::string value;

        if (line.find('=') != line.npos)
        {
            attr = line.substr(0, line.find('='));
            value = line.substr(line.find('=') + 1, line.size() - 1);
            if (attr.find('[') == 0 && attr.find(']') == (attr.size() - 1))
            {
                attr = attr.substr(1, attr.size() - 2);
            }
            else
            {
                return false;
            }
            if (value.find(';') == (value.size() - 1))
            {
                value = value.substr(0, value.size() - 1);
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
        Room::RoomLoader::addParamToRoom(newroom, QString(attr.c_str()), QString(value.c_str()));
    }
    return true;
}

/*!
 * \brief RoomLoader::loadRoomFromFile
 * Search the room file in room directory  according to the name. If the file was founded and was correct. A room is created according to the data and is inserted into the roomloader.
 */
//bool Room::RoomLoader::loadRoomFromFile(QString name, Room::RoomManager *roommanager)
//{
//    QString line;
//    QFile myfile(ROOMFILEDIR + name + ".txt");
//    QFileInfo info(myfile);
//    bool        header;
//    Room::RoomBase *newroom;

//    newroom = roommanager->getNewRoomInstance();
//   qDebug() << info.absoluteFilePath();
//    if (myfile.open(QIODevice::ReadOnly))
//    {
//        QTextStream in(&myfile);
//        while (!in.atEnd())
//        {
//            line = in.readLine();
//            if (!line.isEmpty() && RoomLoader::parseLine(line.toStdString(), header, newroom))
//            {
//                qDebug() << "File loaded";
//            }
//            else
//            {
//                qDebug() << "Error while parsing file";
//                break;
//            }
//        }
//        roommanager->addRoomToModel(newroom);
//        roommanager->addNewRoom();
//        roommanager->setCurrentRoom(roommanager->getRoomModel()->rowCount() - 1);
//        qDebug() << roommanager->getCurrentRoom()->getRoomName();
//        qDebug() << roommanager->getCurrentRoom()->getScale().z();
//        myfile.close();
//    }
//    else
//    {
//        qDebug() << "Unable to open file";
//        return false;
//    }
//    return true;
//}


/*!
 * \brief RoomLoader::saveRoomFile Save a room in file format, the file is created from the room name. The room is saved into the room directory.
 */
bool Room::RoomLoader::saveRoomFile(Room::RoomBase  *room)
{
    QFile file(ROOMFILEDIR + room->getRoomName() + ".txt");

    file.remove();
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qCritical() << "Unable to create and open file";
        return false;
    }
    QTextStream flux(&file);
    flux.setCodec("UTF-8");

    flux <<  qPrintable(FILEHEADER) << endl;
    flux << "[" << "Name" << "]=" << room->getRoomName()  << ";" << endl;
    flux << "[" << "Qml" << "]=" << room->getRoomQmlFile()  << ";" << endl;
    flux << "[" << "PosX" << "]=" << room->getPosition().x() << ";" << endl;
    flux << "[" << "PosY" << "]=" << room->getPosition().y() << ";" << endl;
    flux << "[" << "PosZ" << "]=" << room->getPosition().z() << ";" << endl;
    flux << "[" << "ScaleX" << "]=" << room->getScale().x() << ";" << endl;
    flux << "[" << "ScaleY" << "]=" << room->getScale().y() << ";" << endl;
    flux << "[" << "ScaleZ" << "]=" << room->getScale().z() << ";" << endl;

    file.close();
    qDebug() << "File saved into " << ROOMFILEDIR << qPrintable(room->getRoomName()) << ".txt";
    return true;
}

////////////////// STATIC METHODS CALLBED BY ROOM MANAGER ///////////////////

/*!
 * \brief RoomLoader::saveRoomDatabase Save a room to the database, the room is updated or inserted depending if the room was already present.
 * The requests are asynchronous and this function only sends the request. Does not return.
 */
void    Room::RoomLoader::saveRoomToDatabase(Room::RoomBase *room)
{
    Room::RoomLoader::getInstance()->saveRoom(room);
}

void    Room::RoomLoader::deleteRoomFromDatabase(Room::RoomBase *room)
{
    Room::RoomLoader::getInstance()->deleteRoom(room);
}

void    Room::RoomLoader::restoreRoomsFromDatabase()
{
    Room::RoomLoader::getInstance()->restoreRooms();
}

//////////////// CALLBACKS /////////////////////

void    Room::RoomLoader::receiveResultFromSQLQuery(QList<QSqlRecord> result, int id)
{
    (this->*this->pFunc[id])(result);
}

void    Room::RoomLoader::genericResultCallback(QList<QSqlRecord> result)
{
    Q_UNUSED(result);
}

void    Room::RoomLoader::searchForRoomEditUpdateCallback(QList<QSqlRecord> result)
{
    qDebug() << "searchEditRoomCallBack";
    if (result.size() > 2)
        this->updateExistingRoom(this->roomToSave);
    else
        this->insertNewRoom(this->roomToSave);
}

void    Room::RoomLoader::restoreRoomsCallback(QList<QSqlRecord> result)
{
    qDebug() << "restoreRoomsCallback";
    if (result.size() > 1) // FIRST RECORD IS STATUS COUNT OF RECORDINGS
    {
        result.pop_front();
        foreach (QSqlRecord record, result)
        {
            Room::RoomBase *newroom = Room::RoomManager::getNewRoomInstance();
            newroom->setRoomQmlFile(record.value(2).toString());
            newroom->setRoomName(record.value(1).toString());
            newroom->setPosition(QVector3D(record.value(3).toDouble(), record.value(4).toDouble(), record.value(5).toDouble()));
            newroom->setScale(QVector3D(record.value(6).toDouble(), record.value(7).toDouble(), record.value(8).toDouble()));
            qDebug() << "NEW ROOM : " << newroom->getRoomName() << " " << newroom->getPosition() << " " << newroom->getScale();
            Room::RoomManager::addRoomToModel(newroom);
        }
    }
}

/////////////// QUERIES ///////////////////////

void    Room::RoomLoader::saveRoom(Room::RoomBase *room)
{
    this->roomToSave = room;
    qDebug() << "RoomLoader::saveRoom " << "SELECT * FROM room WHERE name=\"" + room->getRoomName() + "\";";
    emit executeSQLQuery("SELECT * FROM room WHERE name=\"" + room->getRoomName() + "\";", this, SEARCH_FOR_ROOM);
}

void    Room::RoomLoader::updateExistingRoom(Room::RoomBase *room)
{
    QString request = "UPDATE room SET ";
    request += "name=\"";
    request += room->getRoomName();
    request += "\", ";
    request += "modelFile=\"";
    request += room->getRoomQmlFile();
    request += "\", ";
    request += "posX=";
    request += QString::number(room->getPosition().x());
    request += ", ";
    request += "posY=";
    request += QString::number(room->getPosition().y());
    request += ", ";
    request += "posZ=";
    request += QString::number(room->getPosition().z());
    request += ", ";
    request += "scaleX=";
    request += QString::number(room->getScale().x());
    request += ", ";
    request += "scaleY=";
    request += QString::number(room->getScale().y());
    request += ", ";
    request += "scaleZ=";
    request += QString::number(room->getScale().z());
    request += " WHERE ";
    request += "name=\"";
    request += room->getRoomName();
    request += "\";";
    qDebug() << request;
    emit executeSQLQuery(request, this, GENERIC_RESULT);
}

void    Room::RoomLoader::insertNewRoom(Room::RoomBase *room)
{
    QString request = "INSERT INTO room (name, modelFile, posX, posY, posZ, scaleX, scaleY, scaleZ) VALUES (\"";
    request += room->getRoomName();
    request += "\", \"";
    request += room->getRoomQmlFile();
    request += "\", ";
    request += QString::number(room->getPosition().x());
    request += ", ";
    request += QString::number(room->getPosition().y());
    request += ", ";
    request += QString::number(room->getPosition().z());
    request += ", ";
    request += QString::number(room->getScale().x());
    request += ", ";
    request += QString::number(room->getScale().y());
    request += ", ";
    request += QString::number(room->getScale().z());
    request += ");";
    qDebug() << request;
    emit executeSQLQuery(request, this, GENERIC_RESULT);
}

void    Room::RoomLoader::restoreRooms()
{
    QString request = "SELECT * FROM room;";
    qDebug() << "RoomLoader::restoreRooms";
    emit executeSQLQuery(request, this, RESTORE_ROOMS);
}

void    Room::RoomLoader::deleteRoom(Room::RoomBase *room)
{
    QString request = "DELETE FROM room WHERE name = \"";
    request += room->getRoomName();
    request += "\";";
    emit executeSQLQuery(request, this, GENERIC_RESULT);
}
