
SOURCES += $$PWD/Plugins/PluginBase.cpp         \
           $$PWD/Plugins/PluginModelItem.cpp    \
           $$PWD/Rooms/RoomBase.cpp             \
           $$PWD/Rooms/RoomProperties.cpp       \
           $$PWD/Models/ListModel.cpp           \
            $$PWD/Models/SubListedListModel.cpp \
    ../DeveloperAPIFiles/Plugins/PluginQmlPluginProperties.cpp

HEADERS += $$PWD/Plugins/PluginInterface.h	\
           $$PWD/Plugins/PluginModelItem.h	\
           $$PWD/Plugins/PluginBase.h		\
           $$PWD/Services/ServiceInterface.h    \
           $$PWD/Services/DatabaseServiceUserInterface.h \
           $$PWD/Services/WebServiceUserInterface.h      \
           $$PWD/Rooms/RoomInterface.h          \
           $$PWD/Rooms/RoomBase.h               \
           $$PWD/Rooms/RoomProperties.h         \
           $$PWD/Models/ListModel.h             \
           $$PWD/Models/ListItem.h              \
           $$PWD/Models/SubListedListModel.h    \
           $$PWD/Models/SubListedListItem.h \
    ../DeveloperAPIFiles/Plugins/PluginQmlPluginProperties.h \
    ../DeveloperAPIFiles/Plugins/PluginEnums.h


INCLUDEPATH += $$PWD
INCLUDEPATH += $$PWD/Plugins
INCLUDEPATH += $$PWD/Services
INCLUDEPATH += $$PWD/Models
INCLUDEPATH += $$PWD/Rooms

OTHER_FILES +=  $$PWD/qml/Carousel.qml \
    ../DeveloperAPIFiles/qml/PluginBase.qml

QT += sql
