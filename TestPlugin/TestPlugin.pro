#-------------------------------------------------
#
# Project created by QtCreator 2012-06-09T11:42:49
#
#-------------------------------------------------

qml_folder.source = ../plugins_qml
qml_folder.target = ./


 TEMPLATE        = lib
 CONFIG         += qt plugin
 QT             += quick
 QT             +=
 INCLUDEPATH    += ../Tepee3DSampleApp/Plugins

#PluginBase.h and PluginBase.cpp have to be included as sources as qmake performs custom Qt code insertion

 HEADERS         = \
    widgetmodel.h \
    testplugin.h    \
    ../Tepee3DSampleApp/Plugins/PluginBase.h
 SOURCES         = \
    widgetmodel.cpp \
    testplugin.cpp  \
../Tepee3DSampleApp/Plugins/PluginBase.cpp
 TARGET          = qmltestplugin                    #NAME OF THE PLUGIN LIBRAY
 DESTDIR         = ../widget_plugins                   #WHERE TO PUT THE LIBRARY
 DESTDIRQML      = qml_folder


# # install
# target.path = plugins/build
# sources.files = $$SOURCES $$HEADERS $$RESOURCES $$FORMS plugin.pro
# sources.path = ../plugins
# INSTALLS += target sources

OTHER_FILES += \
    qmldir \
    qmltestplugin.qmlproject \
    Widget.qml


# Copies the given files to the destination directory
defineTest(copyToDestDir) {
    files = $$1
    QMAKE_POST_LINK  += mkdir ../plugins_qml $$escape_expand(\\n\\t)
    for(FILE, files) {
        DDIR = $$DESTDIRQML
        message("FILE : ")
        message($$FILE)
        # Replace slashes in paths with backslashes for Windows
        win32:FILE ~= s,/,\\,g
        win32:DDIR ~= s,/,\\,g
        QMAKE_POST_LINK += $$QMAKE_COPY $$quote($$FILE) $$quote($$DDIR) $$escape_expand(\\n\\t)
    }
    message($$QMAKE_POST_LINK)
    export(QMAKE_POST_LINK)
}


#FOR BLACKBERRY PLAYBOOK
qnx {
    QMAKE_LFLAGS += '-Wl,-rpath,\'./app/native/lib\''

    PACKAGE_ARGS = \
        $${PWD}/bar-descriptor.xml $$TARGET \
        -e $${PWD}/icon.png res/icon.png \
        -e $$[QT_INSTALL_LIBS]/libQtCore.so.5 lib/libQtCore.so.5 \
        -e $$[QT_INSTALL_LIBS]/libQtGui.so.5 lib/libQtGui.so.5 \
        -e $$[QT_INSTALL_LIBS]/libQtOpenGL.so.5 lib/libQtOpenGL.so.5 \
        -e $$[QT_INSTALL_LIBS]/libQtNetwork.so.5 lib/libQtNetwork.so.5 \
        -e $$[QT_INSTALL_LIBS]/libQtWidgets.so.5 lib/libQtWidgets.so.5 \
        -e $$[QT_INSTALL_LIBS]/libQtQuick.so.5 lib/libQtQuick.so.5 \
        -e $$[QT_INSTALL_LIBS]/libQtQml.so.5 lib/libQtQml.so.5 \
        -e $$[QT_INSTALL_LIBS]/libQtSql.so.5 lib/libQtSql.so.5 \
        -e $$[QT_INSTALL_LIBS]/libQtV8.so.5 lib/libQtV8.so.5 \
        -e $$[QT_INSTALL_LIBS]/libQtXmlPatterns.so.5 lib/libQtXmlPatterns.so.5 \
        -e $$[QT_INSTALL_PLUGINS]/platforms/libqnx.so plugins/platforms/libqnx.so \
        -e $$[QT_INSTALL_IMPORTS]/ imports/

    package.target = $${TARGET}.bar
    package.depends = $$TARGET
    package.commands = blackberry-nativepackager \
        -package $${TARGET}.bar \
        -devMode -debugToken $$(DEBUG_TOKEN) \
        $${PACKAGE_ARGS}

    QMAKE_EXTRA_TARGETS += package

    OTHER_FILES += bar-descriptor.xml
}



# deploy qml files to correct dir
# copyToDestDir($$OTHER_FILES)


