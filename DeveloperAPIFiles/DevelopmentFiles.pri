
SOURCES += $$PWD/Plugins/PluginBase.cpp

HEADERS += $$PWD/Plugins/PluginInterface.h	\
           $$PWD/Plugins/PluginBase.h		\
           $$PWD/Services/ServiceInterface.h    \
           $$PWD/Services/DatabaseServiceUserInterface.h

INCLUDEPATH += $$PWD
INCLUDEPATH += $$PWD/Plugins
INCLUDEPATH += $$PWD/Services

QT += sql
