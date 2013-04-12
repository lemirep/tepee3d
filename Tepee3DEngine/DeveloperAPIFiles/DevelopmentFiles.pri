
SOURCES += $$PWD/Plugins/PluginBase.cpp         \
           $$PWD/Plugins/PluginModelItem.cpp    \
           $$PWD/Rooms/RoomBase.cpp             \
           $$PWD/Rooms/RoomProperties.cpp       \
           $$PWD/Rooms/RoomModelItem.cpp        \
           $$PWD/Models/ListModel.cpp           \
           $$PWD/Models/SubListedListModel.cpp  \
           $$PWD/Utils.cpp

HEADERS += $$PWD/Plugins/PluginInterface.h	\
           $$PWD/Plugins/PluginModelItem.h	\
           $$PWD/Plugins/PluginBase.h		\
           $$PWD/Services/ServiceInterface.h    \
           $$PWD/Services/DatabaseServiceUserInterface.h \
           $$PWD/Services/WebServiceUserInterface.h      \
           $$PWD/Rooms/RoomInterface.h          \
           $$PWD/Rooms/RoomBase.h               \
           $$PWD/Rooms/RoomProperties.h         \
           $$PWD/Rooms/RoomModelItem.h          \
           $$PWD/Models/ListModel.h             \
           $$PWD/Models/ListItem.h              \
           $$PWD/Models/SubListedListModel.h    \
           $$PWD/Models/SubListedListItem.h     \
           $$PWD/Plugins/PluginEnums.h          \
           $$PWD/View/QmlContentExposerInterface.h \
           $$PWD/Utils.h


INCLUDEPATH += $$PWD
INCLUDEPATH += $$PWD/Plugins
INCLUDEPATH += $$PWD/Services
INCLUDEPATH += $$PWD/Models
INCLUDEPATH += $$PWD/Rooms
INCLUDEPATH += $$PWD/View

OTHER_FILES +=  $$PWD/qml/Carousel.qml \
                $$PWD/qml/PluginBase.qml \
                $$PWD/qml/qmldir \
                $$PWD/js/CameraManagement.js \
                $$PWD/qml/UIComponents/qmldir \
                $$PWD/qml/UIComponents/TextInputComponent.qml \
                $$PWD/qml/Resources/Pictures/text_input_border.png \
                $$PWD/qml/Resources/Pictures/text_input_border_selected.png \
                $$PWD/qml/Resources/Pictures/small_arrow.png \
                $$PWD/qml/FileExplorer.qml \
                $$PWD/qml/FileDelegate.qml \
                $$PWD/qml/FolderDelegate.qml \
                $$PWD/qml/FileLoader.qml \
                $$PWD/qml/Resources/Pictures/plus.png \
                $$PWD/qml/Resources/Pictures/ok.png \
                $$PWD/qml/Resources/Pictures/spanner.png \
                $$PWD/qml/Resources/Pictures/mag_glass.png \
                $$PWD/qml/Resources/Pictures/round.png \
                $$PWD/qml/Resources/Pictures/red_cross.png \
                $$PWD/qml/Resources/Pictures/refresh.png \
                $$PWD/qml/UIComponents/AddButton.qml \
                $$PWD/qml/UIComponents/RefreshButton.qml \
                $$PWD/qml/UIComponents/CloseButton.qml \
                $$PWD/qml/UIComponents/BackButton.qml \
                $$PWD/qml/UIComponents/ForwardButton.qml \
                $$PWD/qml/UIComponents/OkButton.qml \
                $$PWD/qml/UIComponents/SettingsButton.qml \
                $$PWD/qml/UIComponents/ReflectedImage.qml \
                $$PWD/qml/UIComponents/CheckBox.qml

QT += sql
