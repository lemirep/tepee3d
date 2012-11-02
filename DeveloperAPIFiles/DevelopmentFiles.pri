
SOURCES += $$PWD/Plugins/PluginBase.cpp         \
           $$PWD/Plugins/PluginModelItem.cpp    \
           $$PWD/Rooms/RoomBase.cpp             \
           $$PWD/Models/ListModel.cpp

HEADERS += $$PWD/Plugins/PluginInterface.h	\
           $$PWD/Plugins/PluginModelItem.h	\
           $$PWD/Plugins/PluginBase.h		\
           $$PWD/Services/ServiceInterface.h    \
           $$PWD/Services/DatabaseServiceUserInterface.h \
           $$PWD/Services/WebServiceUserInterface.h      \
           $$PWD/Rooms/RoomInterface.h          \
           $$PWD/Rooms/RoomBase.h               \
           $$PWD/Models/ListModel.h             \
           $$PWD/Models/ListItem.h

INCLUDEPATH += $$PWD
INCLUDEPATH += $$PWD/Plugins
INCLUDEPATH += $$PWD/Services
INCLUDEPATH += $$PWD/Models
INCLUDEPATH += $$PWD/Rooms

QT += sql
