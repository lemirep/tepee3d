#include <iostream>
#include <fstream>
#include <QTextStream>

#include "roomloader.h"

#define FILEHEADER  "__ROOMFILE__"

int RoomLoader::lastCalled = 0;
DataInfo *RoomLoader::roomDataSave;

DataInfo::DataInfo()
{
}

DataInfo::~DataInfo()
{
}

void DataInfo::setName(QString name)
{
    this->_name = name;
}

void DataInfo::setModel(QString model)
{
    this->_model = model;
}

void DataInfo::setPosX(qreal x)
{
    this->_pos.setX(x);
}

void DataInfo::setPosY(qreal y)
{
    this->_pos.setY(y);
}

void DataInfo::setPosZ(qreal z)
{
    this->_pos.setZ(z);
}

void DataInfo::setScaleX(qreal x)
{
    this->_scale.setX(x);
}

void DataInfo::setScaleY(qreal y)
{
    this->_scale.setY(y);
}

void DataInfo::setScaleZ(qreal z)
{
    this->_scale.setZ(z);
}

void DataInfo::setAttrValue(QString attr, QString value)
{
    if (attr == "Name")
        this->setName(value);
    if (attr == "Qml")
        this->setModel(value);
    if (attr == "PosX")
        this->setPosX(value.toDouble());
    if (attr == "PosY")
        this->setPosY(value.toDouble());
    if (attr == "PosZ")
        this->setPosZ(value.toDouble());
    if (attr == "ScaleX")
        this->setScaleX(value.toDouble());
    if (attr == "ScaleY")
        this->setScaleY(value.toDouble());
    if (attr == "ScaleZ")
        this->setScaleZ(value.toDouble());
}

void DataInfo::setDataFromRoom(Room::RoomBase *room)
{
    this->_name = room->getRoomName();
    this->_model = room->getRoomQmlFile();
    this->_pos = room->getPosition();
    this->_scale = room->getScale();
}

void DataInfo::writeDataOnFlux(QTextStream &flux)
{
    flux << "[" << "Name" << "]=" << this->_name  << ";" << endl;
    flux << "[" << "Qml" << "]=" << this->_model  << ";" << endl;
    flux << "[" << "PosX" << "]=" << this->_pos.x() << ";" << endl;
    flux << "[" << "PosY" << "]=" << this->_pos.y() << ";" << endl;
    flux << "[" << "PosZ" << "]=" << this->_pos.z() << ";" << endl;
    flux << "[" << "ScaleX" << "]=" << this->_scale.x() << ";" << endl;
    flux << "[" << "ScaleY" << "]=" << this->_scale.y() << ";" << endl;
    flux << "[" << "ScaleZ" << "]=" << this->_scale.z() << ";" << endl;
}

QString DataInfo::getName()
{
    return this->_name;
}

QString DataInfo::getModel()
{
    return this->_model;
}

QVector3D DataInfo::getPos()
{
    return this->_pos;
}

QVector3D DataInfo::getScale()
{
    return this->_scale;
}

bool RoomLoader::parseLine(std::string line, bool &header, DataInfo   *roominfo)
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
        roominfo->setAttrValue(QString(attr.c_str()), QString(value.c_str()));
    }
    return true;
}

void RoomLoader::loadRoomFromFile(QString name, Room::RoomManager *roommanager)
{
    QString line;
    QFile myfile(ROOMFILEDIR + name + ".txt");
    bool        header;
    DataInfo    *roominfo;

    roommanager->addNewRoom();
    roommanager->setCurrentRoom(roommanager->getRoomModel()->rowCount() - 1);
    roominfo = new DataInfo();
    if (myfile.open(QIODevice::ReadOnly))
    {
        QTextStream in(&myfile);
        while (!in.atEnd())
        {
            line = in.readLine();
            if (!line.isEmpty() && RoomLoader::parseLine(line.toStdString(), header, roominfo))
            {
                roommanager->editRoom(1, roominfo->getName(), roominfo->getPos(), roominfo->getScale());
                qDebug() << "File loaded";
            }
            else
            {
                qDebug() << "Error while parsing file";
                break;
            }
        }
        myfile.close();
    }
    else
        qDebug() << "Unable to open file";
}

