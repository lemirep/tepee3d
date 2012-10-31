
SOURCES += $$PWD/Plugins/PluginBase.cpp         \
           $$PWD/Rooms/RoomBase.cpp

HEADERS += $$PWD/Plugins/PluginInterface.h	\
           $$PWD/Plugins/PluginBase.h		\
           $$PWD/Services/ServiceInterface.h    \
           $$PWD/Services/DatabaseServiceUserInterface.h \
           $$PWD/Services/WebServiceUserInterface.h      \
           $$PWD/Rooms/RoomInterface.h          \
           $$PWD/Rooms/RoomBase.h

INCLUDEPATH += $$PWD
INCLUDEPATH += $$PWD/Plugins
INCLUDEPATH += $$PWD/Services
INCLUDEPATH += $$PWD/Rooms

QT += sql
