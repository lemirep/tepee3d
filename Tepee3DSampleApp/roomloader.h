#ifndef ROOMLOADER_H
#define ROOMLOADER_H

#include "BasicRoom.h"

class RoomLoader
{
private:
    static bool parseLine(std::string line, bool &header, std::map<std::string, std::string>  &map);
public:
    static void loadRoomFromFile();
    static void loadRoomFromDatabase();
};

#endif // ROOMLOADER_H
