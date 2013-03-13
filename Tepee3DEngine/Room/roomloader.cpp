#include <iostream>
#include <fstream>
#include <QTextStream>

#include "roomloader.h"

#define FILEHEADER  "__ROOMFILE__"

/*!
 * \namespace Room
 *
 * \brief The Room namespace holds all the classes that deal with
 * Rooms and their management.
 *
 * \inmodule Tepee3D
 */

/*!
 * \class Room::RoomLoader
 * \brief The RoomLoader class is a group a static functions aimed
 * to load or save room in databases and files format.
 *
 */

int Room::RoomLoader::lastCalled = 0;
Room::RoomBase      *Room::RoomLoader::roomDataSave = Room::RoomManager::getNewRoomInstance();

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
bool Room::RoomLoader::loadRoomFromFile(QString name, Room::RoomManager *roommanager)
{
    QString line;
    QFile myfile(ROOMFILEDIR + name + ".txt");
    QFileInfo info(myfile);
    bool        header;
    Room::RoomBase *newroom;

    newroom = roommanager->getNewRoomInstance();
    std::cout << qPrintable(info.absoluteFilePath()) << std::endl;
    if (myfile.open(QIODevice::ReadOnly))
    {
        QTextStream in(&myfile);
        while (!in.atEnd())
        {
            line = in.readLine();
            if (!line.isEmpty() && RoomLoader::parseLine(line.toStdString(), header, newroom))
            {
                qDebug() << "File loaded";
            }
            else
            {
                qDebug() << "Error while parsing file";
                break;
            }
        }
        roommanager->addRoomToModel(newroom);
        roommanager->addNewRoom();
        roommanager->setCurrentRoom(roommanager->getRoomModel()->rowCount() - 1);
        std::cout << qPrintable(roommanager->getCurrentRoom()->getRoomName()) << std::endl;
        std::cout << roommanager->getCurrentRoom()->getScale().z() << std::endl;
        myfile.close();
    }
    else
    {
        qDebug() << "Unable to open file";
        return false;
    }
    return true;
}

/*!
 * \brief RoomLoader::loadRoomFromDatabase Ask the database for a room according to the name provided. The requests are asynchronous and this function only sends the request. Does not return.
 */
void Room::RoomLoader::loadRoomFromDatabase(QString name, Room::RoomManager *roommanager)
{
    QList<QSqlRecord> *result;

    if (false)
    {
        std::cout << "Creation" << std::endl;
        roommanager->executeSQLQuery("CREATE TABLE room (idRoom INTEGER PRIMARY KEY AUTOINCREMENT, name VARCHAR(45), modelFile VARCHAR(200), posX INT, posY INT, posZ INT, scaleX INT, scaleY INT, scaleZ INT);", roommanager, 1);
        roommanager->executeSQLQuery("INSERT INTO room VALUES (1, \"RoomDatabase\", \"C:\\Test\", 0, 0, 0, 1, 1, 1);", roommanager, 2);
        std::cout << "Creation Finsihed" << std::endl;
    }
    roommanager->executeSQLQuery("SELECT * FROM room WHERE name=\"RoomDatabase\";", roommanager, 1); /*" + name +\"*/
    RoomLoader::lastCalled = 1;

    return ;
}

bool Room::RoomLoader::onLoadingRequestFinished(Room::RoomManager *roommanager, QList<QSqlRecord> result)
{
    Room::RoomBase *newroom;
    QVector3D pos;
    QVector3D scale;
    QSqlRecord res;

    newroom = Room::RoomManager::getNewRoomInstance();
    if (result.size() < 2)
        return false;
    res = result.value(1);

    newroom->setRoomName(res.value(1).toString());
    newroom->setRoomQmlFile(res.value(2).toString());
    pos.setX(res.value(3).toDouble());
    pos.setY(res.value(4).toDouble());
    pos.setZ(res.value(5).toDouble());
    scale.setX(res.value(6).toDouble());
    scale.setY(res.value(7).toDouble());
    scale.setZ(res.value(8).toDouble());
    newroom->setPosition(pos);
    newroom->setScale(scale);

    roommanager->addRoomToModel(newroom);
    roommanager->addNewRoom();
    roommanager->setCurrentRoom(roommanager->getRoomModel()->rowCount() - 1);
    std::cout << "Room loaded : " << qPrintable(roommanager->getCurrentRoom()->getRoomName()) << std::endl;
    return true;
}

