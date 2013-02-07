#include <iostream>
#include <fstream>
#include <QTextStream>
#include "roomloader.h"

#define FILEHEADER  "__ROOMFILE__"

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

void RoomLoader::loadRoomFromFile(std::string name, Room::RoomManager *roommanager)
{
    std::string line;
    std::ifstream myfile((std::string)ROOMFILEDIR + name + ".txt");
    bool        header;
    DataInfo    *roominfo;

    roommanager->addNewRoom();
    roommanager->setCurrentRoom(1);
    roominfo = new DataInfo();
    if (myfile.is_open())
      {
        while (myfile.good())
        {
          getline (myfile,line);
          if (!(line == "\n\r" || line == "\n" || line == ""))
          {
            if (RoomLoader::parseLine(line, header, roominfo) == false)
             {
               std::cerr << "Error while parsing file" << std::endl;
               return ;
             }
          }
        }
        myfile.close();
        roommanager->editRoom(1, roominfo->getName(), roominfo->getPos(), roominfo->getScale());
        std::cout << "File loaded" << std::endl;
      }
    else
        std::cerr << "Unable to open file"  << std::endl;
    return ;
}

void RoomLoader::loadRoomFromDatabase(std::string name, Room::RoomManager *roommanager)
{
     //BasicRoom* room = new BasicRoom();
    QList<QSqlRecord> result;

    std::cout << "test" << std::endl;
    if (false)
    {
        std::cout << "Creation" << std::endl;
        roommanager->executeSQLQuery("CREATE TABLE room (idRoom INTEGER PRIMARY KEY AUTOINCREMENT, name VARCHAR(45), modelFile VARCHAR(200), posX INT, posY INT, posZ INT, scaleX INT, scaleY INT, scaleZ INT);", roommanager, 1);
        roommanager->executeSQLQuery("INSERT INTO room VALUES (1, \"RoomDatabase\", \"C:\\Test\", 0, 0, 0, 1, 1, 1);", roommanager, 1);
        std::cout << "Creation Finsihed" << std::endl;
    }
   // if (true)
   // {
    //    roommanager->executeSQLQuery("ALTER TALE room MODIFY idRoom INT NOT NULL PRIMARY KEY", roommanager);
   //sss }
    std::cout << "test" << std::endl;
    roommanager->executeSQLQuery("SELECT * FROM room WHERE name=\"RoomDatabase\";", roommanager, 1); /*" + name +\"*/
    bool isresult = false;
    int i = 0;
    while (i < 100)
    {
        roommanager->receiveResultFromSQLQuery(result, 1);
        if (!result.isEmpty())
        {
          isresult = true;
          std::cout << "Query result " << qPrintable(result[0].value(1).toString()) << std::endl;
        }
      i++;
    }
    std::cout << "No result" << std::endl;
    return ;
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
    QString     request = "";
    DataInfo    *roominfo = new DataInfo();
    bool existing = false;

    roominfo->setDataFromRoom(room);
    if (existing == true)
    {
        request += "UPDATE room SET ";
        request += "name=";
        request += roominfo->getName();
        request += ", ";
        request += "modelFile=";
        request += roominfo->getModel();
        request += ", ";
        request += "posX=";
        request += roominfo->getPos().x();
        request += ", ";
        request += "posY=";
        request += roominfo->getPos().y();
        request += ", ";
        request += "posZ=";
        request += roominfo->getPos().z();
        request += ", ";
        request += "scaleX=";
        request += roominfo->getScale().x();
        request += ", ";
        request += "scaleY=";
        request += roominfo->getScale().y();
        request += ", ";
        request += "scaleZ=";
        request += roominfo->getScale().z();
    }
    else
    {
        std::cout << roominfo->getScale().z() << std::endl;
        request += "INSERT INTO room (name, modelFile, posX, posY, posZ, scaleX, scaleY, scaleZ) VALUES (\"";
        request += roominfo->getName();
        request += "\", \"";
        request += roominfo->getModel();
        request += "\", ";
        request += QString::number(roominfo->getPos().x());
        request += ", ";
        request += QString::number(roominfo->getPos().y());
        request += ", ";
        request += QString::number(roominfo->getPos().z());
        request += ", ";
        request += QString::number(roominfo->getScale().x());
        request += ", ";
        request += QString::number(roominfo->getScale().y());
        request += ", ";
        request += QString::number(roominfo->getScale().z());
        request += ");";
    }


    roommanager->executeSQLQuery(request, roommanager, 1);
}
