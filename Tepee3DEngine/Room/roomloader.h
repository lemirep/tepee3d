#ifndef ROOMLOADER_H
#define ROOMLOADER_H

#include <iostream>
#include <RoomManager.h>

#define ROOMFILEDIR "./RoomFile/"

 class DataInfo
 {
    public :
     DataInfo();
     ~DataInfo();
     void setName(QString name);
     void setModel(QString model);
     void setPosX(qreal x);
     void setPosY(qreal y);
     void setPosZ(qreal z);
     void setPosX(QString x);
     void setPosY(QString y);
     void setPosZ(QString z);
     void setScaleX(qreal x);
     void setScaleY(qreal y);
     void setScaleZ(qreal z);
     void setScaleX(QString x);
     void setScaleY(QString y);
     void setScaleZ(QString z);
     void setDataFromRoom(Room::RoomBase *room);
     void setAttrValue(QString attr, QString value);
     void writeDataOnFlux(QTextStream &flux);
     QString getName();
     QString getModel();
     QVector3D getPos();
     QVector3D getScale();

    private:
     QString _name;
     QString _model;
     QVector3D _pos;
     QVector3D _scale;
 };

class RoomLoader
{

private:
    static bool parseLine(std::string line, bool &header, DataInfo *room);
    static bool onLoadingRequestFinished(Room::RoomManager *roommanager, QList<QSqlRecord> result);
    static bool onSearchingRequestFinished(Room::RoomManager *roommanger, QList<QSqlRecord> result);

public:
    static int      lastCalled;
    static DataInfo *roomDataSave;

    static bool loadRoomFromFile(QString name, Room::RoomManager *roommanager);
    static void loadRoomFromDatabase(QString name, Room::RoomManager *roommanager);
    static bool saveRoomFile(Room::RoomBase *room);
    static void saveRoomDatabase(Room::RoomBase *room, Room::RoomManager *roommanager);
    static bool onRequestFinished(Room::RoomManager *roommanger, QList<QSqlRecord> result);
};

#endif // ROOMLOADER_H