bool Room::RoomLoader::onSearchingRequestFinished(Room::RoomManager *roommanager, QList<QSqlRecord> result)
{
    QString     request = "";

    if (result.size() >= 2)
    {
       request += "UPDATE room SET ";
       request += "name=\"";
       request += RoomLoader::roomDataSave->getRoomName();
       request += "\", ";
       request += "modelFile=\"";
       request += RoomLoader::roomDataSave->getRoomQmlFile();
       request += "\", ";
       request += "posX=";
       request += QString::number(RoomLoader::roomDataSave->getPosition().x());
       request += ", ";
       request += "posY=";
       request += QString::number(RoomLoader::roomDataSave->getPosition().y());
       request += ", ";
       request += "posZ=";
       request += QString::number(RoomLoader::roomDataSave->getPosition().z());
       request += ", ";
       request += "scaleX=";
       request += QString::number(RoomLoader::roomDataSave->getScale().x());
       request += ", ";
       request += "scaleY=";
       request += QString::number(RoomLoader::roomDataSave->getScale().y());
       request += ", ";
       request += "scaleZ=";
       request += RoomLoader::roomDataSave->getScale().z();
       request += " WHERE ";
       request += "name=\"";
       request += RoomLoader::roomDataSave->getRoomName();
       request += "\";";
    }
    else
    {
       request += "INSERT INTO room (name, modelFile, posX, posY, posZ, scaleX, scaleY, scaleZ) VALUES (\"";
       request += RoomLoader::roomDataSave->getRoomName();
       request += "\", \"";
       request += RoomLoader::roomDataSave->getRoomQmlFile();
       request += "\", ";
       request += QString::number(RoomLoader::roomDataSave->getPosition().x());
       request += ", ";
       request += QString::number(RoomLoader::roomDataSave->getPosition().y());
       request += ", ";
       request += QString::number(RoomLoader::roomDataSave->getPosition().z());
       request += ", ";
       request += QString::number(RoomLoader::roomDataSave->getScale().x());
       request += ", ";
       request += QString::number(RoomLoader::roomDataSave->getScale().y());
       request += ", ";
       request += QString::number(RoomLoader::roomDataSave->getScale().z());
       request += ");";
    }
    qDebug() << request;
    roommanager->executeSQLQuery(request, roommanager, 1);

    return true;
}

/*!
 * \brief RoomLoader::onRequestFinished This function is called by the requester object once the request is finished. This function treats the result coming from the database.
 */
bool Room::RoomLoader::onRequestFinished(Room::RoomManager *roommanager, QList<QSqlRecord> result)
{
    if (RoomLoader::lastCalled == 1)
    {
        qDebug() << "SELECT LOAD";
        onLoadingRequestFinished(roommanager, result);
    }
    else if (RoomLoader::lastCalled == 2)
    {
        qDebug() << "SELECT CHECK";
        onSearchingRequestFinished(roommanager, result);
    }
    RoomLoader::lastCalled = 0;
    return true;
}

/*!
 * \brief RoomLoader::saveRoomFile Save a room in file format, the file is created from the room name. The room is saved into the room directory.
 */
bool Room::RoomLoader::saveRoomFile(Room::RoomBase  *room)
{
    QFile file(ROOMFILEDIR + room->getRoomName() + ".txt");

    file.remove();
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        std::cerr << "Unable to create and open file"  << std::endl;
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
    std::cout << "File saved into " << ROOMFILEDIR << qPrintable(room->getRoomName()) << ".txt" << std::endl;
    return true;
}

/*!
 * \brief RoomLoader::saveRoomDatabase Save a room to the database, the room is updated or inserted depending if the room was already present. The requests are asynchronous and this function only sends the request. Does not return.
 */
void Room::RoomLoader::saveRoomDatabase(Room::RoomBase *room, Room::RoomManager *roommanager)
{


    RoomLoader::roomDataSave = room;
    roommanager->executeSQLQuery("SELECT * FROM room WHERE name=\"" + room->getRoomName() + "\";", roommanager, 1);
    RoomLoader::lastCalled = 2;
}
