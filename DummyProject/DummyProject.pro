
  TEMPLATE        = lib
  CONFIG         += qt plugin
  QT             += quick

 #include development files
    include (PATH_TO/DeveloperAPIFiles/DevelopmentFiles.pri)

 TARGET          = DummyProject
 DESTDIR         = PATH_TO/Tepee3DEngine/libraries/widget_libraries
 DESTDIRQML      = qml_folder

HEADERS += \
    DummyProject.h

SOURCES += \
    DummyProject.cpp

OTHER_FILES += \
    DummyProject.qml \
    Menu.qml

# deploy qml files to correct dir
qml_folder.files = $$OTHER_FILES
qml_folder.path = PATH_TO/Tepee3DEngine/plugins_qml/DummyProject

DEPLOYMENT += qml_folder
INSTALLS += qml_folder
