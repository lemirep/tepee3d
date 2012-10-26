#include "roomloader.h"
#include <iostream>
#include <fstream>

bool RoomLoader::parseLine(std::string line, bool &header, std::map<std::string, std::string>  &map)
{
    if (line == "__ROOMFILE__")
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
           std::cout << "attr : " << attr << std::endl;
           std::cout << "value : " << value << std::endl;
        }
        else
        {
            return false;
        }
        map.insert(std::pair<std::string, std::string>(attr, value));
    }
    return true;
}

void RoomLoader::loadRoomFromFile()
{
    std::string line;
    std::ifstream myfile((std::string)"D:/Work/EIP/RoomFile/RoomAlpha.txt");
    bool        header;
    std::map<std::string, std::string>  map;

    if (myfile.is_open())
      {
        while (myfile.good())
        {
          getline (myfile,line);
          if (RoomLoader::parseLine(line, header, map) == false)
            {
              std::cerr << "Error while parsing file" << std::endl;
              return ;
            }
          std::cout << line << std::endl;
        }
        myfile.close();
      }
    else std::cout << "Unable to open file";
    return ;
}

void RoomLoader::loadRoomFromDatabase()
{
    return ;
}
