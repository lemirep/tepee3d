TEMPLATE    = subdirs
SUBDIRS     =  RoomLibrary       \
               ServicesLibraries \
               Tepee3DEngine \
               Plugins

message($$QMAKESPEC)

# BUILD IS DONE ACCORD TO THE ORDER OF SUBDIRS
CONFIG += ordered

# DOC APPEARS ONLY FOR WINDOWS AND LINUX PLATFORMS
linux:win32 {
    !qnx {
        OTHER_FILES += Documentation/config.qdocconf \
                       Documentation/install.qdoc \
                       Documentation/vm_instruction.qdoc \
                       Documentation/how-to-plugins.qdoc \
                       Documentation/all_classes.qdoc \
                       Documentation/index.qdoc
#        SUBDIRS += UnitTests
    }
}

#qnx {
#    OTHER_FILES += bar-descriptor.xml
#    OTHER_FILES += qnx/icon.png
#}

#qnx {
#    QMAKE_LFLAGS += '-Wl,-rpath,\'./app/native/lib\''

##    Create Directory Structure for Playbook Package
#    PACKAGE_ARGS = \
#        $${PWD}/qnx/bar-descriptor.xml $$TARGET \
#        -e $${PWD}/qnx/icon.png res/icon.png \
#        -e $$[QT_INSTALL_LIBS]/libQt5Core.so.5 lib/libQt5Core.so.5 \
#        -e $$[QT_INSTALL_LIBS]/libQt5Gui.so.5 lib/libQt5Gui.so.5 \
#        -e $$[QT_INSTALL_LIBS]/libQt5OpenGL.so.5 lib/libQt5OpenGL.so.5 \
#        -e $$[QT_INSTALL_LIBS]/libQt5Network.so.5 lib/libQt5Network.so.5 \
#        -e $$[QT_INSTALL_LIBS]/libQt5Widgets.so.5 lib/libQt5Widgets.so.5 \
#        -e $$[QT_INSTALL_LIBS]/libQt5Quick.so.5 lib/libQt5Quick.so.5 \
#        -e $$[QT_INSTALL_LIBS]/libQt5Qml.so.5 lib/libQt5Qml.so.5 \
#        -e $$[QT_INSTALL_LIBS]/libQt5Sql.so.5 lib/libQt5Sql.so.5 \
#        -e $$[QT_INSTALL_LIBS]/libQt53DQuick.so.5 lib/libQt53DQuick.so.5  \
#        -e $$[QT_INSTALL_LIBS]/libQt53D.so.5 lib/libQt53D.so.5   \
#        -e $$[QT_INSTALL_LIBS]/libQt5V8.so.5 lib/libQt5V8.so.5 \
#        -e $$[QT_INSTALL_PLUGINS]/platforms/libqqnx.so plugins/platforms/libqqnx.so \
#        -e qml qml \
#        -e $$[QT_INSTALL_IMPORTS]/ imports/

#    package.target = $${TARGET}.bar
#    package.depends = $$TARGET
#    package.commands = blackberry-nativepackager \
#        -package $${TARGET}.bar \
#        -devMode -debugToken /home/lemire_p/.rim/save/debug_token.bar \
#        $${PACKAGE_ARGS}

#    QMAKE_EXTRA_TARGETS += package
#    message($$package.commands)

#    OTHER_FILES += qnx/bar-descriptor.xml
#    OTHER_FILES += qnx/icon.png
#}