void RoomLoader::loadRoomFromDatabase(QString name, Room::RoomManager *roommanager)
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

bool RoomLoader::onLoadingRequestFinished(Room::RoomManager *roommanager, QList<QSqlRecord> result)
{
    QVector3D pos;
    QVector3D scale;
    QSqlRecord res;

    if (result.size() < 2)
        return false;
    res = result.value(1);
    roommanager->setCurrentRoom(roommanager->getRoomModel()->rowCount() - 1);
    std::cout << "New Room name =" << qPrintable(roommanager->getCurrentRoom()->getRoomName()) << std::endl;

    pos.setX(res.value(3).toDouble());
    pos.setY(res.value(4).toDouble());
    pos.setZ(res.value(5).toDouble());
    scale.setX(res.value(6).toDouble());
    scale.setY(res.value(7).toDouble());
    scale.setZ(res.value(8).toDouble());

    roommanager->editRoom(2, res.value(1).toString(), pos, scale);
    std::cout << "Real Room name =" << qPrintable(roommanager->getCurrentRoom()->getRoomName()) << std::endl;
    return true;
}

bool RoomLoader::onSearchingRequestFinished(Room::RoomManager *roommanager, QList<QSqlRecord> result)
{
    QString     request = "";

    if (result.size() >= 2)
    {
       request += "UPDATE room SET ";
       request += "name=\"";
       request += RoomLoader::roomDataSave->getName();
       request += "\", ";
       request += "modelFile=\"";
       request += RoomLoader::roomDataSave->getModel();
       request += "\", ";
       request += "posX=";
       request += QString::number(RoomLoader::roomDataSave->getPos().x());
       request += ", ";
       request += "posY=";
       request += QString::number(RoomLoader::roomDataSave->getPos().y());
       request += ", ";
       request += "posZ=";
       request += QString::number(RoomLoader::roomDataSave->getPos().z());
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
       request += RoomLoader::roomDataSave->getName();
       request += "\";";
    }
    else
    {
       request += "INSERT INTO room (name, modelFile, posX, posY, posZ, scaleX, scaleY, scaleZ) VALUES (\"";
       request += RoomLoader::roomDataSave->getName();
       request += "\", \"";
       request += RoomLoader::roomDataSave->getModel();
       request += "\", ";
       request += QString::number(RoomLoader::roomDataSave->getPos().x());
       request += ", ";
       request += QString::number(RoomLoader::roomDataSave->getPos().y());
       request += ", ";
       request += QString::number(RoomLoader::roomDataSave->getPos().z());
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

void RoomLoader::onRequestFinished(Room::RoomManager *roommanager, QList<QSqlRecord> result)
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
}

void RoomLoader::saveRoomFile(Room::RoomBase  *room)
{
    QFile file(ROOMFILEDIR + room->getRoomName() + ".txt");
    DataInfo    *roominfo = new DataInfo();

    file.remove();
    roominfo->setDataFromRoom(room);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        std::cerr << "Unable to create and open file"  << std::endl;
        return;
    }
    QTextStream flux(&file);
    flux.setCodec("UTF-8");

    flux <<  qPrintable(FILEHEADER) << endl;
    roominfo->writeDataOnFlux(flux);

    file.close();
    std::cout << "File saved into " << ROOMFILEDIR << qPrintable(room->getRoomName()) << ".txt" << std::endl;
}

void RoomLoader::saveRoomDatabase(Room::RoomBase *room, Room::RoomManager *roommanager)
{
    DataInfo    *roominfo = new DataInfo();

    roominfo->setDataFromRoom(room);
    RoomLoader::roomDataSave = roominfo;
    roommanager->executeSQLQuery("SELECT * FROM room WHERE name=\"" + roominfo->getName() + "\";", roommanager, 1);
    RoomLoader::lastCalled = 2;
}
